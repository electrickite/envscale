# See LICENSE file for copyright and license details.

NAME=envscale

PREFIX = /usr

INCS = -I. -I/usr/include
LIBS = -L/usr/lib -lc

CPPFLAGS = -DVERSION=\"${VERSION}\" -D_GNU_SOURCE
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Os -s ${INCS} ${CPPFLAGS} $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = ${LIBS} $(shell pkg-config --libs gtk+-3.0)

CC = cc
LD = ld

SRC = ${NAME}.c
OBJ = ${SRC:.c=.o}

all: options ${NAME}

options:
	@echo ${NAME} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${NAME}: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${NAME} ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/${NAME}

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/${NAME}

.PHONY: all options install uninstall
