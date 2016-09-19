KNOWN_ARCHS.x86_64=x64
KNOWN_ARCHS.i386=x86
KNOWN_ARCHS.i686=x86

ifeq ($(TARGET),)
ARCH=$(shell uname -m)

ifeq (${KNOWN_ARCHS.${ARCH}},)
$(error unsupported/unknown architecture $(ARCH))
else
TARGET=${KNOWN_ARCHS.${ARCH}}
endif

endif

CC.x64 = gcc
CC.x86 = gcc

CFLAGS.x64 = -Wall -g -fPIC
CFLAGS.x86 = -m32 -Wall -g -fPIC

ASFLAGS.x64 = --64
ASFLAGS.x86 = --32

BIN = bin
CC = ${CC.${TARGET}}
CFLAGS = ${CFLAGS.${TARGET}}
ASFLAGS = ${ASFLAGS.${TARGET}}

OBJECTS = bin/callback.o bin/ffcb.o bin/code.o

all: $(BIN) $(OBJECTS)
	ar rcs $(BIN)/libffcb.a $(OBJECTS)

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
