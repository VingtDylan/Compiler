#include "grammertree.h"
#include "semantic.h"
#include "semanticTraverse.h"

extern FieldList hashTable[MAX_HASH_SIZE];

/*void traverseExtDefList(TreeNode *root){
  TreeNode *ExtDefList=root;
  while(ExtDefList->child_num!=0){
    TreeNode *ExtDef=ExtDefList->child[0];
    Type symbolType=Specifier(ExtDef->child[0]);
    
    if(strcmp(ExtDef->child[1]->name,"FunDec")==0){
      FieldList field=(FieldList)malloc(sizeof(FieldList));
      field->name=ExtDef->child[1]->child[0]->value;
      Type funcType=(Type)malloc(sizeof(Type));
      funcType->kind=FUNCTION;
      funcType->u.function.funcType=symbolType;
      funcType->u.function.paranum=0;
      funcType->u.function.parameters=NULL;
      if(strcmp(ExtDef->child[1]->child[2]->name,"VarList")==0){
        TreeNode *VarList=ExtDef->child[1]->child[2];
        while(VarList->child_num!=1){
          Type varType=Specifier(VarList->child[0]->child[0]);
          FieldList tmpField=VarDec(VarList->child[0]->child[1],varType); 
         if(indexSymbol(tmpField->name,0)!=NULL)
            printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,ExtDef->lineno,tmpField->name);
         else
            insertSymbol(tmpField);
         funcType->u.function.paranum++;
         tmpField->tail=funcType->u.function.parameters;
         funcType->u.function.parameters=tmpField;
         VarList=VarList->child[2];
        }
        Type varType=Specifier(VarList->child[0]->child[0]);
        FieldList tmpField=VarDec(VarList->child[0]->child[1],varType);
        if(indexSymbol(tmpField->name,0)!=NULL)
            printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\".\n"NONE,ExtDef->lineno,tmpField->name);
         else
            insertSymbol(tmpField);
         funcType->u.function.paranum++;
         tmpField->tail=funcType->u.function.parameters;
         funcType->u.function.parameters=tmpField;
      }
      field->type=funcType;
      
    }else{

    }
    
  }
}*/

void traverseExtDefList(TreeNode *root){
    TreeNode* ExtDefList=root;
    while(ExtDefList->child_num!=0){//ExtDef ExtDefList
        TreeNode* ExtDef=ExtDefList->child[0];
        Type basictype=Specifier(ExtDef->child[0]);
        if(strcmp(ExtDef->child[1]->name,"ExtDecList")==0){//Specifier ExtDecList SEMI
            TreeNode* temp=ExtDef->child[1];//ExtDecList
            FieldList field;
            while(temp->child_num==3){
                field=VarDec(temp->child[0],basictype);
                if(indexSymbol(field->name,0)!=NULL)
                    printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",ExtDef->lineno,field->name);
                else insertSymbol(field);
                temp=temp->child[2];
            }
            field=VarDec(temp->child[0],basictype);
            if(indexSymbol(field->name,0)!=NULL)
                printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",ExtDef->lineno,field->name);
            else insertSymbol(field);
        }
        else if(strcmp(ExtDef->child[1]->name,"FunDec")==0){//Specifier FunDec CompSt
            FieldList field=(FieldList)malloc(sizeof(FieldList_));
            field->name=ExtDef->child[1]->child[0]->value;
            Type typ=(Type)malloc(sizeof(Type_));
            typ->kind=FUNCTION;
            typ->u.function.funcType=basictype;
            //ID LP RP already done
            typ->u.function.paranum=0;
            typ->u.function.parameters=NULL;

            if(strcmp(ExtDef->child[1]->child[2]->name,"VarList")==0){//ID LP VarList RP
                TreeNode *VarList=ExtDef->child[1]->child[2];
                while(VarList->child_num!=1){//ParamDec COMMA VarList
                    Type tempType=Specifier(VarList->child[0]->child[0]);
                    FieldList tempField=VarDec(VarList->child[0]->child[1],tempType);
                    if(indexSymbol(tempField->name,0)!=NULL)
                        printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",ExtDef->lineno,tempField->name);
                    else insertSymbol(tempField);
                    typ->u.function.paranum++;
                    tempField->tail=typ->u.function.parameters;
                    typ->u.function.parameters=tempField;

                    VarList=VarList->child[2];
                }//ParamDec
                Type tempType=Specifier(VarList->child[0]->child[0]);
                FieldList tempField=VarDec(VarList->child[0]->child[1],tempType);
                if(indexSymbol(tempField->name,0)!=NULL)
                    printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",ExtDef->lineno,tempField->name);
                else insertSymbol(tempField);
                typ->u.function.paranum++;
                tempField->tail=typ->u.function.parameters;
                typ->u.function.parameters=tempField;
            }
            field->type=typ;
            if(indexSymbol(field->name,1)!=NULL)
                printf("Error type 4 at Line %d: Redefined function \"%s\".\n",ExtDef->lineno,field->name);
            else insertSymbol(field);

            //CompSt->LC DefList StmtList RC
            traverseCompSt(ExtDef->child[2],basictype);
        }
        else{//Specifier SIMI
            //do nothing
        }

        if(ExtDefList->child[1]==NULL)//ExtDef
            return;
        ExtDefList=ExtDefList->child[1];
    }
}

void traverseCompSt(TreeNode *root,Type funcType){
    TreeNode *CompSt=root;
    traverseDefList(CompSt->child[1]);
    TreeNode *StmtList=CompSt->child[2];
    while(StmtList!=NULL){
        TreeNode *Stmt_=StmtList->child[0];
        traverseStmt(Stmt_,funcType);
        StmtList=StmtList->child[1];
    }
}

void traverseDefList(TreeNode *root){
    TreeNode* DefList=root;
    while(DefList!=NULL){//Def DefList
        TreeNode* Def=DefList->child[0];
        Type basictype=Specifier(Def->child[0]);
        TreeNode *DecList=Def->child[1];
        while(DecList->child_num==3){//Dec COMMA DecList
            FieldList field=VarDec(DecList->child[0]->child[0],basictype);
            if(indexSymbol(field->name,0)!=NULL)
                printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",DecList->lineno,field->name);
            else insertSymbol(field);
            DecList=DecList->child[2];
        }
        FieldList field=VarDec(DecList->child[0]->child[0],basictype);
        if(indexSymbol(field->name,0)!=NULL)
            printf("Error type 3 at Line %d: Redefined variable \"%s\".\n",DecList->lineno,field->name);
        else insertSymbol(field);
        if(DefList->child[1]==NULL)//Def
            return;
        DefList=DefList->child[1];
    }
}

void traverseStmt(TreeNode *root,Type funcType){
    TreeNode *Stmt_=root;
    if(strcmp(Stmt_->child[0]->name,"RETURN")==0){//RETURN Exp SEMI
        Type returnType=Exp(Stmt_->child[1]);
        if(TypeEqual(funcType,returnType)==0)
            printf("Error type 8 at Line %d: Type mismatched for return.\n",Stmt_->lineno);
    }
    else if(strcmp(Stmt_->child[0]->name,"Exp")==0){//Exp
        Exp(Stmt_->child[0]);
    }
    else if(strcmp(Stmt_->child[0]->name,"CompSt")==0){//CompSt
        traverseCompSt(Stmt_->child[0],funcType);
    }
    else if(strcmp(Stmt_->child[0]->name,"WHILE")==0){//WHILE LP Exp RP Stmt
        Type typ=Exp(Stmt_->child[2]);
        if(!((typ->kind==BASIC)&&(typ->u.basic==INT_TYPE)))
            printf("Error type 5 at Line %d: Only type INT could be used for judgement.\n",Stmt_->lineno);
        traverseStmt(Stmt_->child[4],funcType);
    }
    else if(Stmt_->child_num<6){//IF LP Exp RP Stmt
        Type typ=Exp(Stmt_->child[2]);
        if(typ!=NULL)
            if(!((typ->kind==BASIC)&&(typ->u.basic==INT_TYPE)))
                printf("Error type 5 at Line %d: Only type INT could be used for judgement.\n",Stmt_->lineno);

        traverseStmt(Stmt_->child[4],funcType);
    }
    else{//IF LP Exp RP Stmt ELSE Stmt
        Type typ=Exp(Stmt_->child[2]);
        if(!((typ->kind==BASIC)&&(typ->u.basic==INT_TYPE)))
            printf("Error type 5 at Line %d: Only type INT could be used for judgement.\n",Stmt_->lineno);
        traverseStmt(Stmt_->child[4],funcType);
        traverseStmt(Stmt_->child[6],funcType);
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
