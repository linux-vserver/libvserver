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
#include <wait.h>

#define _LUCID_PRINTF_MACROS
#define _LUCID_SCANF_MACROS
#include <lucid/log.h>
#include <lucid/printf.h>
#include <lucid/scanf.h>
#include <lucid/str.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: ns.c 312 2006-07-18 18:47:37Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "create",    1, 0, 0x10 },
	{ "migrate",   1, 0, 0x11 },
	{ NULL,        0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	          "ns -create  <xid>\n"
	          "   -migrate <xid> -- <program> <args>*\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	int c, status, rc = EXIT_SUCCESS;
	xid_t xid = 0;
	pid_t pid;

	/* logging */
	log_options_t log_options = {
		.ident  = argv[0],
		.stderr = true,
	};

	log_init(&log_options);

#define CASE_GOTO(ID, P) case ID: \
	sscanf(optarg, "%" SCNu32, &xid); \
	goto P; break

	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES

			CASE_GOTO(0x10, create);
			CASE_GOTO(0x11, migrate);

			DEFAULT_GETOPT_CASES
		}
	}

#undef CASE_GOTO

	goto usage;

create:
	switch((pid = ns_clone(SIGCHLD, NULL))) {
		case -1:
			rc = log_perror("ns_clone");
			break;

		case 0:
			if (ns_set(xid, 0) == -1)
				rc = log_perror("ns_set");

			goto out;

		default:
			if (waitpid(pid, &status, 0) == -1)
				rc = log_perror("waitpid");

			if (WIFSIGNALED(status))
				rc = log_error("Caught signal %d", WTERMSIG(status));

			if (WIFEXITED(status))
				rc = WEXITSTATUS(status);
	}

	goto out;

migrate:
	if (ns_enter(xid, 0) == -1)
		rc = log_perror("ns_enter");

	else if (argc > optind+1 && execvp(argv[optind+1], argv+optind+1) == -1)
		rc = log_perror("execvp");

	goto out;

usage:
	usage(EXIT_FAILURE);

out:
	exit(rc);
}
