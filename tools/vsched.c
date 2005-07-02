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
#include <errno.h>
#include <getopt.h>
#include <sys/types.h>

#include "libvserver.h"
#include "tools.h"

#define NAME    "vsched"
#define DESCR   "Context CPU Limit Manager"

#define SHORT_OPTS "hVx:b:vq"

static const
struct option LONG_OPTS[] = {
	{ "help",    no_argument,       0, 'h' },
	{ "version", no_argument,       0, 'V' },
	{ "xid",     required_argument, 0, 'x' },
	{ "bucket",  required_argument, 0, 'b' },
	{ "verbose", no_argument,       0, 'v' },
	{ "quiet",   no_argument,       0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
	bool help;
	bool version;
};

struct options {
	xid_t xid;
	struct vcmd_set_sched_v3 *bucket;
	bool verbose;
	bool quiet;
};

#define SETBUCKET(ATTR,MASK) \
	if ((bucket->ATTR = (int32_t) atol(strsep(&format, delim))) > 0) \
		bucket->set_mask |= MASK;

static inline
void format2bucket(char *format, struct vcmd_set_sched_v3 *bucket)
{
	const char *delim = ",";
	SETBUCKET(fill_rate,     VXSM_FILL_RATE);
	SETBUCKET(interval,      VXSM_INTERVAL);
	SETBUCKET(tokens,        VXSM_TOKENS);
	SETBUCKET(tokens_min,    VXSM_TOKENS_MIN);
	SETBUCKET(tokens_max,    VXSM_TOKENS_MAX);
	SETBUCKET(priority_bias, VXSM_PRIO_BIAS);
}

void cmd_help()
{
	printf("Usage: %s [<command>] <opts>* -- <programm> <args>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "\n"
	       "Available options:\n"
	       "    -x,--xid <xid>          Context ID\n"
	       "    -b,--bucket <format>    Create a bucket described in <format>\n"
	       "\n"
	       "Generic options:\n"
	       "    -v,--verbose            Print verbose information\n"
	       "    -q,--quiet              Be quiet\n"
	       "\n"
	       "Tocken Bucket format string:\n"
	       "    <format> = <FR>,<IV>,<TK>,<TI>,<TA>,<PB> where\n"
	       "                - FR is the fill rate,\n"
	       "                - IV is the interval between fills,\n"
	       "                - TK is the number of tokens in the bucket,\n"
	       "                - TI is the minimum number of tokens to unhold the context,\n"
	       "                - TA is the maximum number of tokens in the bucket, and\n"
	       "                - PB is the priority bias (currently unused).\n"
	       "\n",
	       NAME);
}

int main(int argc, char *argv[])
{
	if (getuid() != 0)
		EXIT("This program requires root privileges", 1);

	struct commands cmds = {
		.help    = false,
		.version = false,
	};
	
	struct vcmd_set_sched_v3 bucket = {
		.set_mask = 0
	};
	
	struct options opts = {
		.xid     = (xid_t) 1,
		.bucket  = &bucket,
		.verbose = false,
		.quiet   = false
	};
	
	int c;
	
	while (1) {
		c = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS, 0);
		if(c == -1) break;
		
		switch (c) {
			case 'h':
				cmd_help(0);
				break;
			
			case 'V':
				CMD_VERSION;
				break;
			
			case 'x':
				opts.xid = (xid_t) atoi(optarg);
				break;
			
			case 'b':
				format2bucket(optarg, opts.bucket);
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
	
	if (opts.xid <= 1)
		if ((opts.xid = vc_task_xid(0)) <= 1)
			EXIT("Invalid --xid given", 1);
	
	if (argc <= optind)
		EXIT("No program given", 1);
	
	if (opts.bucket->set_mask == 0)
		EXIT("You need to specify at least one option in the bucket", 1);
	
	if (vc_set_sched(opts.xid, opts.bucket) < 0)
		PEXIT("Failed to set resource limits", 2);
	
	execvp(argv[optind], argv+optind);
	
	return EXIT_SUCCESS;
}
