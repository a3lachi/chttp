CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = server
SOURCES = server.c utils.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean