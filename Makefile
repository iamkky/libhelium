

LIB=libhelium.a
DIRS=dom

.PHONY: all $(DIRS)

all: ${LIB}

example: example.o 
	gcc ${CFLAGS} -o example example.o ${LIB} $(LIBABD)/libabd.a

${LIB}: ${DIRS}
	${AR} rcs ${LIB} */*.o

$(DIRS):
	${MAKE} -C $@ $(MAKECMDGOALS)

clean:
	for a in ${DIRS}; do ${MAKE} -C $$a clean; done
	rm -f ${LIB} *.o example
