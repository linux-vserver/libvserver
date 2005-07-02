/***************************************************************************
 *   Copyright (C) 2005 by Benedikt Boehm                                  *
 *   hollow@gentoo.org                                                     *
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

#include <getopt.h>

#include "libvserver.h"
#include "tools.h"

#define NAME	"vnetwork"
#define VERSION	"0.1"
#define DESCR	"Network Context Manager"

#define SHORT_OPTS "hVCMARFSn:vq"

static const
struct option LONG_OPTS[] = {
	{ "help",		no_argument, 		0, 'h' },
	{ "version",	no_argument, 		0, 'V' },
	{ "create",		no_argument, 		0, 'C' },
	{ "migrate",	no_argument, 		0, 'M' },
	{ "add",		no_argument, 		0, 'A' },
	{ "remove",		no_argument, 		0, 'R' },
	{ "set-flag",	required_argument, 	0, 'F' },
	{ "set-cap",	required_argument, 	0, 'S' },
	{ "nid",		required_argument, 	0, 'n' },
	{ "verbose",	no_argument, 		0, 'v' },
	{ "quiet",		no_argument, 		0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
};

struct options {
	nid_t nid;
	bool verbose;
	bool quiet;
};

static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <programm> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "    -C,--create             Create a network context\n"
	       "    -M,--migrate            Migrate to an existing context\n"
	       "    -A,--add                Add an interface to the context\n"
	       "    -R,--remove             Remove an interface from the context\n"
	       "    -F,--set-flag <flag>    Set a network context flag\n"
	       "    -S,--set-cap <cap>      Set a network context capability\n"
	       "\n"
	       "Available options:\n"
	       "    -n,--nid <nid>          Network Context ID\n"
	       "\n"
	       "Generic options:\n"
	       "    -v,--verbose            Print verbose information\n"
	       "    -q,--quiet              Be quiet\n"
	       "\n",
	       NAME);
	exit(0);
}

int main(int argc, char *argv[])
{
	if (getuid() != 0)
		EXIT("This programm requires root privileges", 1);
	
	struct commands cmds = {};
	
	struct options opts = {
		.nid     = (nid_t) 1,
		.verbose = false,
		.quiet   = false
	};
	
	int c, cmdcnt = 0;
	
	while (1) {
		c = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS, 0);
		if (c == -1) break;
		
		switch (c) {
			case 'h':
				cmd_help(0);
				break;
			
			case 'V':
				CMD_VERSION;
				break;
			
			case 'v':
				opts.verbose = true;
				break;
			
			case 'q':
				opts.quiet = true;
				break;
			
			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				return EXIT_FAILURE;
				break;
		}
	}
	
	if (cmdcnt == 0)
		EXIT("No command given", 1);
	
	if (cmdcnt > 1)
		EXIT("More than one command given", 1);
	
	if (opts.nid <= 1)
		if ((opts.nid = vc_task_nid(0)) <= 1)
			EXIT("Invalid --nid given", 1);
	
	if (argc <= optind)
		EXIT("No program given", 1);
	
	execvp(argv[optind], argv+optind);
	
	return EXIT_SUCCESS;
}
