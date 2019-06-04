#include "grammertree.h"
#include "semantic.h"
#include "semanticTraverse.h"

extern int IRlength;
extern int IRCapacity;
extern InterCode *IRList;

extern int LabelCounter;
extern int VarCounter;
extern int TempVarCounter; 

void initIRList(){
  IRList=(InterCode*)malloc(MAX_IR_SIZE*sizeof(InterCode));
  if(IRList==NULL){
    PrintError("Error in initIRList\n");
    return ;
  }
  IRCapacity=MAX_IR_SIZE;/*Temp Max lenght*/
  IRlength=0;/*Count begin*/
  LabelCounter=1;
  TempVarCounter=1;
  VarCounter=1;
}

void insertCode(InterCode ir){
  if(IRlength>=IRCapacity){
    IRList=(InterCode*)realloc(IRList,sizeof(InterCode)*(IRCapacity+MAX_IR_SIZE));
    IRCapacity+=MAX_IR_SIZE;
  }
  //printf("%d",ir->kind);
  IRList[IRlength]=ir;
  IRlength++;
}

void genCode(char *filename,bool colored){
  //printf(GREEN"genCode in %s\n"NONE,filename);

  FILE *fp;
  if(strcmp(filename,"stdout")==0){
    fp=stdout;
  }else{
    fp=fopen(filename,"w");
  }
  if(!fp){
    PrintError("Error in genCode's fopen");
    return;
  }  
  for(int i=0;i<IRlength;i++){
    InterCode ir=IRList[i];
    if(ir==NULL)
      continue;
    if(colored){
      switch(ir->kind){
        case LABEL_CODE:
          fputs(GRAY"LABEL "NONE,fp);
          genCodeOp(ir->u.single.op,fp,colored);
          fputs(GRAY" : "NONE,fp);
          break;
        case FUNCTION_CODE:
          fputs(GRAY"FUNCTION "NONE,fp);
          genCodeOp(ir->u.single.op,fp,colored);
          fputs(GRAY" : "NONE,fp);
          break;
        case READ_CODE:
          fputs(GRAY"READ "NONE,fp);
          genCodeOp(ir->u.single.op,fp,colored); 
          break;
        case WRITE_CODE:
          fputs(GRAY"WRITE "NONE,fp);
          genCodeOp(ir->u.single.op,fp,colored);
          break;
        case ASSIGN_CODE:
     	  genCodeOp(ir->u.assignOp.left,fp,colored);
          fputs(GRAY" := "NONE,fp);
          genCodeOp(ir->u.assignOp.right,fp,colored);
	  break;
        case PLUS_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(GRAY" := "NONE, fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(GRAY" + "NONE, fp);
          genCodeOp(ir->u.tripleOp.op2,fp,colored);
          break;
        case MINUS_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(GRAY" := "NONE, fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(GRAY" - "NONE, fp);
	  genCodeOp(ir->u.tripleOp.op2,fp,colored);
	  break;
        case MUL_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(GRAY" := "NONE, fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(GRAY" * "NONE, fp);
	  genCodeOp(ir->u.tripleOp.op2, fp,colored);
	  break;
        case DIV_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(GRAY" := "NONE, fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(GRAY" / "NONE, fp);
	  genCodeOp(ir->u.tripleOp.op2,fp,colored);
	  break;
        case GOTO_CODE:
  	  fputs(GRAY"GOTO "NONE, fp);
	  genCodeOp(ir->u.single.op,fp,colored);
	  break;
        case IF_GOTO_CODE:
	  fputs(GRAY"IF "NONE, fp);
	  genCodeOp(ir->u.ifgotoOp.op1,fp,colored);
	  fputs(GRAY" "NONE, fp);
	  fputs(ir->u.ifgotoOp.relop,fp);
	  fputs(GRAY" "NONE, fp);
	  genCodeOp(ir->u.ifgotoOp.op2,fp,colored);
	  fputs(GRAY" GOTO "NONE, fp);
	  genCodeOp(ir->u.ifgotoOp.label,fp,colored);
          break;/*wokule*/
        case ARG_CODE:
  	  fputs(GRAY"ARG "NONE,fp);
	  genCodeOp(ir->u.single.op,fp,colored);
	  break;/*wokule*/
        case CALL_CODE:
          genCodeOp(ir->u.assignOp.left,fp,colored);
	  fputs(GRAY" := CALL "NONE,fp);
	  genCodeOp(ir->u.assignOp.right,fp,colored);
	  break;
        case PARAMETER_CODE:
          fputs(GRAY"PARAM "NONE,fp);
          genCodeOp(ir->u.single.op,fp,colored);
          break;
        case GET_ADDR_CODE:
          genCodeOp(ir->u.tripleOp.result,fp,colored);
          fputs(GRAY" := &"NONE,fp);
          genCodeOp(ir->u.tripleOp.op1,fp,colored);
          fputs(GRAY" + "NONE,fp);
          genCodeOp(ir->u.tripleOp.op2,fp,colored);/*wo ku le*/
          break;
	case GET_VALUE_CODE:
	  genCodeOp(ir->u.assignOp.left,fp,colored);
	  fputs(GRAY" := *"NONE,fp);
	  genCodeOp(ir->u.assignOp.right,fp,colored);
	  break;
        case DEC_CODE:
         fputs(GRAY"DEC "NONE,fp);
         genCodeOp(ir->u.decOp.op,fp,colored);
	 char str[32];
         sprintf(str,GRAY" %d "NONE,ir->u.decOp.size);
         fputs(str,fp);
         break;
        case RETURN_CODE:
          fputs(GRAY"RETURN "NONE,fp);
	  genCodeOp(ir->u.single.op,fp,colored);
	  break;
        default: PrintHint("Unrecognized Code-kind\n");
      }
      fputs("\n",fp);
    }else{
     switch(ir->kind){
        case LABEL_CODE:
          fputs("LABEL ",fp);
          genCodeOp(ir->u.single.op,fp,colored);
          fputs(" : ",fp);
          break;
        case FUNCTION_CODE:
          fputs("FUNCTION ",fp);
          genCodeOp(ir->u.single.op,fp,colored);
          fputs(" : ",fp);
          break;
        case READ_CODE:
          fputs("READ ",fp);
          genCodeOp(ir->u.single.op,fp,colored); 
          break;
        case WRITE_CODE:
          fputs("WRITE ",fp);
          genCodeOp(ir->u.single.op,fp,colored);
          break;
        case ASSIGN_CODE:
     	  genCodeOp(ir->u.assignOp.left,fp,colored);
          fputs(" := ",fp);
          genCodeOp(ir->u.assignOp.right,fp,colored);
	  break;
        case PLUS_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(" := ", fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(" + ", fp);
          genCodeOp(ir->u.tripleOp.op2,fp,colored);
          break;
        case MINUS_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(" := ", fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(" - ", fp);
	  genCodeOp(ir->u.tripleOp.op2,fp,colored);
	  break;
        case MUL_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(" := ", fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(" * ", fp);
	  genCodeOp(ir->u.tripleOp.op2, fp,colored);
	  break;
        case DIV_CODE:
	  genCodeOp(ir->u.tripleOp.result,fp,colored);
	  fputs(" := ", fp);
	  genCodeOp(ir->u.tripleOp.op1,fp,colored);
	  fputs(" / ", fp);
	  genCodeOp(ir->u.tripleOp.op2,fp,colored);
	  break;
        case GOTO_CODE:
  	  fputs("GOTO ", fp);
	  genCodeOp(ir->u.single.op,fp,colored);
	  break;
        case IF_GOTO_CODE:
	  fputs("IF ", fp);
	  genCodeOp(ir->u.ifgotoOp.op1,fp,colored);
	  fputs(" ", fp);
	  fputs(ir->u.ifgotoOp.relop,fp);
	  fputs(" ", fp);
	  genCodeOp(ir->u.ifgotoOp.op2,fp,colored);
	  fputs(" GOTO ", fp);
	  genCodeOp(ir->u.ifgotoOp.label,fp,colored);
          break;/*wokule*/
        case ARG_CODE:
  	  fputs("ARG ",fp);
	  genCodeOp(ir->u.single.op,fp,colored);
	  break;/*wokule*/
        case CALL_CODE:
          genCodeOp(ir->u.assignOp.left,fp,colored);
	  fputs(" := CALL ",fp);
	  genCodeOp(ir->u.assignOp.right,fp,colored);
	  break;
        case PARAMETER_CODE:
          fputs("PARAM ",fp);
          genCodeOp(ir->u.single.op,fp,colored);
          break;
        case GET_ADDR_CODE:
          genCodeOp(ir->u.tripleOp.result,fp,colored);
          fputs(" := &",fp);
          genCodeOp(ir->u.tripleOp.op1,fp,colored);
          fputs(" + ",fp);
          genCodeOp(ir->u.tripleOp.op2,fp,colored);
          break;
	case GET_VALUE_CODE:
	  genCodeOp(ir->u.assignOp.left,fp,colored);
	  fputs(" := *",fp);
	  genCodeOp(ir->u.assignOp.right,fp,colored);
	  break;
        case DEC_CODE:
          fputs("DEC ",fp);
          genCodeOp(ir->u.decOp.op,fp,colored);
          char str[32];
	  sprintf(str," %d ",ir->u.decOp.size);
          fputs(str,fp);
	  break;
        case RETURN_CODE:
          fputs("RETURN ",fp);
	  genCodeOp(ir->u.single.op,fp,colored);
	  break;
        default: PrintHint("Unrecognized Code-kind\n");
      }
      fputs("\n",fp);
    }
  }
  fclose(fp);
}

void genCodeOp(Operand Op,FILE *fp,bool colored){
  char buffer[32];
  memset(buffer,'\0',sizeof(buffer));
  if(colored){
    switch(Op->kind){
      case LABEL_OP:
        sprintf(buffer,GREEN"label%d"NONE,Op->u.label_no);
        fputs(buffer,fp);   
        break;
      case FUNCTION_OP:
        sprintf(buffer,GREEN"%s"NONE,Op->u.value);
        fputs(buffer,fp);
        break;
      case VARIABLE_OP:
        if(Op->u.value!=NULL){
	  sprintf(buffer,GREEN"%s"NONE,Op->u.value);
	  fputs(buffer,fp);
        }
        break;
      case TEMP_VAR_OP:
        sprintf(buffer,GREEN"t%d"NONE,Op->u.tvar_no);
        fputs(buffer,fp);
        break;
      case CONSTANT_OP:
        sprintf(buffer,GREEN"#%s"NONE,Op->u.value);
        fputs(buffer,fp);
        break;
      case ADDRESS_OP:
	sprintf(buffer,GREEN"*%s"NONE,Op->u.name->u.value);
	fputs(buffer,fp);
	break;
      case TEMP_ADDR_OP:
	sprintf(buffer,GREEN"*t%d"NONE,Op->u.name->u.tvar_no);
	fputs(buffer,fp);
	break;
      default:
        PrintHint("Undone\n");
    }
  }else{
    switch(Op->kind){
      case LABEL_OP:
        sprintf(buffer,"label%d",Op->u.label_no);
        fputs(buffer,fp);   
        break;
      case FUNCTION_OP:
        sprintf(buffer,"%s",Op->u.value);
        fputs(buffer,fp);
        break;
      case VARIABLE_OP:
        if(Op->u.value!=NULL){
	  sprintf(buffer,"%s",Op->u.value);
	  fputs(buffer,fp);
        }
        break;
      case TEMP_VAR_OP:
        sprintf(buffer,"t%d",Op->u.tvar_no);
        fputs(buffer,fp);
        break;
      case CONSTANT_OP:
        sprintf(buffer,"#%s",Op->u.value);
        fputs(buffer,fp);
        break;
      case ADDRESS_OP:
	sprintf(buffer,"*%s",Op->u.name->u.value);
        fputs(buffer,fp);
        break;
      case TEMP_ADDR_OP:
        sprintf(buffer,"*t%d",Op->u.name->u.tvar_no);
        fputs(buffer,fp);
	break;
      default:
        PrintHint("Undone\n");
    }
  }
}
