/***************************************************************************
 *   Copyright 2005 The libvserver Team                                    *
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

#ifndef _MEMCPY_H
#define _MEMCPY_H

#if __WORDSIZE == 64
# define STRALIGN(x) (((unsigned long)x&7)?8-((unsigned long)x&7):0)
#else /* __WORDSIZE == 32 */
# define STRALIGN(x) (((unsigned long)x&3)?4-((unsigned long)x&3):0)
#endif

#define UNALIGNED(x,y) (((unsigned long)x & (sizeof (unsigned long)-1)) ^ ((unsigned long)y & (sizeof (unsigned long)-1)))

static inline
void *Xmemcpy(void *dst, const void *src, size_t n)
{
	void *res = dst;
	unsigned char *c1, *c2;
	int tmp;
	unsigned long  *lx1 = NULL;
	const unsigned long *lx2 = NULL;
	
	if (!UNALIGNED(dst, src) && n > sizeof(unsigned long)) {
		if ((tmp = STRALIGN(dst))) {
			c1 = (unsigned char *) dst;
			c2 = (unsigned char *) src;
			while (tmp-- && n--)
				*c1++ = *c2++;
			
			if (n == (size_t) - 1)
				return (res);
		}
		
		lx1 = (unsigned long *) dst;
		lx2 = (unsigned long *) src;
		
		for (; n >= sizeof(unsigned long); n -= sizeof(unsigned long))
			*lx1++ = *lx2++;
	}
	
	if (n) {
		c1 = (unsigned char *) (lx1?lx1:dst);
		c2 = (unsigned char *) (lx1?lx2:src);
		
		while (n--)
			*c1++ = *c2++;
	}
	
	return (res);
}

#endif /* _MEMCPY_H */
