CC=gcc
CFLAGS=-pthread -Wall
PYLIB=/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/libpython3.6m.a
PYINC=-I/usr/include -I/usr/include -I/usr/include/python3.6 -I/usr/include/python3.6
LIBS=-L -ldl -lpthread -lutil -lm -Xlinker -export-dynamic

SOURCE=./socket/source
BIN=./bin

SRC=$(SOURCE)/socket.c

socket=socket
SCKT_OBJS=$(BIN)/socket.o $(BIN)/socket_utils.o

LIST=$(BIN)/socket

all: $(LIST)

$(BIN)/%: $(SCKT_OBJS)
	$(CC) $(CFLAGS) -g  $(SCKT_OBJS) $(LIBS) $(PYLIBS) -o $(BIN)/socket

$(BIN)/socket.o: ${SRC}
	$(CC) $(CFLAGS) -c ${SRC} -o $(BIN)/socket.o

$(BIN)/socket_utils.o: $(SOURCE)/socket_utils.c
	$(CC) $(CFLAGS) -g 	$(SOURCE)/socket_utils.c -c $(PYINC) -o $(BIN)/socket_utils.o

$(shell   mkdir -p $(BIN))

clean:
	rm -rf $(SCKT_OBJS) ${LIST}

