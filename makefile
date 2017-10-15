DIR=./

snake: main.o console.o queue.o
	cc -o snake main.o console.o queue.o -I . -lpthread -lcurses -g
	
main.o: common.h snake.h queue.h console.h main.c
	cc -o main.o -c main.c -I . -g
	
console.o: console.h console.c
	cc -o console.o -c console.c -I . -g 

queue.o: common.h queue.h queue.c
	cc -o queue.o -c queue.c -I . -g

clean:
	rm *.o snake
