#include "grammertree.h"
#include "semantic.h"
#include "semanticTraverse.h"

extern FieldList hashTable[MAX_HASH_SIZE];

unsigned int hash_pjw(char *name){
  unsigned int val = 0, i;
  for(; *name; ++name){
    val = (val << 2) + *name;
    if(i=val & ~0x3fff)
      val = (val ^ (i>>12)) & 0x3fff;
  }
  return val%MAX_HASH_SIZE;
}

void initHashTable(){
  for(int i=0; i<MAX_HASH_SIZE; i++){
    hashTable[i] = NULL;
  }
}
 
int insertSymbol(FieldList symbol){
  if(symbol==NULL||symbol->name==NULL)
    return 0;
  unsigned int hashkey;
  symbol->hashflag.flag =wander;
  symbol->hashflag.hashed = 0;
  if(symbol->type->kind==FUNCTION)
    hashkey=hash_pjw(1+symbol->name);
  else
    hashkey=hash_pjw(symbol->name);
  if(hashTable[hashkey]==NULL){
    symbol->hashflag.flag=arranged;
    hashTable[hashkey]=symbol;
    return 1;
  }
  while(1){
    hashkey=(++hashkey)%MAX_HASH_SIZE;
    symbol->hashflag.hashed+=1;
    if(hashTable[hashkey]==NULL){
      symbol->hashflag.flag=arranged;
      hashTable[hashkey]=symbol;
      return 1;
    }
    if(symbol->hashflag.hashed>MAX_HASH_SIZE){
      symbol->hashflag.flag=extra;
      PrintSymbol("The hashtable is full!\n");
    }
  }
  return 0;
}

void debugShowSymbol(){
  for(int i=0;i<MAX_HASH_SIZE;i++)
    if(hashTable[i]!=NULL)
      printf(CYAN"hashTableid%d: SymbolName:%s Kind:%d\n"NONE,i,hashTable[i]->name,hashTable[i]->type->kind);
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
    if(tmpSymbol->hashflag.flag==arranged&&strcmp(tmpSymbol->name,name)==0){
      if(isFunc&&(tmpSymbol->type->kind==FUNCTION))
         return tmpSymbol;
      if(!isFunc&&(tmpSymbol->type->kind!=FUNCTION))
         return tmpSymbol;
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

Type Specifier(TreeNode *root){
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
        Type symbolType=Specifier(Def->child[0]);
        TreeNode* DecList=Def->child[1];
        while(DecList->child_num==3){
          /*Dec COMMA DecList*/
          FieldList field=VarDec(DecList->child[0]->child[0],symbolType);
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
        FieldList field=VarDec(DecList->child[0]->child[0],symbolType);
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


FieldList VarDec(TreeNode *root,Type basictype){
  TreeNode *VarDecRoot=root;
  int i=0;
  while(strcmp(VarDecRoot->child[0]->name,"ID")!=0){
    VarDecRoot=VarDecRoot->child[0];
    i++;
  }
  char *s=VarDecRoot->child[0]->value;
  FieldList field=(FieldList)malloc(sizeof(FieldList_));
  field->name=s;
  if(strcmp(root->child[0]->name,"ID")==0){
    field->type=basictype;
    return field;
  }
  switch(i){
    case 1:{
      Type var1=(Type)malloc(sizeof(Type_));
      var1->kind=ARRAY;
      var1->u.array.size=atoi(root->child[2]->value);
      var1->u.array.elem=basictype;
      field->type=var1;
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
      return field;
    }
      break;
    default:
      printf(RED"error in VarDec"NONE);
      break;
  }
}

Type Exp(TreeNode* root){
  if(root==NULL)
    return NULL;
  else if((strcmp(root->child[0]->name,"ID")==0)&&(root->child_num==1)){
    /*ID*/
    FieldList field=indexSymbol(root->child[0]->value,false);
    if(field!=NULL)
      return field->type;
    else{
      printf(CYAN"Error type 1 at Line %d: Undefined variable \"%s\".\n"NONE,root->lineno,root->child[0]->value);
      return NULL;
    }
  }else if(strcmp(root->child[0]->name,"INT")==0){
    /*INT*/
    Type type=(Type)malloc(sizeof(Type_));
    type->kind=BASIC;
    type->u.basic=INT_TYPE;
    return type;
  }else if(strcmp(root->child[0]->name,"FLOAT")==0){
    /*FLOAT*/
    Type type=(Type)malloc(sizeof(Type_));
    type->kind=BASIC;
    type->u.basic=FLOAT_TYPE;
    return type;
  }else if((strcmp(root->child[0]->name,"LP")==0)||(strcmp(root->child[0]->name,"MINUS")==0)||(strcmp(root->child[0]->name,"NOT")==0)){
    return Exp(root->child[1]);
  }else if((strcmp(root->child[1]->name,"PLUS")==0)||(strcmp(root->child[1]->name,"MINUS")==0)||(strcmp(root->child[1]->name,"STAR")==0)||(strcmp(root->child[1]->name,"DIV")==0)){
    Type type1=Exp(root->child[0]);
    Type type2=Exp(root->child[2]);
    if(TypeEqual(type1,type2)==0){
      if((type1!=NULL)&&(type2!=NULL))
        printf(CYAN"Error type 7 at Line %d: Type mismatched for operands.\n"NONE,root->lineno);
        return NULL;
    }
    else 
      return type1;
  }else if((strcmp(root->child[1]->name,"AND")==0)||(strcmp(root->child[1]->name,"OR")==0)||(strcmp(root->child[1]->name,"RELOP")==0)){
    Type type1=Exp(root->child[0]);
    Type type2=Exp(root->child[2]);
    if(TypeEqual(type1,type2)==0){
      if((type1!=NULL)&&(type2!=NULL))
        printf(CYAN"Error type 7 at Line %d: Type mismatched for operands.\n"NONE,root->lineno);
      return NULL;
    }else{
      Type type=(Type)malloc(sizeof(Type_));
      type->kind=BASIC;
      type->u.basic=INT_TYPE;
      return type;
    }
  }else if(strcmp(root->child[1]->name,"ASSIGNOP")==0){
    if(root->child[0]->child_num==1){
      if(!(strcmp(root->child[0]->child[0]->name,"ID")==0)){
        printf(CYAN"Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"NONE,root->lineno);
        return NULL;
      }
    }
  }else if(root->child[0]->child_num==3){
    if(!((strcmp(root->child[0]->child[0]->name,"Exp")==0)&&(strcmp(root->child[0]->child[1]->name,"DOT")==0)&&(strcmp(root->child[0]->child[2]->name,"ID")==0))){
      printf(CYAN"Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"NONE,root->lineno);
      return NULL;
    }
  }else if(root->child[0]->child_num==4){
    if(!((strcmp(root->child[0]->child[0]->name,"Exp")==0)&&(strcmp(root->child[0]->child[1]->name,"LB")==0)&&(strcmp(root->child[0]->child[2]->name,"Exp")==0)&&(strcmp(root->child[0]->child[3]->name,"RB")==0))){
      printf(CYAN"Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n"NONE,root->lineno);
      return NULL;
    }
    Type type1=Exp(root->child[0]);
    Type type2=Exp(root->child[2]);
    if(TypeEqual(type1,type2)==0){
      if((type1!=NULL)&&(type2!=NULL))
        printf(CYAN"Error type 5 at Line %d: Type mismatched for assignment.\n"NONE,root->lineno);
      return NULL;
    }
    else 
      return type1;
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
    if(strcmp(root->child[2]->name,"RP")!=0){
      /*ID LP Args RP*/
      TreeNode* args=root->child[2];
      while(args->child_num!=1){
        /*Exp COMMA Args*/
        Type expType=Exp(args->child[0]);
        FieldList argsField=(FieldList)malloc(sizeof(FieldList_));
        argsField->name="no";
	argsField->type=expType;
        type->u.function.paranum++;
        argsField->tail=type->u.function.parameters;
        type->u.function.parameters=argsField;
        args=args->child[2];
      }
      /*Exp*/
      Type expType=Exp(args->child[0]);
      FieldList argsField=(FieldList)malloc(sizeof(FieldList_));
      argsField->name="no";
      argsField->type=expType;
      type->u.function.paranum++;
      argsField->tail=type->u.function.parameters;
      type->u.function.parameters=argsField;
    }
    if(TypeEqual(type,definedType)==0){
      printf(CYAN"Error type 9 at Line %d: Params wrong in function \"%s\".\n"NONE,root->lineno,root->child[0]->value);
      return NULL;
    }else 
      return definedType->u.function.funcType;
  }else if(strcmp(root->child[1]->name,"DOT")==0){
    /*Exp DOT ID*/
    Type exp=Exp(root->child[0]);
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
    Type exp=Exp(root->child[0]);
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
          if(strcmp(expNode->child[0]->name,"Exp")==0)
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
    Type exp2=Exp(root->child[2]);
    if(exp2->kind!=BASIC){
      printf(CYAN"Error type 12 at Line %d: there is not a integer between \"[\" and \"]\".\n"NONE,root->lineno);
        return NULL;
    }
    else if(exp2->u.basic==FLOAT_TYPE){
      printf(CYAN"Error type 12 at Line %d: there is not a integer between \"[\" and \"]\".\n"NONE,root->lineno);
        return NULL;
    }
    return exp->u.array.elem;
  }else{
    printf("in\n");
    return NULL;
  }
}
