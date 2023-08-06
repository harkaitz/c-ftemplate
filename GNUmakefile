PROJECT=c-ftemplate
VERSION=1.0.0
## Configuration
DESTDIR    =
PREFIX     =/usr/local
AR         =ar
CC         =cc
CFLAGS     =-Wall -g
CPPFLAGS   =
LIBS       =
##
PROGRAMS   =tools/ftemplate tools/shp tools/envsubs
HEADERS    =ftemplate.h
SOURCES    =tools/ftemplate.c
CFLAGS_ALL =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
## -- Usual targets.
all:
install: all
	install -d                  $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS)   $(DESTDIR)$(PREFIX)/bin
	install -d                  $(DESTDIR)$(PREFIX)/include
	install -m755 $(HEADERS)    $(DESTDIR)$(PREFIX)/include
clean:
	rm -f $(PROGRAMS)
## -- Programs.
all: $(PROGRAMS)
tools/shp: tools/shp.c $(HEADERS)
	$(CC) -o $@ tools/shp.c $(CFLAGS_ALL)
tools/ftemplate: tools/ftemplate.c $(HEADERS)
	$(CC) -o $@ tools/ftemplate.c $(CFLAGS_ALL)
tools/envsubs: tools/envsubs.c $(HEADERS)
	$(CC) -o $@ tools/envsubs.c $(CFLAGS_ALL)
## -- BLOCK:license --
install: install-license
install-license: 
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE README.md $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
update: update-license
update-license:
	ssnip README.md
## -- BLOCK:license --
## -- BLOCK:man --
update: update-man
update-man:
	make-h-man update
install: install-man
install-man:
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./ftemplate.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- BLOCK:man --
