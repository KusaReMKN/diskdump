CC=	WCL
CFLAGS=	-3 -bcl=COM -Ox

all:	DISKDUMP.COM

DISKDUMP.COM: MAIN.C DOSCALL.C FATAL.C
	$(CC) $(CFLAGS) -fe=DISKDUMP.COM MAIN.C DOSCALL.C FATAL.C

clean:
	ERASE DISKDUMP.COM
	ERASE *.OBJ
