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

#include <stdlib.h>
#include <inttypes.h>

#define _LUCID_PRINTF_MACROS
#define _LUCID_SCANF_MACROS
#include <lucid/log.h>
#include <lucid/printf.h>
#include <lucid/scanf.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: ns.c 312 2006-07-18 18:47:37Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "ix-attr",   0, 0, 0x10 },
	{ "nx-flags",  0, 0, 0x11 },
	{ "nx-sock",   0, 0, 0x12 },
	{ "vx-bcaps",  0, 0, 0x13 },
	{ "vx-ccaps",  0, 0, 0x14 },
	{ "vx-flags",  0, 0, 0x15 },
	{ "vx-limit",  0, 0, 0x16 },
	{ "vx-mflags", 0, 0, 0x17 },
	{ "vx-sched",  0, 0, 0x18 },
	{ "vx-uname",  0, 0, 0x19 },
	{ NULL,        0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	          "vlist -ix-attr\n"
	          "      -nx-flags\n"
	          "      -nx-sock\n"
	          "      -vx-bcaps\n"
	          "      -vx-ccaps\n"
	          "      -vx-flags\n"
	          "      -vx-limit\n"
	          "      -vx-mflags\n"
	          "      -vx-sched\n"
	          "      -vx-uname\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	int i, c, rc = EXIT_SUCCESS;
	
	uint32_t val32;
	uint64_t val64;
	
	const flist32_t *list32 = NULL;
	const flist64_t *list64 = NULL;
	
	/* logging */
	log_options_t log_options = {
		.ident  = argv[0],
		.stderr = true,
	};
	
	log_init(&log_options);
	
#define CASE_GOTO(ID, S, L) case ID: list ## S = L; goto print_list ## S; break
	
	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES
			
			CASE_GOTO(0x10, 32, ix_attr_list);
			CASE_GOTO(0x11, 64, nx_flags_list);
			CASE_GOTO(0x12, 32, nx_sock_list);
			CASE_GOTO(0x13, 64, vx_bcaps_list);
			CASE_GOTO(0x14, 64, vx_ccaps_list);
			CASE_GOTO(0x15, 64, vx_cflags_list);
			CASE_GOTO(0x16, 32, vx_limit_list);
			CASE_GOTO(0x17, 64, vx_mflags_list);
			CASE_GOTO(0x18, 32, vx_sched_list);
			CASE_GOTO(0x19, 32, vx_uname_list);
			
			DEFAULT_GETOPT_CASES
		}
	}
	
#undef CASE_GOTO
	
	goto usage;
	
print_list32:
	val32 = ~0UL;
	
	if (argc > optind)
		sscanf(argv[optind], "%" SCNu32, &val32);
	
	for (i = 0; list32[i].key; i++)
		if (val32 & list32[i].val)
			printf("[%#.8" PRIx32 "] %s\n", list32[i].val, list32[i].key);
	
	
	goto out;
	
print_list64:
	val64 = ~0UL;
	
	if (argc > optind)
		sscanf(argv[optind], "%llx", &val64);
	
	for (i = 0; list64[i].key; i++)
		if (val64 & list64[i].val)
			printf("[%#.16" PRIx64 "] %s\n", list64[i].val, list64[i].key);
	
	goto out;
	
usage:
	usage(EXIT_FAILURE);

out:
	exit(rc);
}
