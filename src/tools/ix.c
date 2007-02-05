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

#include <stdlib.h>
#include <inttypes.h>

#define _LUCID_PRINTF_MACROS
#define _LUCID_SCANF_MACROS
#include <lucid/log.h>
#include <lucid/mem.h>
#include <lucid/printf.h>
#include <lucid/scanf.h>
#include <lucid/str.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: ix.c 294 2006-07-09 08:46:15Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "attr-set", 0, 0, 0x10 },
	{ "attr-get", 0, 0, 0x11 },
	{ "xid-set",  0, 0, 0x12 },
	{ "xid-get",  0, 0, 0x13 },
	{ NULL,       0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	          "ix -attr-set <file>=<list>*\n"
	          "   -attr-get <file>*\n"
	          "   -xid-set  <file>=<xid>*\n"
	          "   -xid-get  <file>*\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	int c, i, rc = EXIT_SUCCESS;
	char *buf;

	/* syscall data */
	ix_attr_t data;

	mem_set(&data, 0, sizeof(data));

	/* logging */
	log_options_t log_options = {
		.log_ident = argv[0],
		.log_dest  = LOGD_STDERR,
		.log_opts  = LOGO_PRIO|LOGO_IDENT,
	};

	log_init(&log_options);

#define CASE_GOTO(ID, P) case ID: goto P; break

	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES

			CASE_GOTO(0x10, attrset);
			CASE_GOTO(0x11, attrget);
			CASE_GOTO(0x12, xidset);
			CASE_GOTO(0x13, xidget);

			DEFAULT_GETOPT_CASES
		}
	}

#undef CASE_GOTO

	goto usage;

attrset:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		data.filename = argv[i];

		buf = str_chr(argv[i], '=', str_len(argv[i]));

		if (buf)
			*buf++ = '\0';

		if (str_isempty(data.filename) || str_isempty(buf))
			rc = log_error("Invalid argument: %s", argv[i]);

		else if (flist32_from_str(buf, ix_attr_list,
					&data.flags, &data.mask, '~', ",") == -1)
			rc = log_perror("flist32_parse(%s)", data.filename);

		else if (ix_attr_set(&data) == -1)
			rc = log_perror("ix_attr_set(%s)", data.filename);
	}

	goto out;

attrget:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		data.filename = argv[i];

		if (ix_attr_get(&data) == -1)
			rc = log_perror("ix_attr_get(%s)", data.filename);

		else if (!(buf = flist32_to_str(ix_attr_list,
						data.flags & data.mask, ",")))
			rc = log_perror("flist32_to_str(%s)", data.filename);

		else {
			if (!str_isempty(buf))
				printf("%s\n", buf);

			mem_free(buf);
		}
	}

	goto out;

xidset:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		data.filename = argv[i];

		buf = str_chr(argv[i], '=', str_len(argv[i]));

		if (buf)
			*buf++ = '\0';

		if (str_isempty(data.filename) || str_isempty(buf))
			rc = log_error("Invalid argument: %s", argv[i]);

		else if (ix_attr_get(&data) == -1)
			rc = log_perror("ix_attr_get(%s)", data.filename);

		else if (data.mask & IATTR_TAG) {
			sscanf(buf, "%" SCNu32, &data.xid);

			data.flags |= IATTR_TAG;
			data.mask  |= IATTR_TAG;

			if (ix_attr_set(&data) == -1)
				rc = log_perror("ix_attr_set(%s)", data.filename);
		}

		else
			rc = log_error("IATTR_TAG not available: %s", data.filename);
	}

	goto out;

xidget:
	if (argc <= optind)
		goto usage;

	for (i = optind; i < argc; i++) {
		data.filename = argv[i];

		if (ix_attr_get(&data) == -1)
			rc = log_perror("ix_attr_get(%s)", data.filename);

		else if (data.mask & IATTR_TAG)
			printf("%" PRIu32 "\n", data.xid);

		else
			rc = log_error("IATTR_TAG not available: %s", data.filename);
	}

	goto out;

usage:
	usage(EXIT_FAILURE);

out:
	exit(rc);
}
