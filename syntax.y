%{
  #include <stdio.h>
  #include <stdlib.h>
  int yyerror(char *s);
  int yylex();
  extern FILE *yyin;
%}

/* set attribute type for test */
/* %define api.value.type {int} */

/* declare tokens (terminal symbols) */
%union{
  int ivalue;
  float fvalue;
  double dvalue;
}

%token <ivalue> NUM 
%token <ivalue> BINNUM
%token <ivalue> OCTNUM
%token <ivalue> HEXNUM

%token <dvalue> EXPFLOAT

%token ADD 
%token SUB 
%token MUL 
%token DIV 

%token LP 
%token RP 

%token EOL 

%type <dvalue> expr term factor 

%%

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
 | expr ADD term { $$ = $1 + $3; }
 | expr SUB term { $$ = $1 - $3; } 
 ;

term: factor { $$ = $1; }
 | term MUL factor { $$ = $1 * $3; }
 | term DIV factor { $$ = $1 / $3; } 
 ;

factor: NUM { $$ = $1; }
 | BINNUM { $$ = $1; }
 | OCTNUM { $$ = $1; }
 | HEXNUM { $$ = $1; }
 | EXPFLOAT { $$ = $1; }
 | LP expr RP { $$ = $2; }
 ;

%%
int main(int argc,char **argv)
{
  FILE* f=fopen(argv[1],"r");
  if(!f){ 
    perror(argv[1]);
    return 1;
  } 
  printf(">\n");
  yyin=f;  
  yyparse();
  return 0;
}

int yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
}

