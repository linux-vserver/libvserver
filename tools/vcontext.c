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

#include <getopt.h>

#include "libvserver.h"
#include "tools.h"

#define NAME	"vcontext"
#define VERSION	"0.1"
#define DESCR	"Context Manager"

#define SHORT_OPTS "hVCMF:X:x:u:vq"

static const
struct option LONG_OPTS[] = {
	{ "help",		no_argument, 		0, 'h' },
	{ "version",	no_argument, 		0, 'V' },
	{ "create",		no_argument, 		0, 'C' },
	{ "migrate",	no_argument, 		0, 'M' },
	{ "set-flags",	no_argument, 		0, 'F' },
	{ "set-caps",	no_argument, 		0, 'X' },
	{ "xid",		required_argument, 	0, 'x' },
	{ "uid",		required_argument, 	0, 'u' },
	{ "verbose",	no_argument, 		0, 'v' },
	{ "quiet",		no_argument, 		0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
	bool create;
	bool migrate;
	bool setflags;
	bool setcaps;
};

struct options {
	struct vcmd_ctx_flags_v0 flags;
	struct vcmd_ctx_caps_v0 caps;
	xid_t xid;
	uid_t uid;
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
	       "    -C,--create             Create a new security context\n"
	       "    -M,--migrate            Migrate to an existing context\n"
	       "    -F,--set-flags <format> Set context flags described in <format>\n"
	       "    -X,--set-caps <format>  Set context capabilities described in <format>\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          The Context ID\n"
	       "    -u,--uid <uid>          Set the uid of the current process\n"
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
	
	struct commands cmds = {
		.create		= false,
		.migrate	= false,
		.setflags	= false,
		.setcaps	= false
	};
	
	struct options opts = {
		.flags		= 0,
		.caps		= 0,
		.xid		= 0,
		.uid		= 0,
		.verbose	= false,
		.quiet		= false
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
			
			case 'C':
				cmds.create = true;
				cmdcnt++;
				break;
			
			case 'M':
				cmds.migrate = true;
				cmdcnt++;
				break;
			
			case 'F':
				cmds.setflags = true;
				cmdcnt++;
				break;
			
			case 'X':
				cmds.setcaps = true;
				cmdcnt++;
				break;
			
			case 'x':
				opts.xid = (xid_t) atoi(optarg);
				break;
			
			case 'u':
				opts.uid = (uid_t) atoi(optarg);
				break;
			
			case 'v':
				opts.verbose = true;
				break;
			
			case 'q':
				opts.quiet = true;
				break;
			
			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				return 1;
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
	
	struct vcmd_vx_info_v0 info;
	
	if (cmds.create) {
		if (vc_vx_info(opts.xid, &info) >= 0)
			EXIT("Context already exists", 2);
		
		if (vc_ctx_create(opts.xid) < 0)
			PEXIT("Failed to create context", 2);
	}
	
	if (!cmds.create && vc_vx_info(opts.xid, &info) != 0)
		EXIT("Context does not exist", 2);
	
	if (cmds.migrate)
		if (vc_ctx_migrate(opts.xid) < 0)
			PEXIT("Failed to migrate to context", 2);
	
	if (cmds.setflags || cmds.setcaps)
		SEXIT("Not implemented yet...", 1);
	
	if (opts.uid > 0) {
		if (setuid(opts.uid) < 0)
			PEXIT("Failed to change user id", 3);
		
		if (getuid() != opts.uid)
			SEXIT("getuid() returns wrong user id", 3);
	}
	
	execvp(argv[optind], argv+optind);
	
	return EXIT_SUCCESS;
}
