CC.x64 = gcc
CC.x86 = gcc

CFLAGS.x64 = -Wall -g -fPIC
CFLAGS.x86 = -m32 -Wall -g -fPIC

ASFLAGS.x64 = --64
ASFLAGS.x86 = --32

OBJECTS.x64 = bin/callback.o bin/ffcb.o
OBJECTS.x86 = bin/callback.o bin/ffcb.o

BIN = bin
CC = ${CC.${target}}
CFLAGS = ${CFLAGS.${target}}
ASFLAGS = ${ASFLAGS.${target}}
OBJECTS = ${OBJECTS.${target}}

all: $(BIN) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -shared -o $(BIN)/libffcb.a

clean:
	if [ -d $(BIN) ]; then rm -r $(BIN); fi

$(BIN):
	mkdir $(BIN)

$(BIN)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: src/$(target)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: src/$(target)/%.s
	as $(ASFLAGS) $< -o $@
