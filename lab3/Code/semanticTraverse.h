#ifndef _SEMANTICTRAVERSE_H_
#define _SEMANTICTRAVERSE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semantic.h"
#include "grammertree.h"
#include "intercode.h"

Type Condition(TreeNode *root,Operand L1,Operand L2);

void traverseExtDefList(TreeNode *root);
void traverseCompSt(TreeNode *root,Type funcType,char* pname);
void traverseDefList(TreeNode *root,char* pname);
void traverseStmt(TreeNode *root,Type funcType,char* pname);
void traverse(TreeNode *root);

#endif
