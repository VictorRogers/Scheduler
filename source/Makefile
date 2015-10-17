INC_DIR   := header
SRC_DIR   := src
OBJ_DIR   := object

CC        := gcc
CPPFLAGS  := -I$(INC_DIR) -MMD -MP
CFLAGS    := -std=c99 -pedantic -Wall

SOURCES   := $(wildcard $(SRC_DIR)/*.c)
OBJECTS   := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS      := $(wildcard $(OBJ_DIR)/*.d)

.PHONY: clean

scheduler: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(OUTPUT_OPTION) $<

clean: ; $(RM) $(DEPS) $(OBJECTS) scheduler

-include $(DEPS)

$(MAKEFILE_LIST): ;
%.h: ;
%:: %,v
%:: RCS/%,v
%:: RCS/%
%:: s.%
%:: SCCS/s.%
