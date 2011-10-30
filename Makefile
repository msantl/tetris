CC=gcc
CFLAGS=-Wall -pedantic
LIBS=-lpthread -lncurses
SOURCE=tetris.c misc.c
OBJECT=$(SOURCE:.c=.o)
RUN=tetris

all: $(SOURCE) $(RUN)

$(RUN): $(OBJECT)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECT) -o $@
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJECT)
	
