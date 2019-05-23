#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammertree.h"
#include "semanticTraverse.h"
#include "intercode.h"

void initHashTable();
void debugShowSymbol();
void debugShowAllSymbol();
void validateTable();
int insertSymbol(FieldList f);
bool TypeEqual(Type type1,Type type2);
unsigned int hash_pjw(char *name);

Type Specifier(TreeNode *root,char* pname);
FieldList VarDec(TreeNode *root,Type funcType,char* pname,int index);
Type Exp(TreeNode *root,Operand Op);
FieldList indexSymbol(char *name,bool isFunc);

//Type Exp(TreeNode *root,Operand op);

#endif
