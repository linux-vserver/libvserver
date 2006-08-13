// Copyright 2005-2006 Benedikt Böhm <hollow@gentoo.org>
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

#include <stdint.h>
#include <errno.h>

#include "syscall.h"
#include "vserver.h"

#define __NR_clone 120

/* vserver system call */
_syscall3(int, vserver, uint32_t, cmd, uint32_t, id, void *, data)

/* clone system call (glibc only has a wrapper) */
_syscall5(int, clone, int, flags, void *, child_stack, int *, parent_tidptr,
          struct user_desc *, newtls, int *, child_tidptr)