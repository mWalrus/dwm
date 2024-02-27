# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p /usr/share/xsessions
	install -Dm644 ./dwm.desktop /usr/share/xsessions
	mkdir -p ${DESTDIR}${PREFIX}/bin
	install -Dm755 ./dwm ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	mkdir -p /usr/share/dwm
	# wallpaper
	cp -f wallpaper.png /usr/share/dwm/
	# bookmarking script
	install -Dm 755 ./dwm-bookmark /bin/dwm-bookmark
	# dunst config
ifneq (, $(shell command -v dunst))
	mkdir -p /etc/dunst
	cp -f dunstrc /etc/dunst/
endif

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1
	rm -f /usr/share/xsessions/dwm.desktop
	rm -rf /usr/share/dwm
	rm -f /bin/dwm-bookmark
ifneq (, $(shell command -v dunst))
	rm -rf /etc/dunst
endif

.PHONY: all options clean dist install uninstall
