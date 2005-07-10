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

#define NAME  "vinfo"
#define DESCR "Context Information Grabber"

#define T_TASK_XID    'A'
#define T_VX_INFO     'B'
#define T_CFLAGS      'C'
#define T_CCAPS       'D'
#define T_BCAPS       'E'
#define T_RLIMIT      'F'
#define T_RLIMITMASK  'G'
#define T_UNAME       'I'
#define T_TASK_NID    'J'
#define T_NX_INFO     'K'
#define T_NFLAGS      'L'
#define T_NCAPS       'M'
#define T_VS_VERSION  'N'

#define SHORT_OPTS "hVx:n:"

static const
struct option LONG_OPTS[] = {
	{ "help",       no_argument,       0, 'h' },
	{ "version",    no_argument,       0, 'V' },
	{ "task-xid",   required_argument, 0, T_TASK_XID },
	{ "vx-info",    no_argument,       0, T_VX_INFO },
	{ "cflags",     no_argument,       0, T_CFLAGS },
	{ "ccaps",      no_argument,       0, T_CCAPS },
	{ "bcaps",      no_argument,       0, T_BCAPS },
	{ "rlimit",     no_argument,       0, T_RLIMIT },
	{ "rlimitmask", no_argument,       0, T_RLIMITMASK },
	{ "uname",      no_argument,       0, T_UNAME },
	{ "task-nid",   required_argument, 0, T_TASK_NID },
	{ "nx-info",    no_argument,       0, T_NX_INFO },
	{ "nflags",     no_argument,       0, T_NFLAGS },
	{ "ncaps",      no_argument,       0, T_NCAPS },
	{ "vs-version", no_argument,       0, T_VS_VERSION },
	{ "xid",        required_argument, 0, 'x' },
	{ "nid",        required_argument, 0, 'n' },
	{ 0,0,0,0 }
};

struct options {
	xid_t xid;
	nid_t nid;
};

static inline
void cmd_help()
{
	printf("Usage: %s [<command>] <type> <opts>* -- <programm> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "\n"
	       "Available information types:\n"
	       "\n"
	       "  Context information:\n"
	       "    --task-xid <pid>        Print xid of process <pid>\n"
	       "    --vx-info               Print context information\n"
	       "    --cflags                Print context flags\n"
	       "    --ccaps                 Print context capabilities\n"
	       "    --bcaps                 Print system capabilities\n"
	       "    --rlimit                Print context resource limits\n"
	       "    --rlimitmask            Print context resource limit mask\n"
	       "\n"
	       "  Virtual host information:\n"
	       "    --uname                 Print virtual host information aka UTS\n"
	       "\n"
	       "  Network Context information:\n"
	       "    --task-nid <pid>        Print nid of process <pid>\n"
	       "    --nx-info               Print network context information\n"
	       "    --nflags                Print network context flags\n"
	       "    --ncaps                 Print network context capabilities\n"
	       "\n"
	       "  Generic information:\n"
	       "    --vs-version            Print Linux-VServer version\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          Context ID\n"
	       "    -n,--nid <nid>          Network context ID\n"
	       "\n",
	       NAME);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct options opts = {
		.xid = XID_SELF,
		.nid = NID_SELF
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
