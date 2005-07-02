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

#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>

#include "libvserver.h"
#include "tools.h"

#define NAME	"vinfo"
#define DESCR	"Context Information Grabber"

#define T_TASK_XID    'A'
#define T_VX_INFO     'B'
#define T_CFLAGS      'C'
#define T_CCAPS       'D'
#define T_BCAPS       'E'
#define T_RLIMIT      'F'
#define T_RLIMITMASK  'G'
#define T_IATTR       'H'
#define T_UTSNAME     'I'
#define T_TASK_NID    'J'
#define T_NX_INFO     'K'
#define T_NFLAGS      'L'
#define T_NCAPS       'M'
#define T_VS_VERSION  'N'

#define SHORT_OPTS "hVx:n:vq"

static const
struct option LONG_OPTS[] = {
	{ "help",		no_argument, 		0, 'h' },
	{ "version",	no_argument, 		0, 'V' },
	{ "task-xid",	required_argument,	0, T_TASK_XID },
	{ "vx-info",	no_argument, 		0, T_VX_INFO },
	{ "cflags",		no_argument, 		0, T_CFLAGS },
	{ "ccaps",		no_argument, 		0, T_CCAPS },
	{ "bcaps",		no_argument, 		0, T_BCAPS },
	{ "rlimit",		no_argument, 		0, T_RLIMIT },
	{ "rlimitmask",	no_argument, 		0, T_RLIMITMASK },
	{ "iattr",		required_argument,	0, T_IATTR },
	{ "utsname",	no_argument, 		0, T_UTSNAME },
	{ "task-nid",	required_argument,	0, T_TASK_NID },
	{ "nx-info",	no_argument, 		0, T_NX_INFO },
	{ "nflags",		no_argument, 		0, T_NFLAGS },
	{ "ncaps",		no_argument, 		0, T_NCAPS },
	{ "vs-version",	no_argument, 		0, T_VS_VERSION },
	{ "xid",		required_argument, 	0, 'x' },
	{ "nid",		required_argument, 	0, 'n' },
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
	       "  Inode information:\n"
	       "    --iattr <inode>         Print inode information\n"
	       "\n"
	       "  Namespace information:\n"
	       "    --vhi                   Print virtual informations aka UTS\n"
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
	
	if (opts.xid <= 1)
		if ((opts.xid = vc_task_xid(0)) <= 1)
			EXIT("Invalid --xid given", 1);
	
	if (argc <= optind)
		EXIT("No program given", 1);
	
	execvp(argv[optind], argv+optind);
	
	return EXIT_SUCCESS;
}
