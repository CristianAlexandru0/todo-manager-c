CC = gcc
CFLAGS = -Wall -g
TARGET = todo_list

all: $(TARGET)

$(TARGET): todo_list.c
	$(CC) $(CFLAGS) -o $(TARGET) todo_list.c

clean:
	rm -f $(TARGET)