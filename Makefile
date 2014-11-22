#
# Makefile for tips.c
#

# CC = icc
CC = g++
DEBUG = -ggdb
DATE = `date +%Y%m%d%H%M`

tips: tips.c
	$(CC) tips.c -o tips

debug: tips.c
	$(CC) $(DEBUG) tips.c -o tips.debug

tipscheckfile: tipscheckfile.c
	$(CC) $(DEBUG) tipscheckfile.c -o tipscheckfile

install:
	cp -f tips ~/bin

backup:
	cp -f tips.c /nfs/projnfs/backups/tips/tips.c.$(DATE)
	cp -f Makefile /nfs/projnfs/backups/tips/Makefile.$(DATE)

clean:
	rm *.o
