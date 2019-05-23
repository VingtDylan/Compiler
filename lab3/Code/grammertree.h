#ifndef GRAMMERTREE_H_
#define GRAMMERTREE_H_

#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern char* yytext;

#define MAX_CHILD_NUM 10
#define MAX_HASH_SIZE 16384 /*65536*/

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

typedef enum { 
  false,
  true 
} bool;

typedef enum { 
  Node_ID,
  Node_Data,
  Node_Sign,
  Node_Op,
  Node_Logic,
  Node_Fun,
  Node_Program 
} Node_Type;

typedef enum { 
  green,
  blue,
  cyan,
  yellow,
  l_cyan,
  l_purple,
  d_gray 
} Node_Color;

typedef enum { 
  INT_TYPE, 
  FLOAT_TYPE, 
  DOUBLE_TYPE 
} DATA;

typedef enum { 
  BASIC, ARRAY, STRUCTURE, FUNCTION 
} Kind;

typedef enum {
  LABEL_CODE,
  GOTO_CODE,
  IF_GOTO_CODE,
  ASSIGN_CODE,
  TEMP_VAR_OP,/**/
  PLUS_CODE,MINUS_CODE,MUL_CODE,DIV_CODE,
  READ_CODE,WRITE_CODE,
  FUNCTION_CODE,CALL_CODE,ARG_CODE,PARAMETER_CODE,RETURN_CODE
} CODE_KIND;

typedef enum {
  LABEL_OP, 
  VARIABLE_OP,
  CONSTANT_OP,
  FUNCTION_OP,
  DEBUG_OP 
} OP_KIND;

typedef enum { 
  wander,extra,arranged 
} Hashflag;

typedef enum { 
  undefined,unuseparam,defined 
} Nbool;

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;

typedef struct Node {
  int lineno;
  char name[32];
  char value[32];
  int child_num;
  Node_Type type;
  Node_Color color;
  struct Node *parent;
  struct Node *child[MAX_CHILD_NUM];
}TreeNode;

typedef struct Type_ {
  Kind kind;
  union {
    int basic;
    struct {
      Type elem;
      int size;
    }array;
    FieldList structure; 
    struct {
      FieldList parameters;
      Type funcType;
      int paranum;
    }function;
  }u;
}Type_;

typedef struct HashCheck {
  Hashflag flag;
  int hashed;
}Hash;

typedef struct FieldList_ {
  char* name;
  int lineno;
  Type type;
  Nbool defined;
  FieldList tail;
  char parent[32];
  Hash hashflag;
}FieldList_;  

typedef struct Operand_ {
  OP_KIND kind;
  union{
    int tvar_no;
    int label_no;
    char value[32];
    Operand name;
  }u;
  struct Operand_ *prevArgs;
  struct Operand_ *nextArgs;
}Operand_;

typedef struct InterCode_ {
  CODE_KIND kind;
  union{
    struct {
      Operand op;
    }single;
    struct { 
      Operand right,left; 
    }assignOp;
    struct { 
      Operand result,op1,op2;
    }tripleOp;
    struct {
      Operand op1;
      Operand op2;
      Operand label;
      char relop[32];
    }ifgotoOp;
    struct {
      Operand op;
      int size;
    }decOp;
  }u;
}InterCode_;

#define MAX_IR_SIZE 10

FieldList hashTable[MAX_HASH_SIZE];
InterCode *IRList;

int IRlength;
int IRCapacity;
int LabelCounter;
int TempVarCounter;
int VarCounter;

void PrintError(const char *s);
void PrintHint(const char *s);
void PrintSymbol(const char *s);

TreeNode* createNode(char* name,char* text,Node_Type type,Node_Color color);
void addChild(TreeNode* parent,TreeNode* child,int childIndex);
void printTree(TreeNode* parent,int layer);

#endif
