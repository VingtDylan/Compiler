#include "grammertree.h"
#include "semantic.h"
#include "semanticTraverse.h"
#include "string.h"

extern FieldList hashTable[MAX_HASH_SIZE];
extern InterCode *IRList;

unsigned int hash_pjw(char *name){
  unsigned int val = 0, i;
  for(; *name; ++name){
    val = (val << 2) + *name;
    if(i=val & ~0x3fff)
      val = (val ^ (i>>12)) & 0x3fff;
  }
  return val%MAX_HASH_SIZE;
}

int getSize(Type type,int n){
  if(type==NULL)
    return 0;
  if(n==0){
    if(type->kind==BASIC)
      return 4;
    int size=4;
    while(type->u.array.elem->kind!=BASIC){
      size=type->u.array.size*size;
      type=type->u.array.elem;
    }
    size=type->u.array.size*size;
    if(type->u.array.elem->kind==BASIC)
      return size;
  }else if(n==2){
    if(type->u.array.elem->kind==BASIC)
      return 4;
    int size=4;
    while(type->u.array.elem->kind!=BASIC){
      size=type->u.array.size*size;
      if(type->u.array.elem->u.array.elem->kind==BASIC)
	return size;
      type=type->u.array.elem;
    }
    size=type->u.array.size*size;
    return size;
  }
  return 1;
}

void initHashTable(){
  for(int i=0; i<MAX_HASH_SIZE; i++){
    hashTable[i] = NULL;
  }
  /*Extar Function->read()&&write()*/
  /*int read()*/
  FieldList readField=(FieldList)malloc(sizeof(FieldList_));
  readField->name="read";
  Type readType=(Type)malloc(sizeof(Type_));
  readType->kind=FUNCTION;
  Type readReturn=(Type)malloc(sizeof(Type_));
  readReturn->kind=BASIC;
  readReturn->u.basic=INT_TYPE;
  readType->u.function.funcType=readReturn;
  readType->u.function.paranum=0;
  readType->u.function.parameters=NULL;
  readField->type=readType;
  readField->defined=defined;
  insertSymbol(readField);
  /*int write(int write(param)*/
  FieldList writeField=(FieldList)malloc(sizeof(FieldList_));
  writeField->name="write";
  Type writeType=(Type)malloc(sizeof(Type_));
  writeType->kind=FUNCTION;
  Type writeReturn=(Type)malloc(sizeof(Type_));
  writeReturn->kind=BASIC;
  writeReturn->u.basic=INT_TYPE;
  writeType->u.function.funcType=writeReturn;
  writeType->u.function.paranum=1;
  FieldList writeParam=(FieldList)malloc(sizeof(FieldList_));
  writeParam->name="param_of_write";
  Type writeParamType=(Type)malloc(sizeof(Type_));
  writeParamType->kind=BASIC;
  writeParamType->u.basic=INT_TYPE;
  writeParam->type=writeParamType;
  writeType->u.function.parameters=writeParam;
  writeField->type=writeType;
  writeField->defined=defined;
  insertSymbol(writeField);
}
 
int insertSymbol(FieldList symbol){
  //printf(GREEN"debug->name-%s kind-%d\n"NONE,symbol->name,symbol->type->kind);
  if(symbol==NULL||symbol->name==NULL)
    return 0;
  unsigned int hashkey;
  //symbol->hashflag.flag =wander;
  //symbol->hashflag.hashed = 0;
  if(symbol->type->kind==FUNCTION){
    //printf(GREEN"debug->name-%s kind-%d\n"NONE,symbol->name,symbol->type->kind);
    hashkey=hash_pjw(1+symbol->name);
  }
  else
    hashkey=hash_pjw(symbol->name);
  if(hashTable[hashkey]==NULL){
    symbol->hashflag.flag=arranged;
    hashTable[hashkey]=symbol;
    return 1;
  }
  while(1){
    hashkey=(++hashkey)%MAX_HASH_SIZE;
    //symbol->hashflag.hashed+=1;
    if(hashTable[hashkey]==NULL){
      //symbol->hashflag.flag=arranged;
      hashTable[hashkey]=symbol;
      return 1;
    }
    if(symbol->hashflag.hashed>MAX_HASH_SIZE){
      //symbol->hashflag.flag=extra;
      PrintSymbol("The hashtable is full!\n");
    }
  }
  return 0;
}

void debugShowSymbol(){
  for(int i=0;i<MAX_HASH_SIZE;i++)
    if(hashTable[i]!=NULL)
      printf(CYAN"hashTable->id:%d: SymbolName:%s Kind:%d\n"NONE,i,hashTable[i]->name,hashTable[i]->type->kind);
}

void validateTable(){
  for(int i=0;i<MAX_HASH_SIZE;i++){
    if(hashTable[i]!=NULL&&hashTable[i]->defined==undefined&&hashTable[i]->type->kind==FUNCTION){
      printf(CYAN"Error type 18 at Line %d: Undefined function \"%s\".\n"NONE,hashTable[i]->lineno,hashTable[i]->name);
    }/*else if(hashTable[i]!=NULL&&hashTable[i]->parent!=NULL){
        printf(GREEN"%s:%s\n"NONE,hashTable[i]->name,hashTable[i]->parent); 
    }*/
  }
}

void debugShowAllSymbol(){
  static char *CODE_KIND_STR[19]={
    [GOTO_CODE]="GOTO_CODE",
    [IF_GOTO_CODE]="IF_GOTO_CODE",
    [ASSIGN_CODE]="ASSIGN_CODE",
    [PLUS_CODE]="PLUS_CODE",
    [MINUS_CODE]="MINUS_CODE",
    [MUL_CODE]="MUL_CODE",
    [DIV_CODE]"DIV_CODE",
    [READ_CODE]="READ_CODE",
    [WRITE_CODE]="WRITE_CODE",
    [FUNCTION_CODE]="FUNCTION_CODE",
    [CALL_CODE]="CALL_CODE",
    [ARG_CODE]="ARG_CODE",
    [PARAMETER_CODE]="PARAMETER_CODE",
    [RETURN_CODE]="RETURN_CODE",
    [GET_ADDR_CODE]="GET_ADDR_CODE",
    [GET_VALUE_CODE]="GET_VALUE_CODE",
    [DEC_CODE]="DEC_CODE",
    [ADDRASSIGN_CODE]="ADDRASSIGN_CODE"
  };
  InterCode ir;
  for(int i=0;i<IRlength;i++){
    ir=IRList[i];
    if(ir==NULL)
      continue;
    else{
      printf("%d:%s\n",i,CODE_KIND_STR[ir->kind]); 
    }
  }
}

FieldList indexSymbol(char *name,bool isFunc){
  if(name==NULL)
     return NULL;
  unsigned int hashkey;
  if(isFunc)
     hashkey=hash_pjw(1+name);
  else
     hashkey=hash_pjw(name);
  FieldList tmpSymbol=hashTable[hashkey];
  while(tmpSymbol!=NULL){
    if(/*tmpSymbol->hashflag.flag==arranged&&*/strcmp(tmpSymbol->name,name)==0){
      if(isFunc&&(tmpSymbol->type->kind==FUNCTION)){
         //printf(RED"check1:%d\n"NONE,tmpSymbol->type->kind);
         return tmpSymbol;
      }
      if(!isFunc&&(tmpSymbol->type->kind!=FUNCTION)){
         //printf(RED"check2:%d\n"NONE,tmpSymbol->type->kind);
         return tmpSymbol;
      }
    } 
    hashkey=(++hashkey)%MAX_HASH_SIZE;
    tmpSymbol=hashTable[hashkey];  
  }
  return NULL;
}

bool TypeEqual(Type type1,Type type2){
  if((type1==NULL)||(type2==NULL))
    return false;
  if(type1->kind!=type2->kind)
    return false;
  else{
    switch(type1->kind){
      case BASIC:{     
        if(type1->u.basic==type2->u.basic)
	  return true;
	else
          return false;
      }
        break;
      case ARRAY:{
	if(TypeEqual(type1->u.array.elem,type2->u.array.elem))
	  return true;
	else 
	  return false;
      }
	  break;
      case STRUCTURE:{
	FieldList structure1=type1->u.structure;
	FieldList structure2=type2->u.structure;
	if((structure1!=NULL)&&(structure2!=NULL)){
	  while((structure1!=NULL)&&(structure2!=NULL)){
            if(!TypeEqual(structure1->type,structure2->type))
	      return false;
	    structure1=structure1->tail;
	    structure2=structure2->tail;
	  }
	  if((structure1==NULL)&&(structure2==NULL))
	    return true;
	}
	return false;
      }
          break;
      case FUNCTION:{
	if(type1->u.function.paranum!=type2->u.function.paranum)
	  return false;
	FieldList param1=type1->u.function.parameters;
	FieldList param2=type2->u.function.parameters;
        for(int i=0;i<type1->u.function.paranum;i++){
	  if(!TypeEqual(param1->type,param2->type))
	    return false;
	  param1=param1->tail;
   	  param2=param2->tail;
	}
	return true;
      }
        break;
      default:{
        printf(RED"The type is not supported"NONE);
	return false;
      }
        break;
    }
  }
}

Type Specifier(TreeNode *root,char *pname){
  Type specifier=(Type)malloc(sizeof(Type_));
  if(strcmp(root->child[0]->name,"TYPE")==0){
    /*TYPE*/
    specifier->kind=BASIC;
    if(strcmp(root->child[0]->value,"int")==0)
      specifier->u.basic=INT_TYPE;
    else
      specifier->u.basic=FLOAT_TYPE;
    return specifier;
  }else{
    /*tructSpecifer*/
    specifier->kind=STRUCTURE;
    if(root->child[0]->child_num==2){
      /*STRUCT Tag*/
      char *tagName=root->child[0]->child[1]->child[0]->value;
      FieldList field=indexSymbol(tagName,false);
      if(field==NULL){
        printf(CYAN"Error type 17 at Line %d: Undefined structure \"%s\".\n"NONE,root->lineno,tagName);
        specifier->u.structure=NULL;
        return specifier;
      }else if(field->type!=NULL)
        return field->type;
      specifier->u.structure=NULL;
        return specifier;
   }else{
      /*STRUCT OptTag LC DefList RC*/
      TreeNode* DefList=root->child[0]->child[3];
      specifier->u.structure=NULL;
      while(DefList!=NULL){
        /*Def DefList*/
        TreeNode *Def=DefList->child[0];
        Type symbolType=Specifier(Def->child[0],pname);
        TreeNode* DecList=Def->child[1];
        while(DecList->child_num==3){
          /*Dec COMMA DecList*/
          FieldList field=VarDec(DecList->child[0]->child[0],symbolType,pname,1/*Undone*/);        
          if(DecList->child[0]->child_num!=1)
             printf(CYAN"Error type 15 at Line %d: Variable %s in struct is initialized.\n"NONE,Def->lineno,field->name);
          FieldList structureField=specifier->u.structure;
          while(structureField!=NULL){
             if(strcmp(structureField->name,field->name)==0){
               printf(CYAN"Error type 15 at Line %d: Redefined field \"%s\".\n"NONE,Def->lineno,field->name);
               break;
             }
             structureField=structureField->tail;
          }
          if(structureField==NULL){
            if(indexSymbol(field->name,false)!=NULL)
              printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,Def->lineno,field->name);
	    else{
	      insertSymbol(field);
              field->tail=specifier->u.structure;
              specifier->u.structure=field;
	    }
          }
          DecList=DecList->child[2];
        }
        FieldList field=VarDec(DecList->child[0]->child[0],symbolType,pname,1/*Undone*/);
        if(DecList->child[0]->child_num!=1)
          printf(CYAN"Error type 15 at Line %d: Variable \"%s\" in struct is initialized.\n"NONE,Def->lineno,field->name);
            FieldList structureField=specifier->u.structure;
              while(structureField!=NULL){
                if(strcmp(structureField->name,field->name)==0){
                  printf(CYAN"Error type 15 at Line %d: Redefined field \"%s\".\n"NONE,Def->lineno,field->name);
                  break;
                }
                structureField=structureField->tail;
              }
              if(structureField==NULL){
	        if(indexSymbol(field->name,false)!=NULL)
		  printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,Def->lineno,field->name);
		else{
		  insertSymbol(field);
                  field->tail=specifier->u.structure;
                  specifier->u.structure=field;
		}
              }
              DefList=DefList->child[1];
        }
        if(root->child[0]->child[1]!=NULL){
          /*OptTag*/
          FieldList field=(FieldList)malloc(sizeof(FieldList_));
          field->type=specifier;
          char *optTagName=root->child[0]->child[1]->child[0]->value;
          field->name=optTagName;
          if(indexSymbol(field->name,false)!=NULL)
            printf(CYAN"Error type 16 at Line %d: Duplicated name \"%s\".\n"NONE,root->lineno,field->name);
          else
            insertSymbol(field);
         }
         return specifier;
      }
   }
}


FieldList VarDec(TreeNode *root,Type basictype,char *pname,int index){
  /*if(root==NULL)
    return NULL;
  if(strcmp(root->child[0]->name,"ID")==0){
    FieldList field=(FieldList)malloc(sizeof(FieldList_));
    field->name,root->child[0]->value;
    strcat(field->parent,pname);
    field->type=basictype;
    return field;
  }else
    return NULL;*/
  TreeNode *VarDecRoot=root;
  int i=0;
  while(strcmp(VarDecRoot->child[0]->name,"ID")!=0){
    VarDecRoot=VarDecRoot->child[0];
    i++;
  }
  char *s=VarDecRoot->child[0]->value;
  FieldList field=(FieldList)malloc(sizeof(FieldList_));
  field->name=s;
  strcat(field->parent,pname);
  //field->lineno=VarDecRoot->child[0]->lineno;
  if(strcmp(root->child[0]->name,"ID")==0){
    field->type=basictype;
    //printf(RED"%d"NONE,basictype->u.basic);
    return field;
  }
  switch(i){
    case 1:{
      Type var1=(Type)malloc(sizeof(Type_));
      var1->kind=ARRAY;
      var1->u.array.size=atoi(root->child[2]->value);
      var1->u.array.elem=basictype;
      field->type=var1;
      field->defined=defined;
      return field;
    }
      break;
    case 2:{
      Type var1=(Type)malloc(sizeof(Type_));
      var1->kind=ARRAY;
      var1->u.array.size=atoi(root->child[2]->value);
      var1->u.array.elem=basictype;
      Type var2=(Type)malloc(sizeof(Type_));
      var2->kind=ARRAY;
      var2->u.array.size=atoi(root->child[0]->child[2]->value);
      var2->u.array.elem=var1;
      field->type=var2;
      field->defined=defined;
      //printf("1:%s,%d\n",field->name,field->defined);
      return field;
    }
      break;
    default:
      printf(RED"error in VarDec"NONE);
      break;
  }
}

Type Exp(TreeNode* root,Operand place){
  /*printTree(root,0);*/
  if(root==NULL)
    return NULL;
  else if((strcmp(root->child[0]->name,"ID")==0)&&(root->child_num==1)){
    /*ID*/
    FieldList field=indexSymbol(root->child[0]->value,false);
    if(field!=NULL){
      if(place!=NULL){
	/*
	  variable=lookup(sym_table,ID)
	  [place :=variable.name]
	*/
        place->kind=VARIABLE_OP;
        strcpy(place->u.value,root->child[0]->value);
      }
      //printf(GREEN"%s:%d\n"NONE,field->name,field->type->u.basic);
      return field->type;
    }
    else{
      printf(CYAN"Error type 1 at Line %d: Undefined variable \"%s\".\n"NONE,root->lineno,root->child[0]->value);
      return NULL;
    }
  }else if(strcmp(root->child[0]->name,"INT")==0){
    /*INT*/
    Type type=(Type)malloc(sizeof(Type_));
    type->kind=BASIC;
    type->u.basic=INT_TYPE;
    if(place!=NULL){
      /*
	value=get_value()
	[place:=value]
      */
      Operand intOp=(Operand)malloc(sizeof(Operand_));
      intOp->kind=CONSTANT_OP;
      strcpy(intOp->u.value,root->child[0]->value);
      InterCode intIR=(InterCode)malloc(sizeof(InterCode_));
      intIR->kind=ASSIGN_CODE;
      intIR->u.assignOp.right=intOp;
      place->kind=TEMP_VAR_OP;
      place->u.tvar_no=TempVarCounter++;
      intIR->u.assignOp.left=place;
      insertCode(intIR);
    } 
    return type;
  }else if(strcmp(root->child[0]->name,"FLOAT")==0){
    /*FLOAT*/
    Type type=(Type)malloc(sizeof(Type_));
    type->kind=BASIC;
    type->u.basic=FLOAT_TYPE;
    /*Appended*/
    if(place!=NULL){
      Operand floatOp=(Operand)malloc(sizeof(Operand_));
      floatOp->kind=CONSTANT_OP;
      strcpy(floatOp->u.value,root->child[0]->value);
      InterCode floatIR=(InterCode)malloc(sizeof(InterCode_));
      floatIR->kind=ASSIGN_CODE;
      floatIR->u.assignOp.right=floatOp;
      place->kind=TEMP_VAR_OP;
      place->u.tvar_no=TempVarCounter++;
      floatIR->u.assignOp.left=place;
      insertCode(floatIR);
    }
    return type;
  }else if((strcmp(root->child[0]->name,"LP")==0)||(strcmp(root->child[0]->name,"MINUS")==0)||(strcmp(root->child[0]->name,"NOT")==0)){
    if(strcmp(root->child[0]->name,"LP")==0){
      return Exp(root->child[1],place);
    }else if(strcmp(root->child[0]->name,"MINUS")==0){
      /*Minus Exp1*/
      /*
	t1=new_temp()
        code1=translate_Exp(Exp1,sym_table,t1)
	code2=[place:=t1+t2]
	code1+code2
      */
      if(strcmp(root->child[1]->child[0]->name,"INT")==0&&place!=NULL){
        int n=atoi(root->child[1]->child[0]->value);
        if(n>=0){
     	  Type numType=Exp(root->child[1],NULL);
          place->kind=CONSTANT_OP;
          sprintf(place->u.value,"-%s",root->child[1]->child[0]->value);
          return numType;/*nanshou*/
        }
      }  
      Operand expOp=(Operand)malloc(sizeof(Operand_));
      Type type=Exp(root->child[1],expOp);
      if(type==NULL)
        return NULL;
      if(place!=NULL){
        Operand zeroOp=(Operand)malloc(sizeof(Operand_));
        zeroOp->kind=CONSTANT_OP;
        strcpy(zeroOp->u.value,"0");
        InterCode minusIR=(InterCode)malloc(sizeof(InterCode_));
        minusIR->kind=MINUS_CODE;
        minusIR->u.tripleOp.result=place;
        minusIR->u.tripleOp.op1=zeroOp;
        minusIR->u.tripleOp.op2=expOp;
        place->kind=TEMP_VAR_OP;
        place->u.tvar_no=TempVarCounter++;
        insertCode(minusIR);
      }
      return type;
    }else if(strcmp(root->child[0]->name,"NOT")==0){
      /*NOT Exp1*/
      /*
	label1=new_label()
	label2=new_label();
	code0=[place:=#0]
	code1=translate_Cond(Exp,label,label2,sym_table)
	code2=[LABEL label1]+[place:=#1]
        code0+code1+code2+[LABEL label2]
      */
      //gen code0
      //[place:=0]
      InterCode NOTIR=(InterCode)malloc(sizeof(InterCode_));
      NOTIR->kind=ASSIGN_CODE;
      NOTIR->u.assignOp.left=place;
      Operand zeroOp=(Operand)malloc(sizeof(Operand_));
      zeroOp->kind=CONSTANT_OP;
      strcpy(zeroOp->u.value,"0");
      NOTIR->u.assignOp.right=zeroOp;
      if(place!=NULL){
        place->kind=TEMP_VAR_OP;
        insertCode(NOTIR);
      }
      //label1
      Operand L1=(Operand)malloc(sizeof(Operand_));
      L1->kind=LABEL_OP;
      L1->u.label_no=LabelCounter++;
      //label2
      Operand L2=(Operand)malloc(sizeof(Operand_));
      L2->kind=LABEL_OP;
      L2->u.label_no=LabelCounter++;
      //gen code1
      Type type=Condition(root,L1,L2);
      //gen code2
      //[LABEL label1]
      InterCode L1IR=(InterCode)malloc(sizeof(InterCode_));
      L1IR->kind=LABEL_CODE;    
      L1IR->u.single.op=L1;
      insertCode(L1IR);
      //[place:=1]
      if(place!=NULL){
        Operand L=(Operand)malloc(sizeof(Operand_));
        L->kind=CONSTANT_OP;
        strcpy(L->u.value,"1");
        InterCode LIR=(InterCode)malloc(sizeof(InterCode_));
        LIR->kind=ASSIGN_CODE;    
        LIR->u.assignOp.left=place;
        LIR->u.assignOp.right=L;
        insertCode(LIR);
      }
      //[LABEL label2]
      InterCode L2IR=(InterCode)malloc(sizeof(InterCode_));
      L2IR->kind=LABEL_CODE;    
      L2IR->u.single.op=L2;
      insertCode(L2IR);
      return type;
    }
    return Exp(root->child[1],place);
  }else if((strcmp(root->child[1]->name,"PLUS")==0)||(strcmp(root->child[1]->name,"MINUS")==0)||(strcmp(root->child[1]->name,"STAR")==0)||(strcmp(root->child[1]->name,"DIV")==0)){
    /*
      t1=new_temp()
      t2=new_temp()
      code1=translate_Exp(Exp,sym_table,t1)
      code2=translate_Exp(Exp,sym_table,t2)
      code3=[place := t1 Op t2]
      code1+code2+code3
    */
    Operand tmpOp1=(Operand)malloc(sizeof(Operand_));
    Operand tmpOp2=(Operand)malloc(sizeof(Operand_));
    memset(tmpOp1,0,sizeof(Operand_));
    memset(tmpOp2,0,sizeof(Operand_));
    Type type1,type2;
    bool flag1=false,flag2=false;
    //gen code1
    if(strcmp(root->child[0]->child[0]->name,"INT")==0){
      flag1=true;
      type1=Exp(root->child[0],NULL);
      tmpOp1->kind=CONSTANT_OP;
      sprintf(tmpOp1->u.value,"%s",root->child[0]->child[0]->value);
    }else{
      tmpOp1->kind=TEMP_VAR_OP;
      //printf("flag b %s\n",root->child[0]->child[0]->value);
      type1=Exp(root->child[0],tmpOp1);
      //printf(GREEN"%d\n"NONE,type1->u.basic);
    }
    //gen code2
    if(strcmp(root->child[2]->child[0]->name,"INT")==0){
      flag2=true;
      type2=Exp(root->child[2],NULL);/*0->2wsl*/
      tmpOp2->kind=CONSTANT_OP;
      sprintf(tmpOp2->u.value,"%s",root->child[2]->child[0]->value);
    }else{
      tmpOp2->kind=TEMP_VAR_OP;
      type2=Exp(root->child[2],tmpOp2);
    }
    //printf("flaga %d:%d;%d:%d\n",type1->kind,type1->u.basic,type2->kind,type2->u.basic);
    //Type type1=Exp(root->child[0],place);
    //Type type2=Exp(root->child[2],place);
    if(TypeEqual(type1,type2)==0){
      if((type1!=NULL)&&(type2!=NULL))
        printf(CYAN"Error type 7 at Line %d: Type mismatched for operands.\n"NONE,root->lineno);
        return NULL;
    }
    else {
      //gen code3
      if(place==NULL)
        return NULL;
      InterCode codeIR=(InterCode)malloc(sizeof(InterCode_));
      if(strcmp(root->child[1]->name,"PLUS")==0)
        codeIR->kind=PLUS_CODE;
      else if(strcmp(root->child[1]->name,"MINUS")==0)
        codeIR->kind=MINUS_CODE;
      else if(strcmp(root->child[1]->name,"STAR")==0)
        codeIR->kind=MUL_CODE;
      else if(strcmp(root->child[1]->name,"DIV")==0)
        codeIR->kind=DIV_CODE;
      place->kind=TEMP_VAR_OP;
      place->u.tvar_no=TempVarCounter++;
      if(flag1&&flag2){
        int num1=atoi(root->child[0]->child[0]->value);
        int num2=atoi(root->child[2]->child[0]->value);
        int result=0;
        switch(codeIR->kind){
          case PLUS_CODE:
            result=num1+num2;
            break;
          case MINUS_CODE:
            result=num1-num2;
            break;
          case MUL_CODE:
            result=num1*num2;
            break;
          case DIV_CODE:
            result=num1/num2;/*num2==0?*/
            break;
        }
        //free(tmpOp2);
        tmpOp1->kind=CONSTANT_OP;    
        sprintf(tmpOp1->u.value,"%d",result);
        codeIR->kind=ASSIGN_CODE;
        codeIR->u.assignOp.left=place;
        codeIR->u.assignOp.right=tmpOp1;
      }else{
        codeIR->u.tripleOp.op1=tmpOp1;
        codeIR->u.tripleOp.op2=tmpOp2;
        codeIR->u.tripleOp.result=place;
      }
      insertCode(codeIR);
      return type1;
    }
  }else if((strcmp(root->child[1]->name,"AND")==0)||(strcmp(root->child[1]->name,"OR")==0)||(strcmp(root->child[1]->name,"RELOP")==0)){
    /*label1 = new_label()*/
    /*label2 = new_label()*/
    Operand L1=(Operand)malloc(sizeof(Operand_));
    Operand L2=(Operand)malloc(sizeof(Operand_));
    L1->kind=LABEL_OP;
    L2->kind=LABEL_OP;
    L1->u.label_no=LabelCounter++;
    L2->u.label_no=LabelCounter++;
    /*gen Code0 = [place := #0]*/
    if(place!=NULL){
      InterCode codeIR0=(InterCode)malloc(sizeof(InterCode));
      codeIR0->kind=ASSIGN_CODE;
      codeIR0->u.assignOp.left=place;
      Operand zeroOp=(Operand)malloc(sizeof(Operand_));
      zeroOp->kind=CONSTANT_OP;
      strcpy(zeroOp->u.value,"0");
      codeIR0->u.assignOp.right=zeroOp;
      insertCode(codeIR0);
    } 
    /*gen Code1 = translate_cond()*/ 
    Type type=Condition(root,L1,L2);
    /*gen Code2 = [Label label1] + [place:=1]*/
    InterCode L1IR=(InterCode)malloc(sizeof(InterCode));
    L1IR->kind=LABEL_CODE;
    L1IR->u.single.op=L1; 
    insertCode(L1IR);
    if(place!=NULL){
      InterCode codeIR2=(InterCode)malloc(sizeof(InterCode_));
      codeIR2->kind=ASSIGN_CODE;
      codeIR2->u.assignOp.left=place;
      Operand oneOp=(Operand)malloc(sizeof(Operand_));
      oneOp->kind=CONSTANT_OP;
      strcpy(oneOp->u.value,"1");
      codeIR2->u.assignOp.right=oneOp;
      insertCode(codeIR2);
    }
    /*gen [Label label2]*/
    InterCode L2IR=(InterCode)malloc(sizeof(InterCode_));
    L2IR->kind=LABEL_CODE;
    L2IR->u.single.op=L2;
    insertCode(L2IR);
    return type;
    /*
    Type type1=Exp(root->child[0],Op);
    Type type2=Exp(root->child[2],Op);
    if(TypeEqual(type1,type2)==0){
      if((type1!=NULL)&&(type2!=NULL))
        printf(CYAN"Error type 7 at Line %d: Type mismatched for operands.\n"NONE,root->lineno);
      return NULL;
    }else{
      Type type=(Type)malloc(sizeof(Type_));
      type->kind=BASIC;
      type->u.basic=INT_TYPE;
      return type;
    }*/
  }else if(strcmp(root->child[1]->name,"ASSIGNOP")==0){
    InterCode assignIR=(InterCode)malloc(sizeof(InterCode_));
    assignIR->kind=ASSIGN_CODE;/*wokule!!!!!!*/
    if(root->child[0]->child_num==1){
      if(!(strcmp(root->child[0]->child[0]->name,"ID")==0)){
        printf(CYAN"Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"NONE,root->lineno);
        return NULL;
      }
    }else if(root->child[0]->child_num==3){
    // Bug !!!!!!!!
      if(!((strcmp(root->child[0]->child[0]->name,"Exp")==0)&&(strcmp(root->child[0]->child[1]->name,"DOT")==0)&&(strcmp(root->child[0]->child[2]->name,"ID")==0))){
      	printf(CYAN"Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"NONE,root->lineno);
      return NULL;
      }
    }else if(root->child[0]->child_num==4){
      if(!((strcmp(root->child[0]->child[0]->name,"Exp")==0)&&(strcmp(root->child[0]->child[1]->name,"LB")==0)&&(strcmp(root->child[0]->child[2]->name,"Exp")==0)&&(strcmp(root->child[0]->child[3]->name,"RB")==0))){
        printf(CYAN"Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"NONE,root->lineno);
      return NULL;
      }
    }
    Operand LeftOp=(Operand)malloc(sizeof(Operand_));
    Operand RightOp=(Operand)malloc(sizeof(Operand_));
    LeftOp->kind=TEMP_VAR_OP;
    //gen code1
    Type type1=Exp(root->child[0],LeftOp);
    Type type2;
    if(strcmp(root->child[2]->child[0]->name,"INT")==0){
      RightOp->kind=CONSTANT_OP;
      sprintf(RightOp->u.value,"%s",root->child[2]->child[0]->value);
    }else{
      RightOp->kind=TEMP_VAR_OP;
      type2=Exp(root->child[2],RightOp);
    }
    //printf("%s,%d:%d\n",root->child[0]->child[0]->value,type1->u.basic,type2->u.basic);
    if(TypeEqual(type1,type2)==0){
      if((type1!=NULL)&&(type2!=NULL))
        printf(CYAN"Error type 5 at Line %d: Type mismatched for assignment.\n"NONE,root->lineno);
      return NULL;
    }
    else{
      //gen code2
      assignIR->u.assignOp.left=LeftOp;
      assignIR->u.assignOp.right=RightOp;
      insertCode(assignIR);
      if(place!=NULL){
         InterCode assignIRPlace=(InterCode)malloc(sizeof(InterCode_));
         assignIRPlace->kind=ASSIGN_CODE;
	 assignIRPlace->u.assignOp.left=place;
  	 assignIRPlace->u.assignOp.right=LeftOp;//RightOp;
         insertCode(assignIRPlace);
      }
      return type1;
    }
  }else if(strcmp(root->child[0]->name,"ID")==0){
    /*ID LP RP*/
    FieldList field=indexSymbol(root->child[0]->value,true);
    if(field==NULL){
      FieldList field2=indexSymbol(root->child[0]->value,false);
      if(field2!=NULL)
        printf(CYAN"Error type 11 at Line %d: \"%s\" is not a function.\n"NONE,root->lineno,root->child[0]->value);
      else 
        printf(CYAN"Error type 2 at Line %d: Undefined function \"%s\".\n"NONE,root->lineno,root->child[0]->value);
      return NULL;
    }
    Type definedType=field->type;
    Type type=(Type)malloc(sizeof(Type_));
    type->kind=FUNCTION;
    type->u.function.paranum=0;
    type->u.function.parameters=NULL;
    char string_func[80]="\0";
    char make_func[80]="\0";
    FieldList param=(FieldList)malloc(sizeof(FieldList_));
    param=definedType->u.function.parameters;
    /*for(int i=0;i<definedType->u.function.paranum;i++){
      if(i==definedType->u.function.paranum-1)
        strcat(make_func,param->type->u.basic==FLOAT_TYPE?"float":"int");
      else{
        strcat(make_func,param->type->u.basic==FLOAT_TYPE?"float,":"int,");
        param=param->type->u.function.parameters;
      }
    }*/
    if(strcmp(root->child[2]->name,"RP")==0){
      //gen READ place
      if(strcmp(root->child[0]->value,"read")==0){
         /*printf(GREEN"READ_CODE"NONE);*/
         if(place!=NULL){
           InterCode readIR=(InterCode)malloc(sizeof(InterCode_));
           readIR->kind=READ_CODE;
           place->kind=TEMP_VAR_OP;
	   place->u.tvar_no=TempVarCounter++;
	   readIR->u.single.op=place;
           insertCode(readIR); 
         }
      }else{
         /*TODO*/
        //gen [place:=CALL function.name]
        Operand funcOp=(Operand)malloc(sizeof(Operand_));
        funcOp->kind=FUNCTION_OP;
        strcpy(funcOp->u.value,root->child[0]->value);
        InterCode callIR=(InterCode)malloc(sizeof(InterCode_));
	if(place==NULL){
	  place=(Operand)malloc(sizeof(Operand_));
        }
        callIR->kind=CALL_CODE;
	callIR->u.assignOp.left=place;
	callIR->u.assignOp.right=funcOp;
	place->kind=TEMP_VAR_OP;
	place->u.tvar_no=TempVarCounter++;
	insertCode(callIR);
      }
    }
    else if(strcmp(root->child[2]->name,"RP")!=0){
      /*ID LP Args RP*/
      if(strcmp(root->child[0]->value,"write")==0){
        Operand argOp=(Operand)malloc(sizeof(Operand_));
        Type type;
        TreeNode *exp=root->child[2]->child[0];
        if(strcmp(exp->child[0]->name,"INT")==0){
          type=Exp(exp,NULL);
          argOp->kind=CONSTANT_OP;
          sprintf(argOp->u.value,"%s",exp->child[0]->value);
        }else{
          argOp->kind=TEMP_VAR_OP;
          type=Exp(exp,argOp);
        }
        InterCode writeIR=(InterCode)malloc(sizeof(InterCode_));
        writeIR->kind=WRITE_CODE;
        writeIR->u.single.op=argOp;
        insertCode(writeIR);
      }else{
        TreeNode* args=root->child[2];
        //printTree(root->child[2],0);
        Operand* argsList=(Operand*)malloc(sizeof(Operand)*30);/*wokule*/
        Operand argOp=(Operand)malloc(sizeof(Operand_));
        memset(argOp,0,sizeof(Operand_));
        Type type;
        int i=0;
	if(strcmp(args->child[0]->child[0]->name,"INT")==0){
          type=Exp(args->child[0],NULL);
          argOp->kind=CONSTANT_OP;
          sprintf(argOp->u.value,"%s",args->child[0]->child[0]->value);
        }else{
          argOp->kind=TEMP_VAR_OP;
	  type=Exp(args->child[0],argOp);/*bug*/
        }
        if(type->kind==ARRAY&&argOp->kind==VARIABLE_OP){
          char s[32];
          sprintf(s,"&%s",argOp->u.value);
          strcpy(argOp->u.value,s);
        }
        argsList[i++]=argOp;
        while(args->child_num!=1){
          /*Exp COMMA Args*/
	  args=args->child[2];
          Operand argOp=(Operand)malloc(sizeof(Operand_));
          Type expType;
          if(strcmp(args->child[0]->child[0]->name,"INT")==0){
            expType=Exp(args->child[0],NULL);
            argOp->kind=CONSTANT_OP;
            sprintf(argOp->u.value,"%s",args->child[0]->child[0]->value);
          }else{
            argOp->kind=TEMP_VAR_OP;
	    expType=Exp(args->child[0],argOp);
          }
          if(expType->kind==ARRAY&&argOp->kind==VARIABLE_OP){
	    char s[32];
            sprintf(s,"&%s",argOp->u.value);
            argsList[i++]=argOp;
	  }
          //Type expType=Exp(args->child[0],place);
          /*FieldList argsField=(FieldList)malloc(sizeof(FieldList_));
          argsField->name="no";
          argsField->type=expType;
          type->u.function.paranum++;
          argsField->tail=type->u.function.parameters;
          type->u.function.parameters=argsField;
          strcat(string_func,expType->u.basic==FLOAT_TYPE?"float,":"int,");*/
	  //args=args->child[2];
        }
        while(i>0){
          InterCode argIR=(InterCode)malloc(sizeof(InterCode_));
          argIR->kind=ARG_CODE;
	  argIR->u.single.op=argsList[--i];
	  insertCode(argIR);
        }
        //free(argsList);
        Operand funcOp=(Operand)malloc(sizeof(Operand_));
        funcOp->kind=FUNCTION_OP;
	strcpy(funcOp->u.value,root->child[0]->value);
	InterCode callIR=(InterCode)malloc(sizeof(InterCode_));
	callIR->kind=CALL_CODE;
	if(place==NULL){
          place=(Operand)malloc(sizeof(Operand_));
        }
        place->kind=TEMP_VAR_OP;
	place->u.tvar_no=TempVarCounter++;
	callIR->u.assignOp.left=place;
	callIR->u.assignOp.right=funcOp;
	insertCode(callIR);
        /*Exp*/
        /*Type expType=Exp(args->child[0],place);
        FieldList argsField=(FieldList)malloc(sizeof(FieldList_));
        argsField->name="no";
        argsField->type=expType; 
        type->u.function.paranum++;
        argsField->tail=type->u.function.parameters;
        type->u.function.parameters=argsField;
        strcat(string_func,expType->u.basic==FLOAT_TYPE?"float":"int");*/
      }
    }
    /*
    if(TypeEqual(type,definedType)==0){
      printf(CYAN"Error type 9 at Line %d: Functions \"%s(%s)\" is not applicable for arguments \"(%s).\"\n"NONE,root->lineno,root->child[0]->value,make_func,string_func);
      return NULL;
    }else*/
    //printf("ss%d\n",definedType->u.function.funcType->u.basic); 
    return definedType->u.function.funcType;
  }else if(strcmp(root->child[1]->name,"DOT")==0){
    /*Exp DOT ID*/
    Type exp=Exp(root->child[0],place);
    if(exp->kind!=STRUCTURE){
      TreeNode* expNode=root->child[0];
      char *s;
      switch(expNode->child_num){
        case 1:{
          if(strcmp(expNode->child[0]->name,"ID")==0)
            s=expNode->child[0]->value;
        }
          break;
        case 3:{
          if(strcmp(expNode->child[2]->name,"ID")==0)
            s=expNode->child[0]->value;
        }
          break;
        case 4:{
          if(strcmp(expNode->child[0]->name,"Exp")==0)
            if(strcmp(expNode->child[0]->child[0]->name,"ID")==0)
              s=expNode->child[0]->child[0]->value;
        }
          break;
        default:
          s="error";
          break;
      }
      if(indexSymbol(s,0)!=NULL)
        printf(CYAN"Error type 13 at Line %d: Illegal use of \".\".\n"NONE,root->lineno);
      return NULL;
    }
    char *s=root->child[2]->value;
    FieldList field=exp->u.structure;
    while(field!=NULL){
      if(strcmp(field->name,s)==0)
        return field->type;
      field=field->tail;
    }
    printf(CYAN"Error type 14 at Line %d: Non-existent field \"%s\".\n"NONE,root->lineno,root->child[2]->value);
    return NULL;
  }else if(strcmp(root->child[1]->name,"LB")==0){
    /*Exp LB Exp RB*/
    Operand baseOp=(Operand)malloc(sizeof(Operand_));
    Type exp=Exp(root->child[0],baseOp);
    if(exp->kind!=ARRAY){
      TreeNode* expNode=root->child[0];
      char *s;
      switch(expNode->child_num){
        case 1:{
          if(strcmp(expNode->child[0]->name,"ID")==0)
            s=expNode->child[0]->value;
        }
          break;
        case 3:{
          if(strcmp(expNode->child[2]->name,"ID")==0)
            s=expNode->child[0]->value;
        }
          break;
        case 4:{
          if(strcmp(expNode->child[0]->name,"exp")==0)
            if(strcmp(expNode->child[0]->child[0]->name,"ID")==0)
              s=expNode->child[0]->child[0]->value;
        }
          break;
        default:
          s="error";
          break;
      }
      if(indexSymbol(s,false)!=NULL)
        printf(CYAN"Error type 10 at Line %d: \"%s\" is not an array.\n"NONE,root->lineno,s);
      return NULL;
    }
    Type exp2;
    Operand indexOp=(Operand)malloc(sizeof(Operand_));
    if(strcmp(root->child[2]->child[0]->name,"INT")==0){
      exp2=Exp(root->child[2],NULL);
      indexOp->kind=CONSTANT_OP;
      sprintf(indexOp->u.value,"%s",root->child[2]->child[0]->value);
    }else{
      exp2=Exp(root->child[2],indexOp);
    } 
    //exp2=Exp(root->child[2],place);
    Operand offsetOp=(Operand)malloc(sizeof(Operand_));
    offsetOp->kind=TEMP_VAR_OP;
    offsetOp->u.tvar_no=TempVarCounter++;
    if(strcmp(root->child[2]->child[0]->name,"INT")==0&&atoi(root->child[2]->child[0]->value)==0){
      offsetOp->kind=CONSTANT_OP;
      strcpy(offsetOp->u.value,"0");
    }else{
      Operand widthOp=malloc(sizeof(Operand_));
      widthOp->kind=CONSTANT_OP;
      int width=getSize(exp,2); 
      sprintf(widthOp->u.value,"%d",width);
      InterCode offsetIR=(InterCode)malloc(sizeof(InterCode_));
      offsetIR->kind=MUL_CODE;
      offsetIR->u.tripleOp.result=offsetOp;
      offsetIR->u.tripleOp.op1=indexOp;
      offsetIR->u.tripleOp.op2=widthOp;
      insertCode(offsetIR);
    }
    InterCode baseIR=(InterCode)malloc(sizeof(InterCode_));
    baseIR->kind=GET_ADDR_CODE;
    baseIR->u.tripleOp.op1=baseOp;
    baseIR->u.tripleOp.op2=offsetOp;
    if(exp->u.array.elem->kind==BASIC){
      baseIR->kind=GET_ADDR_CODE;
      Operand tmpAddrOp=(Operand)malloc(sizeof(Operand_));
      tmpAddrOp->kind=TEMP_VAR_OP;
      tmpAddrOp->u.tvar_no=TempVarCounter++;
      baseIR->u.tripleOp.result=tmpAddrOp;
      place->kind=TEMP_ADDR_OP;
      place->u.name=tmpAddrOp;
    }else{
      baseIR->u.tripleOp.result=place;
      place->kind=TEMP_VAR_OP;
      place->u.tvar_no=TempVarCounter++;
    }
    if(strcmp(root->child[0]->child[0]->name,"ID")==0){
      FieldList field=indexSymbol(baseOp->u.value,false);
      //printf("2:%s,%s,%s,%d\n",root->child[0]->child[0]->value,baseOp->u.value,field->name,field->defined);
      if(field->defined!=defined)
        baseIR->kind=PLUS_CODE;
    }
    else{
      baseIR->kind=PLUS_CODE;
    }
    insertCode(baseIR);
    if(exp2->kind!=BASIC){
      printf(CYAN"Error type 12 at Line %d: \"%s\" is not a integer\n"NONE,root->lineno,root->child[2]->child[0]->value);
      return NULL;
    }
    else if(exp2->u.basic==FLOAT_TYPE){
      printf(CYAN"Error type 12 at Line %d: \"%s\" is not a integer\n"NONE,root->lineno,root->child[2]->child[0]->value);
      return NULL;
    }
    return exp->u.array.elem;
  }else{
    printf("in\n");
    return NULL;
  }
}
