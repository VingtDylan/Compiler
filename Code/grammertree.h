#ifndef GRAMMERTREE_H_
#define GRAMMERTREE_H_

#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern char* yytext;

#define MAX_CHILD_NUM 10

#define NONE       "\033[m"          /*Clear*/
#define RED        "\033[0;32;31m"   /*Bug*/
#define GREEN      "\033[0;32;32m"   /*Node_Data*/
#define BLUE       "\033[0;32;34m"   /*Node_Sign*/
#define CYAN       "\033[0;36m"      /*Node_Op*/
#define PURPLE     "\033[0;35m"      /*Hint*/
#define BRANCH     "\033[0;33m"      /*BROWN*/
#define YELLOW     "\033[1;33m"      /*Node_Logic*/
#define L_CYAN     "\033[1;36m"      /*Node_Fun*/
#define L_PURPLE   "\033[1;35m"      /*Node_ID*/
#define GRAY       "\033[1;31;40m"   /*Node_Program*/
#define WHITE      "\033[1;37m"

typedef enum { false,true } bool;
typedef enum { Node_ID,Node_Data,Node_Sign,Node_Op,Node_Logic,Node_Fun,Node_Program } Node_Type;
typedef enum { green,blue,cyan,yellow,l_cyan,l_purple,d_gray }Node_Color;

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
void addChild(TreeNode* parent,TreeNode* child,int childIndex);
void printTree(TreeNode* parent,int layer);

#endif
