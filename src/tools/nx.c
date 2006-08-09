// Copyright 2006 Benedikt Böhm <hollow@gentoo.org>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the
// Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "tools.h"
#include "vserver.h"

static const char *rcsid = "$Id: nx.c 294 2006-07-09 08:46:15Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "create",    1, 0, 0x10 },
	{ "migrate",   1, 0, 0x11 },
	{ "set-flags", 1, 0, 0x12 },
	{ "get-flags", 1, 0, 0x13 },
	{ "add-addr",  1, 0, 0x14 },
	{ "rem-addr",  1, 0, 0x15 },
	{ NULL,        0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	          "nx -create    <nid> [<list>] [-- <program> <args>*]\n"
	          "   -migrate   <nid> -- <program> <args>*\n"
	          "   -set-flags <nid> <list>\n"
	          "   -get-flags <nid>\n"
	          "   -add-addr  <nid> <addr>/<netmask>*\n"
	          "   -rem-addr  <nid> <addr>/<netmask>*\n");
	exit(rc);
}

static
int str_to_addr(char *str, uint32_t *ip, uint32_t *mask)
{
	struct in_addr ib;
	char *addr_ip, *addr_mask;
	
	*ip   = 0;
	*mask = 0;
	
	addr_ip   = strtok(str, "/");
	addr_mask = strtok(NULL, "/");
	
	if (addr_ip == 0)
		return -1;
	
	if (inet_aton(addr_ip, &ib) == -1)
		return -1;
	
	*ip = ib.s_addr;
	
	if (addr_mask == 0) {
		/* default to /24 */
		*mask = ntohl(0xffffff00);
	} else {
		if (strchr(addr_mask, '.') == 0) {
			/* We have CIDR notation */
			int sz = atoi(addr_mask);
			
			for (*mask = 0; sz > 0; --sz) {
				*mask >>= 1;
				*mask  |= 0x80000000;
			}
			
			*mask = ntohl(*mask);
		} else {
			/* Standard netmask notation */
			if (inet_aton(addr_mask, &ib) == -1)
				return -1;
			
			*mask = ib.s_addr;
		}
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	INIT_ARGV0
	
	int c, i;
	nid_t nid = 0;
	char *buf;
	
	/* syscall data */
	struct nx_create_flags cf = {
		.flags = 0,
	};
	
	struct nx_flags flags = {
		.flags = 0,
		.mask  = 0,
	};
	
	struct nx_addr addr;
	
	uint64_t mask;
	
#define CASE_GOTO(ID, P) case ID: nid = atoi(optarg); goto P; break
	
	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES
			
			CASE_GOTO(0x10, create);
			CASE_GOTO(0x11, migrate);
			CASE_GOTO(0x12, setflags);
			CASE_GOTO(0x13, getflags);
			CASE_GOTO(0x14, addaddr);
			CASE_GOTO(0x15, remaddr);
			
			DEFAULT_GETOPT_CASES
		}
	}
	
#undef CASE_GOTO
	
	goto usage;
	
create:
	if (argc > optind && strcmp(argv[optind], "--") != 0)
		if (flist64_from_str(argv[optind], nflags_list, &cf.flags, &mask, '~', ',') == -1)
			perr("flist64_from_str");
	
	if (nx_create(nid, &cf) == -1)
		perr("nx_create");
	
	if (argc > optind+1)
		execvp(argv[optind+1], argv+optind+1);
	
	goto out;

migrate:
	if (nx_migrate(nid) == -1)
		perr("nx_migrate");
	
	if (argc > optind+1)
		execvp(argv[optind+1], argv+optind+1);
	
	goto out;
	
setflags:
	if (argc <= optind)
		goto usage;
	
	if (flist64_from_str(argv[optind], nflags_list, &flags.flags, &flags.mask, '~', ',') == -1)
		perr("flist64_from_str");
	
	if (nx_set_flags(nid, &flags) == -1)
		perr("nx_set_flags");
	
	goto out;
	
getflags:
	if (nx_get_flags(nid, &flags) == -1)
		perr("nx_get_flags");
	
	if (!(buf = flist64_to_str(nflags_list, flags.flags, '\n')))
		perr("flist64_to_str");
	
	printf("%s", buf);
	free(buf);
	
	goto out;
	
addaddr:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		addr.type  = NXA_TYPE_IPV4;
		addr.count = 1;
		
		if (str_to_addr(argv[i], &addr.ip[0], &addr.mask[0]) == -1)
			perr("str_to_addr");
		
		if (nx_add_addr(nid, &addr) == -1)
			perr("nx_add_addr");
	}
	
	goto out;
	
remaddr:
	if (argc <= optind)
		goto usage;
	
	for (i = optind; argc > i; i++) {
		addr.type  = NXA_TYPE_IPV4;
		addr.count = 1;
		
		if (str_to_addr(argv[i], &addr.ip[0], &addr.mask[0]) == -1)
			perr("str_to_addr");
		
		if (nx_rem_addr(nid, &addr) == -1)
			perr("nx_rem_addr");
	}
	
	goto out;
	
usage:
	usage(EXIT_FAILURE);

out:
	exit(EXIT_SUCCESS);
}
