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

#define _LUCID_PRINTF_MACROS
#define _LUCID_SCANF_MACROS
#include <lucid/addr.h>
#include <lucid/bitmap.h>
#include <lucid/log.h>
#include <lucid/mem.h>
#include <lucid/printf.h>
#include <lucid/scanf.h>
#include <lucid/str.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: nx.c 294 2006-07-09 08:46:15Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "create",      1, 0, 0x10 },
	{ "migrate",     1, 0, 0x11 },
	{ "info",        1, 0, 0x12 },
	{ "addr-add",    1, 0, 0x13 },
	{ "addr-remove", 1, 0, 0x14 },
	{ "flags-set",   1, 0, 0x15 },
	{ "flags-get",   1, 0, 0x16 },
	{ "sock-stat",   1, 0, 0x17 },
	{ NULL,          0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	       "nx -create      <nid> [<list>] [-- <program> <args>*]\n"
	       "   -migrate     <nid> -- <program> <args>*\n"
	       "   -info        <nid>\n"
	       "   -addr-add    <nid> <addr>/<netmask>*\n"
	       "   -addr-remove <nid> <addr>/<netmask>*\n"
	       "   -flags-set   <nid> <list>\n"
	       "   -flags-get   <nid>\n"
	       "   -sock-stat   <nid> <type>*\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	int c, i, rc = EXIT_SUCCESS;
	nid_t nid = 0;
	char *buf;

	/* syscall data */
	union {
		nx_addr_t      a;
		nx_flags_t     f;
		nx_info_t      i;
		nx_sock_stat_t s;
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
	sscanf(optarg, "%" SCNu32, &nid); \
	goto P; break

	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES

			CASE_GOTO(0x10, create);
			CASE_GOTO(0x11, migrate);
			CASE_GOTO(0x12, info);
			CASE_GOTO(0x13, addradd);
			CASE_GOTO(0x14, addrremove);
			CASE_GOTO(0x15, flagsset);
			CASE_GOTO(0x16, flagsget);
			CASE_GOTO(0x17, sockstat);

			DEFAULT_GETOPT_CASES
		}
	}

#undef CASE_GOTO

	goto usage;

create:
	if (argc > optind && str_cmp(argv[optind], "--") != 0) {
		if (flist64_from_str(argv[optind], nx_flags_list,
					&data.f.flags, &data.f.mask, '~', ",") == -1)
			rc = log_perror("flist64_from_str");

		else if (nx_create(nid, &data.f) == -1)
			rc = log_perror("nx_create");

		if (argc > optind+2 && execvp(argv[optind+2], argv+optind+2) == -1)
			rc = log_perror("execvp");
	}

	else {
		if (nx_create(nid, NULL) == -1)
			log_perror("nx_create");

		else if (argc > optind+1 && execvp(argv[optind+1], argv+optind+1) == -1)
			rc = log_perror("execvp");
	}

	goto out;

migrate:
	if (nx_migrate(nid) == -1)
		rc = log_perror("nx_migrate");

	else if (argc > optind+1 && execvp(argv[optind+1], argv+optind+1) == -1)
		rc = log_perror("execvp");

	goto out;

info:
	if (nx_info(nid, &data.i) == -1)
		rc = log_perror("nx_info");

	else
		printf("nid=%" PRIu32 "\n", data.i.nid);

	goto out;

addradd:
	if (argc <= optind)
		goto usage;

	data.a.type  = NXA_TYPE_IPV4;
	data.a.count = 1;

	for (i = optind; i < argc; i++) {
		if (addr_from_str(argv[i], &data.a.ip[0], &data.a.mask[0]) == -1)
			rc = log_perror("addr_from_str(%s)", argv[i]);

		else if (nx_addr_add(nid, &data.a) == -1)
			rc = log_perror("nx_addr_add(%s)", argv[i]);
	}

	goto out;

addrremove:
	if (argc <= optind)
		goto usage;

	data.a.type  = NXA_TYPE_IPV4;
	data.a.count = 1;

	for (i = optind; i < argc; i++) {
		if (addr_from_str(argv[i], &data.a.ip[0], &data.a.mask[0]) == -1)
			rc = log_perror("addr_from_str(%s)", argv[i]);

		else if (nx_addr_remove(nid, &data.a) == -1)
			rc = log_perror("nx_addr_remove(%s)", argv[i]);
	}

	goto out;

flagsset:
	if (argc <= optind)
		goto usage;

	if (flist64_from_str(argv[optind], nx_flags_list,
				&data.f.flags, &data.f.mask, '~', ",") == -1)
		rc = log_perror("flist64_from_str");

	else if (nx_flags_set(nid, &data.f) == -1)
		rc = log_perror("nx_set_flags");

	goto out;

flagsget:
	if (nx_flags_get(nid, &data.f) == -1)
		rc = log_perror("nx_flags_get");

	else {
		buf = flist64_to_str(nx_flags_list, data.f.flags, "\n");

		if (!str_isempty(buf))
			printf("%s", buf);

		mem_free(buf);
	}

	goto out;

sockstat:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		if (!(data.s.id = flist32_getval(nx_sock_list, argv[i])))
			rc = log_perror("flist32_getval(%s)", argv[i]);

		else {
			data.s.id = v2i32(data.s.id);

			if (nx_sock_stat(nid, &data.s) == -1)
				rc = log_perror("nx_sock_stat(%s)", argv[i]);

			else
				printf("%s=%"
						PRIu32 "/%" PRIu64 ",%"
						PRIu32 "/%" PRIu64 ",%"
						PRIu32 "/%" PRIu64 "\n",
						argv[i],
						data.s.count[0], data.s.total[0],
						data.s.count[1], data.s.total[1],
						data.s.count[2], data.s.total[2]);
		}
	}

	goto out;

usage:
	usage(EXIT_FAILURE);

out:
	exit(rc);
}
