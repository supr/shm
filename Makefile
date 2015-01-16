SERVER_TARG=shm_server
CLIENT_TARG=shm_client

SERVER_SRCS=shm_server.c
CLIENT_SRCS=shm_client.c

KEY?=0xDEAD

CFLAGS=-DKEY=$(KEY) -D_GNU_SOURCE -std=c99 

all: server client

server: $(SERVER_TARG)

client: $(CLIENT_TARG)

$(SERVER_TARG): $(SERVER_SRCS)
	$(CC) -o $@ $(CFLAGS) $^

$(CLIENT_TARG): $(CLIENT_SRCS)
	$(CC) -o $@ $(CFLAGS) $^

clean:
	rm -fr $(SERVER_TARG) $(CLIENT_TARG)

.PHONY:
	all clean
