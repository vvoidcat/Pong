OUTNAME = "pong"
CC = gcc -Wall -Werror -Wextra -std=c11


all: cleanall build clean

build:
	$(CC) ... -o $(OUTNAME)

rebuild: cleanall build


launch:
	./$(OUTNAME)


clean:
	/bin/rm -rf *.o

cleanall:
	/bin/rm -rf *.o $(OUTNAME)
