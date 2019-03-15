#ifndef GRAMMERTREE_H_
#define GRAMMERTREE_H_

extern int yylineno;
extern char* yytext;

typedef struct Node{
  int type;
  int lineno;
  char* name;
  char* value;
  struct Node *leftChild;
  struct Node *rightChild;
}TreeNode;

struct TreeNode *create_Leaf();
struct TreeNode *create_Node();
struct TreeNode *create_empty();

void printTree(TreeNode *root,int layer);

#endif
