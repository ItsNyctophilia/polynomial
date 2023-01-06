.DEFAULT_GOAL := libpoly.a
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -Wvla -Wwrite-strings -Waggregate-return -Wfloat-equal

libpoly.a: libpoly.a(poly.o) -lm

.PHONY: debug
debug: CFLAGS += -g
debug: libpoly.a

.PHONY: profile
profile: CFLAGS += -pg
profile: libpoly.a

.PHONY: check
check: libpoly.a test/test-all
	./test/test-all

test/test-all: LDFLAGS += -L.
test/test-all: LDLIBS += -lpoly
test/test-all: LDLIBS += -lcheck -lm -lrt -lpthread -lsubunit
test/test-all: test/test-all.o test/test-poly.o

.PHONY: clean
clean:
	$(RM) *.o libpoly.a test/*.o test/test-all test/test-poly


