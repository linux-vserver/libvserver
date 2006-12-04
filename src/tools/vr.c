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
#include <inttypes.h>
#include <sys/ioctl.h>

#define _LUCID_PRINTF_MACROS
#include <lucid/log.h>
#include <lucid/open.h>
#include <lucid/printf.h>
#include <lucid/str.h>

#include "tools.h"
#include "vserver.h"

#ifndef VROOT_SET_DEV
#define VROOT_SET_DEV 0x5600
#endif

#ifndef VROOT_CLR_DEV
#define VROOT_CLR_DEV 0x5601
#endif

static const char *rcsid = "$Id: vr.c 238 2006-06-30 06:37:25Z hollow $";

static
struct option long_opts[] = {
	COMMON_LONG_OPTS
	{ "set",   1, 0, 0x10 },
	{ "clear", 1, 0, 0x11 },
	{ NULL,    0, 0, 0 },
};

static inline
void usage(int rc)
{
	printf("Usage:\n\n"
	          "vr -set   <dev> <realdev>\n"
	          "   -clear <dev>\n");
	exit(rc);
}

int main(int argc, char *argv[])
{
	int c, fd, realfd, rc = EXIT_SUCCESS;
	char *dev;
	
	/* logging */
	log_options_t log_options = {
		.ident  = argv[0],
		.stderr = true,
	};
	
	log_init(&log_options);
	
#define CASE_GOTO(ID, P) case ID: dev = optarg; goto P; break
	
	/* parse command line */
	while (GETOPT(c)) {
		switch (c) {
			COMMON_GETOPT_CASES
			
			CASE_GOTO(0x10, set);
			CASE_GOTO(0x11, clear);
			
			DEFAULT_GETOPT_CASES
		}
	}
	
#undef CASE_GOTO
	
	goto usage;
	
set:
	if (argc <= optind)
		goto usage;
	
	if ((fd = open_read(dev)) == -1)
		rc = log_perror("open_read");
	
	else if ((realfd = open_read(argv[optind])) == -1) {
		close(fd);
		rc = log_perror("open_read");
	}
	
	else {
		/* TODO: vr.c:97: warning: cast to pointer from integer of different size */
		if (ioctl(fd, VROOT_SET_DEV, (void *)realfd) == -1)
			rc = log_perror("ioctl");
		
		close(realfd);
		close(fd);
	}
	
	goto out;
	
clear:
	fd = open_read(dev);
	
	if (fd == -1)
		rc = log_perror("open_read");
	
	else {
		if (ioctl(fd, VROOT_CLR_DEV, 0) == -1)
			rc = log_perror("ioctl");
		
		close(fd);
	}
	
	goto out;
	
usage:
	usage(EXIT_FAILURE);

out:
	exit(rc);
}
