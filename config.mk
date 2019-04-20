# See LICENSE file for copyright and license details.

VERSION = 0.2.0

PREFIX = /usr
MANPREFIX = ${PREFIX}/share/man

INCS = -I. -I/usr/include
LIBS = -L/usr/lib -lc

CPPFLAGS = -DVERSION=\"${VERSION}\" -D_GNU_SOURCE
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Os -s ${INCS} ${CPPFLAGS} $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = ${LIBS} $(shell pkg-config --libs gtk+-3.0)

CC = cc
LD = ld
