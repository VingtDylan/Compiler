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
  extern bool error_exist;
  int lexerror(char *s);
  int getbinvalue(char ch);
  int getoctvalue(char ch);
  int gethexvalue(char ch);
  int atobin(char *s);
  int atooct(char *s,int option);
  int atohex(char *s);
%}

digit [0-9]
letter [a-zA-Z]
bin [01]
oct [0-7]
hex [0-9a-fA-F]

BIN 0[bB]{bin}*
BINERROR 0[bB][0-9a-zA-Z]* 
DEC ([1-9]{digit}*)|0
OCT2 0{oct}*
OCT1 0[oO]{oct}*
OCTERROR 0[0-9a-wyzA-WYZ][0-9a-zA-Z]*
HEX 0[xX]{hex}*
HEXERROR 0[xX][0-9a-zA-Z]*

EXPFLOAT e{digit}*
COMMONFLOAT {digit}*[.]{digit}+f?
FLOAT {EXPFLOAT}|{COMMONFLOAT}

COMMENT \/\*([^*]|(\*[^"/"]))*\*\/[\n]*

TYPE int|float|double
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
ID [_a-zA-Z][_a-zA-Z0-9]*

%%

; { return SEMI; }
, { return COMMA; }
= { return ASSIGNOP; }
>|<|>=|<=|==|!= { return RELOP; }
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
{DEC} { yylval.ivalue = atoi(yytext); 
        yylval.treenode = createNode("DEC",yytext,Node_Data,green);
        return INT; 
      }
{BIN} { yylval.ivalue = atobin(yytext); 
        yylval.treenode = createNode("BIN",yytext,Node_Data,green);
        return INT; }
{BINERROR} { fprintf(stderr,"Error type A at Line %d: check the bin number \"%s\" !\n",yylineno,yytext); error_exist=true; return INT; }
{OCT1} { yylval.ivalue = atooct(yytext,1); 
         yylval.treenode = createNode("OCT",yytext,Node_Data,green);
         return INT; }
{OCT2} { yylval.ivalue = atooct(yytext,2);
         yylval.treenode = createNode("OCT",yytext,Node_Data,green);
         return INT; }
{OCTERROR} { fprintf(stderr,"Error type A at Line %d: check the oct number \"%s\" !\n",yylineno,yytext); error_exist=true; return INT; }
{HEX} { yylval.ivalue = atohex(yytext); 
        yylval.treenode = createNode("HEX",yytext,Node_Data,green);
        return INT; }
{HEXERROR} { fprintf(stderr,"Error type A at Line %d: check the hex number \"%s\" !\n",yylineno,yytext); error_exist=true; return INT; }
{EXPFLOAT} { yylval.dvalue = atof("0.001"); 
             yylval.treenode = createNode("EXPFLOAT",yytext,Node_Data,green);
             return FLOAT; }
{COMMONFLOAT} { yylval.fvalue = atof(yytext);
                yylval.treenode = createNode("COMMONFLOAT",yytext,Node_Data,green);
                return FLOAT; }
[\n]+      { yycolumn=1; /*return EOL;*/ }
[ \t\r]+   { /* ignore white space */ }
{COMMENT} { PrintHint("Here is a comment!\n"); }
{ID} { /*printf("this is a ID \"%s\"\n",yytext);*/ return ID; }
.   { lexerror(yytext); }

%%


int yywrap(){
  return 1;
}

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
