
CC=gcc
CFLAGS=-Wall -Wextra -fPIC
LDFLAGS=

MAIN_OBJS=main.c.o globals.c.o
OBJS=$(addprefix obj/, $(MAIN_OBJS))

BIN=libdd-re.so

.PHONY: clean all inject

# -------------------------------------------

all: $(BIN)

clean:
	rm -f $(OBJS)
	rm -f $(BIN)

inject: $(BIN)
	bash ./inject.sh

# -------------------------------------------

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): obj/%.c.o : src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<
