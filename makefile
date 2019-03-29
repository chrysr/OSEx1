CC=g++
CFLAGS=-I.
DEPS=graph.h node.h edge.h heads.h
OBJ=graph.o node.o edge.o main.o heads.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mygraph: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.Phony: clean
clean:
	-rm $(OBJ)
	-rm mygraph
