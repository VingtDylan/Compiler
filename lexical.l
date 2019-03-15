%option yylineno
%{
  #include "syntax.tab.h"
  #include "grammertree.h"
  int yycolumn=1;
  #define YY_USER_ACTION\
    yylloc.first_line=yylloc.last_line=yylineno;\
    yylloc.first_column=yycolumn;\
    yylloc.last_column=yycolumn+yyleng-1;\
    yycolumn+=yyleng;
  int lexerror(char *s);
  int getbinvalue(char ch);
  int getoctvalue(char ch);
  int gethexvalue(char ch);
  int atobin(char *s);
  int atooct(char *s,int option);
  int atohex(char *s);
%}

digit [0-9]
positive [1-9]
letter [a-zA-Z]
bindigit [01]
octdigit [0-7]
hexdigit [0-9a-fA-F]
COMMENT \/\*([^*]|(\*[^"/"]))*\*\/[\n]*
TYPE int|float|double
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
ID [_a-zA-Z][_a-zA-Z0-9]*

%%

";" { return SEMI; }
"," { return COMMA; }
"=" { return ASSIGNOP; }
">"|"<"|">="|"<="|"=="|"!=" { return RELOP; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return STAR; }
"/" { return DIV; }
"&&" { return AND; }
"||" { return OR; }
"." { return DOT; }
"!" { return NOT; }
"(" { return LP; }
")" { return RP; }
"[" { return LB; }
"]" { return RB; }
"{" { return LC; }
"}" { return RC; }
{TYPE} { return TYPE; }
{STRUCT} { return STRUCT; }
{RETURN} { return RETURN; }
{IF} { return IF; }
{ELSE} { return ELSE; }
{WHILE} { return WHILE; }
{positive}{digit}*|0  { yylval.ivalue = atoi(yytext); return INT; }
0[bB]{bindigit}+ { yylval.ivalue = atobin(yytext); return INT; }
0[oO]{octdigit}+ { yylval.ivalue = atooct(yytext,1); return INT; }
0{octdigit}+ { yylval.ivalue = atooct(yytext,2); return INT; }
0[xX]{hexdigit}+ { yylval.ivalue = atohex(yytext); return INT; }
e{digit}+ { yylval.dvalue = atof("0.001"); return FLOAT;}
[\n]+      { yycolumn=1; /*return EOL;*/ }
[ \t\r]*   { /* ignore white space */ }
{COMMENT} { printf("here is a comment!\n"); }
{ID} { return ID;printf("this is a ID%s\n",yytext); }
.   { lexerror(yytext); }

%%

int lexerror(char *s){
  fprintf(stderr, "lexical error!Error type A at Line %d:Mysterious character \"%s\"\n", yylineno,s);
}

int getbinvalue(char ch){
  if(ch>='0' && ch<='1')
    return ch-'0';
  return -1;
}

int getoctvalue(char ch){
  if(ch>='0' && ch<='7')
    return ch-'0';
  return -1;
}

int gethexvalue(char ch){
  if(ch>='0' && ch<='9')
    return ch-'0';
  if(ch>='A' && ch<='F')
    return ch-'A'+10;
  if(ch>='a' && ch<='f')
    return ch-'a'+10;
  return -1;
}

int atobin(char *s){
  int sum = 0;
  int radius = 1;
  int len = strlen(s);
  for(int i = len-1;i > 1;i--){
    sum += radius*getbinvalue(*(s+i));
    radius *= 2;
  }
  return sum;
}

int atooct(char *s,int option){
  int sum = 0;
  int radius = 1;
  int len = strlen(s);
  for(int i = len-1;i > (2-option);i--){
    sum += radius*getoctvalue(*(s+i));
    radius *= 8;
  }
  return sum;
}

int atohex(char *s){
  int sum = 0;
  int radius = 1;
  int len = strlen(s);
  for(int i = len-1;i > 1;i--){
    sum += radius*gethexvalue(*(s+i));
    radius *= 16; 	
  } 
  return sum;
}
