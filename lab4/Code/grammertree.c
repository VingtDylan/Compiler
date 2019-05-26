#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammertree.h"

extern int yylineno;

void PrintError(const char *s){
  printf(RED"Debug here:%s"NONE,s);
}

void PrintHint(const char *s){
  printf(PURPLE"Hint:%s"NONE,s);
}

void PrintSymbol(const char *s){
  printf(CYAN"SymbolDebug:-> %s"NONE,s);
}


TreeNode* createNode(char* name,char* text,Node_Type type,Node_Color color){
  TreeNode *leaf = (TreeNode*)malloc(sizeof(TreeNode));
  strcpy(leaf->name,name);
  strcpy(leaf->value,text);
  leaf->type=type;
  leaf->lineno=yylineno;
  leaf->color=color;
  leaf->child_num=0;
  leaf->parent=NULL;
  for(int i=0;i<MAX_CHILD_NUM;i++)
    leaf->child[i]=NULL;
  return leaf;
}

void addChild(TreeNode* parent,TreeNode* child,int childIndex){
  parent->child[childIndex-1]=child;
  parent->child_num++;
  parent->lineno=parent->child[0]->lineno;
  //child->parent=parent;
}

void printTree(TreeNode *parent,int layer){
  //PrintHint("Grammer Tree is followed!\n");
  if(parent==NULL)
    return ;
  for(int i=0;i<layer+1;i++)
    printf(BRANCH"--"NONE);
  if(parent->child_num>=1){ /*Node*/
    switch(parent->type){
      case Node_ID: printf(L_PURPLE"%s (%d)\n"NONE,parent->name,parent->lineno); break;
      case Node_Data: printf(GREEN"%s (%d)\n"NONE,parent->name,parent->lineno); break;
      case Node_Sign: printf(BLUE"%s (%d)\n"NONE,parent->name,parent->lineno); break;
      case Node_Op: printf(CYAN"%s (%d)\n"NONE,parent->name,parent->lineno); break;
      case Node_Logic: printf(YELLOW"%s (%d)\n"NONE,parent->name,parent->lineno); break;
      case Node_Fun: printf(L_CYAN"%s (%d)\n"NONE,parent->name,parent->lineno); break;
      case Node_Program: printf(GRAY"%s (%d)\n"NONE,parent->name,parent->lineno); break;
    }
    for(int i=0;i<parent->child_num;i++){
      printTree(parent->child[i],layer+1);
    }
  }else{ /*leaf*/
   if(strcmp(parent->name,"INT")==0)
     printf(GREEN"%s: %d\n"NONE,parent->name,atoi(parent->value));
   else if(strcmp(parent->name,"FLOAT")==0)
     printf(GREEN"%s: %f\n"NONE,parent->name,atof(parent->value));
   else if(strcmp(parent->name,"ID")==0)
     printf(L_PURPLE"%s: %s\n"NONE,parent->name,parent->value);
   else if(strcmp(parent->name,"TYPE")==0)
     printf(L_PURPLE"%s: %s\n"NONE,parent->name,parent->value);
   else
     printf(BLUE"%s\n"NONE,parent->name);
  }
}
