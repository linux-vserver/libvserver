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
#include <signal.h>
#include <sys/types.h>

#include "vserver.h"
#include "tools.h"

#define NAME  "vdlimit"
#define DESCR "Disk Limit Manager"

#define SHORT_OPTS "hVARS:x:m:f:"

static const
struct option LONG_OPTS[] = {
	{ "help",    no_argument,       0, 'h' },
	{ "version", no_argument,       0, 'V' },
	{ "add",     no_argument,       0, 'A' },
	{ "remove",  no_argument,       0, 'R' },
	{ "set",     required_argument, 0, 'S' },
	{ "xid",     required_argument, 0, 'x' },
	{ "mount",   required_argument, 0, 'm' },
	{ "flags",   required_argument, 0, 'f' },
	{ 0,0,0,0 }
};

struct commands {
	bool add;
	bool remove;
	bool set;
};

struct options {
	xid_t xid;
	char *mount;
	struct vx_dlimit dlimit;
};

static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <program> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "    -A,--add                Add a disk limit entry\n"
	       "    -R,--remove             Remove a disk limit entry\n"
	       "    -S,--set <format>       Set a disk limit described in <format>\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          The Context ID\n"
	       "    -m,--mount <dir>        The mount point of the disk\n"
	       "    -f,--flags <flags>      Disk limit flags\n"
	       "\n"
	       "Disk Limit format string:\n"
	       "    <format> = <SU>,<SM>,<IU>,<IM>,<RR> where\n"
	       "                - SU is the used space in kbytes,\n"
	       "                - SM is the maximum space in kbytes,\n"
	       "                - IU is the used inode count,\n"
	       "                - IM is the maximum inode count, and\n"
	       "                - RR is reserved for root in percent.\n"
	       "\n",
	       NAME);
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct commands cmds = {
		.add    = false,
		.remove = false,
		.set    = false
	};

	struct options opts = {
		.xid     = XID_SELF,
		.mount   = 0,
		.dlimit  = { 0, 0, 0, 0, 0, 0 },
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
		EXIT("This program requires root privileges", 1);

	if (argc > optind)
		execvp(argv[optind], argv+optind);

	exit(EXIT_SUCCESS);
}