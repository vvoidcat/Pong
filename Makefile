OUTNAME = "pong"
##CC = gcc -Wall -Werror -Wextra -std=c11
CC = gcc


all: cleanall build clean

build: src/pong_main.c src/pong.c
	$(CC) src/pong_main.c src/pong.c -o $(OUTNAME)

rebuild: cleanall build


launch:
	./$(OUTNAME)


clean:
	/bin/rm -rf *.o

cleanall:
	/bin/rm -rf *.o $(OUTNAME)
