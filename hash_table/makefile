NAME=idfk

# Directories
SRCD=./source
BLDD=./build
OBJD=$(BLDD)/objects
DIRS=.

# Files
SRCS=$(foreach D,$(DIRS),$(wildcard $(SRCD)/$(D)/*.c))
OBJS=$(patsubst $(SRCD)/%.c,$(OBJD)/%.obj,$(SRCS))
BIN=$(BLDD)/$(NAME).exe

# Build
CC=clang
CFLGS=-std=c11 -O3
WFLGS=-Wall -Wextra
FLGS=$(CFLGS) $(WFLGS) $(IFLGS)

all:$(BIN)

r:$(BIN)
	clear
	$(BIN)

$(BIN):$(OBJS)
	$(CC) $^ -o $@ $(LFLGS)

$(OBJD)/%.obj:$(SRCD)/%.c
	$(CC) -c $^ -o $@ $(FLGS)

c:$(BLDD)
	rm -rf $(OBJS) $(BIN)

f:
	clang-format -i $(SRCS) $(foreach D,$(DIRS),$(wildcard $(SRCD)/$(D)/*.h))

.PHONY:all r c f
