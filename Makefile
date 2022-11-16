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

## Usual targets.
all:
install: all
	@echo "I bin/ $(PROGRAMS)"
	@install -d                  $(DESTDIR)$(PREFIX)/bin
	@install -m755 $(PROGRAMS)   $(DESTDIR)$(PREFIX)/bin
	@echo "I include/ $(HEADERS)"
	@install -d                  $(DESTDIR)$(PREFIX)/include
	@install -m755 $(HEADERS)    $(DESTDIR)$(PREFIX)/include
clean:
	@echo "D $(PROGRAMS)"
	@rm -f $(PROGRAMS)

## Programs.
all: $(PROGRAMS)
shp: ./tools/shp.c $(HEADERS)
	@echo "B $@ $^"
	@$(CC) -o $@ ./tools/shp.c $(CFLAGS_ALL)
ftemplate: ./tools/ftemplate.c $(HEADERS)
	@echo "B $@ $^"
	@$(CC) -o $@ ./tools/ftemplate.c $(CFLAGS_ALL)

## -- manpages --
install: install-man3
install-man3:
	@echo 'I share/man/man3/'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/ftemplate.3'
	@cp ./ftemplate.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- manpages --
## -- license --
install: install-license
install-license: LICENSE
	@echo 'I share/doc/c-ftemplate/LICENSE'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-ftemplate
	@cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-ftemplate
## -- license --
