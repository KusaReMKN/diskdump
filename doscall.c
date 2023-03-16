#
/*
 * DOSCALL.C -- Wrapper functions for DOS-specific functions
 */

#include <ctype.h>
#include <dos.h>
#include <i86.h>
#include <stdio.h>	/* for debug */
#include <stdlib.h>

#include "fatal.h"

unsigned
dosAllocMem(unsigned paragraphs)
{
	unsigned segment;

	if (_dos_allocmem(paragraphs, &segment) != 0)
		fatal(EXIT_FAILURE, "dosAllocMem");

	return segment;
}

int
dosClose(int handle)
{
	if (_dos_close(handle) != 0)
		fatal(EXIT_FAILURE, "dosClose");

	return 0;
}

int
dosCreat(const char *path, unsigned attr)
{
	int handle;

	if (_dos_creat(path, attr, &handle) != 0)
		fatal(EXIT_FAILURE, "dosCreat (%s)", path);

	return handle;
}

int
dosFreeMem(unsigned segment)
{
	if (_dos_freemem(segment) != 0)
		fatal(EXIT_FAILURE, "dosFreeMem");

	return 0;
}

int
dosGetDiskFree(int drive, struct diskfree_t *diskSpace)
{
	unsigned error;

	drive = toupper(drive) - '@';	/* A: = 1, B: = 2, ... */
	if (_dos_getdiskfree(drive, diskSpace) != 0)
		fatal(EXIT_FAILURE, "dosGetDiskFree (%c:)", drive + '@');

	return 0;
}

int
dosReadDisk(int drive, void __far *buffer, unsigned sector, unsigned first)
{
	unsigned flags;

	drive = toupper(drive) - 'A';	/* A: = 0, B: = 1, ... */
	__asm {
		PUSH	DS;
		MOV	AX, drive;
		MOV	CX, sector;
		MOV	DX, first;
		LDS	BX, buffer;
		INT	25H;
		POP	DX;	/* Discard */
		POP	DS;
		PUSHF;
		POP	flags;
	}
	if (flags & INTR_CF)
		return -1;

	return 0;
}

int
dosWrite(int handle, void const __far *buffer, unsigned count)
{
	unsigned written;

	if (_dos_write(handle, buffer, count, &written) != 0)
		fatal(EXIT_FAILURE, "dosWrite");
	if (written != count)
		fatal(EXIT_FAILURE, "dosWrite");

	return 0;
}
