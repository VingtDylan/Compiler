# 编译器设定和编i译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

CMM_SOURCES := $(wildcard ../Test/*.cmm)
C_SOURCES := $(wildcard ../Test/*.c)
NUM_OF_CMM := $(words $(CMM_SOURCES))
NUM_OF_C := $(words $(C_SOURCES))
INDEX_CMM := $(shell seq 1 $(NUM_OF_CMM))
INDEX_C := $(shell seq 1 $(NUM_OF_C))

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly -g

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test CMM C all
test:
	./parser ../Test/test19.cmm

CMM:  
	for n in $(INDEX_CMM);\
	do\
		echo "Output of test$$n.cmm";\
		./parser ../Test/test$$n.cmm;\
	done

C:
	for n in $(INDEX_C);\
	do	./parser ../Test/test$$n.c;\
	done

all: 	
	for case in $(shell find ../Test/*);\
		do	./parser $$case;\
		done

clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
