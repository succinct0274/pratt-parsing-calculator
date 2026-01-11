CC=clang
CFLAGS=-Wall -Wextra -g -O0

OUT_DIR=output
SRCS=$(wildcard *.c)
OBJS=$(addprefix $(OUT_DIR)/, $(SRCS:.c=.o)) 
TARGET=$(OUT_DIR)/main

all: $(TARGET)

# $@ mean $(TARGET); $^ means $(OBJS)
$(TARGET): $(OBJS)
	$(CC) $(CFLARGS) -o $@ $^

# $< means first element in $^
$(OUT_DIR)/%.o: %.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)

run: $(OUT_DIR)/main
	./output/main

.PHONY: run clean all