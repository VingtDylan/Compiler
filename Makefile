.PHONY: run

run:
	bison -d -v syntax.y
	flex lexical.l
	gcc -o parser syntax.tab.c lex.yy.c -lfl -ly
	./parser test.cmm 
