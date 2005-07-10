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
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/types.h>

#include "vserver.h"
#include "tools.h"

#define NAME  "vnetwork"
#define DESCR "Network Context Manager"

#define SHORT_OPTS "hVCMARFPn:f:p:"

static const
struct option LONG_OPTS[] = {
	{ "help",      no_argument,       0, 'h' },
	{ "version",   no_argument,       0, 'V' },
	{ "create",    no_argument,       0, 'C' },
	{ "migrate",   no_argument,       0, 'M' },
	{ "add",       no_argument,       0, 'A' },
	{ "remove",    no_argument,       0, 'R' },
	{ "set-flags", no_argument,       0, 'F' },
	{ "set-caps",  no_argument,       0, 'P' },
	{ "nid",       required_argument, 0, 'n' },
	{ "flags",     required_argument, 0, 'f' },
	{ "caps",      required_argument, 0, 'p' },
	{ 0,0,0,0 }
};

struct commands {
	bool create;
	bool migrate;
	bool add;
	bool remove;
	bool setflags;
	bool setcaps;
};

struct options {
	nid_t nid;
	struct nx_flags flags;
	struct nx_caps caps;
};

static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <program> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "    -C,--create             Create a network context\n"
	       "    -M,--migrate            Migrate to an existing context\n"
	       "    -A,--add                Add an interface to the context\n"
	       "    -R,--remove             Remove an interface from the context\n"
	       "    -F,--set-flags          Set network context flags\n"
	       "    -P,--set-caps           Set network context capabilities\n"
	       "\n"
	       "Available options:\n"
	       "    -n,--nid <nid>          Network Context ID\n"
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
		.add      = false,
		.remove   = false,
		.setflags = false,
		.setcaps  = false
	};

	struct options opts = {
		.nid   = NID_SELF,
		.flags = { .flags = 0, .mask = 0 },
		.caps  = { .caps = 0, .mask = 0 }
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

			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				exit(EXIT_USAGE);
				break;
		}
	}

	if (getuid() != 0)
		EXIT("This programm requires root privileges", 1);

	if (argc > optind)
		execvp(argv[optind], argv+optind);

	exit(EXIT_SUCCESS);
}
