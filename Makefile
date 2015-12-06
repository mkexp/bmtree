prog := sort_by_ntz
prog_objs := sort_by_ntz.o

CC := mpicc
CFLAGS := -std=c11 -Wall -O2
LDFLAGS := -lm

.PHONY: all clean

all: $(prog)

$(prog): $(prog_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

sort_by_ntz.o: sort_by_ntz.c

clean:
	@rm -rf *.o $(prog)
