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

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: ix.c 294 2006-07-09 08:46:15Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "get-attr", 1, 0, 0x10 },
	{ "set-attr", 1, 0, 0x11 },
	{ "get-xid",  1, 0, 0x12 },
	{ "set-xid",  1, 0, 0x13 },
	{ NULL,       0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	          "ix -get-attr <file>\n"
	          "   -set-attr <file> <list>\n"
	          "   -get-xid  <file>\n"
	          "   -set-xid  <file> <xid>\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	INIT_ARGV0
	
	int c;
	char *buf;
	
	/* syscall data */
	struct ix_attr attr = {
		.filename = NULL,
		.xid      = 0,
		.flags    = 0,
		.mask     = 0,
	};
	
#define CASE_GOTO(ID, P) case ID: attr.filename = optarg; goto P; break
	
	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES
			
			CASE_GOTO(0x10, getattr);
			CASE_GOTO(0x11, setattr);
			CASE_GOTO(0x12, getxid);
			CASE_GOTO(0x13, setxid);
			
			DEFAULT_GETOPT_CASES
		}
	}
	
#undef CASE_GOTO
	
	goto usage;
	
getattr:
	if (ix_get_attr(&attr) == -1)
		perr("ix_get_attr");
	
	if (!(buf = flist32_to_str(iattr_list, attr.flags & attr.mask, ',')))
		perr("flist32_to_str");
	
	if (strlen(buf) > 0)
		printf("%s\n", buf);
	
	free(buf);
	goto out;
	
setattr:
	if (argc <= optind)
		goto usage;
	
	if (flist32_from_str(argv[optind], iattr_list, &attr.flags, &attr.mask, '~', ',') == -1)
		perr("flist32_parse");
	
	if (ix_set_attr(&attr) == -1)
		perr("ix_set_attr");
	
	goto out;
	
getxid:
	if (ix_get_attr(&attr) == -1)
		perr("ix_get_attr");
	
	if (attr.mask & IATTR_TAG)
		printf("%" PRIu32 "\n", attr.xid);
	
	else
		err("%s: IATTR_XID not available", attr.filename);
	
	goto out;
	
setxid:
	if (argc <= optind)
		goto usage;
	
	if (ix_get_attr(&attr) == -1)
		perr("ix_get_attr");
	
	if (attr.mask & IATTR_TAG) {
		attr.xid = atoi(argv[optind]);
		
		attr.flags |= IATTR_TAG;
		attr.mask  |= IATTR_TAG;
		
		if (ix_set_attr(&attr) == -1)
			perr("ix_set_attr");
		
		goto out;
	}
	
	else
		err("%s: IATTR_XID not available", attr.filename);
	
	goto out;
	
usage:
	usage(EXIT_FAILURE);

out:
	exit(EXIT_SUCCESS);
}
