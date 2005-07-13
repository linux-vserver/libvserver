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
#include <getopt.h>
#include <sys/types.h>

#include "vserver.h"
#include "tools.h"

#define NAME  "vcontext"
#define DESCR "Context Manager"

#define SHORT_OPTS "hVCMFPx:u:f:p:"

static const
struct option LONG_OPTS[] = {
	{ "help",      no_argument,       0, 'h' },
	{ "version",   no_argument,       0, 'V' },
	{ "create",    no_argument,       0, 'C' },
	{ "migrate",   no_argument,       0, 'M' },
	{ "set-flags", no_argument,       0, 'F' },
	{ "set-caps",  no_argument,       0, 'P' },
	{ "xid",       required_argument, 0, 'x' },
	{ "uid",       required_argument, 0, 'u' },
	{ "flags",     required_argument, 0, 'f' },
	{ "caps",      required_argument, 0, 'p' },
	{ 0,0,0,0 }
};

struct commands {
	bool create;
	bool migrate;
	bool setflags;
	bool setcaps;
};

struct options {
	xid_t xid;
	uid_t uid;
	struct vx_flags flags;
	struct vx_caps caps;
};

static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <program> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "    -C,--create             Create a new security context\n"
	       "    -M,--migrate            Migrate to an existing context\n"
	       "    -F,--set-flags          Set context flags\n"
	       "    -P,--set-caps           Set context capabilities\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          The Context ID\n"
	       "    -u,--uid <uid>          Set the user id for <program>\n"
	       "    -f,--flags <format>     Set flags described in <format>\n"
	       "    -p,--caps <format>      Set capabilities described in <format>\n"
	       "\n",
	       NAME);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct commands cmds = {
		.create   = false,
		.migrate  = false,
		.setflags = false,
		.setcaps  = false
	};

	struct options opts = {
		.xid   = XID_SELF,
		.uid   = (uid_t) 0,
		.flags = { .flags = 0, .mask = 0 },
		.caps  = { .bcaps = 0, .ccaps = 0, .cmask = 0 }
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

			case 'P':
				cmds.setcaps = true;
				break;

			case 'x':
				opts.xid = (xid_t) atoi(optarg);
				break;

			case 'u':
				opts.uid = (uid_t) atoi(optarg);
				break;

			case 'f':
				//opts.flags = 0; /* TODO: implement flag parser (maybe in lib?) */
				SEXIT("--flags not implemented yet...", EXIT_USAGE);
				break;

			case 'p':
				//opts.caps = 0; /* TODO: implement caps parser (maybe in lib?) */
				SEXIT("--caps not implemented yet...", EXIT_USAGE);
				break;

			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				exit(EXIT_USAGE);
				break;
		}
	}

	if (getuid() != 0)
		SEXIT("This program requires root privileges", EXIT_USAGE);

	if (cmds.create && cmds.migrate)
		EXIT("Can't create and migrate at the same time", EXIT_USAGE);

	if (cmds.create)
		if (vx_create(opts.xid, opts.flags.flags) < 0)
			PEXIT("Failed to create context", EXIT_COMMAND);

	if (cmds.migrate)
		if (vx_migrate(opts.xid) < 0)
			PEXIT("Failed to migrate to context", EXIT_COMMAND);

	if (cmds.setflags)
		if (vx_set_flags(opts.xid, &opts.flags) < 0)
			PEXIT("Failed to set context flags", EXIT_COMMAND);

	if (cmds.setcaps)
		if (vx_set_caps(opts.xid, &opts.caps) < 0)
			PEXIT("Failed to set context capabilities", EXIT_COMMAND);

	if (opts.uid > 0)
		if (setuid(opts.uid) < 0)
			PEXIT("Failed to change user id", EXIT_OPTS);

	if (argc > optind)
		execvp(argv[optind], argv+optind);

	exit(EXIT_SUCCESS);
}
