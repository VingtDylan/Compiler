#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammertree.h"
#include "semanticTraverse.h"

void initHashTable();
void debugShowSymbol();
void validateTable();
int insertSymbol(FieldList f);
bool TypeEqual(Type type1,Type type2);
unsigned int hash_pjw(char *name);

Type Specifier(TreeNode *root,char* pname);
FieldList VarDec(TreeNode *root,Type funcType,char* pname);
Type Exp(TreeNode *root);
FieldList indexSymbol(char *name,bool isFunc); 

#endif
