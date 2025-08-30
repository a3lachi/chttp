CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = server
SOURCE = server.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: clean