#include "grammertree.h"
#include "semantic.h"
#include "semanticTraverse.h"

extern FieldList hashTable[MAX_HASH_SIZE];

Type Condition(TreeNode *root,Operand L1,Operand L2){
  /*L1->B.true L2->B.false*/
  if(strcmp(root->child[0]->name,"Exp")==0){
    TreeNode *tmp=root->child[1];
    if(strcmp(root->child[1]->name,"RELOP")==0){
      /*
	t1=new_temp()
	t2=new_temp()
	code1=translate_Exp(Exp1,sym_table,t1)
	code2=translate_Exp(Exp2,sym_table,t2)
	op=get_relop(RELOP)
	code3=[IF t1 op t2 GOTO label_true]
	code1+code2+code3+[GOTO label_false]	
      */
      //gen t1,t2
      Operand tmpVarOp1=(Operand)malloc(sizeof(Operand_));
      Type typ1;
      //gen code1
      if(strcmp(root->child[0]->child[0]->name,"INT")==0){
        typ1=Exp(root->child[0],NULL);
        tmpVarOp1->kind=CONSTANT_OP;
        sprintf(tmpVarOp1->u.value,"%s",root->child[0]->child[0]->value);
      }else{
        tmpVarOp1->kind=TEMP_VAR_OP;
        typ1=Exp(root->child[0],tmpVarOp1);
      }
      Operand tmpVarOp2=malloc(sizeof(Operand_));
      Type typ2;
      //gen code2
      if(strcmp(root->child[2]->child[0]->name,"INT")==0){
        typ2=Exp(root->child[2],NULL);
        tmpVarOp2->kind=CONSTANT_OP;
        sprintf(tmpVarOp2->u.value,"%s",root->child[2]->child[0]->value);
      }else{
        tmpVarOp2->kind=TEMP_VAR_OP;
        typ2=Exp(root->child[2],tmpVarOp2);
      }
      /*if(typ1==NULL||typ2==NULL){
	printf("emmm");
        return NULL;
      }*/
      //gen code3
      InterCode ifgotoIR=(InterCode)malloc(sizeof(InterCode_));
      ifgotoIR->kind=IF_GOTO_CODE;
      ifgotoIR->u.ifgotoOp.op1=tmpVarOp1;
      ifgotoIR->u.ifgotoOp.op2=tmpVarOp2;
      ifgotoIR->u.ifgotoOp.label=L1;
      strcpy(ifgotoIR->u.ifgotoOp.relop,root->child[1]->value);
      insertCode(ifgotoIR);
      //[GOTO label_false]
      InterCode gotoIR=malloc(sizeof(InterCode_));
      gotoIR->kind=GOTO_CODE;
      gotoIR->u.single.op=L2;
      insertCode(gotoIR);
      return typ2;
    }else if(strcmp(root->child[1]->name,"AND")==0){
      /*
	label1=new_label()
	code1=translate_Cond(Exp1,label1,label_false,sym_table)
	code2=translate_Cond(Exp2,label_true,label_false,sym_table)
	code1+[LABEL label1]+code2
      */
      //gen label1
      Operand labelOp=(Operand)malloc(sizeof(Operand_));
      labelOp->kind=LABEL_OP;
      labelOp->u.label_no=LabelCounter++;
      //gen code1
      Type type1=Condition(root->child[0],labelOp,L2);
      //[LABEL label1
      InterCode labelIR=(InterCode)malloc(sizeof(InterCode_));
      labelIR->kind=LABEL_CODE;
      labelIR->u.single.op=labelOp;
      insertCode(labelIR);
      //gen code2
      Type type2=Condition(root->child[2],L1,L2);
      return type1;//TODO
    }else if(strcmp(root->child[1]->name,"OR")==0){
      /*
        label=new_label()
	code1=translate_Cond(Exp1,label_true,label1,sym_rable)
	code2=translate_Cond(Exp2,label_true,label_false,sym_table)
	code1+[LABEL label1]+code2
      */
      //gen label1
      Operand labelOp=(Operand)malloc(sizeof(Operand_));
      labelOp->kind=LABEL_OP;
      labelOp->u.label_no=LabelCounter++;
      //gen code1
      Type type1=Condition(root->child[0],L1,labelOp);
      //[LABEL label1]
      InterCode labelIR=(InterCode)malloc(sizeof(InterCode_));
      labelIR->kind=LABEL_CODE;
      labelIR->u.single.op=labelOp;
      insertCode(labelIR);
      //gen code2
      Type type2=Condition(root->child[2],L1,L2);
      return type1;
    }
  }else if(strcmp(root->child[0]->name,"NOT")==0){
    return Condition(root->child[1],L2,L1);
  }else{
    //printf("unhandled Cond");
    /*
      t1=new_temp()
      code1=translate_Exp(Exp,sym_table,t1)
      code2=[IF t1!=#0 'GOTO' label_true]
      code1+code2+[GOTO label_false]
    */
    //gen t1
    Operand tmpOp=(Operand)malloc(sizeof(Operand_));
    Type type;
    //gen code1
    if(strcmp(root->child[0]->name,"INT")==0){
      type=Exp(root,NULL);
      tmpOp->kind=CONSTANT_OP;
      sprintf(tmpOp->u.value,"%s",root->child[0]->value);
    }else{
      tmpOp->kind=TEMP_VAR_OP;
      type=Exp(root,tmpOp);
    }  
    //gen code2
    InterCode ifgotoIR=(InterCode)malloc(sizeof(InterCode_));
    ifgotoIR->kind=IF_GOTO_CODE;
    ifgotoIR->u.ifgotoOp.op1=tmpOp;
    strcpy(ifgotoIR->u.ifgotoOp.relop,"!=");
    Operand zeroOp=(Operand)malloc(sizeof(Operand_));
    zeroOp->kind=CONSTANT_OP;
    strcpy(zeroOp->u.value,"0");
    ifgotoIR->u.ifgotoOp.op2=zeroOp;
    ifgotoIR->u.ifgotoOp.label=L1;
    insertCode(ifgotoIR);
    //gen [GOTO label_false]
    InterCode gotoIR=(InterCode)malloc(sizeof(InterCode_));
    gotoIR->kind=GOTO_CODE;
    gotoIR->u.single.op=L2;
    insertCode(gotoIR);
    return type;
  }
  return NULL;
}

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
	
      Operand funcOp=(Operand)malloc(sizeof(Operand_));
      funcOp->kind=FUNCTION_OP;
      strcpy(funcOp->u.value,field->name);
      InterCode funcIR=(InterCode)malloc(sizeof(InterCode_));
      funcIR->kind=FUNCTION_CODE;
      funcIR->u.single.op=funcOp;
      //printf("\n%s\n",funcIR->u.single.op->u.value);
      insertCode(funcIR);

      /*ID LP VarList RP*/
      if(strcmp(ExtDef->child[1]->child[2]->name,"VarList")==0){
        TreeNode *VarListRoot=ExtDef->child[1]->child[2];
        /*ParamDec COMMA VarList*/
        while(VarListRoot->child_num!=1){
          Type varType=Specifier(VarListRoot->child[0]->child[0],field->name);
          FieldList VarDecField=VarDec(VarListRoot->child[0]->child[1],varType,field->name,1/*Undone*/);
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
          Operand paramOp=(Operand)malloc(sizeof(Operand_));
          //InterCode paramIR=(InterCode)malloc(sizeof(InterCode_));
	  if(VarDecField->type->kind==BASIC){
            paramOp->kind=VARIABLE_OP;
            strcpy(paramOp->u.value,funcType->u.function.parameters->name);
            InterCode paramIR=(InterCode)malloc(sizeof(InterCode_));
	    paramIR->kind=PARAMETER_CODE;
            paramIR->u.single.op=paramOp;
            insertCode(paramIR);
	  }else if(VarDecField->type->kind==ARRAY){
	    /*TODO*/
            paramOp->kind=VARIABLE_OP;
            strcpy(paramOp->u.value,funcType->u.function.parameters->name);
            InterCode paramIR=(InterCode)malloc(sizeof(InterCode_));
            paramIR->kind=PARAMETER_CODE;
            paramIR->u.single.op=paramOp;
            insertCode(paramIR);
          }
          VarListRoot=VarListRoot->child[2];
        }
        /*ParamDec*/
        Type varType=Specifier(VarListRoot->child[0]->child[0],field->name);
        FieldList VarDecField=VarDec(VarListRoot->child[0]->child[1],varType,field->name,1/*Undone*/); 
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
        Operand paramOp=(Operand)malloc(sizeof(Operand_));
        InterCode paramIR=(InterCode)malloc(sizeof(InterCode_));
        paramOp->kind=VARIABLE_OP;
        strcpy(paramOp->u.value,funcType->u.function.parameters->name);
        paramIR->kind=PARAMETER_CODE;
        paramIR->u.single.op=paramOp;
        insertCode(paramIR);
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
       int index=1;
       while(ExtDecList->child_num==3){
         /*VarDec COMMA ExtDecList*/
         field=VarDec(ExtDecList->child[0],symbolType,"Program",index);
         if(indexSymbol(field->name,false)!=NULL)
           printf(CYAN"Error type 3 at Line %d: Redefined variable \"%s\" .\n"NONE,ExtDef->lineno,field->name);
         else
           insertSymbol(field);
         ExtDecList=ExtDecList->child[2];
       }
       field=VarDec(ExtDecList->child[0],symbolType,"Program",index);
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
      FieldList field=VarDec(DecList->child[0]->child[0],symbolType,pname,1/*Undone*/);
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
    FieldList field=VarDec(DecList->child[0]->child[0],symbolType,pname,1/*Undone*/);
    //printf("%s:%d\n",DecList->child[0]->child[0]->child[0]->value,field->type->u.basic);
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
    //Exp(Stmt->child[0]);
    Exp(Stmt->child[0],NULL);
  }else if(strcmp(Stmt->child[0]->name,"CompSt")==0){
    /*CompSt*/
    traverseCompSt(Stmt->child[0],funcType,pname);
  }else if(strcmp(Stmt->child[0]->name,"RETURN")==0){
    /*RETURN Exp SEMI*/
    Type returnType=NULL;/*kule*///=Exp(Stmt->child[1],NULL);
    Operand returnOp=(Operand)malloc(sizeof(Operand_));
    memset(returnOp,0,sizeof(Operand_));
    if(strcmp(root->child[1]->child[0]->name,"INT")==0){
      returnOp->kind=CONSTANT_OP;
      strcpy(returnOp->u.value,root->child[1]->child[0]->value);
      returnType=Exp(Stmt->child[1],returnOp);/*Bug*/
    }else{
      returnType=Exp(Stmt->child[1],returnOp);  
    }
    if(TypeEqual(funcType,returnType)==0)
      printf(CYAN"Error type 8 at Line %d: Type mismatched for return.\n"NONE,Stmt->lineno);
    InterCode returnIR=(InterCode)malloc(sizeof(InterCode_));
    returnIR->kind=RETURN_CODE;
    returnIR->u.single.op=returnOp;
    insertCode(returnIR);
  }else if(Stmt->child_num==5&&strcmp(Stmt->child[0]->name,"IF")==0){
    /*TODO*/
    /*IF LP Exp RP Stmt*/
    /*
      label1=new_label()
      label2=new_label()
      code1=translate_Cond(Exp,label1,label2,sym_table)
      code2=translate_Stmt(Stmt1,sym_table)
      code1+[LABEL label1]+code2+[LABEL label2]
    */
    /*gen Label L1 L2*/
    Operand L1=(Operand)malloc(sizeof(Operand_));
    L1->kind=LABEL_OP;
    L1->u.label_no=LabelCounter++;
    Operand L2=(Operand)malloc(sizeof(Operand_));
    L2->kind=LABEL_OP;
    L2->u.label_no=LabelCounter++;
    /*gen Code1*/
    /*true false*/ 
    Type expType=Condition(Stmt->child[2],L1,L2);
    //Type expType=Exp(Stmt->child[2]);
    if(expType!=NULL)
      if(!((expType->kind==BASIC)&&(expType->u.basic==INT_TYPE)))
        printf(CYAN"Error type 5 at Line %d: Only type INT could be used for judgement.\n"NONE,Stmt->lineno);
    /*gen Label L1*/
    InterCode L1IR=(InterCode)malloc(sizeof(InterCode_));
    L1IR->kind=LABEL_CODE;
    L1IR->u.single.op=L1;
    insertCode(L1IR);
    /*gen childCode*/
    traverseStmt(Stmt->child[4],funcType,pname);
    /*gen Label L2*/
    InterCode L2IR=(InterCode)malloc(sizeof(InterCode_));
    L2IR->kind=LABEL_CODE;
    L2IR->u.single.op=L2;
    insertCode(L2IR);
  }else if(Stmt->child_num==7&&strcmp(Stmt->child[0]->name,"IF")==0){
    /*TODO*/
    /*IF LP Exp RP Stmt ELSE Stmt*/
    /*the same way*/
    Operand L1=(Operand)malloc(sizeof(Operand_));
    L1->kind=LABEL_OP;
    L1->u.label_no=LabelCounter++;
    Operand L2=(Operand)malloc(sizeof(Operand_));
    L2->kind=LABEL_OP;
    L2->u.label_no=LabelCounter++;
    Type expType=Condition(Stmt->child[2],L1,L2);
    //Type expType=Exp(Stmt->child[2]);
    if(!((expType->kind==BASIC)&&(expType->u.basic==INT_TYPE)))
      printf(CYAN"Error type 5 at Line %d: Only type INT could be used for judgement.\n"NONE,Stmt->lineno);
    //gen L1
    InterCode L1IR=(InterCode)malloc(sizeof(InterCode_));
    L1IR->kind=LABEL_CODE;
    L1IR->u.single.op=L1;
    insertCode(L1IR);    

    traverseStmt(Stmt->child[4],funcType,pname);
    //goto L3
    Operand L3=(Operand)malloc(sizeof(Operand_));
    L3->kind=LABEL_OP;
    L3->u.label_no=LabelCounter++;
    InterCode gotoL3IR=(InterCode)malloc(sizeof(InterCode_));
    gotoL3IR->kind=GOTO_CODE;
    gotoL3IR->u.single.op=L3;
    insertCode(gotoL3IR);
    //gen L2
    InterCode L2IR=(InterCode)malloc(sizeof(InterCode_));
    L2IR->kind=LABEL_CODE;
    L2IR->u.single.op=L2;
    insertCode(L2IR);

    traverseStmt(Stmt->child[6],funcType,pname);
    //gen L3
    InterCode L3IR=(InterCode)malloc(sizeof(InterCode_));
    L3IR->kind=LABEL_CODE;
    L3IR->u.single.op=L3;
    insertCode(L3IR);
  }else if(strcmp(Stmt->child[0]->name,"WHILE")==0){
    /*WHILE LP Exp RP Stmt*/
    /* LABEL L1 */
    Operand L1=(Operand)malloc(sizeof(Operand_));
    L1->kind=LABEL_OP;
    L1->u.label_no=LabelCounter++;
    InterCode L1IR=(InterCode)malloc(sizeof(InterCode_));
    L1IR->kind=LABEL_CODE;
    L1IR->u.single.op=L1;
    insertCode(L1IR);
    /* L2 L3 */
    Operand L2=(Operand)malloc(sizeof(Operand_));
    L2->kind=LABEL_OP;
    L2->u.label_no=LabelCounter++;
    Operand L3=(Operand)malloc(sizeof(Operand_));
    L3->kind=LABEL_OP;
    L3->u.label_no=LabelCounter++;
    /*true,false*/
    Type expType=Condition(root->child[2],L2,L3);
    //Type expType=Exp(Stmt->child[2]);
    if(!((expType->kind==BASIC)&&(expType->u.basic==INT_TYPE)))
      printf(CYAN"Error type 5 at Line %d: Only type INT could be used for judgement.\n"NONE,Stmt->lineno);
    /*gen L2*/
    InterCode L2IR=(InterCode)malloc(sizeof(InterCode_));
    L2IR->kind=LABEL_CODE;
    L2IR->u.single.op=L2;
    insertCode(L2IR);
    /*gen childcode*/
    traverseStmt(Stmt->child[4],funcType,pname);
    /*GOTO: LABEL(L1)*/
    InterCode gotoL1IR=(InterCode)malloc(sizeof(InterCode_));
    gotoL1IR->kind=GOTO_CODE;
    gotoL1IR->u.single.op=L1;
    insertCode(gotoL1IR);
    /*gen L3*/
    InterCode L3IR=(InterCode)malloc(sizeof(InterCode_));
    L3IR->kind=LABEL_CODE;
    L3IR->u.single.op=L3;
    insertCode(L3IR);
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
