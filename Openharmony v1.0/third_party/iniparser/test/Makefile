CC   ?= gcc

ifndef V
QUIET_CC         = @echo "CC	$@";
QUIET_MAKE_TESTS = @echo "GN	Alltests.c";
endif

DEPS = $(shell ls ../src/*.[ch])

SRC = $(shell ls *.c | sed 's/AllTests.c//')
OBJ = $(SRC:.c=.o)

INCLUDE = -I../src
CFLAGS  += -pipe -ansi -pedantic -Wall -Wextra -g
LDFLAGS +=

all: check

check: testrun
	@./testrun

testrun: AllTests.o $(OBJ)
	$(QUIET_CC)$(CC) -o $@ AllTests.o $(OBJ) $(LDFLAGS)

AllTests.o: $(OBJ)
	$(QUIET_MAKE_TESTS)./make-tests.sh > AllTests.c
	$(QUIET_CC)$(CC) -c -o AllTests.o AllTests.c $(CFLAGS) $(INCLUDE)

%.o: %.c $(DEPS)
	$(QUIET_CC)$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

clean veryclean:
	rm -rf AllTests.c
	rm -rf $(OBJ) AllTests.o
	rm -rf testrun
