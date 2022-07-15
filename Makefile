## Configuration
DESTDIR    =
PREFIX     =/usr/local
AR         =ar
CC         =gcc
CFLAGS     =-Wall -g
CPPFLAGS   =
LIBS       =
PROGRAMS   =ftemplate shp
HEADERS    =ftemplate.h
SOURCES    =tools/ftemplate.c
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
clean:
	rm -f $(PROGRAMS)

shp: ./tools/shp.c $(HEADERS)
	$(CC) -o $@ ./tools/shp.c $(CFLAGS_ALL)
ftemplate: ./tools/ftemplate.c $(HEADERS)
	$(CC) -o $@ ./tools/ftemplate.c $(CFLAGS_ALL)
