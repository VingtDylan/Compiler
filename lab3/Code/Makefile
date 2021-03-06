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
	$(CC) -g -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly 

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test run
test:
	ulimit -c 1024
	./parser ../Test/test4.cmm ../Test/out4.ir

run:
	ulimit -c 1024
	./parser ../Test/test4.cmm
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
