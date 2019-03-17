%locations
%error-verbose
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "grammertree.h"
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
  double dvalue;
  char *string;
  struct Node* treenode; 
}

%token <string> ID
%token <ivalue> INT
%token <fvalue> FLOAT

%token SEMI COMMA ASSIGNOP RELOP
%token PLUS MINUS STAR DIV   
%token AND OR DOT NOT
%token TYPE STRUCT
%token LP RP LB RB LC RC
%token IF ELSE WHILE
%token RETURN EOL

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

%start Program

%%
/*High-Level Definition*/

Program: ExtDefList
;

ExtDefList: ExtDef ExtDefList
 |
;

ExtDef: Specifier ExtDecList SEMI
/* | Specifier ExtDecList SEMI EOL EOL*/
 | Specifier SEMI
/* | Specifier SEMI EOL EOL*/
 | Specifier FunDec CompSt
/* | Specifier FunDec CompSt EOL*/
 | error SEMI { /*yyerrok;*/ }
;

ExtDecList: VarDec
 | VarDec COMMA ExtDecList
;

/* Specifier*/

Specifier: TYPE
 | StructSpecifier
;

StructSpecifier: STRUCT OptTag LC DefList RC
 | STRUCT Tag
;

OptTag: ID
 |
;

Tag: ID
;

/*Declarators*/

VarDec: ID
 | VarDec LB INT RB
 | VarDec LB error RB { /*yyerrok;*/ }
;

FunDec: ID LP VarList RP
 | ID LP RP
 | error RP { /*yyerrok;*/ }
;

VarList: ParamDec COMMA VarList
 | ParamDec
;

ParamDec: Specifier VarDec
 | error COMMA { /*yyerrok;*/ }
 | error RP { /*yyerrok;*/ }
;

/*Statements*/

CompSt: LC DefList StmtList RC
/*| LC EOL DefList StmtList RC*/
 | LC error RC { }
;

StmtList:Stmt StmtList
 |
;

Stmt: Exp SEMI
 | CompSt
 | RETURN Exp SEMI
 | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
 | IF LP Exp RP Stmt ELSE Stmt
 | IF LP Exp RP error ELSE Stmt { PrintError("Missing \";\" ?\n");  /*yyerrok;*/ } 
 | WHILE LP Exp RP Stmt
;

/*Local Definitions*/

DefList: Def DefList
 | 
;

Def: Specifier DecList SEMI
/* | Specifier DecList SEMI EOL*/
 | error SEMI {}
;

DecList: Dec
 | Dec COMMA DecList
;

Dec: VarDec
 | VarDec ASSIGNOP Exp
;

/*Expressions*/

Exp: Exp ASSIGNOP Exp {}
 | Exp AND Exp {}
 | Exp OR Exp {}
 | Exp RELOP Exp {}
 | Exp PLUS Exp {}
 | Exp MINUS Exp {}
 | Exp STAR Exp {}
 | Exp DIV Exp {}
 | LP Exp RP {}
 | MINUS Exp {}
 | NOT Exp {}
 | ID LP Args RP {}
 | ID LP RP {}
 | Exp LB Exp RB {}
 | Exp LB error RB { PrintError("Missing \"]\" ?\n"); /*yyerrok;*/ }
 | Exp DOT ID {}
 | ID {}
 | INT {}
 | FLOAT {}
;

Args: Exp COMMA Args {}
 | Exp {}
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
  if(!error_exist)
    printTree(Root,0);
  else
    PrintHint("Solve the errors come first\n");
  return 0;
}

int yyerror(const char *s)
{
  fprintf(stderr, NONE"Error type B at Line %d:%s\n",yylineno,s);
  //fprintf(stderr, "error: %s\n", s);
}

