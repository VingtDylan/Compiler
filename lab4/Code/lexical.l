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

%option yylineno

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

EXPFLOAT {digit}*[.]{digit}*[eE][+-]?{digit}+
EXPERROR ([.]?[eE]{digit}*)|({digit}*[.]{digit}*[eE][+-]?)
COMMONFLOAT {digit}+[.]{digit}+f?
FLOAT {EXPFLOAT}|{COMMONFLOAT}

COMERROR \/\*([^\/^\*]*|(\/[^\*])|(\*[^\/]))*\/\*
COMMENT (\/\*([^\*\/]*|(\*[^\/])|(\/[^\*]))*\*\/)|(\/\/[^\n]*[\n])

TYPE int|float|double
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
ID [_a-zA-Z][_a-zA-Z0-9]*

%%

; { yylval.treenode = createNode("SEMI",yytext,Node_Sign,blue);
    return SEMI; }
, { yylval.treenode = createNode("COMMA",yytext,Node_Sign,blue);
    return COMMA; }
= { yylval.treenode = createNode("ASSIGNOP",yytext,Node_Sign,blue);
    return ASSIGNOP; }
>|<|>=|<=|==|!= { yylval.treenode = createNode("RELOP",yytext,Node_Sign,blue);
                  return RELOP; }
"+" { yylval.treenode = createNode("PLUS",yytext,Node_Op,cyan);
      return PLUS; }
"-" { yylval.treenode = createNode("MINUS",yytext,Node_Op,cyan);
      return MINUS; }
"*" { yylval.treenode = createNode("STAR",yytext,Node_Op,cyan);
      return STAR; }
"/" { yylval.treenode = createNode("DIV",yytext,Node_Op,cyan);
      return DIV; }
"&&" { yylval.treenode = createNode("AND",yytext,Node_Logic,yellow);
       return AND; }
"||" { yylval.treenode = createNode("OR",yytext,Node_Logic,yellow);
       return OR; }
"." { yylval.treenode = createNode("DOT",yytext,Node_Fun,l_cyan);
      return DOT; }
"!" { yylval.treenode = createNode("NOT",yytext,Node_Fun,l_cyan);
      return NOT; }
"(" { yylval.treenode = createNode("LP",yytext,Node_Fun,l_cyan);
      return LP; }
")" { yylval.treenode = createNode("RP",yytext,Node_Fun,l_cyan);
      return RP; }
"[" { yylval.treenode = createNode("LB",yytext,Node_Fun,l_cyan);
      return LB; }
"]" { yylval.treenode = createNode("RB",yytext,Node_Fun,l_cyan);
      return RB; }
"{" { yylval.treenode = createNode("LC",yytext,Node_Fun,l_cyan);
      return LC; }
"}" { yylval.treenode = createNode("RC",yytext,Node_Fun,l_cyan);
      return RC; }
{TYPE} { yylval.treenode = createNode("TYPE",yytext,Node_ID,l_purple);
         return TYPE; }
{STRUCT} { yylval.treenode = createNode("STRUCT",yytext,Node_ID,l_purple); 
           return STRUCT; }
{RETURN} { yylval.treenode = createNode("RETURN",yytext,Node_ID,l_purple);
           return RETURN; }
{IF} { yylval.treenode = createNode("IF",yytext,Node_ID,l_purple);
       return IF; }
{ELSE} { yylval.treenode = createNode("ELSE",yytext,Node_ID,l_purple);
         return ELSE; }
{WHILE} { yylval.treenode = createNode("WHILE",yytext,Node_ID,l_purple);
          return WHILE; }
{DEC} { /*yylval.ivalue = atoi(yytext);*/
        yylval.treenode = createNode("INT",yytext,Node_Data,green);
        return INT; }
{BIN} { yylval.ivalue = atobin(yytext); 
        snprintf(yytext, 10,"%d",atobin(yytext));
        yylval.treenode = createNode("INT",yytext,Node_Data,green);
        return INT; }
{BINERROR} { fprintf(stderr,"Error type A at Line %d: check the bin number \"%s\" !\n",yylineno,yytext); 
             error_exist=true;
             return INT; }
{OCT1} { /*yylval.ivalue = atooct(yytext,1);*/ 
         snprintf(yytext, 10,"%d",atooct(yytext,1));
         yylval.treenode = createNode("INT",yytext,Node_Data,green);
         return INT; }
{OCT2} { /*yylval.ivalue = atooct(yytext,2);*/
         snprintf(yytext, 10,"%d",atooct(yytext,2));
         yylval.treenode = createNode("INT",yytext,Node_Data,green);
         return INT; }
{OCTERROR} { fprintf(stderr,"Error type A at Line %d: check the oct number \"%s\" !\n",yylineno,yytext);
             error_exist = true;
             return INT; }
{HEX} { /*yylval.ivalue = atohex(yytext);*/
        snprintf(yytext, 10,"%d",atohex(yytext));
        yylval.treenode = createNode("INT",yytext,Node_Data,green);
        return INT; }
{HEXERROR} { fprintf(stderr,"Error type A at Line %d: check the hex number \"%s\" !\n",yylineno,yytext); 
             error_exist = true; 
             return INT; }
{EXPFLOAT} { /*yylval.dvalue = atof("0.001");*/
             //snprintf(yytext, 10,"%f",atof(yytext));
             yylval.treenode = createNode("FLOAT",yytext,Node_Data,green);
             /*yylval.treenode = createNode("EXPFLOAT",yytext,Node_Data,green);*/
             return FLOAT; }
{EXPERROR} { fprintf(stderr,"Error Type A at Line %d: check the float number \"%s\" !\n",yylineno,yytext);
             error_exist = true;
             return FLOAT;  }
{COMMONFLOAT} { /*yylval.fvalue = atof(yytext);*/
                yylval.treenode = createNode("FLOAT",yytext,Node_Data,green);     
                /*yylval.treenode = createNode("COMMONFLOAT",yytext,Node_Data,green);*/
                return FLOAT; }
[\n]+      { yycolumn=1; /*return EOL;*/ }
[ \t\r]+   { /* ignore white space */ }
{COMMENT} { /*PrintHint("Here is a comment!");
            printf("at Line %d!\n",yylineno);*/ }
{COMERROR} { fprintf(stderr,"Error Type B at line %d: nested comment error!\n",yylineno);
             error_exist = true; }
{ID} { /*printf("this is a ID \"%s\"\n",yytext);*/ 
       yylval.treenode =createNode("ID",yytext,Node_ID,l_purple);
       return ID; }
.   { error_exist=true;
      lexerror(yytext); }

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
