## Configuration
DESTDIR    =
PREFIX     =/usr/local
AR         =ar
CC         =gcc
CFLAGS     =-Wall -g
CPPFLAGS   =
LIBS       =
PROGRAMS   =ftemplate shp
HEADERS    =ftemplate.h incbin-fp.h
SOURCES    =tools/ftemplate.c
CFLAGS_ALL =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)

## Usual targets.
all:
install: all
	install -d                  $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS)   $(DESTDIR)$(PREFIX)/bin
	install -d                  $(DESTDIR)$(PREFIX)/include
	install -m755 $(HEADERS)    $(DESTDIR)$(PREFIX)/include
clean:
	rm -f $(PROGRAMS)

## Programs.
all: $(PROGRAMS)
shp: ./tools/shp.c $(HEADERS)
	$(CC) -o $@ ./tools/shp.c $(CFLAGS_ALL)
ftemplate: ./tools/ftemplate.c $(HEADERS)
	$(CC) -o $@ ./tools/ftemplate.c $(CFLAGS_ALL)

## -- manpages --
ifneq ($(PREFIX),)
MAN_3=./ftemplate.3 
install: install-man3
install-man3: $(MAN_3)
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp $(MAN_3) $(DESTDIR)$(PREFIX)/share/man/man3
endif
## -- manpages --
## -- license --
ifneq ($(PREFIX),)
install: install-license
install-license: LICENSE
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-ftemplate
	cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-ftemplate
endif
## -- license --
