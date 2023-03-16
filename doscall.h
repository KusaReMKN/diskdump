#
/*
 * DOSCALL.H -- Wrapper functions for DOS-specific functions
 */

#ifndef MKN_DOSCALL_H
#define MKN_DOSCALL_H	1

#include <dos.h>

unsigned dosAllocMem(unsigned paragraphs);
int	dosClose(int handle);
int	dosCreat(const char *path, unsigned attr);
int	dosFreeMem(unsigned segment);
int	dosGetDiskFree(int drive, struct diskfree_t *diskSpace);
int	dosReadDisk(int drive, void __far *buffer,
		unsigned sector, unsigned first);
int	dosWrite(int handle, void const __far *buffer, unsigned count);

#endif	/* MKN_DOSCALL_H */
