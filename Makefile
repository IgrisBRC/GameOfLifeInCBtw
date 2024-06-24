main: main.o
	cc -o main main.o -g -Wall -fsanitize=address

main.o: main.c
	cc -c main.c -g -Wall -fsanitize=address

clean:
	rm main.o main
