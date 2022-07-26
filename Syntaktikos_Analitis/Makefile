all:
	bison -d python.y
	flex python.l
	gcc -o parser python.tab.c lex.yy.c
	./parser input.txt output.txt
	make clean
clean:
	rm python.tab.c python.tab.h lex.yy.c parser
