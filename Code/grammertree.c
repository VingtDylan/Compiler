#include <stdio.h>
#include <stdlib.h>
#include "grammertree.h"

void PrintError(const char *s){
  printf(RED"Debug here:%s"NONE,s);
}

void PrintHint(const char *s){
  printf(PURPLE"Hint:%s"NONE,s);
}


TreeNode* createNode(char* name,char* text,Node_Type type,Node_Color color){
  TreeNode *leaf = (TreeNode*)malloc(sizeof(TreeNode));
  strcpy(leaf->name,name);
  strcpy(leaf->value,text);
  leaf->type=type;
  leaf->lineno=yylineno;
  leaf->color=color;
  leaf->parent=NULL;
  for(int i=0;i<MAX_CHILD_NUM;i++)
    leaf->child[i]=NULL;
  return leaf;
}

void addChild(){
 
}

void printTree(TreeNode *parent,int layer){
  PrintHint("Grammer Tree is followed!\n");
  if(parent==NULL)
    return ;
  for(int i=0;i<layer+10;i++)
    printf(BRANCH"--"NONE);
}
