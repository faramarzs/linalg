PROG = lin

WFLAGS = -Wall -Wno-unused-variable -Wno-unused-function \
		 -Wno-deprecated-declarations -Wno-varargs
INCFLAGS= -I$(HOMEBREW_PREFIX)/include
CFLAGS = -g $(INCFLAGS) $(WFLAGS)
LDFLAGS = -L $(HOMEBREW_PREFIX)/lib -lcrypto
#CFLAGS = -g -Wall -I/opt/homebrew/include -Wno-deprecated-declarations 
#LDFLAGS = -L /opt/homebrew/lib -lcrypto
#CFLAGS = -g -Wall -Wno-deprecated-declarations -I/opt/local/include
#LDFLAGS = -L /opt/local/lib -lcrypto

INSTALLDIR = /usr/local/bin

OBJS = mem.o log.o mat.o lin.o
HEADERS = mem.h log.h mat.h

all: ${HEADERS} ${PROG}

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o $@ ${OBJS} ${LDFLAGS}

install:	${PROG}
	cp ${PROG} ${INSTALLDIR}

clean:
	${RM} ${OBJS}
	${RM} -r *.dSYM

clobber:	clean
	${RM} ${PROG}

style:
	astyle --style=kr --indent=spaces=4 lin.c
	astyle --style=kr --indent=spaces=4 log.c
	astyle --style=kr --indent=spaces=4 mem.c
	astyle --style=kr --indent=spaces=4 mat.c
