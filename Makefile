CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc/utils -Isrc/metrics
SERVER_TARGET = server
CLIENT_TARGET = client
SERVER_SOURCES = src/server/server.c src/utils/utils.c
CLIENT_SOURCES = src/client/client.c src/metrics/metrics.c

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_SOURCES)
	$(CC) $(CFLAGS) -o $(SERVER_TARGET) $(SERVER_SOURCES)

$(CLIENT_TARGET): $(CLIENT_SOURCES)
	$(CC) $(CFLAGS) -o $(CLIENT_TARGET) $(CLIENT_SOURCES)

clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)

.PHONY: all clean