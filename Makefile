## Configuration
DESTDIR    =
PREFIX     =/usr/local
AR         =ar
CC         =gcc
CFLAGS     =-Wall -g
CPPFLAGS   =
LIBS       =
## Sources and targets
PROGRAMS   =ftemplate shp
HEADERS    =ftemplate.h
MARKDOWNS  =ftemplate.3.md README.md
MANPAGES_3 =ftemplate.3
SOURCES    =tools/ftemplate.c
## AUXILIARY
CFLAGS_ALL =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)

## STANDARD TARGETS
all: $(PROGRAMS)
help:
	@echo "all     : Build everything."
	@echo "clean   : Clean files."
	@echo "install : Install all produced files."
install: all
	install -d                  $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS)   $(DESTDIR)$(PREFIX)/bin
	install -d                  $(DESTDIR)$(PREFIX)/include
	install -m755 $(HEADERS)    $(DESTDIR)$(PREFIX)/include
	install -d                  $(DESTDIR)$(PREFIX)/share/man/man3
	install -m644 $(MANPAGES_3) $(DESTDIR)$(PREFIX)/share/man/man3
clean:
	rm -f $(PROGRAMS)

shp: ./tools/shp.c $(HEADERS)
	$(CC) -o $@ ./tools/shp.c $(CFLAGS_ALL)
ftemplate: ./tools/ftemplate.c $(HEADERS)
	$(CC) -o $@ ./tools/ftemplate.c $(CFLAGS_ALL)
