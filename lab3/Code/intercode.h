#ifndef __INTERCODE_H__
#define __INTERCODE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grammertree.h"
#include "semanticTraverse.h"
#include "semantic.h"

void initIRList();
void insertCode(InterCode ir);
void genCode(char *filename,bool colored);
void genCodeOp(Operand op,FILE *fp,bool colored);

#endif
