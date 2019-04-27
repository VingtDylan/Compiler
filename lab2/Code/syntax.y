%locations
%error-verbose
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "grammertree.h"
  #include "semantic.h"
  #include "semanticTraverse.h"
  #include "lex.yy.c"
  int yyerror(const char *s);
  int yylex();
  extern void yyrestart(FILE*);
  extern int yyparse(); 
  extern FILE *yyin;
  extern int yylineno;
  bool error_exist=false;
  TreeNode* Root=NULL;
%}

/* set attribute type for test */
/* %define api.value.type {int} */

/* declare tokens (terminal symbols) */
%union{
  int ivalue;
  float fvalue;
  //double dvalue;
  //char *string;
  struct Node* treenode; 
}

//%token <string> ID
//%token <ivalue> INT
//%token <fvalue> FLOAT

%token <treenode> ID INT FLOAT
%token <treenode> SEMI COMMA ASSIGNOP RELOP
%token <treenode> PLUS MINUS STAR DIV   
%token <treenode> AND OR DOT NOT
%token <treenode> TYPE STRUCT
%token <treenode> LP RP LB RB LC RC
%token <treenode> IF ELSE WHILE
%token <treenode> RETURN /*EOL*/

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV 
%right NOT /*NEG*/
%left LP RP LB RB DOT

%type <treenode> Program ExtDefList ExtDef ExtDecList 
%type <treenode> Specifier StructSpecifier OptTag Tag 
%type <treenode> VarDec FunDec VarList ParamDec
%type <treenode> CompSt StmtList Stmt
%type <treenode> DefList Def DecList Dec
%type <treenode> Exp Args

%start Program

%%
/*High-Level Definition*/

Program    : ExtDefList { 
               $$ = createNode("Program"," ",Node_Program,d_gray); 
               addChild($$,$1,1);  
               Root=$$; 
             }
;

ExtDefList : ExtDef ExtDefList { 
               $$ = createNode("ExtDefList"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
             }
           | { $$ = NULL ;/*NULL*/}
;

ExtDef     : Specifier ExtDecList SEMI { 
               $$ = createNode("ExtDef"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
             }
        /* | Specifier ExtDecList SEMI EOL EOL*/
           | Specifier SEMI { 
               $$ = createNode("ExtDef"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
             }
        /* | Specifier SEMI EOL EOL*/
           | Specifier FunDec CompSt { 
               $$ = createNode("ExtDef"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
             }
           | Specifier FunDec SEMI {
               $$ = createNode("ExtDef"," ",Node_Program,d_gray);
               addChild($$,$1,1);
               addChild($$,$2,2);
               addChild($$,$3,3);
             }
        /* | Specifier FunDec CompSt EOL*/
           | error SEMI { error_exist = true;/*yyerrok;*/ }
;

ExtDecList : VarDec { 
               $$ = createNode("ExtDecList"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
           | VarDec COMMA ExtDecList { 
               $$ = createNode("ExtDecList"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
             }
;

/* Specifier*/

Specifier  : TYPE { 
               $$ = createNode("Specifier"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
           | StructSpecifier { 
               $$ = createNode("StructSpecifier"," ",Node_Program,d_gray);
               addChild($$,$1,1);
             }
;

StructSpecifier: STRUCT OptTag LC DefList RC { 
                   $$ = createNode("StructSpecifier"," ",Node_Program,d_gray); 
                   addChild($$,$1,1);
                   addChild($$,$2,2); 
                   addChild($$,$3,3); 
                   addChild($$,$4,4); 
                   addChild($$,$5,5); 
                 }
           | STRUCT Tag { 
               $$ = createNode("StructSpecifier"," ",Node_Program,d_gray);
               addChild($$,$1,1); 
               addChild($$,$2,2); 
             }
;

OptTag     : ID { 
               $$ = createNode("OptTag"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
           | { $$ = NULL; /*NULL*/} 
;

Tag        : ID { 
               $$ = createNode("Tag"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
;

/*Declarators*/

VarDec     : ID { 
               $$ = createNode("VarDec"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
           | VarDec LB INT RB { 
               $$ = createNode("VarDec"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
               addChild($$,$4,4); 
             }
           | VarDec LB error RB { error_exist = true; /*yyerrok;*/ }
;

FunDec     : ID LP VarList RP { 
               $$ = createNode("FunDec"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
               addChild($$,$4,4); 
             }
           | ID LP RP { 
               $$ = createNode("FunDec"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
             }
           | error RP { error_exist = true; /*yyerrok;*/ }
;

VarList    : ParamDec COMMA VarList { 
               $$ = createNode("VarList"," ",Node_Program,d_gray);
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
             }
           | ParamDec { 
               $$ = createNode("VarList"," ",Node_Program,d_gray); 
               addChild($$,$1,1);
             }
;

ParamDec   : Specifier VarDec { 
               $$ = createNode("ParamDec"," ",Node_Program,d_gray);
               addChild($$,$1,1);
               addChild($$,$2,2); }
           | error COMMA { error_exist = true;/*yyerrok;*/ }
           | error RP { /*yyerrok;*/ }
;

/*Statements*/

CompSt     : LC DefList StmtList RC { 
             $$ = createNode("CompSt"," ",Node_Program,d_gray); 
             addChild($$,$1,1); 
             addChild($$,$2,2);
             addChild($$,$3,3); 
             addChild($$,$4,4); 
             }
         /*| LC EOL DefList StmtList RC*/
           | LC error RC { error_exist = true; }
;

StmtList   : Stmt StmtList { 
               $$ = createNode("StmtList"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
             }
           | { $$ = NULL; /*NULL*/}
;

Stmt       : Exp SEMI { 
               $$ = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
             }
           | CompSt { 
               $$ = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
           | RETURN Exp SEMI { 
               $$ = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
             }
           | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE { 
               $$ = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
               addChild($$,$4,4);
               addChild($$,$5,5); 
             }
           | IF LP Exp RP Stmt ELSE Stmt { 
               $$ = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
               addChild($$,$4,4);
               addChild($$,$5,5); 
               addChild($$,$6,6);
               addChild($$,$7,7); 
             }
           | IF LP Exp RP error ELSE Stmt { 
               PrintError("Missing \";\" ?\n");  
               error_exist = true;
               /*yyerrok;*/ 
             } 
           | WHILE LP Exp RP Stmt { 
               $$ = createNode("Stmt"," ",Node_Program,d_gray);
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
               addChild($$,$4,4);
               addChild($$,$5,5);
             }
;

/*Local Definitions*/

DefList    : Def DefList { 
               $$ = createNode("DefList"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
             }
           | { $$ = NULL; /*NULL*/} 
;

Def        : Specifier DecList SEMI { 
               $$ = createNode("Def"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2); 
               addChild($$,$3,3); 
             }
        /* | Specifier DecList SEMI EOL*/
           | error SEMI {}
;

DecList    : Dec { 
               $$ = createNode("DecList"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
           | Dec COMMA DecList { 
               $$ = createNode("DecList"," ",Node_Program,d_gray);
               addChild($$,$1,1);
               addChild($$,$2,2);
               addChild($$,$3,3); 
             }
;

Dec        : VarDec { 
               $$ = createNode("Dec"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
             }
           | VarDec ASSIGNOP Exp { 
               $$ = createNode("Dec"," ",Node_Program,d_gray); 
               addChild($$,$1,1); 
               addChild($$,$2,2);
               addChild($$,$3,3); 
             }
;

/*Expressions*/

Exp       : Exp ASSIGNOP Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1);
              addChild($$,$2,2);
              addChild($$,$3,3); 
            }
          | Exp AND Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray);
              addChild($$,$1,1);
              addChild($$,$2,2);
              addChild($$,$3,3);
            }
          | Exp OR Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
              addChild($$,$2,2);
              addChild($$,$3,3); 
            }
          | Exp RELOP Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray);
              addChild($$,$1,1); 
              addChild($$,$2,2); 
              addChild($$,$3,3); 
            }
          | Exp PLUS Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray);
              addChild($$,$1,1); 
              addChild($$,$2,2);
              addChild($$,$3,3); 
            }
          | Exp MINUS Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
              addChild($$,$2,2); 
              addChild($$,$3,3); 
            }
          | Exp STAR Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
              addChild($$,$2,2);
              addChild($$,$3,3);
            }
          | Exp DIV Exp { 
              $$ = createNode("Expf"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
              addChild($$,$2,2); 
              addChild($$,$3,3); 
            }
          | LP Exp RP { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1);
              addChild($$,$2,2);
              addChild($$,$3,3); 
            }
          | MINUS Exp { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1);
              addChild($$,$2,2); 
            }
          | NOT Exp {
              $$ = createNode("Exp"," ",Node_Program,d_gray);
              addChild($$,$1,1);
              addChild($$,$2,2);
            }
          | ID LP Args RP { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1);
              addChild($$,$2,2); 
              addChild($$,$3,3);
              addChild($$,$4,4); 
            }
          | ID LP RP { 
              $$ = createNode("Exp"," ",Node_Program,d_gray);
              addChild($$,$1,1);
              addChild($$,$2,2);
              addChild($$,$3,3); 
            }
          | Exp LB Exp RB { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
              addChild($$,$2,2);
              addChild($$,$3,3); 
              addChild($$,$4,4);
            }
          | Exp LB error RB { 
              PrintError("Missing \"]\" ?\n");
              error_exist = true;
              /*yyerrok;*/ 
            }
          | Exp DOT ID { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
              addChild($$,$2,2); 
              addChild($$,$3,3); 
            }
          | ID { 
              $$ = createNode("Exp"," ",Node_Program,d_gray);
              addChild($$,$1,1); 
            }
          | INT { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
            }
          | FLOAT { 
              $$ = createNode("Exp"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
            }
;

Args      : Exp COMMA Args { 
              $$ = createNode("Args"," ",Node_Program,d_gray); 
              addChild($$,$1,1); 
              addChild($$,$2,2); 
              addChild($$,$3,3); 
            }
          | Exp { 
              $$ = createNode("Args"," ",Node_Program,d_gray); 
              addChild($$,$1,1);
            }
;

/*
start: 
 | start expr EOL {
     int digit = 0;
     while(($2-(int)($2))>0){
       digit += 1;
       $2 *= 10;
     }
     if(digit==0)
       printf("= %d\n> ", (int)$2);
     else
       printf("= %.*lf\n> ", digit,$2); 
   }
 ;

expr: term
 | expr PLUS term { $$ = $1 + $3; }
 | expr MINUS term { $$ = $1 - $3; } 
 ;

term: factor { $$ = $1; }
 | term STAR factor { $$ = $1 * $3; }
 | term DIV factor { $$ = $1 / $3; } 
 ;

factor: INT { $$ = $1; }
 | FLOAT { $$ = $1; }
 | LP expr RP { $$ = $2; }
 ;
*/

%%
int main(int argc,char **argv)
{
  FILE* f=fopen(argv[1],"r");
  if(!f){ 
    perror(argv[1]);
    return 1;
  } 
  yylineno=1;
  //yyin=f;  
  yyrestart(f);
  yyparse();
  if(!error_exist){
    //No tree will be printed;
    //printTree(Root,0);
    initHashTable();
    traverse(Root);
    //validateTable();
    //debugShowSymbol();
  }
  else
    PrintHint("Solve the errors come first\n");
  return 0;
}

int yyerror(const char *s)
{
  fprintf(stderr, NONE"Error type B at Line %d:%s\n",yylineno,s);
  //fprintf(stderr, "error: %s\n", s);
}

