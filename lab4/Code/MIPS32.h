#ifndef _MIPS32_H_
#define _MIPS32_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "semanticTraverse.h"
#include "grammertree.h"
#include "intercode.h"

typedef struct var_t{
  int reg_no;
  Operand op;
  struct var_t *next;
}VarDef;

typedef struct reg_t{
  char name[10];
  struct var_t *var;
  int old;
}RegDef;

typedef struct stack_t{
  int length;
  int old[1024];
  int from; 
  VarDef *varStack[1024];
}StkDef;

#define REG_NUM 32
#define REG_IN_USE 32

RegDef Regs[REG_NUM];
VarDef *VarDefList;
StkDef Stack;
int argsnum;

void storeVars(FILE *fp,bool colored);
void loadVars(FILE *fp,bool colored);
int getReg(Operand op,FILE *fp);
void genMIPS32Code(char *filename,bool colored);
void init_regs();
void genMIPS32Header(FILE *fp,bool colored);
void genMIPS32Objects(FILE *fp,bool colored);
void genMIPS32CodeIR(FILE *fp,InterCode ir,int index,bool colored);

#endif
