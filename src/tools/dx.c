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
#include <lucid/str.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: dx.c 267 2006-07-06 08:25:19Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "limit-add",    1, 0, 0x10 },
	{ "limit-remove", 1, 0, 0x11 },
	{ "limit-set",    1, 0, 0x12 },
	{ "limit-get",    1, 0, 0x13 },
	{ NULL,           0, 0, 0 },
};

static
uint32_t str_to_dlim(char *str)
{
	if (str == NULL)
		return CDLIM_KEEP;
	
	if (str_cmp(str, "inf") == 0)
		return CDLIM_INFINITY;
	
	if (str_cmp(str, "keep") == 0)
		return CDLIM_KEEP;
	
	uint32_t lim;
	sscanf(str, "%" SCNu32, &lim);
	
	return lim;
}

static
char *dlim_to_str(uint32_t lim)
{
	char *buf;
	
	if (lim == CDLIM_INFINITY)
		asprintf(&buf, "%s", "inf");
	else
		asprintf(&buf, "%" PRIu32, lim);
	
	return buf;
}

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	       "dx -limit-add    <xid> <path>*\n"
	       "   -limit-remove <xid> <path>*\n"
	       "   -limit-set    <xid> <path>=<su>,<st>,<iu>,<it>,<rr>*\n"
	       "   -limit-get    <xid> <path>*\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	char *buf, *buf2;
	int c, i, rc = EXIT_SUCCESS;
	xid_t xid = 0;
	
	/* syscall data */
	dx_limit_t data;
	
	str_zero(&data, sizeof(data));
	
	/* logging */
	log_options_t log_options = {
		.ident  = argv[0],
		.stderr = true,
	};
	
	log_init(&log_options);
	
#define CASE_GOTO(ID, P) case ID: sscanf(optarg, "%" SCNu32, &xid); goto P; break
	
	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES
			
			CASE_GOTO(0x10, limitadd);
			CASE_GOTO(0x11, limitremove);
			CASE_GOTO(0x12, limitset);
			CASE_GOTO(0x13, limitget);
			
			DEFAULT_GETOPT_CASES
		}
	}
	
#undef CASE_GOTO
	
	goto usage;
	
limitadd:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; i < argc; i++) {
		data.filename = argv[i];
		
		if (dx_limit_add(xid, &data) == -1)
			rc = log_perror("dx_limit_add(%s)", data.filename);
	}
	
	goto out;
	
limitremove:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; i < argc; i++) {
		data.filename = argv[i];
		
		if (dx_limit_remove(xid, &data) == -1)
			rc = log_perror("dx_limit_remove(%s)", data.filename);
	}
	
	goto out;
	
limitset:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; i < argc; i++) {
		data.filename = argv[i];
		
		buf2 = str_index(argv[i], '=', str_len(argv[i]));
		
		if (buf2)
			*buf2++ = '\0';
		
		if (str_isempty(data.filename))
			rc = log_error("Invalid argument: %s", argv[i]);
		
		else {
			buf = buf2;
			buf2 = str_index(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.space_used = str_to_dlim(buf);
			
			buf = buf2;
			buf2 = str_index(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.space_total = str_to_dlim(buf);
			
			buf = buf2;
			buf2 = str_index(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.inodes_used = str_to_dlim(buf);
			
			buf = buf2;
			buf2 = str_index(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.inodes_total = str_to_dlim(buf);
			
			buf = buf2;
			buf2 = str_index(buf, ',', str_len(buf)); if (buf2) *buf2++ = '\0';
			data.reserved = str_to_dlim(buf);
			
			if (dx_limit_set(xid, &data) == -1)
				rc = log_perror("dx_limit_set(%s)", data.filename);
		}
	}
	
	goto out;
	
limitget:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; i < argc; i++) {
		data.filename = argv[i];
		
		if (dx_limit_get(xid, &data) == -1)
			rc = log_perror("dx_limit_get(%s)", data.filename);
		
		else {
			printf("%s=", argv[i]);
			
			buf = dlim_to_str(data.space_used);
			printf("%s,", buf);
			free(buf);
			
			buf = dlim_to_str(data.space_total);
			printf("%s,", buf);
			free(buf);
			
			buf = dlim_to_str(data.inodes_used);
			printf("%s,", buf);
			free(buf);
			
			buf = dlim_to_str(data.inodes_total);
			printf("%s,", buf);
			free(buf);
			
			buf = dlim_to_str(data.reserved);
			printf("%s,", buf);
			free(buf);
		}
	}
	
	goto out;
	
usage:
	usage(EXIT_FAILURE);
	
out:
	exit(rc);
}
