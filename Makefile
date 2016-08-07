project: input.o logic.o main.o out.o stack.o
	cc *.o -o project -lSDL -lSDL_image -lm
input.o: input.c input.h main.h logic.h
	cc -c input.c 
logic.o: logic.c logic.h main.h
	cc -c logic.c
main.o: main.c input.h out.h main.h
	cc -c main.c
out.o: out.c out.h main.h logic.h stack.h
	cc -c out.c
stack.o: stack.c stack.h
	cc -c stack.c
clean :
	rm *.o project	
