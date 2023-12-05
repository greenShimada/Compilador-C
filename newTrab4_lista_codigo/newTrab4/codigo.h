#include "mycomp.h"
#include "listacodigo.h"
char instrucao[50];

int temp=-1;
int newTemp() {
	return temp--;
}

int argNumber = 0;
int returnArgNumber(){
	if (argNumber < 3){
		return argNumber++;
	}
	
}

int label = 0;
int newLabel() {
	return label++;
}


char reg1[5];
char reg2[5];
char reg_temp[5];
void FuncCall(struct no *$$, int $1){
	create_cod(&$$->code); 
	$$->place = $1;
	sprintf(instrucao, "\tjal L%d\n", $$->place);
	insert_cod(&$$->code, instrucao);
}

void Funcao(struct no *Func, int $2, struct no $4, struct no $8){
	unsigned short int lblNumber;
	char label[10];
	lblNumber = newLabel();
	sprintf(label, "L%d:", $2);
	char nome[10];
	
	getName($2, nome);
	if (strcmp(nome,"$s0") == 0) {
		
		printf("\n%s\n%s\tli $v0, 10\n\tsyscall",
	label,
	$8.code);}
	else{
		char move[20];
		int arg = returnArgNumber();
		sprintf(move, "\tmove $a%d,$s%d", arg, $4.place + 1);
		printf("\n%s\n%s\n%s\n\tjr $ra",label, move,$8.code);
	}
}

void getName(int num, char *name) {
  if (num >= 0 ) {
    sprintf(name,"$s%d",num);
  }
  else 
    sprintf(name,"$t%d",-(num+1));
}

/* modificado */
void Atrib(struct no *Atrib, int $1, struct no $3) {
char name_dest[5];
char name_orig[5];
	getName($3.place,name_orig);
	getName($1,name_dest);
	sprintf(instrucao,"\tmove %s,%s\n",name_dest,name_orig);
	create_cod(&Atrib->code);
	insert_cod(&Atrib->code,$3.code);
	insert_cod(&Atrib->code,instrucao);
}

/* modificado */
void Li(struct no *Exp, int num) {
char name_dest[5];
	create_cod(&Exp->code);
	getName(Exp->place,name_dest);
	sprintf(instrucao,"\tli %s,%d\n",name_dest,num);
	insert_cod(&Exp->code,instrucao);
}

void ExpAri(char *operacao, struct no *Exp, struct no Exp1, struct no Exp2) {
char name_reg1[5];
char name_reg2[5];
char name_temp[5];
	Exp->place = newTemp();
	
	
	create_cod(&Exp->code);
	insert_cod(&Exp->code,Exp1.code);
	insert_cod(&Exp->code,Exp2.code);
	getName(Exp1.place,name_reg1);
	getName(Exp2.place,name_reg2);
	getName(Exp->place,name_temp);	
	sprintf(instrucao,"\t%s %s,%s,%s\n",operacao, name_temp,
	         name_reg1, name_reg2);
	insert_cod(&Exp->code,instrucao);	         
}

void ExpRel(char *branch, struct no *Exp, struct no Exp1, struct no Exp2) { 

char name_reg1[5];
char name_reg2[5];
char name_temp[5];
	Exp->place = newTemp();
	getName(Exp->place,name_temp);		
	create_cod(&Exp->code);
	insert_cod(&Exp->code,Exp1.code);
	insert_cod(&Exp->code,Exp2.code);

	getName(Exp1.place,name_reg1);
	getName(Exp2.place,name_reg2);
	getName(Exp->place,name_temp);
	sprintf(instrucao,"\tli %s,1\n",name_temp);
    insert_cod(&Exp->code,instrucao);	
	newLabel();
	sprintf(instrucao,"\t%s %s,%s,L%d\n",branch, name_reg1,name_reg2,label);
	insert_cod(&Exp->code,instrucao);
	sprintf(instrucao,"\tli %s,0\n",name_temp);
	insert_cod(&Exp->code,instrucao);
	sprintf(instrucao,"L%d:",label);
	insert_cod(&Exp->code,instrucao);
}

void Println(struct no *Print, struct no Exp) {
// falta adaptar a lista de codigos		
char name_reg[10];
	create_cod(&Print->code);
	getName(Exp.place,name_reg);
	
	sprintf(instrucao,"\tli $v0, 1\n");
	insert_cod(&Print->code,instrucao);
	
	sprintf(instrucao,"\tmove $a0,%s\n", name_reg);
	insert_cod(&Print->code,instrucao);

	sprintf(instrucao,"\tsyscall\n");
	insert_cod(&Print->code,instrucao);

	sprintf(instrucao,"\tli $v0,11\n"); 
	insert_cod(&Print->code,instrucao);

   	sprintf(instrucao,"\tli $a0,'\\n'\n"); 
	insert_cod(&Print->code,instrucao);

    sprintf(instrucao,"\tsyscall\n"); 
	insert_cod(&Print->code,instrucao);
}
void Print(struct no *Print, struct no Exp) {
// falta adaptar a lista de codigos		
char name_reg[10];
	create_cod(&Print->code);
	getName(Exp.place,name_reg);
	
	sprintf(instrucao,"\tli $v0, 1\n");
	insert_cod(&Print->code,instrucao);
	
	sprintf(instrucao,"\tmove $a0,%s\n", name_reg);
	insert_cod(&Print->code,instrucao);

	sprintf(instrucao,"\tsyscall\n");
	insert_cod(&Print->code,instrucao);
}
void Read(struct no *Read_cmd, int reg) {
// falta adaptar a lista de codigos		
char name_reg[10];
	create_cod(&Read_cmd->code);
	sprintf(instrucao,"\tli $v0, 5\n");
	insert_cod(&Read_cmd->code,instrucao);
	
	getName(reg,name_reg);
	sprintf(instrucao,"\tsyscall\n");
	insert_cod(&Read_cmd->code,instrucao);
	
	sprintf(instrucao,"\tmove %s,$v0\n", name_reg);
	insert_cod(&Read_cmd->code,instrucao);
	 
}

void If(struct no *If_cmd, struct no Exp, struct no Compound) 
{  
// adaptado a lista de codigos
char reg_temp[10];

  create_cod(&If_cmd->code);
  insert_cod(&If_cmd->code,Exp.code);
  
  
  getName(Exp.place,reg_temp);
  newLabel();  
 	
  sprintf(instrucao,"\tbeq %s,0,L%d\n", reg_temp,label); 
  insert_cod(&If_cmd->code,instrucao);	
  
  insert_cod(&If_cmd->code,Compound.code); 
  	
  sprintf(instrucao,"L%d:", label); 
  insert_cod(&If_cmd->code,instrucao);	
}

void IfElse(struct no *If_cmd, struct no Exp, struct no Compound1, struct no Compound2) 
{  
// adaptado a lista de codigos
char reg_temp[10];
int aux_label;

  create_cod(&If_cmd->code);
  insert_cod(&If_cmd->code,Exp.code);
  
  
  getName(Exp.place,reg_temp);
  newLabel();  
 	
  sprintf(instrucao,"\tbeq %s,0,L%d\n", reg_temp,label); 
  insert_cod(&If_cmd->code,instrucao);	
  
  insert_cod(&If_cmd->code,Compound1.code); 
  
  aux_label = label;
  newLabel();
  sprintf(instrucao,"\tj L%d\n", label);  	
  insert_cod(&If_cmd->code,instrucao);	

  sprintf(instrucao,"L%d:", aux_label); 
  insert_cod(&If_cmd->code,instrucao);
  	
  insert_cod(&If_cmd->code,Compound2.code); 

  sprintf(instrucao,"L%d:", label); 
  insert_cod(&If_cmd->code,instrucao);	
  
}

void While(struct no *While_cmd, struct no Exp, struct no Compound){
	char reg_temp[10];
	int aux_label;
	aux_label = newLabel();

	create_cod(&While_cmd->code);
	sprintf(instrucao, "WHILE%d:\n", aux_label);
	insert_cod(&While_cmd->code, instrucao);
	insert_cod(&While_cmd->code, Exp.code);
	getName(Exp.place, reg_temp);

	newLabel();
	sprintf(instrucao, "\tbeq %s, 0, END_WHILE%d\n", reg_temp, label);
	insert_cod(&While_cmd->code, instrucao);
	insert_cod(&While_cmd->code, Compound.code);
	sprintf(instrucao, "j WHILE%d\n", aux_label);
	insert_cod(&While_cmd->code, instrucao);
	sprintf(instrucao, "END_WHILE%d:\n", label);
	insert_cod(&While_cmd->code, instrucao);
	
}
void DoWhile(struct no *DoWhile_cmd, struct no Exp, struct no Compound){
	char reg_temp[10];
	int aux_label;
	newLabel();
	int auxLabel = label;

	create_cod(&DoWhile_cmd->code);
	sprintf(instrucao, "L%d:\n", aux_label);
	insert_cod(&DoWhile_cmd->code, instrucao);

	insert_cod(&DoWhile_cmd->code, Compound.code);
	insert_cod(&DoWhile_cmd->code, Exp.code);
	getName(Exp.place, reg_temp);

	newLabel();
	sprintf(instrucao, "\tbeq %s, 0, L%d\n", reg_temp, label);
	insert_cod(&DoWhile_cmd->code, instrucao);

	sprintf(instrucao, "j L%d\n", aux_label);
	insert_cod(&DoWhile_cmd->code, instrucao);
	sprintf(instrucao, "L%d:\n", label);
	insert_cod(&DoWhile_cmd->code, instrucao);
}