#
/*
 * DISKDUMP.C -- A diskette image generator
 */

#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "doscall.h"
#include "fatal.h"

static int	verbose;

static void	usage(void);

int
main(int argc, char *argv[])
{
	int c, drive, handle;
	struct diskfree_t df;
	unsigned long i, totalBytes, totalSectors;
	unsigned j, paragraphs, segment;
	char __far *buffer;

	while ((c = getopt(argc, argv, "Vv")) != -1)
		switch (c) {
		case 'V':
		case 'v':
			verbose = 1;
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	if (!isalpha(argv[0][0]) && argv[0][1] != '\0' && argv[0][1] != ':')
		errno = EINVAL, fatal(EXIT_FAILURE, "%s", argv[0]);
	drive = argv[0][0];
	dosGetDiskFree(drive, &df);
	totalSectors = (unsigned long)df.sectors_per_cluster
						* df.total_clusters;
	totalBytes   = (unsigned long)df.bytes_per_sector
						* totalSectors;
	verbose && printf("Drive (%c:) summary:\n", drive);
	verbose && printf("    Total Clusters:%10u\n" , df.total_clusters);
	verbose && printf("    Total Sectors :%10lu\n", totalSectors);
	verbose && printf("    Total Bytes   :%10lu\n\n", totalBytes);

	paragraphs = (df.bytes_per_sector >> 4) + 1;
	segment = dosAllocMem(paragraphs);
	buffer = MK_FP(segment, 0x0000);
	verbose && printf("Allocated Memory:\n");
	verbose && printf("    Total Paragraphs:%10u\n", paragraphs);
	verbose && printf("    Segment Address :    %#04x\n\n", segment);

	handle = dosCreat(argv[1], 0);

	for (i = 0; i < totalSectors; i++) {
		for (j = 0; j < df.bytes_per_sector; j += sizeof(long))
			*(long __far *)&buffer[j] = 0;
		if (dosReadDisk(drive, buffer, 1, i) != 0)
			verbose && printf("\nError Sector: %lu\n", i);
		dosWrite(handle, buffer, df.bytes_per_sector);
		_dos_commit(handle);
		verbose && printf("\r%lu / %lu ...", i, totalSectors);
		fflush(stdout);
	}
	verbose && printf("\r%lu / %lu Done.\n", totalSectors, totalSectors);

	dosClose(handle);

	dosFreeMem(segment);

	return 0;
}

static void
usage(void)
{
	fprintf(stderr, "Usage: DISKDUMP [/V] drive: filename\n");
	exit(EXIT_FAILURE);
}
