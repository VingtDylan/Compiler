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
      printf(CYAN"%d: name:%s kind:%d\n"NONE,i,hashTable[i]->name,hashTable[i]->type->kind);
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
  else {
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
		  if(!TypeEqual(structure1->type,structure2->type)){
			return false;
		  }
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
              printf(RED"The type is not supported"RED);
	      return false;
	    }
            break;
     }
  }
}

/*Type Specifier(TreeNode *root){
  Type specifier=(Type)malloc(sizeof(Type));
  if(strcmp(root->child[0]->name,"TYPE")==0){
    specifier->kind=BASIC;
    if(strcmp(root->child[0]->value,"int")==0)
      specifier->u.basic=INT_TYPE;

    return specifier;
  }else{
    specifier=NULL;
  }
  return specifier;
}*/

Type Specifier(TreeNode *root){
    Type spe=(Type)malloc(sizeof(Type_));
    if(strcmp(root->child[0]->name,"TYPE")==0){//TYPE
        spe->kind=BASIC;
        if(strcmp(root->child[0]->value,"int")==0)
            spe->u.basic=INT_TYPE;
        else spe->u.basic=FLOAT_TYPE;
        return spe;
    }
    else{
        spe->kind=STRUCTURE;
        if(root->child[0]->child_num==2){//STRUCT Tag
            char *s=root->child[0]->child[1]->child[0]->value;
            FieldList field=indexSymbol(s,0);
            if(field==NULL){
                printf("Error type 17 at Line %d: Undefined structure \"%s\".\n",root->lineno,s);
                spe->u.structure=NULL;
                return spe;
            }
            else if(field->type!=NULL)
                return field->type;
            spe->u.structure=NULL;
            return spe;
        }
        else{//STRUCT OptTag LC DefList RC
            TreeNode* DefList=root->child[0]->child[3];
            spe->u.structure=NULL;
            //DefList in STRUCT is different from that outside
            while(DefList!=NULL){//Def DefList
                TreeNode *Def=DefList->child[0];
                Type basictype=Specifier(Def->child[0]);
          
                TreeNode* DecList=Def->child[1];
                while(DecList->child_num==3){//Dec COMMA DecList
                    FieldList field=VarDec(DecList->child[0]->child[0],basictype);
                    if(DecList->child[0]->child_num!=1)
                        printf("Error type 15 at Line %d: Variable %s in struct is initialized.\n",Def->lineno,field->name);
                    FieldList temp=spe->u.structure;
                    while(temp!=NULL){
                        if(strcmp(temp->name,field->name)==0){
                            printf("Error type 15 at Line %d: Redefined field \"%s\".\n",Def->lineno,field->name);
                            break;
                        }
                        temp=temp->tail;
                    }
                    if(temp==NULL){
			if(indexSymbol(field->name,0)!=NULL)
			    printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",Def->lineno,field->name);
			else{
			    insertSymbol(field);
                            field->tail=spe->u.structure;
                            spe->u.structure=field;
			}
                    }
                    DecList=DecList->child[2];
                }
                FieldList field=VarDec(DecList->child[0]->child[0],basictype);
                if(DecList->child[0]->child_num!=1)
                    printf("Error type 15 at Line %d: Variable \"%s\" in struct is initialized.\n",Def->lineno,field->name);
                FieldList temp=spe->u.structure;
                while(temp!=NULL){
                    if(strcmp(temp->name,field->name)==0){
                        printf("Error type 15 at Line %d: Redefined field \"%s\".\n",Def->lineno,field->name);
                        break;
                    }
                    temp=temp->tail;
                }
                if(temp==NULL){
		    if(indexSymbol(field->name,0)!=NULL)
		        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",Def->lineno,field->name);
		    else{
			insertSymbol(field);
                        field->tail=spe->u.structure;
                        spe->u.structure=field;
		    }
                }
                DefList=DefList->child[1];
            }
            if(root->child[0]->child[1]!=NULL){//OptTag exist
                FieldList field=(FieldList)malloc(sizeof(FieldList_));
                field->type=spe;
                char *s=root->child[0]->child[1]->child[0]->value;//get the name of OptTag
                field->name=s;
                if(indexSymbol(field->name,0)!=NULL)
                    printf("Error type 16 at Line %d: Duplicated name \"%s\".\n",root->lineno,field->name);
                else insertSymbol(field);
            }
            return spe;
        }
    }
}


FieldList VarDec(TreeNode *root,Type basictype){
    TreeNode *temp=root;
    int i=0;
    while(strcmp(temp->child[0]->name,"ID")!=0){
        temp=temp->child[0];
        i++;
    }
    char *s=temp->child[0]->value;

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
        }break;
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
        }break;
        default:printf("error in VarDec");break;
    }
}

Type Exp(TreeNode* root){
    if(root==NULL)
        return NULL;
    else if((strcmp(root->child[0]->name,"ID")==0)&&(root->child_num==1)){//ID
        FieldList field=indexSymbol(root->child[0]->value,0);
        if(field!=NULL)
            return field->type;
        else{
            printf("Error type 1 at Line %d: Undefined variable \"%s\".\n",root->lineno,root->child[0]->value);
            return NULL;
        }
    }
    else if(strcmp(root->child[0]->name,"INT")==0){//INT
        Type typ=(Type)malloc(sizeof(Type_));
        typ->kind=BASIC;
        typ->u.basic=INT_TYPE;
        return typ;
    }
    else if(strcmp(root->child[0]->name,"FLOAT")==0){//FLOAT
        Type typ=(Type)malloc(sizeof(Type_));
        typ->kind=BASIC;
        typ->u.basic=FLOAT_TYPE;
        return typ;
    }
    else if((strcmp(root->child[0]->name,"LP")==0)||(strcmp(root->child[0]->name,"MINUS")==0)||(strcmp(root->child[0]->name,"NOT")==0)){
        return Exp(root->child[1]);
    }
    else if((strcmp(root->child[1]->name,"PLUS")==0)||(strcmp(root->child[1]->name,"MINUS")==0)||(strcmp(root->child[1]->name,"STAR")==0)||(strcmp(root->child[1]->name,"DIV")==0)){
        Type typ1=Exp(root->child[0]);
        Type typ2=Exp(root->child[2]);
        if(TypeEqual(typ1,typ2)==0){
            if((typ1!=NULL)&&(typ2!=NULL))
                printf("Error type 7 at Line %d: Type mismatched for operands.\n",root->lineno);
            return NULL;
        }
        else return typ1;
    }
    else if((strcmp(root->child[1]->name,"AND")==0)||(strcmp(root->child[1]->name,"OR")==0)||(strcmp(root->child[1]->name,"RELOP")==0)){
        Type typ1=Exp(root->child[0]);
        Type typ2=Exp(root->child[2]);
        if(TypeEqual(typ1,typ2)==0){
            if((typ1!=NULL)&&(typ2!=NULL))
                printf("Error type 7 at Line %d: Type mismatched for operands.\n",root->lineno);
            return NULL;
        }
        else{
	    Type typ=(Type)malloc(sizeof(Type_));
	    typ->kind=BASIC;
	    typ->u.basic=INT_TYPE;
  	    return typ;
	}
    }
    else if(strcmp(root->child[1]->name,"ASSIGNOP")==0){
        if(root->child[0]->child_num==1){
            if(!(strcmp(root->child[0]->child[0]->name,"ID")==0)){
                printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",root->lineno);
                return NULL;
            }
        }
        else if(root->child[0]->child_num==3){
            if(!((strcmp(root->child[0]->child[0]->name,"Exp")==0)&&(strcmp(root->child[0]->child[1]->name,"DOT")==0)&&(strcmp(root->child[0]->child[2]->name,"ID")==0))){
                printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",root->lineno);
                return NULL;
            }
        }
        else if(root->child[0]->child_num==4){
            if(!((strcmp(root->child[0]->child[0]->name,"Exp")==0)&&(strcmp(root->child[0]->child[1]->name,"LB")==0)&&(strcmp(root->child[0]->child[2]->name,"Exp")==0)&&(strcmp(root->child[0]->child[3]->name,"RB")==0))){
                printf("Error type 6 at Line %d: The left-hand side of an assignment must be a variable.\n",root->lineno);
                return NULL;
            }
        }
        Type typ1=Exp(root->child[0]);
        Type typ2=Exp(root->child[2]);
        if(TypeEqual(typ1,typ2)==0){
            if((typ1!=NULL)&&(typ2!=NULL))
                printf("Error type 5 at Line %d: Type mismatched for assignment.\n",root->lineno);
            return NULL;
        }
        else return typ1;
    }
    else if(strcmp(root->child[0]->name,"ID")==0){//ID LP RP
        FieldList fie=indexSymbol(root->child[0]->value,1);
        if(fie==NULL){
            FieldList fie2=indexSymbol(root->child[0]->value,0);
            if(fie2!=NULL)
                printf("Error type 11 at Line %d: \"%s\" is not a function.\n",root->lineno,root->child[0]->value);
            else printf("Error type 2 at Line %d: Undefined function \"%s\".\n",root->lineno,root->child[0]->value);
            return NULL;
        }
        Type definedType=fie->type;

        Type typ=(Type)malloc(sizeof(Type_));
        typ->kind=FUNCTION;
        typ->u.function.paranum=0;
        typ->u.function.parameters=NULL;
        if(strcmp(root->child[2]->name,"RP")!=0){//ID LP Args RP
            TreeNode* temp=root->child[2];
            while(temp->child_num!=1){//Exp COMMA Args
                Type tempType=Exp(temp->child[0]);
                FieldList tempField=(FieldList)malloc(sizeof(FieldList_));
                tempField->name="no";
		tempField->type=tempType;
                typ->u.function.paranum++;
                tempField->tail=typ->u.function.parameters;
                typ->u.function.parameters=tempField;
                temp=temp->child[2];
            }//Exp
            Type tempType=Exp(temp->child[0]);
            FieldList tempField=(FieldList)malloc(sizeof(FieldList_));
            tempField->name="no";//just for temp compare
	    tempField->type=tempType;
            typ->u.function.paranum++;
            tempField->tail=typ->u.function.parameters;
            typ->u.function.parameters=tempField;
        }
        if(TypeEqual(typ,definedType)==0){
            printf("Error type 9 at Line %d: Params wrong in function \"%s\".\n",root->lineno,root->child[0]->value);
            return NULL;
        }
        else return definedType->u.function.funcType;
    }
    else if(strcmp(root->child[1]->name,"DOT")==0){//Exp DOT ID
        Type typ1=Exp(root->child[0]);
        if(typ1->kind!=STRUCTURE){
            TreeNode* temp=root->child[0];
            char *s;
            switch(temp->child_num){
                case 1:{
                    if(strcmp(temp->child[0]->name,"ID")==0)
                        s=temp->child[0]->value;
                }break;
                case 3:{
                    if(strcmp(temp->child[2]->name,"ID")==0)
                        s=temp->child[0]->value;
                }break;
                case 4:{
                    if(strcmp(temp->child[0]->name,"Exp")==0)
                        if(strcmp(temp->child[0]->child[0]->name,"ID")==0)
                            s=temp->child[0]->child[0]->value;
                }break;
                default:s="error";break;
            }
            if(indexSymbol(s,0)!=NULL)
                printf("Error type 13 at Line %d: Illegal use of \".\".\n",root->lineno);
            return NULL;
        }
        char *s=root->child[2]->value;
        FieldList temp=typ1->u.structure;
        while(temp!=NULL){
            if(strcmp(temp->name,s)==0)
                return temp->type;

            temp=temp->tail;
        }
        
        printf("Error type 14 at Line %d: Non-existent field \"%s\".\n",root->lineno,root->child[2]->value);
        return NULL;
    }
    else if(strcmp(root->child[1]->name,"LB")==0){//Exp LB Exp RB
        Type typ1=Exp(root->child[0]);
        if(typ1->kind!=ARRAY){
            TreeNode* temp=root->child[0];
            char *s;
            switch(temp->child_num){
                case 1:{
                    if(strcmp(temp->child[0]->name,"ID")==0)
                        s=temp->child[0]->value;
                }break;
                case 3:{
                    if(strcmp(temp->child[2]->name,"ID")==0)
                        s=temp->child[0]->value;
                }break;
                case 4:{
                    if(strcmp(temp->child[0]->name,"Exp")==0)
                        if(strcmp(temp->child[0]->child[0]->name,"ID")==0)
                            s=temp->child[0]->child[0]->value;
                }break;
                default:s="error";break;
            }
            if(indexSymbol(s,0)!=NULL)
                printf("Error type 10 at Line %d: \"%s\" is not an array.\n",root->lineno,s);
            return NULL;
        }
        Type temp=Exp(root->child[2]);
        if(temp->kind!=BASIC){
            printf("Error type 12 at Line %d: there is not a integer between \"[\" and \"]\".\n",root->lineno);
            return NULL;
        }
        else if(temp->u.basic==FLOAT_TYPE){
            printf("Error type 12 at Line %d: there is not a integer between \"[\" and \"]\".\n",root->lineno);
            return NULL;
        }
        //no error
        return typ1->u.array.elem;
    }
    else{
        printf("in\n");
        return NULL;
    }
}
