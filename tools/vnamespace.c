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

#define NAME  "vnamespace"
#define DESCR "Filesystem Namespace Manager"

#define SHORT_OPTS "hVESCx:"

static const
struct option LONG_OPTS[] = {
	{ "help",    no_argument,       0, 'h' },
	{ "version", no_argument,       0, 'V' },
	{ "enter",   no_argument,       0, 'E' },
	{ "set",     no_argument,       0, 'S' },
	{ "cleanup", no_argument,       0, 'C' },
	{ "xid",     required_argument, 0, 'x' },
	{ 0,0,0,0 }
};

struct commands {
	bool enter;
	bool set;
	bool cleanup;
};

struct options {
	xid_t xid;
};

static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <program> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "    -E,--enter              Enter the namespace of context <xid>\n"
	       "    -S,--set                Make current namespace the namespace of current context\n"
	       "    -C,--cleanup            Remove all mounts from current context\n" /* TODO: is this correct? */
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          The Context ID\n"
	       "\n",
	       NAME);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct commands cmds = {
		.enter   = false,
		.set     = false,
		.cleanup = false
	};

	struct options opts = {
		.xid = XID_SELF
	};

	int c;

	while (1) {
		c = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS, 0);
		if(c == -1) break;

		switch (c) {
			case 'h':
				cmd_help();
				break;

			case 'V':
				CMD_VERSION(NAME, DESCR);
				break;

			case 'E':
				cmds.enter = true;
				break;

			case 'S':
				cmds.set = true;
				break;

			case 'C':
				cmds.cleanup = true;
				break;

			case 'x':
				opts.xid = (xid_t) atoi(optarg);
				break;

			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				exit(EXIT_USAGE);
				break;
		}
	}

	if (getuid() != 0)
		SEXIT("This programm requires root privileges", EXIT_USAGE);

	if (cmds.set && cmds.enter)
		EXIT("Can't set and enter at the same time", EXIT_USAGE);

	if (cmds.enter)
		if (vx_enter_namespace(opts.xid) < 0)
			PEXIT("Failed to enter namespace", EXIT_COMMAND);

	if (cmds.set)
		if (vx_set_namespace() < 0)
			PEXIT("Failed to set namespace", EXIT_COMMAND);

	if (cmds.cleanup)
		if (vx_cleanup_namespace() < 0)
			PEXIT("Failed to cleanup namespace", EXIT_COMMAND);

	if (argc > optind)
		execvp(argv[optind], argv+optind);

	exit(EXIT_SUCCESS);
}
