/***************************************************************************
 *   Copyright 2005 by the libvserver team                                 *
 *   See AUTHORS for details                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <sys/types.h>

#include "vserver.h"
#include "tools.h"

#define NAME  "vcontext"
#define DESCR "Context Manager"

#define SHORT_OPTS "hVCMF:X:x:u:"

static const
struct option LONG_OPTS[] = {
	{ "help",      no_argument,       0, 'h' },
	{ "version",   no_argument,       0, 'V' },
	{ "create",    no_argument,       0, 'C' },
	{ "migrate",   no_argument,       0, 'M' },
	{ "set-flags", no_argument,       0, 'F' },
	{ "set-caps",  no_argument,       0, 'X' },
	{ "xid",       required_argument, 0, 'x' },
	{ "uid",       required_argument, 0, 'u' },
	{ 0,0,0,0 }
};

struct commands {
	bool create;
	bool migrate;
	bool setflags;
	bool setcaps;
};

struct options {
	struct vx_flags flags;
	struct vx_caps caps;
	xid_t xid;
	uid_t uid;
};

static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <programm> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "    -C,--create             Create a new security context\n"
	       "    -M,--migrate            Migrate to an existing context\n"
	       "    -F,--set-flags <format> Set context flags described in <format>\n"
	       "    -X,--set-caps <format>  Set context capabilities described in <format>\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          The Context ID\n"
	       "    -u,--uid <uid>          Set the uid of the current process\n"
	       "\n",
	       NAME);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct commands cmds = {
		.create		= false,
		.migrate	= false,
		.setflags	= false,
		.setcaps	= false
	};

	struct options opts = {
		.flags		= { .flags = 0, .mask = 0 },
		.caps		= { .bcaps = 0, .ccaps = 0, .cmask = 0 },
		.xid		= XID_SELF,
		.uid		= (uid_t) 0
	};

	int c;

	while (1) {
		c = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS, 0);
		if (c == -1) break;

		switch (c) {
			case 'h':
				cmd_help();
				break;

			case 'V':
				CMD_VERSION(NAME, DESCR);
				break;

			case 'C':
				cmds.create = true;
				break;

			case 'M':
				cmds.migrate = true;
				break;

			case 'F':
				cmds.setflags = true;
				break;

			case 'X':
				cmds.setcaps = true;
				break;

			case 'x':
				opts.xid = (xid_t) atoi(optarg);
				break;

			case 'u':
				opts.uid = (uid_t) atoi(optarg);
				break;

			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				return 1;
				break;
		}
	}

	if (getuid() != 0)
		SEXIT("This program requires root privileges", 1);

	if (cmds.create && cmds.migrate)
		EXIT("Can't create and migrate at the same time", 1);

	if (cmds.create)
		if (vx_create(opts.xid, 0) < 0)
			PEXIT("Failed to create context", 2);

	if (cmds.migrate)
		if (vx_migrate(opts.xid) < 0)
			PEXIT("Failed to migrate to context", 2);

	if (cmds.setflags)
		SEXIT("--set-flags not implemented yet...", 1);

	if (cmds.setcaps)
		SEXIT("--set-caps not implemented yet...", 1);

	if (opts.uid > 0)
		if (setuid(opts.uid) < 0)
			PEXIT("Failed to change user id", 3);

	if (argc > optind)
		execvp(argv[optind], argv+optind);

	return EXIT_SUCCESS;
}
