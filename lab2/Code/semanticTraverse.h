#ifndef _SEMANTICTRAVERSE_H_
#define _SEMANTICTRAVERSE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semantic.h"
#include "grammertree.h"

void traverseExtDefList(TreeNode *root);
void traverseCompSt(TreeNode *root,Type funcType);
void traverseDefList(TreeNode *root);
void traverseStmt(TreeNode *root,Type funcType);
void traverse(TreeNode *root);

#endif
