PROJECT =c-ftemplate
VERSION =1.0.0
DESTDIR =
PREFIX  =/usr/local
AR      =ar
CC      =gcc -pedantic-errors -std=c99 -Wall
PROGRAMS=ftemplate$(EXE) shp$(EXE) envsubs$(EXE)
HEADERS =ftemplate.h
SOURCES =tools/ftemplate.c
##
all: $(PROGRAMS)
install:
	@install -d $(DESTDIR)$(PREFIX)/bin
	@install -d $(DESTDIR)$(PREFIX)/include
	install -m755 $(PROGRAMS) $(DESTDIR)$(PREFIX)/bin
	install -m755 $(HEADERS)  $(DESTDIR)$(PREFIX)/include
clean:
	rm -f $(PROGRAMS)
shp$(EXE): tools/shp.c $(HEADERS)
	$(CC) -o $@ tools/shp.c $(CFLAGS)
ftemplate$(EXE): tools/ftemplate.c $(HEADERS)
	$(CC) -o $@ tools/ftemplate.c $(CFLAGS)
envsubs$(EXE): tools/envsubs.c $(HEADERS)
	$(CC) -o $@ tools/envsubs.c $(CFLAGS)
## -- BLOCK:license --
install: install-license
install-license: 
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE  $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
## -- BLOCK:license --
## -- BLOCK:man --
install: install-man
install-man:
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./ftemplate.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- BLOCK:man --
