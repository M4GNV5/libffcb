CC = gcc
TARGET = ia64
CFLAGS = -Wall -g -fPIC
ASFLAGS = --64

BIN = bin

OBJECTS += bin/callback.o
OBJECTS += bin/ffcb.o
OBJECTS += bin/common.o

all: $(BIN) $(OBJECTS)
	$(CC) $(OBJECTS) -shared -o $(BIN)/libffcb.so

clean:
	if [ -d $(BIN) ]; then rm -r $(BIN); fi

$(BIN):
	mkdir $(BIN)

$(BIN)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: src/$(TARGET)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: src/$(TARGET)/%.s
	as $(ASFLAGS) $< -o $@
