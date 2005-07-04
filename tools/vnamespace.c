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

#define NAME	"vnamespace"
#define DESCR	"Filesystem Namespace Manager"

#define SHORT_OPTS "hVESCx:vq"

struct option const
LONG_OPTS[] = {
	{ "help",		no_argument, 		0, 'h' },
	{ "version",	no_argument, 		0, 'V' },
	{ "enter",		no_argument, 		0, 'E' },
	{ "set",		no_argument, 		0, 'S' },
	{ "cleanup",	no_argument, 		0, 'C' },
	{ "xid",		required_argument, 	0, 'x' },
	{ "verbose",	no_argument, 		0, 'v' },
	{ "quiet",		no_argument, 		0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
	bool help;
	bool version;
	bool enter;
	bool set;
	bool cleanup;
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
	       "    -E,--enter              Enter the namespace of context <xid>\n"
	       "    -S,--set                Make current namespace the namespace of current context\n"
	       "    -C,--cleanup            Remove all mounts from current context\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          The Context ID\n"
	       "\n"
	       "Generic options:\n"
	       "    -v,--verbose            Print verbose information\n"
	       "    -q,--quiet              Be quiet (i.e. no output at all)\n"
	       "\n",
	       NAME);
	exit(0);
}

int main(int argc, char *argv[])
{
	if (getuid() != 0)
		SEXIT("This programm requires root privileges", 1);

	struct commands cmds = {
		.help		= false,
		.version	= false,
		.enter		= false,
		.set		= false,
		.cleanup	= false,
	};

	struct options opts = {
		.xid		= (xid_t) 1,
		.verbose	= false,
		.quiet		= false
	};

	int c, cmdcnt = 0;
	
	while (1) {
		c = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS, 0);
		if(c == -1) break;
		
		switch (c) {
			case 'h':
				cmd_help(0);
				break;
			
			case 'V':
				CMD_VERSION(NAME, VERSION, DESCR);
				break;
			
			case 'E':
				cmds.enter = true;
				cmdcnt++;
				break;
			
			case 'S':
				cmds.set = true;
				cmdcnt++;
				break;
			
			case 'C':
				cmds.cleanup = true;
				cmdcnt++;
				break;

			case 'x':
				opts.xid = (xid_t) atoi(optarg);
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
	
	if (cmds.enter)
		if (vc_enter_namespace(opts.xid) < 0)
			PEXIT("Failed to enter namespace", 2);
	
	if (cmds.set)
		if (vc_set_namespace() < 0)
			PEXIT("Failed to set namespace", 2);
	
	if (cmds.cleanup)
		if (vc_cleanup_namespace() < 0)
			PEXIT("Failed to cleanup namespace", 2);

	execvp(argv[optind], argv+optind);

	return EXIT_SUCCESS;
}
