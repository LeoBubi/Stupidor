CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c17

SRC_DIR := src
OBJ_DIR := obj

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

EXEC := stupidor


.PHONY: all clean


all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	@rm -rf $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rvf $(OBJ_DIR) $(EXEC)