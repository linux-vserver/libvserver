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
#define DESCR	"Virtual Host Information Manager"

#define SHORT_OPTS "hVGS:x:"

static const
struct option LONG_OPTS[] = {
	{ "help",    no_argument,       0, 'h' },
	{ "version", no_argument,       0, 'V' },
	{ "get",     no_argument,       0, 'G' },
	{ "set",     required_argument, 0, 'S' },
	{ "xid",     required_argument, 0, 'x' },
	{ 0,0,0,0 }
};

struct commands {
	bool get;
	bool set;
};

struct vhi_name_fields {
	char context[VHI_SIZE];
	char sysname[VHI_SIZE];
	char nodename[VHI_SIZE];
	char release[VHI_SIZE];
	char version[VHI_SIZE];
	char machine[VHI_SIZE];
	char domainname[VHI_SIZE];
};

struct options {
	struct vhi_name_fields vhi;
	xid_t xid;
};

#define GET_VHI_NAME(NAME, PTR) do { \
	if (vx_get_vhi_name(xid, VHIN_ ## NAME, PTR, VHI_SIZE) == -1) \
		PEXIT("Failed to get " #NAME " name", EXIT_COMMAND); \
	} while (0)

static inline
void get_vhi_names(xid_t xid, struct vhi_name_fields *vhi)
{
	GET_VHI_NAME(CONTEXT,    vhi->context);
	GET_VHI_NAME(SYSNAME,    vhi->sysname);
	GET_VHI_NAME(NODENAME,   vhi->nodename);
	GET_VHI_NAME(RELEASE,    vhi->release);
	GET_VHI_NAME(VERSION,    vhi->version);
	GET_VHI_NAME(MACHINE,    vhi->machine);
	GET_VHI_NAME(DOMAINNAME, vhi->domainname);
}

static inline
void print_vhi_names(xid_t xid, struct vhi_name_fields *vhi)
{
	printf("XID: %d\n",        xid);
	printf("Context: %s\n",    vhi->context);
	printf("Sysname: %s\n",    vhi->sysname);
	printf("Nodename: %s\n",   vhi->nodename);
	printf("Release: %s\n",    vhi->release);
	printf("Version: %s\n",    vhi->version);
	printf("Machine: %s\n",    vhi->machine);
	printf("Domainname: %s\n", vhi->domainname);
}

static inline
int format2vhi(char *format, struct vhi_name_fields *vhi)
{
	const char *delim = ",", *tmp = format;
	int i = 0;

	while ((tmp = strpbrk(tmp, delim))) {
		tmp++; /* Skip delimiter */
		i++;
	}

	if (i != 6)
		return EXIT_USAGE;

	strncpy(vhi->context,    strsep(&format, delim), VHI_SIZE);
	strncpy(vhi->sysname,    strsep(&format, delim), VHI_SIZE);
	strncpy(vhi->nodename,   strsep(&format, delim), VHI_SIZE);
	strncpy(vhi->release,    strsep(&format, delim), VHI_SIZE);
	strncpy(vhi->version,    strsep(&format, delim), VHI_SIZE);
	strncpy(vhi->machine,    strsep(&format, delim), VHI_SIZE);
	strncpy(vhi->domainname, strsep(&format, delim), VHI_SIZE);

	return EXIT_SUCCESS;
}

static inline
int set_vhi_name(xid_t xid, int field, char *name)
{
	if (!strlen(name))
		return EXIT_SUCCESS;
	
	if (vx_set_vhi_name(xid, field, name) < 0)
		printf("Failed to set VHI field '%d': %s", field, strerror(field));
	
	return EXIT_SUCCESS;
}

static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <program> <args>*\n"
			"\n"
			"Available commands:\n"
			"    -h,--help               Show this help message\n"
			"    -V,--version            Print version information\n"
			"    -G,--get                Get virtual host information\n"
			"    -S,--set <format>       Set virtual host information described in <format>\n"
			"\n"
			"Available options:\n"
			"    -x,--xid <xid>          The Context ID\n"
			"\n"
			"VHI format string:\n"
			"    <format> = <CN>,<SN>,<NN>,<KR>,<KV>,<MA>,<DN> where\n"
			"                - CN is the context name,\n"
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
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	struct commands cmds = {
		.get		= false,
		.set		= false
	};

	struct options opts = {
		.xid		= XID_SELF
	};

	int c;

	while (1) {
		c = getopt_long(argc, argv, SHORT_OPTS, LONG_OPTS, 0);
		if(c == -1) break;

		switch (c) {
			case 'h':
				cmd_help();
				break;

			case 'V':
				CMD_VERSION(NAME, DESCR);
				break;

			case 'G':
				cmds.get = true;
				break;

			case 'S':
				cmds.set = true;
				if (format2vhi(optarg, &opts.vhi))
					EXIT("Invalid vhi format", EXIT_USAGE);
				break;

			case 'x':
				opts.xid = (xid_t) atoi(optarg);
				break;

			default:
				printf("Try '%s --help' for more information\n", argv[0]);
				exit(EXIT_USAGE);
				break;
		}
	}

	if (getuid() != 0)
		SEXIT("This programm requires root privileges", EXIT_USAGE);

	if (cmds.get) {
		get_vhi_names(opts.xid, &opts.vhi);
		print_vhi_names(opts.xid, &opts.vhi);
	}

	if (cmds.set) {
		printf("context: %s\n", opts.vhi.context);
		set_vhi_name(opts.xid, VHIN_CONTEXT,    opts.vhi.context);
		set_vhi_name(opts.xid, VHIN_SYSNAME,    opts.vhi.sysname);
		set_vhi_name(opts.xid, VHIN_NODENAME,   opts.vhi.nodename);
		set_vhi_name(opts.xid, VHIN_RELEASE,    opts.vhi.release);
		set_vhi_name(opts.xid, VHIN_VERSION,    opts.vhi.version);
		set_vhi_name(opts.xid, VHIN_MACHINE,    opts.vhi.machine);
		set_vhi_name(opts.xid, VHIN_DOMAINNAME, opts.vhi.domainname);
	}

	if (argc > optind)
		execvp(argv[optind], argv+optind);

	exit(EXIT_SUCCESS);
}
