// Copyright 2006 Benedikt Böhm <hollow@gentoo.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the
// Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>
#include <signal.h>

#define _LUCID_PRINTF_MACROS
#define _LUCID_SCANF_MACROS
#include <lucid/bitmap.h>
#include <lucid/log.h>
#include <lucid/mem.h>
#include <lucid/printf.h>
#include <lucid/scanf.h>
#include <lucid/str.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: vx.c 294 2006-07-09 08:46:15Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "create",      1, 0, 0x10 },
	{ "migrate",     1, 0, 0x11 },
	{ "info",        1, 0, 0x12 },
	{ "stat",        1, 0, 0x13 },
	{ "bcaps-set",   1, 0, 0x14 },
	{ "bcaps-get",   1, 0, 0x15 },
	{ "ccaps-set",   1, 0, 0x16 },
	{ "ccaps-get",   1, 0, 0x17 },
	{ "flags-set",   1, 0, 0x18 },
	{ "flags-get",   1, 0, 0x19 },
	{ "limit-set",   1, 0, 0x1A },
	{ "limit-get",   1, 0, 0x1B },
	{ "limit-stat",  1, 0, 0x1C },
	{ "limit-reset", 1, 0, 0x1D },
	{ "sched-set",   1, 0, 0x1E },
	{ "uname-set",   1, 0, 0x1F },
	{ "uname-get",   1, 0, 0x20 },
	{ "kill",        1, 0, 0x21 },
	{ "wait",        1, 0, 0x22 },
	{ "sched-get",   1, 0, 0x23 },
	{ "sched-info",  1, 0, 0x24 },
	{ NULL,          0, 0, 0 },
};

static
uint64_t str_to_rlim(char *str)
{
	if (str == NULL)
		return CRLIM_KEEP;

	if (str_equal(str, "inf"))
		return CRLIM_INFINITY;

	if (str_equal(str, "keep"))
		return CRLIM_KEEP;

	uint64_t lim;

	sscanf(str, "%" SCNu64, &lim);

	return lim;
}

static
char *rlim_to_str(uint64_t lim)
{
	char *buf;

	if (lim == CRLIM_INFINITY)
		asprintf(&buf, "%s", "inf");
	else
		asprintf(&buf, "%" PRIu64, lim);

	return buf;
}

static
int check_cpuid(int cpuid)
{
	int numcpus = sysconf(_SC_NPROCESSORS_ONLN);

    if (cpuid < 0 || cpuid >= numcpus)
		return 0;
	else
		return 1;
}

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
			"vx -create      <xid> [<list>] [-- <program> <args>*]\n"
			"   -migrate     <xid> [<list>] -- <program> <args>*\n"
			"   -info        <xid>\n"
			"   -stat        <xid>\n"
			"   -bcaps-set   <xid> <list>\n"
			"   -bcaps-get   <xid>\n"
			"   -ccaps-set   <xid> <list>\n"
			"   -ccaps-get   <xid>\n"
			"   -flags-set   <xid> <list>\n"
			"   -flags-get   <xid>\n"
			"   -limit-set   <xid> <type>=<min>,<soft>,<hard>*\n"
			"   -limit-get   <xid> <type>*\n"
			"   -limit-stat  <xid> <type>*\n"
			"   -limit-reset <xid>\n"
			"   -sched-set   <xid> <type>=<value>*\n"
			"   -sched-get   <xid> <cpuid>\n"
			"   -sched-info  <xid> <cpuid>\n"
			"   -uname-set   <xid> <type>=<value>*\n"
			"   -uname-get   <xid> <type>*\n"
			"   -kill        <xid> [<pid> [<sig>]]\n"
			"   -wait        <xid>\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	char *buf, *buf2;
	int c, i, sig = SIGKILL, rc = EXIT_SUCCESS;
	int32_t buf32;
	pid_t pid = 0;
	xid_t xid = 0;

	/* syscall data */
	union {
		vx_flags_t      f;
		vx_info_t       i;
		vx_limit_t      l;
		vx_limit_stat_t ls;
		vx_sched_t      s;
		vx_sched_info_t si;
		vx_stat_t       st;
		vx_uname_t      u;
		vx_wait_t       w;
	} data;

	mem_set(&data, 0, sizeof(data));

	/* logging */
	log_options_t log_options = {
		.log_ident = argv[0],
		.log_dest  = LOGD_STDERR,
		.log_opts  = LOGO_PRIO|LOGO_IDENT,
	};

	log_init(&log_options);

#define CASE_GOTO(ID, P) case ID: \
sscanf(optarg, "%" SCNu32, &xid); \
if (xid < 2 || xid > 65535) { log_error_and_die("Invalid xid: %d", xid); } \
goto P; break

	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES

			CASE_GOTO(0x10, create);
			CASE_GOTO(0x11, migrate);
			CASE_GOTO(0x12, info);
			CASE_GOTO(0x13, stat);
			CASE_GOTO(0x14, bcapsset);
			CASE_GOTO(0x15, bcapsget);
			CASE_GOTO(0x16, ccapsset);
			CASE_GOTO(0x17, ccapsget);
			CASE_GOTO(0x18, flagsset);
			CASE_GOTO(0x19, flagsget);
			CASE_GOTO(0x1A, limitset);
			CASE_GOTO(0x1B, limitget);
			CASE_GOTO(0x1C, limitstat);
			CASE_GOTO(0x1D, limitreset);
			CASE_GOTO(0x1E, schedset);
			CASE_GOTO(0x1F, unameset);
			CASE_GOTO(0x20, unameget);
			CASE_GOTO(0x21, kill);
			CASE_GOTO(0x22, wait);
			CASE_GOTO(0x23, schedget);
			CASE_GOTO(0x24, schedinfo);

			DEFAULT_GETOPT_CASES
		}
	}

#undef CASE_GOTO

	goto usage;

create:
	if (argc > optind && str_cmp(argv[optind], "--") != 0) {
		if (flist64_from_str(argv[optind], vx_cflags_list,
							&data.f.flags, &data.f.mask, '~', ",") == -1)
			rc = log_perror("flist64_from_str");

		else if (vx_create(xid, &data.f) == -1)
			rc = log_perror("vx_create");

		else if (argc > optind+2 && execvp(argv[optind+2], argv+optind+2) == -1)
			rc = log_perror("execvp");
	}

	else {
		if (vx_create(xid, NULL) == -1)
			rc = log_perror("vx_create");

		else if (argc > optind+1 && execvp(argv[optind+1], argv+optind+1) == -1)
			rc = log_perror("execvp");
	}

	goto out;

migrate:
	if (argc > optind && str_cmp(argv[optind], "--") != 0) {
		if (flist64_from_str(argv[optind], vx_mflags_list,
							&data.f.flags, &data.f.mask, '~', ",") == -1)
			rc = log_perror("flist64_from_str");

		else if (vx_migrate(xid, &data.f) == -1)
			rc = log_perror("vx_migrate");

		else if (argc > optind+2 && execvp(argv[optind+2], argv+optind+2) == -1)
			rc = log_perror("execvp");
	}

	else {
		if (vx_migrate(xid, NULL) == -1)
			rc = log_perror("vx_migrate");

		else if (argc > optind+1 && execvp(argv[optind+1], argv+optind+1) == -1)
			rc = log_perror("execvp");
	}

	goto out;

info:
	if (vx_info(xid, &data.i) == -1)
		rc = log_perror("vx_info");

	else {
		printf("xid=%" PRIu32 "\n", data.i.xid);
		printf("initpid=%" PRIu32 "\n", data.i.initpid);
	}

	goto out;

stat:
	if (vx_stat(xid, &data.st) == -1)
		rc = log_perror("vx_get_stat");

	else {
		printf("usecnt=%" PRIu32 "\n", data.st.usecnt);
		printf("tasks=%"  PRIu32 "\n", data.st.tasks);

		printf("nr_threads=%" PRIu32 "\n", data.st.nr_threads);
		printf("nr_running=%" PRIu32 "\n", data.st.nr_running);
		printf("nr_unintr=%"  PRIu32 "\n", data.st.nr_unintr);
		printf("nr_onhold=%"  PRIu32 "\n", data.st.nr_onhold);
		printf("nr_forks=%"   PRIu32 "\n", data.st.nr_forks);

		printf("load[0]=%" PRIu32 "\n", data.st.load[0]);
		printf("load[1]=%" PRIu32 "\n", data.st.load[1]);
		printf("load[2]=%" PRIu32 "\n", data.st.load[2]);

		printf("offset=%" PRIu64 "\n", data.st.offset);
		printf("uptime=%" PRIu64 "\n", data.st.uptime);
	}

	goto out;

bcapsset:
	if (argc <= optind)
		goto usage;

	if (flist64_from_str(argv[optind], vx_bcaps_list,
						&data.f.flags, &data.f.mask, '~', ",") == -1)
		rc = log_perror("flist64_from_str");

	else if (vx_bcaps_set(xid, &data.f) == -1)
		rc = log_perror("vx_bcaps_set");

	goto out;

bcapsget:
	if (vx_bcaps_get(xid, &data.f) == -1)
		rc = log_perror("vx_bcaps_get");

	else {
		buf = flist64_to_str(vx_bcaps_list, data.f.flags, "\n");

		if (!str_isempty(buf))
			printf("%s\n", buf);

		mem_free(buf);
	}

	goto out;

ccapsset:
	if (argc <= optind)
		goto usage;

	if (flist64_from_str(argv[optind], vx_ccaps_list,
						&data.f.flags, &data.f.mask, '~', ",") == -1)
		rc = log_perror("flist64_from_str");

	else if (vx_ccaps_set(xid, &data.f) == -1)
		rc = log_perror("vx_ccaps_set");

	goto out;

ccapsget:
	if (vx_ccaps_get(xid, &data.f) == -1)
		rc = log_perror("vx_ccaps_get");

	else {
		buf = flist64_to_str(vx_ccaps_list, data.f.flags, "\n");

		if (!str_isempty(buf))
			printf("%s\n", buf);

		mem_free(buf);
	}

	goto out;

flagsset:
	if (argc <= optind)
		goto usage;

	if (flist64_from_str(argv[optind], vx_cflags_list,
						&data.f.flags, &data.f.mask, '~', ",") == -1)
		rc = log_perror("flist64_from_str");

	else if (vx_flags_set(xid, &data.f) == -1)
		rc = log_perror("vx_flags_set");

	goto out;

flagsget:
	if (vx_flags_get(xid, &data.f) == -1)
		rc = log_perror("vx_flags_get");

	else {
		buf = flist64_to_str(vx_cflags_list, data.f.flags, "\n");

		if (!str_isempty(buf))
			printf("%s\n", buf);

		mem_free(buf);
	}

	goto out;

limitset:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		buf = argv[i];

		buf2 = str_chr(buf, '=', str_len(buf));

		if (buf2)
			*buf2++ = '\0';

		if (!(data.l.id = flist32_getval(vx_limit_list, buf)))
			rc = log_perror("flist32_getval(%s)", argv[i]);

		else {
			data.l.id = v2i32(data.l.id);

			buf = buf2;
			buf2 = str_chr(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.l.minimum = str_to_rlim(buf);

			buf = buf2;
			buf2 = str_chr(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.l.softlimit = str_to_rlim(buf);

			buf = buf2;
			buf2 = str_chr(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.l.maximum = str_to_rlim(buf);

			if (vx_limit_set(xid, &data.l) == -1)
				rc = log_perror("vx_limit_set(%s)", argv[i]);
		}
	}

	goto out;

limitget:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		if (!(data.l.id = flist32_getval(vx_limit_list, argv[i])))
			rc = log_perror("flist32_getval(%s)", argv[i]);

		else {
			data.l.id = v2i32(data.l.id);

			if (vx_limit_get(xid, &data.l) == -1)
				rc = log_perror("vx_limit_get(%s)", argv[i]);

			else {
				printf("%s=", argv[i]);

				buf = rlim_to_str(data.l.minimum);
				printf("%s,", buf);
				mem_free(buf);

				buf = rlim_to_str(data.l.softlimit);
				printf("%s,", buf);
				mem_free(buf);

				buf = rlim_to_str(data.l.maximum);
				printf("%s\n", buf);
				mem_free(buf);
			}
		}
	}

	goto out;

limitstat:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		if (!(data.ls.id = flist32_getval(vx_limit_list, argv[i])))
			rc = log_perror("flist32_getval(%s)", argv[i]);

		else {
			data.ls.id = v2i32(data.ls.id);

			if (vx_limit_stat(xid, &data.ls) == -1)
				rc = log_perror("vx_limit_stat(%s)", argv[i]);

			else
				printf("%s=%" PRIu32 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 "\n",
		           argv[i],
		           data.ls.hits,  data.ls.minimum,
		           data.ls.value, data.ls.maximum);
		}
	}

	goto out;

limitreset:
	if (vx_limit_reset(xid) == -1)
		rc = log_perror("vx_limit_reset");

	goto out;

schedset:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		buf  = argv[i];
		buf2 = str_chr(buf, '=', str_len(buf));

		if (buf2)
			*buf2++ = '\0';

		if (str_isempty(buf))
			rc = log_error("Invalid argument: %s", argv[i]);

		else if (!(buf32 = flist32_getval(vx_sched_list, buf)))
			rc = log_perror("flist32_getval(%s)", buf);

		else {
			data.s.mask |= buf32;

			if (str_isempty(buf2))
				continue;

			switch (buf32) {
				case VXSM_FILL_RATE:  data.s.fill_rate[0] = atoi(buf2); break;
				case VXSM_FILL_RATE2: data.s.fill_rate[1] = atoi(buf2); break;
				case VXSM_INTERVAL:   data.s.interval[0]  = atoi(buf2); break;
				case VXSM_INTERVAL2:  data.s.interval[1]  = atoi(buf2); break;
				case VXSM_TOKENS:     data.s.tokens       = atoi(buf2); break;
				case VXSM_TOKENS_MIN: data.s.tokens_min   = atoi(buf2); break;
				case VXSM_TOKENS_MAX: data.s.tokens_max   = atoi(buf2); break;
				case VXSM_PRIO_BIAS:  data.s.prio_bias    = atoi(buf2); break;
				case VXSM_CPU_ID:
					data.s.cpu_id = atoi(buf2);
					if (!check_cpuid(data.s.cpu_id))
						log_error_and_die("Invalid cpuid: %d", data.s.cpu_id);
					break;
				case VXSM_BUCKET_ID:  data.s.bucket_id    = atoi(buf2); break;
			}
		}
	}

	if (vx_sched_set(xid, &data.s) == -1)
		log_perror("vx_sched_set");

	goto out;

schedget:
	if (argc <= optind)
		goto usage;

	data.s.cpu_id = atoi(argv[optind]);

	if (!check_cpuid(data.s.cpu_id))
		log_error_and_die("Invalid cpuid: %d", data.s.cpu_id);

	if (vx_sched_get(xid, &data.s) == -1)
		log_perror("vx_sched_get");

	printf("fill_rate=%" PRIi32 "\n", data.s.fill_rate[0]);
	printf("fill_rate2=%" PRIi32 "\n", data.s.fill_rate[1]);
	printf("interval=%" PRIi32 "\n", data.s.interval[0]);
	printf("interval2=%" PRIi32 "\n", data.s.interval[1]);
	printf("tokens=%" PRIi32 "\n", data.s.tokens);
	printf("tokens_min=%" PRIi32 "\n", data.s.tokens_min);
	printf("tokens_max=%" PRIi32 "\n", data.s.tokens_max);
	printf("prio_bias=%" PRIi32 "\n", data.s.prio_bias);

	goto out;

schedinfo:
	if (argc <= optind)
		goto usage;

	data.si.cpu_id = atoi(argv[optind]);

	if (!check_cpuid(data.si.cpu_id))
		log_error_and_die("Invalid cpuid: %d", data.si.cpu_id);

	if (vx_sched_info(xid, &data.si) == -1)
		log_perror("vx_sched_info");

	printf("user_msec=%" PRIu64 "\n", data.si.user_msec);
	printf("sys_msec=%" PRIu64 "\n", data.si.sys_msec);
	printf("hold_msec=%" PRIu64 "\n", data.si.hold_msec);
	printf("token_usec=%" PRIu32 "\n", data.si.token_usec);
	printf("vavavoom=%" PRIi32 "\n", data.si.vavavoom);

	goto out;

unameset:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		buf  = argv[i];
		buf2 = str_chr(buf, '=', str_len(buf));

		if (buf2)
			*buf2++ = '\0';

		if (str_isempty(buf) || str_isempty(buf2) || str_len(buf2) > 64)
			rc = log_error("Invalid argument: %s", argv[i]);

		else if (!(data.u.id = flist32_getval(vx_uname_list, buf)))
			rc = log_perror("flist32_getval(%s)", buf);

		else {
			data.u.id = v2i32(data.u.id);

			mem_set(data.u.value, 0, 65);
			mem_cpy(data.u.value, buf2, str_len(buf2));

			if (vx_uname_set(xid, &data.u) == -1)
				rc = log_perror("vx_uname_set(%s)", buf);
		}
	}

	goto out;

unameget:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		if (!(data.u.id = flist32_getval(vx_uname_list, argv[i])))
			rc = log_perror("flist32_getval(%s)", argv[i]);

		else {
			data.u.id = v2i32(data.u.id);

			if (vx_uname_get(xid, &data.u) == -1)
				rc = log_perror("vx_uname_get(%s)", argv[i]);

			else
				printf("%s=%s\n", argv[i], data.u.value);
		}
	}

	goto out;

wait:
	if (vx_wait(xid, &data.w) == -1)
		rc = log_perror("vx_wait");

	else {
		printf("reboot_cmd=%" PRIi32 "\n", data.w.reboot_cmd);
		printf("exit_code=%" PRIi32 "\n", data.w.exit_code);
	}

	goto out;

kill:
	if (argc > optind)
		pid = atoi(argv[optind]);

	if (argc > optind+1)
		sig = atoi(argv[optind+1]);

	if (vx_kill(xid, pid, sig) == -1)
		rc = log_perror("vx_kill");

	goto out;

usage:
	usage(EXIT_FAILURE);

out:
	exit(rc);
}
