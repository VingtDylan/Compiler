%{
  #include "syntax.tab.h"
  int lexerror(char *s);
  int getbinvalue(char ch);
  int getoctvalue(char ch);
  int gethexvalue(char ch);
  int atobin(char *s);
  int atooct(char *s);
  int atohex(char *s);
%}
/*
typedef union YYSTYPE{
  int ivalue;
  float fvalue;
  double dvalue;
}YYSTYPE;

extern YYSTYPE yylval;
*/
digit [0-9]
letter [a-zA-Z]
bindigit [01]
octdigit [0-7]
hexdigit [0-9a-fA-F]

%%
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"(" { return LP; }
")" { return RP; }
{digit}+  { yylval.ivalue = atoi(yytext); return NUM; }
0[bB]{bindigit}+ { yylval.ivalue = atobin(yytext); return BINNUM; }
0[oO]{octdigit}+ { yylval.ivalue = atooct(yytext); return OCTNUM; }
0[xX]{hexdigit}+ { yylval.ivalue = atohex(yytext); return HEXNUM; }
e{digit}+ { yylval.dvalue = atof("0.001"); return EXPFLOAT;}
\n      { return EOL; }
[ \t]   { /* ignore white space */ }
.   { lexerror(yytext); }
%%

int lexerror(char *s){
  fprintf(stderr, "lexical error: %s\n", s);
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

int atooct(char *s){
  int sum = 0;
  int radius = 1;
  int len = strlen(s);
  for(int i = len-1;i > 1;i--){
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
