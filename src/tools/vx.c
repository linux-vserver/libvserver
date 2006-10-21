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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <lucid/bitmap.h>
#include <lucid/str.h>

#include "tools.h"
#include "vserver.h"

void do_vlogin(int argc, char *argv[], int ind);

static const char *rcsid = "$Id: vx.c 294 2006-07-09 08:46:15Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "create",           1, 0, 0x10 },
	{ "migrate",          1, 0, 0x11 },
	{ "get-info",         1, 0, 0x12 },
	{ "set-bcaps",        1, 0, 0x13 },
	{ "set-ccaps",        1, 0, 0x14 },
	{ "set-flags",        1, 0, 0x15 },
	{ "set-limit",        1, 0, 0x16 },
	{ "set-sched",        1, 0, 0x17 },
	{ "set-uname",        1, 0, 0x18 },
	{ "get-bcaps",        1, 0, 0x19 },
	{ "get-ccaps",        1, 0, 0x1A },
	{ "get-flags",        1, 0, 0x1B },
	{ "get-limit",        1, 0, 0x1C },
	{ "get-uname",        1, 0, 0x1D },
	{ "get-stat",         1, 0, 0x1E },
	{ "get-limit-stat",   1, 0, 0x1F },
	{ "reset-limit-stat", 1, 0, 0x20 },
	{ "kill",             1, 0, 0x21 },
	{ "wait",             1, 0, 0x22 },
	{ NULL,               0, 0, 0 },
};

static
uint64_t str_to_rlim(char *str)
{
	if (str == NULL)
		return CRLIM_KEEP;
	
	if (strcmp(str, "inf") == 0)
		return CRLIM_INFINITY;
	
	if (strcmp(str, "keep") == 0)
		return CRLIM_KEEP;
	
	return atoi(str);
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

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	          "vx -create           <xid> [<list>] [-- <program> <args>*]\n"
	          "   -migrate          <xid> [<list>] -- <program> <args>*\n"
	          "   -get-info         <xid>\n"
	          "   -set-bcaps        <xid> <list>\n"
	          "   -set-ccaps        <xid> <list>\n"
	          "   -set-flags        <xid> <list>\n"
	          "   -set-limit        <xid> <type>=<min>,<soft>,<hard>*\n"
	          "   -set-sched        <xid> <type>=<value>*\n"
	          "   -set-uname        <xid> <type>=<value>*\n"
	          "   -get-bcaps        <xid>\n"
	          "   -get-ccaps        <xid>\n"
	          "   -get-flags        <xid>\n"
	          "   -get-limit        <xid> <type>*\n"
	          "   -get-uname        <xid> <type>*\n"
	          "   -get-stat         <xid>\n"
	          "   -get-limit-stat   <xid> <type>*\n"
	          "   -reset-limit-stat <xid>\n"
	          "   -kill             <xid> [<pid> <sig>]\n"
	          "   -wait             <xid>\n"
	          );
	exit(rc);
}

int main(int argc, char *argv[])
{
	INIT_ARGV0
	
	int c, i;
	xid_t xid = 0;
	char *buf;
	uint64_t mask;
	pid_t pid = 0;
	int sig = SIGKILL;
	
	/* syscall data */
	struct vx_info        info;
	struct vx_stat        stat;
	struct vx_flags       flags;
	struct vx_sched       sched;
	struct vx_caps        ccaps;
	struct vx_uname       uname;
	struct vx_wait_result wait_result;
	struct vx_limit_stat  limit_stat;
	
	/* TODO: do we really need to initialize this to ~0ULL? */
	struct vx_caps bcaps = {
		.caps = ~(0ULL),
		.mask = ~(0ULL),
	};
	
	/* TODO: move this to setlimit? */
	struct vx_limit limit = {
		.minimum   = CRLIM_KEEP,
		.softlimit = CRLIM_KEEP,
		.maximum   = CRLIM_KEEP,
	};
	
#define CASE_GOTO(ID, P) case ID: xid = atoi(optarg); goto P; break
	
	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES
			
			CASE_GOTO(0x10, create);
			CASE_GOTO(0x11, migrate);
			CASE_GOTO(0x12, getinfo);
			CASE_GOTO(0x13, setbcaps);
			CASE_GOTO(0x14, setccaps);
			CASE_GOTO(0x15, setflags);
			CASE_GOTO(0x16, setlimit);
			CASE_GOTO(0x17, setsched);
			CASE_GOTO(0x18, setuname);
			CASE_GOTO(0x19, getbcaps);
			CASE_GOTO(0x1A, getccaps);
			CASE_GOTO(0x1B, getflags);
			CASE_GOTO(0x1C, getlimit);
			CASE_GOTO(0x1D, getuname);
			CASE_GOTO(0x1E, getstat);
			CASE_GOTO(0x1F, getlimitstat);
			CASE_GOTO(0x20, resetlimitstat);
			CASE_GOTO(0x21, kill);
			CASE_GOTO(0x22, wait);
			
			DEFAULT_GETOPT_CASES
		}
	}
	
#undef CASE_GOTO
	
	goto usage;
	
create:
	if (argc > optind && strcmp(argv[optind], "--") != 0) {
		if (flist64_from_str(argv[optind], cflags_list, &flags.flags, &mask, '~', ',') == -1)
			perr("flist64_from_str");
		
		if (vx_create(xid, &flags) == -1)
			perr("vx_create");
		
		if (argc > optind+2)
			execvp(argv[optind+2], argv+optind+2);
	}
	
	else {
		if (vx_create(xid, NULL) == -1)
			perr("vx_create");
		
		if (argc > optind+1)
			execvp(argv[optind+1], argv+optind+1);
	}
	
	goto out;

migrate:
	if (argc > optind && strcmp(argv[optind], "--") != 0) {
		if (flist64_from_str(argv[optind], mflags_list, &flags.flags, &mask, '~', ',') == -1)
			perr("flist64_from_str");
		
		if (vx_migrate(xid, &flags) == -1)
			perr("vx_migrate");
		
		if (argc > optind+2)
			execvp(argv[optind+2], argv+optind+2);
	}
	
	else {
		if (vx_migrate(xid, NULL) == -1)
			perr("vx_migrate");
		
		if (argc > optind+1)
			execvp(argv[optind+1], argv+optind+1);
	}
	
	goto out;
	
getinfo:
	if (vx_get_info(xid, &info) == -1)
		perr("vx_get_info");
	
	printf("XID=%" PRIu32 "\n", info.xid);
	printf("InitPID=%" PRIu32 "\n", info.initpid);
	
	goto out;
	
setbcaps:
	if (argc <= optind)
		goto usage;
	
	if (flist64_from_str(argv[optind], bcaps_list, &bcaps.caps, &bcaps.mask, '~', ',') == -1)
		perr("flist64_from_str");
	
	if (vx_set_bcaps(xid, &bcaps) == -1)
		perr("vx_set_bcaps");
	
	goto out;
	
setccaps:
	if (argc <= optind)
		goto usage;
	
	if (flist64_from_str(argv[optind], ccaps_list, &ccaps.caps, &ccaps.mask, '~', ',') == -1)
		perr("flist64_from_str");
	
	if (vx_set_ccaps(xid, &ccaps) == -1)
		perr("vx_set_ccaps");
	
	goto out;
	
setflags:
	if (argc <= optind)
		goto usage;
	
	if (flist64_from_str(argv[optind], cflags_list, &flags.flags, &flags.mask, '~', ',') == -1)
		perr("flist64_from_str");
	
	if (vx_set_flags(xid, &flags) == -1)
		perr("vx_set_flags");
	
	goto out;
	
setlimit:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		buf = strtok(argv[i], "=");
		
		if (buf == NULL)
			goto usage;
		
		if (!(limit.id = flist32_getval(rlimit_list, buf)))
			perr("flist32_getval");
		
		limit.id = v2i32(limit.id);
		
		if ((buf = strtok(NULL, ",")) == NULL)
			goto usage;
		else
			limit.minimum = str_to_rlim(buf);
		
		if ((buf = strtok(NULL, ",")) == NULL)
			goto usage;
		else
			limit.softlimit = str_to_rlim(buf);
		
		if ((buf = strtok(NULL, ",")) == NULL)
			goto usage;
		else
			limit.maximum = str_to_rlim(buf);
		
		if (vx_set_limit(xid, &limit) == -1)
			perr("vx_set_rlimit");
	}
	
	goto out;
	
setsched:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		buf = strtok(argv[i], "=");
		
		if (buf == NULL)
			goto usage;
		
		if (!(sched.set_mask = flist32_getval(sched_list, buf)))
			perr("flist32_getval");
		
		buf = strtok(NULL, "=");
		
		if (buf == NULL)
			goto usage;
		
		switch (sched.set_mask) {
			case VXSM_FILL_RATE:
				sched.fill_rate = atoi(buf);
				break;
			
			case VXSM_FILL_RATE2:
				sched.fill_rate = atoi(buf);
				break;
			
			case VXSM_INTERVAL:
				sched.interval = atoi(buf);
				break;
			
			case VXSM_INTERVAL2:
				sched.interval = atoi(buf);
				break;
			
			case VXSM_TOKENS:
				sched.tokens = atoi(buf);
				break;
			
			case VXSM_TOKENS_MIN:
				sched.tokens_min = atoi(buf);
				break;
			
			case VXSM_TOKENS_MAX:
				sched.tokens_max = atoi(buf);
				break;
			
			case VXSM_PRIO_BIAS:
				sched.prio_bias = atoi(buf);
				break;
			
			case VXSM_CPU_ID:
				sched.cpu_id = atoi(buf);
				break;
			
			case VXSM_BUCKET_ID:
				sched.bucket_id = atoi(buf);
				break;
		}
		
		if (vx_set_sched(xid, &sched) == -1)
			perr("vx_set_sched");
	}
	
	goto out;
	
setuname:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		buf = strtok(argv[i], "=");
		
		if (buf == NULL)
			goto usage;
		
		if (!(uname.id = flist32_getval(uname_list, buf)))
			perr("flist32_getval");
		
		uname.id = v2i32(uname.id);
		
		buf = strtok(NULL, "=");
		
		if (buf == NULL)
			goto usage;
		
		bzero(uname.value, 65);
		strncpy(uname.value, buf, 64);
		
		if (vx_set_uname(xid, &uname) == -1)
			perr("vx_set_uname");
	}
	
	goto out;
	
getbcaps:
	if (vx_get_bcaps(xid, &bcaps) == -1)
		perr("vx_get_bcaps");
	
	buf = flist64_to_str(bcaps_list, bcaps.caps, '\n');
	
	if (!str_isempty(buf))
		printf("%s\n", buf);
	
	free(buf);
	
	goto out;
	
getccaps:
	if (vx_get_ccaps(xid, &ccaps) == -1)
		perr("vx_get_ccaps");
	
	buf = flist64_to_str(ccaps_list, ccaps.caps, '\n');
	
	if (!str_isempty(buf))
		printf("%s\n", buf);
	
	free(buf);
	
	goto out;
	
getflags:
	if (vx_get_flags(xid, &flags) == -1)
		perr("vx_get_flags");
	
	buf = flist64_to_str(cflags_list, flags.flags, '\n');
	
	if (!str_isempty(buf))
		printf("%s\n", buf);
	
	free(buf);
	
	goto out;
	
getlimit:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		if (!(limit.id = flist32_getval(rlimit_list, argv[i])))
			perr("flist32_getval");
		
		limit.id = v2i32(limit.id);
		
		if (vx_get_limit(xid, &limit) == -1)
			perr("vx_get_rlimit");
		
		printf("%s=", argv[i]);
		
		buf = rlim_to_str(limit.minimum);
		printf("%s,", buf);
		free(buf);
		
		buf = rlim_to_str(limit.softlimit);
		printf("%s,", buf);
		free(buf);
		
		buf = rlim_to_str(limit.maximum);
		printf("%s\n", buf);
		free(buf);
	}
	
	goto out;
	
getuname:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		if (!(uname.id = flist32_getval(uname_list, argv[i])))
			perr("flist32_getval");
		
		uname.id = v2i32(uname.id);
		
		if (vx_get_uname(xid, &uname) == -1)
			perr("vx_get_uname");
		
		printf("%s=%s\n", argv[i], uname.value);
	}
	
	goto out;
	
getstat:
	if (vx_get_stat(xid, &stat) == -1)
		perr("vx_get_stat");
	
	printf("usecnt=%" PRIu32 "\n", stat.usecnt);
	printf("tasks=%"  PRIu32 "\n", stat.tasks);
	
	printf("nr_threads=%" PRIu32 "\n", stat.nr_threads);
	printf("nr_running=%" PRIu32 "\n", stat.nr_running);
	printf("nr_unintr=%"  PRIu32 "\n", stat.nr_unintr);
	printf("nr_onhold=%"  PRIu32 "\n", stat.nr_onhold);
	printf("nr_forks=%"   PRIu32 "\n", stat.nr_forks);
	
	printf("load[0]=%" PRIu32 "\n", stat.load[0]);
	printf("load[1]=%" PRIu32 "\n", stat.load[1]);
	printf("load[2]=%" PRIu32 "\n", stat.load[2]);
	
	printf("offset=%" PRIu64 "\n", stat.offset);
	printf("uptime=%" PRIu64 "\n", stat.uptime);
	
	goto out;
	
getlimitstat:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		if (!(limit_stat.id = flist32_getval(rlimit_list, argv[i])))
			perr("flist32_getval");
		
		limit_stat.id = v2i32(limit_stat.id);
		
		if (vx_get_limit_stat(xid, &limit_stat) == -1)
			perr("vx_get_limit_stat");
		
		printf("%s=%" PRIu32 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 "\n",
		       argv[i],
		       limit_stat.hits,  limit_stat.minimum,
		       limit_stat.value, limit_stat.maximum);
	}
	
	goto out;
	
resetlimitstat:
	if (vx_reset_limit_stat(xid) == -1)
		perr("vx_reset_limit_stat");
	
	goto out;
	
wait:
	if (vx_wait(xid, &wait_result) == -1)
		perr("vx_wait");
	
	printf("reboot_cmd=%" PRIi32 "\n", wait_result.reboot_cmd);
	printf("exit_code=%" PRIi32 "\n", wait_result.exit_code);
	
	goto out;
	
kill:
	if (argc > optind+1) {
		pid = atoi(argv[optind]);
		sig = atoi(argv[optind+1]);
	}
	
	else if (argc > optind)
		goto usage;
	
	if (vx_kill(xid, pid, sig) == -1)
		perr("vx_kill");
	
	goto out;
	
usage:
	usage(EXIT_FAILURE);

out:
	exit(EXIT_SUCCESS);
}
