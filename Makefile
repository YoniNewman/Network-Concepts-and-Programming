TARGET: exe
main.o: main.c
	gcc -c main.c -o main.o
ip_math_coding.o: ip_math_coding.c
	gcc -c ip_math_coding.c -o ip_math_coding.o
exe: ip_math_coding.o main.o
	gcc ip_math_coding.o main.o -o exe
debug.out: main.c ip_math_coding.c
	gcc -g main.c ip_math_coding.c -o debug.out

clean:
	rm ip_math_coding.o
	rm main.o
	rm exe
	rm debug.out
