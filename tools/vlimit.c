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

#include "vserver.h"
#include "tools.h"

#define NAME	"vlimit"
#define DESCR	"Context Resource Limit Manager"

#define SHORT_OPTS "hVCESCNx:snekmdvq"

static const
struct option LONG_OPTS[] = {
	{ "help",		no_argument, 		0, 'h' },
	{ "version",	no_argument, 		0, 'V' },
	{ "verbose",	no_argument, 		0, 'v' },
	{ "quiet",		no_argument, 		0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
};

struct options {
	xid_t xid;
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
	       "    -S,--set                Set the resource limit of context <xid>\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          Context ID\n"
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
		.xid     = (xid_t) 1,
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
				CMD_VERSION(NAME, VERSION, DESCR);
				break;
			
			case 'v':
				opts.verbose = true;
				break;
			
			case 'q':
				opts.quiet = true;
				break;
			
			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				exit(EXIT_FAILURE);
				break;
		}
	}
	
	if (cmdcnt == 0)
		EXIT("No command given", 1);
	
	if (cmdcnt > 1)
		EXIT("More than one command given", 1);
	
	if (opts.xid <= 1)
		if ((opts.xid = vx_get_task_xid(0)) <= 1)
			EXIT("Invalid --xid given", 1);
	
	if (argc <= optind)
		EXIT("No program given", 1);
	
	execvp(argv[optind], argv+optind);
	
	exit(EXIT_SUCCESS);
}
