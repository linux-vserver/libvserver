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
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <sys/types.h>

#include "vserver.h"
#include "tools.h"

#define NAME	"vuname"
#define DESCR	"uts virtualization tool"

#define VHI_LENGTH 65

#define SHORT_OPTS "hViGI:x:vq"

struct option const
LONG_OPTS[] = {
	{ "help",		no_argument, 		0, 'h' },
	{ "version",	no_argument, 		0, 'V' },
	{ "get",		no_argument, 		0, 'G' },
	{ "set",		required_argument,	0, 'I' },
	{ "xid",		required_argument,	0, 'x' },
	{ "verbose",	no_argument, 		0, 'v' },
	{ "quiet",		no_argument, 		0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
	bool help;
	bool version;
	bool get;
	bool set;
};

struct vhifields {
	char context[VHI_LENGTH];
	char sysname[VHI_LENGTH];
	char nodename[VHI_LENGTH];
	char release[VHI_LENGTH];
	char version[VHI_LENGTH];
	char machine[VHI_LENGTH];
	char domainname[VHI_LENGTH];
};

struct options {
	struct vhifields vhifields;
	xid_t xid;
	bool verbose;
	bool quiet;
};

/* TODO Reduce code... */
void get_vhi_names(xid_t xid, struct vhifields *vhi)
{
	if (vx_get_vhi_name(xid, VHIN_CONTEXT, vhi->context, VHI_LENGTH) == -1)
		PEXIT("Failed to get context name", 2);

	if (vx_get_vhi_name(xid, VHIN_SYSNAME, vhi->sysname, VHI_LENGTH) == -1)
		PEXIT("Failed to get sysname", 2);

	if (vx_get_vhi_name(xid, VHIN_NODENAME, vhi->nodename, VHI_LENGTH) == -1)
		PEXIT("Failed to get nodename", 2);

	if (vx_get_vhi_name(xid, VHIN_RELEASE, vhi->release, VHI_LENGTH) == -1)
		PEXIT("Failed to get release", 2);

	if (vx_get_vhi_name(xid, VHIN_VERSION, vhi->version, VHI_LENGTH) == -1)
		PEXIT("Failed to get version", 2);

	if (vx_get_vhi_name(xid, VHIN_MACHINE, vhi->machine, VHI_LENGTH) == -1)
		PEXIT("Failed to get machine name", 2);

	if (vx_get_vhi_name(xid, VHIN_DOMAINNAME, vhi->domainname, VHI_LENGTH) == -1)
		PEXIT("Failed to get domainname", 2);
}

void print_vhi_names(xid_t xid, struct vhifields *vhi)
{
	printf("XID: %d\n", xid);
	printf("Context: %s\n", vhi->context);
	printf("Sysname: %s\n", vhi->sysname);
	printf("Nodename: %s\n", vhi->nodename);
	printf("Release: %s\n", vhi->release);
	printf("Version: %s\n", vhi->version);
	printf("Machine: %s\n", vhi->machine);
	printf("Domain name: %s\n", vhi->domainname);
}

	static inline
int format2vhifields(char *format, struct vhifields *vhifields)
{
	const char *delim = ",", *tmp = format;
	int i = 0;

	while ((tmp = strpbrk(tmp, delim))) {
		tmp++; /* Skip delimiter */
		i++;
	}

	if (i != 6)
		return -1;

	strncpy(vhifields->context, strsep(&format, delim), VHI_LENGTH);
	strncpy(vhifields->sysname, strsep(&format, delim), VHI_LENGTH);
	strncpy(vhifields->nodename, strsep(&format, delim), VHI_LENGTH);
	strncpy(vhifields->release, strsep(&format, delim), VHI_LENGTH);
	strncpy(vhifields->version, strsep(&format, delim), VHI_LENGTH);
	strncpy(vhifields->machine, strsep(&format, delim), VHI_LENGTH);
	strncpy(vhifields->domainname, strsep(&format, delim), VHI_LENGTH);

	return 0;
}

	static inline
int set_vhiname(xid_t xid, int field, char *name)
{
	if (!strlen(name))
		return 0;

	if (vx_set_vhi_name(xid, field, name) < 0)
		PEXIT(strcat(strcat("Failed to set VHI field (", (char*) field), ")"), 2);
}

	static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <programm> <args>*\n"
			"\n"
			"Available commands:\n"
			"    -h,--help               Show this help message\n"
			"    -V,--version            Print version information\n"
			"    -G,--get             Get virtual host information\n"
			"    -I,--set <format>    Set virtual host information aka UTS described in <format>\n"
			"\n"
			"Available options:\n"
			"    -x,--xid <xid>          The Context ID\n"
			"\n"
			"Generic options:\n"
			"    -v,--verbose            Print verbose information\n"
			"    -q,--quiet              Be quiet (i.e. no output at all)\n"
			"\n"
			"VHI format string:\n"
			"    <format> = <CN>,<SN>,<NN>,<KR>,<KV>,<MA>,<DN> where\n"
			"                - CN is the context name\n"
			"                - SN is the system name,\n"
			"                - NN is the network node hostname,\n"
			"                - KR is the kernel release,\n"
			"                - KV is the kernel version,\n"
			"                - MA is the hardware machine, and\n"
			"                - DN is the network node domain name.\n"
			"\n"
			"    Empty fields cause the value to be left the same as before\n"
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
		.get		= false,
		.set		= false
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

			case 'G':
				cmds.get = true;
				cmdcnt++;
				break;

			case 'I':
				cmds.set = true;
				if (format2vhifields(optarg, &opts.vhifields))
					EXIT("Invalid vhi format", 1);
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
				return EXIT_FAILURE;
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

	if (cmds.get) {
		get_vhi_names(opts.xid, &opts.vhifields);
		print_vhi_names(opts.xid, &opts.vhifields);
	}

	if (cmds.set) {
		set_vhiname(opts.xid, VHIN_CONTEXT, opts.vhifields.context);
		set_vhiname(opts.xid, VHIN_SYSNAME, opts.vhifields.sysname);
		set_vhiname(opts.xid, VHIN_NODENAME, opts.vhifields.nodename);
		set_vhiname(opts.xid, VHIN_RELEASE, opts.vhifields.release);
		set_vhiname(opts.xid, VHIN_VERSION, opts.vhifields.version);
		set_vhiname(opts.xid, VHIN_MACHINE, opts.vhifields.machine);
		set_vhiname(opts.xid, VHIN_DOMAINNAME, opts.vhifields.domainname);
	}

	if (argc > optind)
		execvp(argv[optind], argv+optind);

	return EXIT_SUCCESS;
}
