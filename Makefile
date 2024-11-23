
CC = gcc
CFLAGS = -std=c99 -Wall -Werror


SRCS = table_parser.c stack.c


OBJS = $(SRCS:.c=.o)


TARGET = table_parser


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)


run: $(TARGET)
	./$(TARGET)


.PHONY: all clean run
