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

#define CMD_VERSION(name, version, desc) do { \
	printf("%s %s -- %s\n", name, version, desc); \
	printf("This program is part of libvserver\n\n"); \
	\
	printf("Copyright (c) 2005 Benedikt Boehm <hollow@gentoo.org>\n"); \
	printf("This program is free software; you can redistribute it and/or\n"); \
	printf("modify it under the terms of the GNU General Public License\n"); \
}	while(0)

/* exit, silent exit, perror exit
 *
 * exit code conventions:
 * 
 * 0 = OK
 * 1 = Wrong usage
 * 2 = A command failed
 * 3 = An opts specific function failed
 */
#define EXIT(MSG,RC) { \
	printf(MSG"; try '%s --help' for more information\n", argv[0]); \
	exit(RC); \
}

#define SEXIT(MSG,RC) { \
	printf(MSG"\n"); \
	exit(RC); \
}

#define PEXIT(MSG,RC) { \
	perror(MSG); \
	exit(RC); \
}
