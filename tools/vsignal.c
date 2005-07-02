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
#include <signal.h>
#include <sys/types.h>

#include "libvserver.h"
#include "tools.h"

#define NAME	"vsignal"
#define DESCR	"Context Signal Helper"

#define SHORT_OPTS "hVKWp:s:x:vq"

static const
struct option LONG_OPTS[] = {
	{ "help",    no_argument,       0, 'h' },
	{ "version", no_argument,       0, 'V' },
	{ "kill",    no_argument,       0, 'K' },
	{ "wait",    no_argument,       0, 'W' },
	{ "pid",     required_argument, 0, 'p' },
	{ "sig",     required_argument, 0, 's' },
	{ "xid",     required_argument, 0, 'x' },
	{ "verbose", no_argument,       0, 'v' },
	{ "quiet",   no_argument,       0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
	bool help;
	bool version;
	bool kill;
	bool wait;
};

struct options {
	pid_t pid;
	int32_t sig;
	xid_t xid;
	bool verbose;
	bool quiet;
};

typedef struct signalmap_f {
	const char *name;
	int num;
} signalmap_f;

static const
struct signalmap_f signalmap[] = {
	{ "ABRT", SIGABRT },
	{ "ALRM", SIGALRM },
	{ "BUS", SIGBUS },
	{ "CHLD", SIGCHLD },
	{ "CONT", SIGCONT },
	{ "FPE", SIGFPE },
	{ "HUP", SIGHUP },
	{ "ILL", SIGILL },
	{ "INT", SIGINT },
	{ "KILL", SIGKILL },
	{ "PIPE", SIGPIPE },
	{ "QUIT", SIGQUIT },
	{ "SEGV", SIGSEGV },
	{ "STOP", SIGSTOP },
	{ "TERM", SIGTERM },
	{ "TSTP", SIGTSTP },
	{ "TTIN", SIGTTIN },
	{ "TTOU", SIGTTOU },
	{ "USR1", SIGUSR1 },
	{ "USR2", SIGUSR2 },
	{ "POLL", SIGPOLL },
	{ "PROF", SIGPROF },
	{ "SYS", SIGSYS },
	{ "TRAP", SIGTRAP },
	{ "URG", SIGURG },
	{ "VTALRM", SIGVTALRM },
	{ "XCPU", SIGXCPU },
	{ "XFSZ", SIGXFSZ }
};

static const int signalmap_s = sizeof signalmap / sizeof signalmap[0];

static inline
int sigcmp(const void *a, const void *b)
{
	return strcasecmp(((const signalmap_f*)a)->name, ((const signalmap_f*)b)->name);
}

static
int str2sig(const char *str)
{
	const signalmap_f signalmap_f = { str, 0 };
	const struct signalmap_f *res = bsearch(
		&signalmap_f,
		signalmap,
		signalmap_s,
		sizeof signalmap_f,
		sigcmp
	);
	
	if (res)
		return res->num;
	
	return 0;
}

static inline
void cmd_help(int rc)
{
	printf("Usage: %s <command> <opts>*\n"
	       "\n"
	       "Available commands:\n"
	       "    -h,--help               Show this help message\n"
	       "    -V,--version            Print version information\n"
	       "    -K,--kill               Kill context of process <pid>\n"
	       "    -W,--wait               Wait until the context has exited\n"
	       "\n"
	       "Available options:\n"
	       "    -p,--pid <pid>          Send signal <sig> to process <pid>\n"
	       "    -s,--sig <sig>          Send signal <sig> to process <pid>\n"
	       "    -x,--xid <xid>          The Context ID\n"
	       "\n"
	       "Generic options:\n"
	       "    -v,--verbose            Print verbose information\n"
	       "    -q,--quiet              Be quiet\n"
	       "\n",
	       NAME);
	exit(rc);
}

int main(int argc, char *argv[])
{
	if (getuid() != 0)
		EXIT("This programm requires root privileges", 1);
	
	struct commands cmds = {
		.help		= false,
		.version	= false,
		.kill		= false,
		.wait		= false
	};
	
	struct options opts = {
		.pid		= (pid_t) 0,
		.sig		= (int32_t) SIGKILL,
		.xid		= (xid_t) 1,
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
			
			case 'K':
				cmds.kill = true;
				cmdcnt++;
				break;
			
			case 'W':
				cmds.wait = true;
				cmdcnt++;
				break;
			
			case 'p':
				opts.pid = (pid_t) atoi(optarg);
				break;
			
			case 's':
				opts.sig = (int32_t) str2sig(optarg);
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
				return EXIT_FAILURE;
				break;
		}
	}
	
	if (cmdcnt == 0)
		EXIT("No command given", 1);
	
	if (cmdcnt > 1)
		EXIT("More than one command given", 1);
	
	if (opts.xid <= 1)
		if ((opts.xid = vc_task_xid(opts.pid)) <= 1)
			EXIT("Invalid --xid given", 1);
	
	if (cmds.kill) {
		struct vcmd_ctx_kill_v0 ctxkill = {
			.pid = (int32_t) opts.pid,
			.sig = (int32_t) opts.sig
		};
		
		if (vc_ctx_kill(opts.xid, &ctxkill) < 0)
			PEXIT("Failed to kill process/context", 2);
	}
	
	if (cmds.wait)
		EXIT("Not implemented yet...", 1);
	
	return EXIT_FAILURE;
}
