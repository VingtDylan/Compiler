#ifndef GRAMMERTREE_H_
#define GRAMMERTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern int yylineno;
extern char* yytext;

#define MAX_CHILD_NUM 10

#define NONE    "\033[m"          /*Clear*/
#define RED     "\033[0;32;31m"   /*Bug*/
#define GREEN   "\033[0;32;32m"
#define BLUE    "\033[0;32;34m"   
#define CYAN    "\033[0;36m"
#define PURPLE  "\033[0;35m"      /*Hint*/
#define BRANCH  "\033[0;33m"      /*BROWN*/
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

typedef enum { false,true } bool;
typedef enum { Node_ID,Node_Data,Node_Sign } Node_Type;
typedef enum { green }Node_Color;

typedef struct Node{
  int lineno;
  char name[32];
  char value[32];
  int child_num;
  Node_Type type;
  Node_Color color;
  struct Node *parent;
  struct Node *child[MAX_CHILD_NUM];
}TreeNode;

void PrintError(const char *s);
void PrintHint(const char *s);

TreeNode* createNode(char* name,char* text,Node_Type type,Node_Color color);
void addChild();
void printTree(TreeNode *parent,int layer);

#endif
