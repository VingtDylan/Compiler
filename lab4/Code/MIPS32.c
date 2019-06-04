#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammertree.h"
#include "intercode.h"
#include "semantic.h"
#include "semanticTraverse.h"
#include "MIPS32.h"

extern InterCode *IRList;
extern RegDef Regs[REG_NUM];
extern VarDef *VarDefList;
extern StkDef Stack;
extern char *CODE_KIND_STR[19];
extern int IRlength;
extern int argsnum;

static int RegList[32]={
  8,9,10,11,12,13,14,15,24,25,
  16,17,18,19,20,21,22,23,
  4,5,6,7,
  26,27,
  2,3,
  28,29,30,31,1,0
};

void storeVars(FILE *fp,bool colored){
  //TODO
  VarDef *var=VarDefList;
  while(var!=NULL){
    if(var->reg_no>=0){
      Stack.varStack[Stack.length]=var;
      
    }
  }
}

void loadVars(FILE *fp,bool colored){
  //TODO
}

int getReg(Operand op,FILE *fp,bool colored){
  VarDef *var=VarDefList;
  while(var!=NULL){
    if(op->kind==TEMP_VAR_OP&&var->op->u.tvar_no==op->u.tvar_no){
      //printf(GREEN"Exist 1\n"NONE);
      break;
    }else if(op->kind==VARIABLE_OP&&strcmp(var->op->u.value,op->u.value)==0){
      //printf(GREEN"Exist 2\n"NONE);
      break;
    }
    var=var->next;
  }
  
  //regs empty->insert
  if(var==NULL){
    var=(VarDef*)malloc(sizeof(VarDef));
    var->reg_no=-1;
    var->op=op;
    if(op->kind==TEMP_VAR_OP||op->kind==VARIABLE_OP){
      var->next=VarDefList;
      VarDefList=var;
      //printf(GREEN"Insert op\n"NONE);
    }
  } 

  if(var->reg_no==-1){
    int reg_no=-1;
    for(int i=0;i<REG_IN_USE;i++){
      if(Regs[RegList[i]].var!=NULL){
        Regs[RegList[i]].old++;
      }
    }
    for(int i=0;i<REG_IN_USE;i++){
      if(Regs[RegList[i]].var==NULL){
        reg_no=RegList[i];
        break;
      }
    }
    if(reg_no==-1){
      int maxold=Regs[RegList[0]].old;
      for(int i=0;i<REG_IN_USE;i++){
        if(Regs[RegList[i]].old>maxold){
          maxold=Regs[RegList[i]].old;
          reg_no=RegList[i];
        }
      }
    }
    var->reg_no=reg_no;
    Regs[reg_no].var=var;
    if(var->op->kind==CONSTANT_OP){
      char buffer[32];
      if(colored)
        sprintf(buffer,GRAY"  li %s, %s\n"NONE,Regs[reg_no].name,var->op->u.value);    
      else
        sprintf(buffer,"  li %s, %s\n",Regs[reg_no].name,var->op->u.value);
      fputs(buffer,fp);
    } 
  }
  Regs[var->reg_no].old=0;
  return var->reg_no; 
  //return 1;
}

void genMIPS32Code(char *filename,bool colored){
  FILE *fp;
  if(strcmp(filename,"stdout")==0){
    fp=stdout;
  }else{
    fp=fopen(filename,"w");
  }
  if(!fp){
    PrintError("Error in genMIPS32Code's fopen");
    return;
  }
  //fputs("genMIP32Code\n",fp);
  genMIPS32Objects(fp,colored);
  fclose(fp);
  return ;
}

void init_regs(){
  for(int i=0;i<REG_IN_USE;i++){
    Regs[i].var=NULL;
    Regs[i].old=0;
  }
  
  strcpy(Regs[0].name,"$zero");
  strcpy(Regs[1].name,"$at");
  strcpy(Regs[2].name,"$v0");
  strcpy(Regs[3].name,"$v1");
  strcpy(Regs[4].name,"$a0");
  strcpy(Regs[5].name,"$a1");
  strcpy(Regs[6].name,"$a2");
  strcpy(Regs[7].name,"$a3");
  strcpy(Regs[8].name,"$t0");
  strcpy(Regs[9].name,"$t1");
  strcpy(Regs[10].name,"$t2");
  strcpy(Regs[11].name,"$t3");
  strcpy(Regs[12].name,"$t4");
  strcpy(Regs[13].name,"$t5");
  strcpy(Regs[14].name,"$t6");
  strcpy(Regs[15].name,"$t7");
  strcpy(Regs[16].name,"$s0");
  strcpy(Regs[17].name,"$s1");
  strcpy(Regs[18].name,"$s2");
  strcpy(Regs[19].name,"$s3");
  strcpy(Regs[20].name,"$s4");
  strcpy(Regs[21].name,"$s5");
  strcpy(Regs[22].name,"$s6");
  strcpy(Regs[23].name,"$s7");
  strcpy(Regs[24].name,"$t8");
  strcpy(Regs[25].name,"$t9");  
  strcpy(Regs[26].name,"$k0");
  strcpy(Regs[27].name,"$k1");
  strcpy(Regs[28].name,"$gp");
  strcpy(Regs[29].name,"$sp");
  strcpy(Regs[30].name,"$fp");
  strcpy(Regs[31].name,"$ra");
  /*
  strcpy(Regs[0].name, "$t0");
  strcpy(Regs[1].name, "$t1");
  strcpy(Regs[2].name, "$t2");
  strcpy(Regs[3].name, "$t3");
  strcpy(Regs[4].name, "$t4");
  strcpy(Regs[5].name, "$t5");
  strcpy(Regs[6].name, "$t6");
  strcpy(Regs[7].name, "$t7");
  strcpy(Regs[8].name, "$t8");
  strcpy(Regs[9].name, "$t9");
  strcpy(Regs[10].name, "$s0");
  strcpy(Regs[11].name, "$s1");
  strcpy(Regs[12].name, "$s2");
  strcpy(Regs[13].name, "$s3");
  strcpy(Regs[14].name, "$s4");
  strcpy(Regs[15].name, "$s5");
  strcpy(Regs[16].name, "$s6");
  strcpy(Regs[17].name, "$s7");
  strcpy(Regs[18].name, "$v1");
  strcpy(Regs[19].name, "$fp");
  strcpy(Regs[20].name, "$a0");
  strcpy(Regs[21].name, "$a1");
  strcpy(Regs[22].name, "$a2");
  strcpy(Regs[23].name, "$a3");
  strcpy(Regs[24].name, "$v0");	
  strcpy(Regs[25].name, "$ra");
  strcpy(Regs[26].name, "$gp");	
  strcpy(Regs[27].name, "$sp");	
  strcpy(Regs[28].name, "$k0");	
  strcpy(Regs[29].name, "$k1");
  strcpy(Regs[30].name, "$at");	
  strcpy(Regs[31].name, "$zero");
  */return ;
}

void genMIPS32Header(FILE *fp,bool colored){
  if(colored){
    fputs(GRAY".data\n"NONE,fp);
    fputs(GRAY"_prompt: .asciiz \"Enter an integer:\"\n"NONE,fp);
    fputs(GRAY"_ret: .asciiz \"\\n\"\n"NONE,fp);
    fputs(GRAY".globl main\n"NONE,fp);
    fputs(GRAY".text\n"NONE,fp);

    fputs(GRAY"read:\n"NONE,fp);
    fputs(GRAY"  li $v0, 4\n"NONE,fp);
    fputs(GRAY"  la $a0, _prompt\n"NONE,fp);
    fputs(GRAY"  syscall\n"NONE,fp);
    fputs(GRAY"  li $v0, 5\n"NONE,fp);
    fputs(GRAY"  syscall\n"NONE,fp);
    fputs(GRAY"  jr $ra\n"NONE,fp);
    fputs(GRAY"\n"NONE,fp);
    
    fputs(GRAY"write:\n"NONE,fp);
    fputs(GRAY"  li $v0,1 \n"NONE,fp);
    fputs(GRAY"  syscall\n"NONE,fp);
    fputs(GRAY"  li $v0, 4\n"NONE,fp);
    fputs(GRAY"  la $a0, _ret\n"NONE,fp);
    fputs(GRAY"  syscall\n"NONE,fp);
    fputs(GRAY"  move $v0, $0\n"NONE,fp);
    fputs(GRAY"  jr $ra\n"NONE,fp);
  }else{
    fputs(".data\n",fp);
    fputs("_prompt: .asciiz \"Enter an integer:\"\n",fp);
    fputs("_ret: .asciiz \"\\n\"\n",fp);
    fputs(".globl main\n",fp);
    fputs(".text\n",fp);

    fputs("read:\n",fp);
    fputs("  li $v0, 4\n",fp);
    fputs("  la $a0, _prompt\n",fp);
    fputs("  syscall\n",fp);
    fputs("  li $v0, 5\n",fp);
    fputs("  syscall\n",fp);
    fputs("  jr $ra\n",fp);
    fputs("\n",fp);
    
    fputs("write:\n",fp);
    fputs("  li $v0,1 \n",fp);
    fputs("  syscall\n",fp);
    fputs("  li $v0, 4\n",fp);
    fputs("  la $a0, _ret\n",fp);
    fputs("  syscall\n",fp);
    fputs("  move $v0, $0\n",fp);
    fputs("  jr $ra\n",fp);
  }
  return ;
}

void genMIPS32Objects(FILE *fp,bool colored){
  VarDefList=NULL;
  argsnum=0;
  init_regs();
  genMIPS32Header(fp,colored);
  for(int i=0;i<IRlength;i++){
    InterCode ir=IRList[i];
    if(ir==NULL)
      continue;
    genMIPS32CodeIR(fp,ir,i,colored);  
  }
  return;
}


void genMIPS32CodeIR(FILE *fp,InterCode ir,int index,bool colored){
  //fputs("genMIP32CodeIR\n",fp);
  if(ir==NULL)
    return ;
  if(ir->kind==LABEL_CODE){
    char buffer[32];
    if(colored)
      sprintf(buffer,GRAY"label%d:\n"NONE,ir->u.single.op->u.label_no);
    else
      sprintf(buffer,"label%d:\n",ir->u.single.op->u.label_no);
    fputs(buffer,fp);
  }else if(ir->kind==FUNCTION_CODE){
    char buffer[32];
    if(colored)
      sprintf(buffer,GRAY"\n%s:\n"NONE,ir->u.single.op->u.value);
    else
      sprintf(buffer,"\n%s:\n",ir->u.single.op->u.value);
    fputs(buffer,fp);
    VarDef *var=VarDefList;
    while(var!=NULL){
      VarDefList=var->next;
      free(var);
      var=VarDefList;
    }
    for(int i=0;i<REG_IN_USE;i++){
      Regs[i].old=0;
      Regs[i].var=NULL;
    }
    int i=0;
    while(IRList[index+i+1]->kind==PARAMETER_CODE){
      int reg_no=getReg(IRList[index+i+1]->u.single.op,fp,colored);
      memset(buffer,0,sizeof(buffer));
      if(colored)
        sprintf(buffer,GRAY"  move %s, $a%d\n"NONE,Regs[reg_no].name,i);
      else
        sprintf(buffer,"  move %s, $a%d\n",Regs[reg_no].name,i);
      fputs(buffer,fp);
      i++;
    }
  }else if(ir->kind==READ_CODE){
    if(colored){
      fputs(GRAY"  addi $sp, $sp, -4\n"NONE,fp);
      fputs(GRAY"  sw $ra, 0($sp)\n"NONE,fp);
      fputs(GRAY"  jal read\n"NONE,fp);
      int reg_no=getReg(ir->u.single.op,fp,colored);
      fputs(GRAY"  lw $ra, 0($sp)\n"NONE,fp);
      fputs(GRAY"  addi $sp, $sp, 4\n"NONE,fp);
      char buffer[32];
      sprintf(buffer,GRAY"  move %s, $v0\n"NONE,Regs[reg_no].name);
      fputs(buffer,fp);
    }else{
      fputs("  addi $sp, $sp, -4\n",fp);
      fputs("  sw $ra, 0($sp)\n",fp);
      fputs("  jal read\n",fp);
      int reg_no=getReg(ir->u.single.op,fp,colored);
      fputs("  lw $ra, 0($sp)\n",fp);
      fputs("  addi $sp, $sp, 4\n",fp);
      char buffer[32];
      sprintf(buffer,"  move %s, $v0\n",Regs[reg_no].name);
      fputs(buffer,fp);      
    }
  }else if(ir->kind==WRITE_CODE){
    if(colored){
      int reg_no=getReg(ir->u.single.op,fp,colored);
      char buffer[32];
      sprintf(buffer,GRAY"  move $a0, %s\n"NONE,Regs[reg_no].name);
      fputs(buffer,fp);
      fputs(GRAY"  addi $sp, $sp, -4\n"NONE,fp);
      fputs(GRAY"  sw $ra, 0($sp)\n"NONE,fp);
      fputs(GRAY"  jal write\n"NONE,fp);
      fputs(GRAY"  lw $ra, 0($sp)\n"NONE,fp);
      fputs(GRAY"  addi $sp, $sp, 4\n"NONE,fp);
    }else{
      int reg_no=getReg(ir->u.single.op,fp,colored);
      char buffer[32];
      sprintf(buffer,"  move $a0, %s\n",Regs[reg_no].name);
      fputs(buffer,fp);
      fputs("  addi $sp, $sp, -4\n",fp);
      fputs("  sw $ra, 0($sp)\n",fp);
      fputs("  jal write\n",fp);
      fputs("  lw $ra, 0($sp)\n",fp);
      fputs("  addi $sp, $sp, 4\n",fp);
    }
  }else if(ir->kind==ASSIGN_CODE){
    Operand leftOp=ir->u.assignOp.left;
    Operand rightOp=ir->u.assignOp.right;
    if(rightOp->kind==CONSTANT_OP){
      int reg_no=getReg(leftOp,fp,colored);
      char buffer[32];
      if(colored)
        sprintf(buffer,GRAY"  li %s, %s\n"NONE,Regs[reg_no].name,rightOp->u.value);
      else
        sprintf(buffer,"  li %s, %s\n",Regs[reg_no].name,rightOp->u.value);
      fputs(buffer,fp);
    }else if(rightOp->kind==TEMP_VAR_OP||rightOp->kind==VARIABLE_OP){
      int reg_no1=getReg(leftOp,fp,colored);
      int reg_no2=getReg(rightOp,fp,colored);
      char buffer[32];
      if(colored)
        sprintf(buffer,GRAY"  move %s, %s\n"NONE,Regs[reg_no1].name,Regs[reg_no2].name);
      else
        sprintf(buffer,"  move %s, %s\n",Regs[reg_no1].name,Regs[reg_no2].name);
      fputs(buffer,fp);
    }
  }else if(ir->kind==PLUS_CODE){
    Operand result=ir->u.tripleOp.result;
    Operand op1=ir->u.tripleOp.op1;
    Operand op2=ir->u.tripleOp.op2;
    if(op2->kind==CONSTANT_OP){
      int reg_no1=getReg(result,fp,colored);
      int reg_no2=getReg(op1,fp,colored);
      char buffer[64];
      if(colored)
        sprintf(buffer,GRAY"  addi %s, %s, %s\n"NONE,Regs[reg_no1].name,Regs[reg_no2].name,op2->u.value);
      else
        sprintf(buffer,"  addi %s, %s, %s\n",Regs[reg_no1].name,Regs[reg_no2].name,op2->u.value);
      fputs(buffer,fp); 
    }else{
      int reg_no1=getReg(result,fp,colored);
      int reg_no2=getReg(op1,fp,colored);
      int reg_no3=getReg(op2,fp,colored);
      char buffer[64];
      if(colored)
        sprintf(buffer,GRAY"  add %s, %s, %s\n"NONE,Regs[reg_no1].name,Regs[reg_no2].name,Regs[reg_no3].name);
      else
        sprintf(buffer,"  add %s, %s, %s\n",Regs[reg_no1].name,Regs[reg_no2].name,Regs[reg_no3].name);     
      fputs(buffer,fp);
    }
  }else if(ir->kind==MINUS_CODE){
    Operand result=ir->u.tripleOp.result;
    Operand op1=ir->u.tripleOp.op1;
    Operand op2=ir->u.tripleOp.op2;
    if(op2->kind==CONSTANT_OP){
      int reg_no1=getReg(result,fp,colored);
      int reg_no2=getReg(op1,fp,colored);//bug  !
      char buffer[64];
      if(colored)
        sprintf(buffer,GRAY"  addi %s, %s, -%s\n"NONE,Regs[reg_no1].name,Regs[reg_no2].name,op2->u.value);
      else
        sprintf(buffer,"  addi %s, %s, -%s\n",Regs[reg_no1].name,Regs[reg_no2].name,op2->u.value);
      fputs(buffer,fp);//fputs left
    }else{
      int reg_no1=getReg(result,fp,colored);
      int reg_no2=getReg(op1,fp,colored);
      int reg_no3=getReg(op2,fp,colored);
      char buffer[64];
      if(colored)
        sprintf(buffer,GRAY"  sub %s, %s, %s\n"NONE,Regs[reg_no1].name,Regs[reg_no2].name,Regs[reg_no3].name);
      else
        sprintf(buffer,"  sub %s, %s, %s\n",Regs[reg_no1].name,Regs[reg_no2].name,Regs[reg_no3].name);
      fputs(buffer,fp);
    }
  }else if(ir->kind==MUL_CODE){
    Operand result=ir->u.tripleOp.result;
    Operand op1=ir->u.tripleOp.op1;
    Operand op2=ir->u.tripleOp.op2;
    int reg_no1=getReg(result,fp,colored);
    int reg_no2=getReg(op1,fp,colored);
    int reg_no3=getReg(op2,fp,colored);
    char buffer[64];
    if(colored)
      sprintf(buffer,GRAY"  mul %s, %s, %s\n"NONE,Regs[reg_no1].name,Regs[reg_no2].name,Regs[reg_no3].name);
    else
      sprintf(buffer,"  mul %s, %s, %s\n",Regs[reg_no1].name,Regs[reg_no2].name,Regs[reg_no3].name);
    fputs(buffer,fp);
  }else if(ir->kind==GOTO_CODE){
    Operand op=ir->u.single.op;
    char buffer[32];
    if(colored)
      sprintf(buffer,GRAY"  j label%d\n"NONE,ir->u.single.op->u.label_no);
    else
      sprintf(buffer,"  j label%d\n",ir->u.single.op->u.label_no);
    fputs(buffer,fp);
  }else if(ir->kind==IF_GOTO_CODE){
    int reg_no1=getReg(ir->u.ifgotoOp.op1,fp,colored);
    int reg_no2=getReg(ir->u.ifgotoOp.op2,fp,colored);
    char options[8];
    strcpy(options,ir->u.ifgotoOp.relop);
    if(strcmp(options,"==")==0){
      memset(options,0,sizeof(options));
      strcpy(options,"beq");
    }else if(strcmp(options,"!=")==0){
      memset(options,0,sizeof(options));
      strcpy(options,"bne");
    }else if(strcmp(options,">")==0){
      memset(options,0,sizeof(options));
      strcpy(options,"bgt");
    }else if(strcmp(options,"<")==0){
      memset(options,0,sizeof(options));
      strcpy(options,"blt");
    }else if(strcmp(options,">=")==0){
      memset(options,0,sizeof(options));
      strcpy(options,"bge");
    }else if(strcmp(options,"<=")==0){
      memset(options,0,sizeof(options));
      strcpy(options,"ble");
    }
    char buffer[64];
    if(colored)
      sprintf(buffer,GRAY"  %s %s, %s, label%d\n"NONE,options,Regs[reg_no1].name,Regs[reg_no2].name,ir->u.ifgotoOp.label->u.label_no);
    else
      sprintf(buffer,"  %s %s, %s, label%d\n",options,Regs[reg_no1].name,Regs[reg_no2].name,ir->u.ifgotoOp.label->u.label_no);
    fputs(buffer,fp);
  }else if(ir->kind==ARG_CODE){
    //TODO
    if(argsnum>=4){
      argsnum=4;
    }else{
      argsnum++;
    }
    getReg(ir->u.single.op,fp,colored);
  }else if(ir->kind==CALL_CODE){
    char buffer[32];
    int offset=-4*argsnum-4;
    if(colored){
      sprintf(buffer,GRAY"  addi $sp, $sp, %d\n"NONE,offset);
      fputs(buffer,fp);
      fputs(GRAY"  sw $ra, 0($sp)\n"NONE,fp);
    }else{
      sprintf(buffer,"  addi $sp, $sp, %d\n",offset);
      fputs(buffer,fp);
      fputs("  sw $ra, 0($sp)\n",fp);
    }
    if(argsnum==1){
      //TODO
      if(colored){
        fputs(GRAY"  sw $a0, 4($sp)\n"NONE,fp);
        InterCode pre=IRList[index-1];
        int reg_no=getReg(pre->u.single.op,fp,colored);
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,GRAY"  move $a0 %s\n"NONE,Regs[reg_no].name);
        fputs(buffer,fp);
      }else{
        fputs("  sw $a0, 4($sp)\n",fp);
        InterCode pre=IRList[index-1];
        int reg_no=getReg(pre->u.single.op,fp,colored);
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"  move $a0 %s\n",Regs[reg_no].name);
        fputs(buffer,fp);
      }
      //storeVar(fp);
      VarDef *var=VarDefList;
      while(var!=NULL){
        if(var->reg_no>=0){
          Stack.varStack[Stack.length]=var;//
          if(colored){
            fputs(GRAY"  addi $sp, $sp, -4\n"NONE,fp);
            char buffer[32];
            sprintf(buffer,GRAY"  sw %s, 0($sp)\n"NONE,Regs[var->reg_no].name);
            fputs(buffer,fp);
          }else{
            fputs("  addi $sp, $sp, -4\n",fp);
            char buffer[32];
            sprintf(buffer,"  sw %s, 0($sp)\n",Regs[var->reg_no].name);
            fputs(buffer,fp);
          }
          Regs[var->reg_no].var=NULL;
          Stack.old[Stack.length]=Regs[var->reg_no].old;
          Regs[var->reg_no].old=0;
          Stack.length++;
        }
        var=var->next;
      }
      VarDefList=NULL;
      memset(buffer,0,sizeof(buffer));
      if(colored)
        sprintf(buffer,GRAY"  jal %s\n"NONE,ir->u.assignOp.right->u.value);
      else
        sprintf(buffer,"  jal %s\n",ir->u.assignOp.right->u.value);
      fputs(buffer,fp);

      //loadVar(fp);
      var=VarDefList;
      while(var!=NULL){
        VarDefList=var->next;
        free(var);
        var=VarDefList;
      }
      for(int i=Stack.length-1;i>=0;i--){
        VarDef *varIndex=Stack.varStack[i];
        if(varIndex==NULL)
          continue;
        varIndex->next=VarDefList;
        VarDefList=varIndex;
        char buffer[32];
        if(colored){
          sprintf(buffer,GRAY"  lw %s, 0($sp)\n"NONE,Regs[varIndex->reg_no].name);
          fputs(buffer,fp);
          fputs(GRAY"  addi $sp, $sp, 4\n"NONE,fp);
        }else{
          sprintf(buffer,"  lw %s, 0($sp)\n",Regs[varIndex->reg_no].name);
          fputs(buffer,fp);
          fputs("  addi $sp, $sp, 4\n",fp);
        }
        Regs[varIndex->reg_no].var=varIndex;
        Regs[varIndex->reg_no].old=Stack.old[i];
      }
      Stack.length=0;
      if(colored){
        fputs(GRAY"  lw $a0, 4($sp)\n"NONE,fp);
        fputs(GRAY"  lw $ra, 0($sp)\n"NONE,fp);
        fputs(GRAY"  addi $sp, $sp, 8\n"NONE,fp);
      }else{
        fputs("  lw $a0, 4($sp)\n",fp);
        fputs("  lw $ra, 0($sp)\n",fp);
        fputs("  addi $sp, $sp, 8\n",fp);
      }
    }
    argsnum=0;
    int reg_no=getReg(ir->u.assignOp.left,fp,colored);
    memset(buffer,0,sizeof(buffer));
    if(colored)
      sprintf(buffer,GRAY"  move %s, $v0\n"NONE,Regs[reg_no].name);
    else
      sprintf(buffer,"  move %s, $v0\n",Regs[reg_no].name);
    fputs(buffer,fp);
  }else if(ir->kind==RETURN_CODE){
    Operand op=ir->u.single.op;
    if(op->kind==CONSTANT_OP&&strcmp(op->u.value,"0")==0){
      if(colored)
        fputs(GRAY"  move $v0, $0\n"NONE,fp);
      else
        fputs("  move $v0, $0\n",fp);
    }else{
      int reg_no=getReg(op,fp,colored);
      char buffer[32];
      if(colored)
        sprintf(buffer,GRAY"  move $v0, %s\n"NONE,Regs[reg_no].name);
      else
        sprintf(buffer,"  move $v0, %s\n",Regs[reg_no].name);     
      fputs(buffer,fp);     
    }
    if(colored)
      fputs(GRAY"  jr $ra\n"NONE,fp);
    else
      fputs("  jr $ra\n",fp);
  }else if(ir->kind==PARAMETER_CODE){
    
  }else{
    printf(GREEN"%s\n"NONE,CODE_KIND_STR[ir->kind]);
    //PrintHint("Unrecognized ir->kind\n");
  }
}
