PLAYGROUND_PATH=../playground

PROGRAM=clicker

CFLAGS=-O0 -g -Werror=implicit-function-declaration
CPPFLAGS=-I$(PLAYGROUND_PATH) -I$(PLAYGROUND_PATH)/externals/include -MMD
LDFLAGS=-L$(PLAYGROUND_PATH) -L$(PLAYGROUND_PATH)/externals/x86_64-linux-gnu
LDLIBS=-lpg -lglfw3 -lm

OBJS=src/main.o src/game.o src/gui.o tests/test_button.o tests/test_counter.o src/utils.o tests/test_ascii.o

DEPS=$(OBJS:.o=.d)

.PHONY: all

all: $(PROGRAM)

-include $(DEPS)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM) config.bin

