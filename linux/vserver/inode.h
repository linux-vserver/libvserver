#ifndef _VX_INODE_H
#define _VX_INODE_H


#define IATTR_TAG	0x01000000

#define IATTR_ADMIN	0x00000001
#define IATTR_WATCH	0x00000002
#define IATTR_HIDE	0x00000004
#define IATTR_FLAGS	0x00000007

#define IATTR_BARRIER	0x00010000
#define IATTR_IUNLINK	0x00020000
#define IATTR_IMMUTABLE 0x00040000


/* inode ioctls */

#define FIOC_GETXFLG	_IOR('x', 5, long)
#define FIOC_SETXFLG	_IOW('x', 6, long)

#else	/* _VX_INODE_H */
#warning duplicate inclusion
#endif	/* _VX_INODE_H */
