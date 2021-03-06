#include "grammertree.h"
#include "semantic.h"
#include "semanticTraverse.h"

extern FieldList hashTable[MAX_HASH_SIZE];

void traverseExtDefList(TreeNode *root){
  TreeNode *ExtDefList=root;
  /*ExtDef ExtDefList*/
  while(ExtDefList->child_num!=0){
    TreeNode *ExtDef=ExtDefList->child[0];
    Type symbolType=Specifier(ExtDef->child[0],"Rrogram"); /*TODO*/
    /*Specifier FunDec CompSt*/
    if(strcmp(ExtDef->child[1]->name,"FunDec")==0){
      /*ID LP VarList=NULL RP*/
      FieldList field=(FieldList)malloc(sizeof(FieldList_));
      field->name=ExtDef->child[1]->child[0]->value;
      field->lineno=ExtDef->child[1]->child[0]->lineno;
      Type funcType=(Type)malloc(sizeof(Type_));
      funcType->kind=FUNCTION;
      funcType->u.function.funcType=symbolType;
      funcType->u.function.paranum=0;
      funcType->u.function.parameters=NULL;
      /*ID LP VarList RP*/
      if(strcmp(ExtDef->child[1]->child[2]->name,"VarList")==0){
        TreeNode *VarListRoot=ExtDef->child[1]->child[2];
        /*ParamDec COMMA VarList*/
        while(VarListRoot->child_num!=1){
          Type varType=Specifier(VarListRoot->child[0]->child[0],field->name);
          FieldList VarDecField=VarDec(VarListRoot->child[0]->child[1],varType,field->name);
          VarDecField->defined=unuseparam;
          strcat(VarDecField->parent,field->name); 
          if(indexSymbol(VarDecField->name,false)!=NULL&&indexSymbol(VarDecField->name,false)->defined!=unuseparam)
            printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,ExtDef->lineno,VarDecField->name);
          else
            insertSymbol(VarDecField);
          funcType->u.function.paranum++;
          VarDecField->tail=funcType->u.function.parameters;
          VarDecField->defined=unuseparam;
          funcType->u.function.parameters=VarDecField;
          VarListRoot=VarListRoot->child[2];
        }
        /*ParamDec*/
        Type varType=Specifier(VarListRoot->child[0]->child[0],field->name);
        FieldList VarDecField=VarDec(VarListRoot->child[0]->child[1],varType,field->name); 
        VarDecField->defined=unuseparam;
        /*bug QaQ*/
        strcat(VarDecField->parent,field->name);
        if(indexSymbol(VarDecField->name,false)!=NULL&&indexSymbol(VarDecField->name,false)->defined!=unuseparam)
          printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,ExtDef->lineno,VarDecField->name);
        else
          insertSymbol(VarDecField);
        funcType->u.function.paranum++;
        VarDecField->tail=funcType->u.function.parameters;
        VarDecField->defined=unuseparam;
        funcType->u.function.parameters=VarDecField;
      }
      field->type=funcType;
      //printTree(ExtDef,0);
      if(strcmp(ExtDef->child[2]->name,"SEMI")==0)
        field->defined=undefined;
      else
        field->defined=defined;
      //printf(RED"sname-%s kind-%d\n"NONE,field->name,field->type->kind);
      //printf("params%d\n",field->type->u.function.paranum++);
      FieldList indexField=indexSymbol(field->name,true);
      if(indexField!=NULL){
        if(indexField->defined==defined&&field->defined==defined)
          printf(CYAN"Error type 4 at Line %d: Redefined function \"%s\" .\n"NONE,ExtDef->lineno,field->name);
        else if(indexField->defined==undefined){
          /*Collide*/
          if(!TypeEqual(field->type,indexField->type))
             printf(CYAN"Error type 19 at Line %d: Inconsistent declaration of function \"%s\".\n"NONE,ExtDef->lineno,field->name);
          else if(field->defined==defined){
             indexField->defined=defined;
          }
      
        }
        /*else if(indexField->defined==undefined&&field->defined==undefined)
          printf(CYAN"Error type 19 at Line %d: Inconsistent declaration of function \"%s\".\n"NONE,ExtDef->lineno,field->name);*/
      }
      else{
        //printf(GREEN"sssname-%s kind-%d\n"NONE,field->name,field->type->kind);
        //Bug !!!!!!!
        insertSymbol(field);      
        //printf(GREEN"ssname-%s kind-%d\n"NONE,field->name,field->type->kind);
      }
      /*CompSt todo*/
      //debugShowSymbol();
      traverseCompSt(ExtDef->child[2],symbolType,ExtDef->child[1]->child[0]->value);
    }
    /*Specifier ExtDecList SEMI*/
    else if(strcmp(ExtDef->child[1]->name,"ExtDecList")==0){
       TreeNode *ExtDecList=ExtDef->child[1];
       FieldList field;
       while(ExtDecList->child_num==3){
         /*VarDec COMMA ExtDecList*/
         field=VarDec(ExtDecList->child[0],symbolType,"Program");
         if(indexSymbol(field->name,false)!=NULL)
           printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\" .\n"NONE,ExtDef->lineno,field->name);
         else
           insertSymbol(field);
         ExtDecList=ExtDecList->child[2];
       }
       field=VarDec(ExtDecList->child[0],symbolType,"Program");
       if(indexSymbol(field->name,false)!=NULL)
         printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\" .\n"NONE,ExtDef->lineno,field->name);
       else
         insertSymbol(field);
    }
    /*Specifier SEMI*/
    else{
       //TODO
    }
    if(ExtDefList->child[1]==NULL)
      /*ExtDef NULL*/
      return ;
    else 
      /*ExtDef ExtDefList*/
      ExtDefList=ExtDefList->child[1];
  }
}

void traverseCompSt(TreeNode *root,Type funcType,char* pname){
  /*LC DefList StmtList RC*/
  TreeNode *CompSt=root;
  traverseDefList(CompSt->child[1],pname);
  TreeNode *StmtList=CompSt->child[2];
  while(StmtList!=NULL){
    /*Stmt StmtList*/
    TreeNode *Stmt=StmtList->child[0];
    traverseStmt(Stmt,funcType,pname);
    StmtList=StmtList->child[1];
  }
  /*StmtList=NULL*/
}

void traverseDefList(TreeNode *root,char* pname){
  TreeNode* DefList=root;
  while(DefList!=NULL){
    /*Def DefList*/
    TreeNode* Def=DefList->child[0];
    Type symbolType=Specifier(Def->child[0],pname);
    TreeNode *DecList=Def->child[1];
    while(DecList->child_num==3){
      /*Dec COMMA DecList*/
      FieldList field=VarDec(DecList->child[0]->child[0],symbolType,pname);
      FieldList indexField=indexSymbol(field->name,false);
      if(indexField!=NULL){
        if(strstr(indexField->parent,pname)!=NULL){
          printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,DecList->lineno,field->name);
        }
        else{
          strcat(indexField->parent,pname);
          //printf(PURPLE"Pass\n"NONE);
        }
      }
      else 
        insertSymbol(field);
      DecList=DecList->child[2];
    }
    /*Dec*/
    FieldList field=VarDec(DecList->child[0]->child[0],symbolType,pname);
    FieldList indexField=indexSymbol(field->name,false);
    if(indexField!=NULL){
      if(strstr(indexField->parent,pname)!=NULL){
        printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,DecList->lineno,field->name);
      }
      else{
        strcat(indexField->parent,pname);
        //printf(PURPLE"Pass\n"NONE);
      }
    }
    else 
      insertSymbol(field);
    if(DefList->child[1]==NULL)
      /*Def*/
      return;
    DefList=DefList->child[1];
  }
}

void traverseStmt(TreeNode *root,Type funcType,char* pname){
  TreeNode *Stmt=root;
  if(strcmp(Stmt->child[0]->name,"Exp")==0){
    /*Exp SEMI*/
    //printf("%d\n",Stmt->child[0]->child_num);
    Exp(Stmt->child[0]);
  }else if(strcmp(Stmt->child[0]->name,"CompSt")==0){
    /*CompSt*/
    traverseCompSt(Stmt->child[0],funcType,pname);
  }else if(strcmp(Stmt->child[0]->name,"RETURN")==0){
    /*RETURN Exp SEMI*/
    Type returnType=Exp(Stmt->child[1]);
    if(TypeEqual(funcType,returnType)==0)
      printf(CYAN"Error type 8 at Line %d: Type mismatched for return.\n"NONE,Stmt->lineno);
  }else if(Stmt->child_num==5&&strcmp(Stmt->child[0]->name,"IF")==0){
    /*TODO*/
    /*IF LP Exp RP Stmt*/
    Type expType=Exp(Stmt->child[2]);
    if(expType!=NULL)
      if(!((expType->kind==BASIC)&&(expType->u.basic==INT_TYPE)))
        printf(CYAN"Error type 5 at Line %d: Only type INT could be used for judgement.\n"NONE,Stmt->lineno);
    traverseStmt(Stmt->child[4],funcType,pname);
  }else if(Stmt->child_num==7&&strcmp(Stmt->child[0]->name,"IF")==0){
    /*TODO*/
    /*IF LP Exp RP Stmt ELSE Stmt*/
    Type expType=Exp(Stmt->child[2]);
    if(!((expType->kind==BASIC)&&(expType->u.basic==INT_TYPE)))
      printf(CYAN"Error type 5 at Line %d: Only type INT could be used for judgement.\n"NONE,Stmt->lineno);
    traverseStmt(Stmt->child[4],funcType,pname);
    traverseStmt(Stmt->child[6],funcType,pname);
  }else if(strcmp(Stmt->child[0]->name,"WHILE")==0){
    /*WHILE LP Exp RP Stmt*/
    Type expType=Exp(Stmt->child[2]);
    if(!((expType->kind==BASIC)&&(expType->u.basic==INT_TYPE)))
      printf(CYAN"Error type 5 at Line %d: Only type INT could be used for judgement.\n"NONE,Stmt->lineno);
    traverseStmt(Stmt->child[4],funcType,pname);
  }
}

void traverse(TreeNode *root){
  //PrintHint("Semantic analysis is followed!\n");
  if(root==NULL)
    return;
  if(strcmp(root->name,"ExtDefList")==0){
    traverseExtDefList(root);
    return;
  }
  if(root->child_num!=0)
    for(int i=0;i<root->child_num;i++)
       traverse(root->child[i]);
}
