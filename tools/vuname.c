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

#define NAME	"vuname"
#define VERSION	"0.1"
#define DESCR	"uts virtualization tool"

#define VHI_LENGTH 65

#define SHORT_OPTS "hVI:x:vq"

struct option const
LONG_OPTS[] = {
	{ "help",		no_argument, 		0, 'h' },
	{ "version",	no_argument, 		0, 'V' },
	{ "setvhi",		required_argument,	0, 'I' },
	{ "xid",		required_argument,	0, 'x' },
	{ "verbose",	no_argument, 		0, 'v' },
	{ "quiet",		no_argument, 		0, 'q' },
	{ 0,0,0,0 }
};

struct commands {
	bool help;
	bool version;
	bool setvhi;
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

	static inline
int format2vhifields(char *format, struct vhifields *vhifields)
{
	const char *delim = ",", *tmp = format;
	int i = 0;

	while (tmp = strpbrk(tmp, delim)) {
		tmp++; /* Skip delimiter */
		i++;
	}

	if (i != 5)
		return -1;

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
	if (strlen(name) <= 0)
		return 0;

	struct vcmd_vx_vhi_name_v0 vhiname;

	if (field != 0) {
		vhiname.field = field;
		strcpy(vhiname.name, name);
		if (vc_set_vhi_name(xid, &vhiname) < 0)
			PEXIT(strcat(strcat("Failed to set VHI field (", (char*) vhiname.field), ")"), 2);
	}
}

	static inline
void cmd_help()
{
	printf("Usage: %s <command> <opts>* -- <programm> <args>*\n"
			"\n"
			"Available commands:\n"
			"    -h,--help               Show this help message\n"
			"    -V,--version            Print version information\n"
			"    -I,--setvhi <format>    Set virtual host information aka UTS described in <format>\n"
			"\n"
			"Available options:\n"
			"    -x,--xid <xid>          The Context ID\n"
			"\n"
			"Generic options:\n"
			"    -v,--verbose            Print verbose information\n"
			"    -q,--quiet              Be quiet (i.e. no output at all)\n"
			"\n"
			"VHI format string:\n"
			"    <format> = <SN>,<NN>,<KR>,<KV>,<MA>,<DN> where\n"
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
		.setvhi		= false
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
				CMD_VERSION;
				break;

			case 'I':
				cmds.setvhi = true;
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
		if ((opts.xid = vc_task_xid(0)) <= 1)
			EXIT("Invalid --xid given", 1);

	if (argc <= optind)
		EXIT("No program given", 1);

	if (cmds.setvhi) {
		set_vhiname(opts.xid, VHIN_SYSNAME, opts.vhifields.sysname);
		set_vhiname(opts.xid, VHIN_NODENAME, opts.vhifields.nodename);
		set_vhiname(opts.xid, VHIN_RELEASE, opts.vhifields.release);
		set_vhiname(opts.xid, VHIN_VERSION, opts.vhifields.version);
		set_vhiname(opts.xid, VHIN_MACHINE, opts.vhifields.machine);
		set_vhiname(opts.xid, VHIN_DOMAINNAME, opts.vhifields.domainname);
	}

	execvp(argv[optind], argv+optind);

	return EXIT_SUCCESS;
}
