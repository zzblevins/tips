#
# Makefile for tips.c
#

# CC = icc
CC = g++
DEBUG = -ggdb
DATE = `date +%Y%m%d%H%M`

APP = tips

$(APP): $(APP).c
	$(CC) $(APP).c -o $(APP)

debug: $(APP).c
	$(CC) $(DEBUG) $(APP).c -o $(APP).debug

tipscheckfile: tipscheckfile.c
	$(CC) $(DEBUG) tipscheckfile.c -o tipscheckfile

install:
	cp -f $(APP) ~/bin

backup:
	cp -f $(APP).c /nfs/projnfs/backups/$(APP)/tips.c.$(DATE)
	cp -f Makefile /nfs/projnfs/backups/$(APP)/Makefile.$(DATE)

clean:
	rm -f *.o ; rm $(APP)
