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

#include <getopt.h>

#include <lucid/flist.h>

#define COMMON_LONG_OPTS \
	{ "help",    0, 0, 0x01 }, \
	{ "version", 0, 0, 0x02 },

#define COMMON_GETOPT_CASES \
	case 0x01: usage(EXIT_SUCCESS); break; \
	case 0x02: printf("%s\n", rcsid); exit(EXIT_SUCCESS); break;

#define DEFAULT_GETOPT_CASES default: usage(EXIT_FAILURE); break;

#define GETOPT(VAL) ((VAL = getopt_long_only(argc, argv, "", long_opts, NULL)) != -1)

/* lists.c */
extern const flist32_t ix_attr_list[];
extern const flist64_t nx_flags_list[];
extern const flist32_t nx_sock_list[];
extern const flist64_t vx_bcaps_list[];
extern const flist64_t vx_ccaps_list[];
extern const flist64_t vx_cflags_list[];
extern const flist32_t vx_limit_list[];
extern const flist64_t vx_mflags_list[];
extern const flist32_t vx_sched_list[];
extern const flist32_t vx_uname_list[];
