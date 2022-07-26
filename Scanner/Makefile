all:
	flex -o scanner.c scanner.l
	gcc -o scanner scanner.c
	./scanner input.txt output.txt
clean:
	rm lex.yy.c scanner
