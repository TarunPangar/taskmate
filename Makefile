BASE_DIR := $(shell pwd)
CC		= gcc
INCLUDE = -I$(BASE_DIR)/inc
SOURCE	= $(BASE_DIR)/src
EXEC	= todo
CFLAGS	= -g $(INCLUDE) -MMD -MP
RM		= rm -f

SRCS    :=  $(SOURCE)/main.c \
			$(SOURCE)/options.c \
			$(SOURCE)/task.c

OBJECTS := $(SRCS:%.c=%.o)
DEPS    := $(OBJECTS:.o=.d)

.PHONY: all clean run

default: all

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

# Compile .c files into .o files
$(SOURCE)/%.o: $(SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files for incremental builds
-include $(DEPS)

clean:
	$(RM) $(EXEC) $(SOURCE)/*.o $(SOURCE)/*.d

run: all
	./$(EXEC)
