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
#include <string.h>
#include <inttypes.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: dx.c 267 2006-07-06 08:25:19Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "add-limit", 1, 0, 0x10 },
	{ "rem-limit", 1, 0, 0x11 },
	{ "set-limit", 1, 0, 0x12 },
	{ "get-limit", 1, 0, 0x13 },
	{ NULL,        0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	       "dx -add-limit <xid> <path>\n"
	       "   -rem-limit <xid> <path>\n"
	       "   -set-limit <xid> <path> <su>,<st>,<iu>,<it>,<rr>\n"
	       "   -get-limit <xid> <path>\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	INIT_ARGV0
	
	int c, i;
	xid_t xid = 0;
	char *buf;
	
	/* syscall data */
	struct dx_limit limit = {
		.filename     = NULL,
		.space_used   = CDLIM_KEEP,
		.space_total  = CDLIM_KEEP,
		.inodes_used  = CDLIM_KEEP,
		.inodes_total = CDLIM_KEEP,
		.reserved     = CDLIM_KEEP,
		.flags        = 0,
	};
	
#define CASE_GOTO(ID, P) case ID: xid = atoi(optarg); goto P; break
	
	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES
			
			CASE_GOTO(0x10, addlimit);
			CASE_GOTO(0x11, remlimit);
			CASE_GOTO(0x12, setlimit);
			CASE_GOTO(0x13, getlimit);
			
			DEFAULT_GETOPT_CASES
		}
	}
	
#undef CASE_GOTO
	
	goto usage;
	
addlimit:
	if (argc <= optind)
		goto usage;
	
	limit.filename = argv[optind];
	
	if (dx_add_limit(xid, &limit) == -1)
		perr("dx_add_limit");
	
	goto out;
	
remlimit:
	if (argc <= optind)
		goto usage;
	
	limit.filename = argv[optind];
	
	if (dx_rem_limit(xid, &limit) == -1)
		perr("dx_rem_limit");
	
	goto out;
	
setlimit:
	if (argc <= optind)
		goto usage;
	
	limit.filename = argv[optind];
	
	i = 0;
	
	for (buf = strtok(argv[optind+1], ","); buf != NULL; i++) {
		if (strlen(buf) < 1)
			continue;
		
#define BUF2LIM(LIM) do { \
	if (strcasecmp(buf, "inf") == 0)       LIM = CDLIM_INFINITY; \
	else if (strcasecmp(buf, "keep") == 0) LIM = CDLIM_KEEP; \
	else                                   LIM = (uint32_t) atoi(buf); \
} while(0)
		
		switch (i) {
			case 0: BUF2LIM(limit.space_used); break;
			case 1: BUF2LIM(limit.space_total); break;
			case 2: BUF2LIM(limit.inodes_used); break;
			case 3: BUF2LIM(limit.inodes_total); break;
			case 4: BUF2LIM(limit.reserved); break;
		}
		
#undef BUF2LIM
		
		buf = strtok(NULL, ",");
	}
	
	if (i != 5)
		goto usage;
	
	if (dx_set_limit(xid, &limit) == -1)
		perr("dx_set_limit");
	
	goto out;
	
getlimit:
	if (argc <= optind)
		goto usage;
	
	limit.filename = argv[optind];
	
	if (dx_get_limit(xid, &limit) == -1)
		perr("dx_get_limit");
	
#define LIM2OUT(LIM, DELIM) do { \
	if (LIM == CDLIM_INFINITY) printf("%s", "inf"); \
	else printf("%" PRIu32, LIM); \
	printf("%c", DELIM); \
} while(0)
	
	LIM2OUT(limit.space_used,   ',');
	LIM2OUT(limit.space_total,  ',');
	LIM2OUT(limit.inodes_used,  ',');
	LIM2OUT(limit.inodes_total, ',');
	LIM2OUT(limit.reserved,     '\n');
	
#undef LIM2OUT
	
	goto out;
	
usage:
	usage(EXIT_FAILURE);

out:
	exit(EXIT_SUCCESS);
}
