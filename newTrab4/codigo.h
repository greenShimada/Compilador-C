#include "mycomp.h"
#include "listacodigo.h"
char instrucao[30];

int temp=-1;
int newTemp() {
	return temp--;
}

int Label = 0;
int newLabel() {
	return Label++;
}

char reg1[5];
char reg2[5];
char reg_temp[5];
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

/*void La(struct no *Exp, struct no $2, int reg1){
char name_dest[5];
char name_orig[5];
	getName($2.place,name_dest);
	getName($3.place,name_orig);

	sprintf(instrucao,"\tmove %s,%s\n",name_dest,name_orig);
	create_cod(&Atrib->code);
	insert_cod(&Atrib->code,$3.code);
	insert_cod(&Atrib->code,instrucao);


}*/
/* modificado */
void Li(struct no *Exp, int num) {
char name_dest[5];
	create_cod(&Exp->code);
	getName(Exp->place,name_dest);
	sprintf(instrucao,"\tli %s,%d\n",name_dest,num);
	insert_cod(&Exp->code,instrucao);
}

void ExpAri(char *operacao, int temp, int reg1, int reg2) {
char name_reg1[5];
char name_reg2[5];
char name_temp[5];
	getName(reg1,name_reg1);
	getName(reg2,name_reg2);
	getName(temp,name_temp);	
	printf("\t%s %s,%s,%s\n",operacao, name_temp,
	         name_reg1, name_reg2);
}

void ExpRel(char *branch, int temp, int reg1, int reg2) {
char name_reg1[5];
char name_reg2[5];
char name_temp[5];
	getName(reg1,name_reg1);
	getName(reg2,name_reg2);
	getName(temp,name_temp);
	printf("\tli %s,1\n",name_temp);
	newLabel();
	printf("\t%s %s,%s,L%d\n",branch, name_reg1, 
	name_reg2,Label);
	printf("\tli %s,0\n",name_temp);
	printf("L%d:",Label);
}

void Println(struct no *reg) {
char name_reg[10];
	printf("\tli $v0, 1\n");
	getName(reg->place,name_reg);
	printf("\tmove $a0,%s\n", name_reg);
	printf("\tsyscall\n");
	printf("\tli $v0,11\n"); 
   	printf("\tli $a0,'\\n'\n"); 
    printf("\tsyscall\n"); 
}
void Print(struct no *reg) {
char name_reg[10];
	printf("\tli $v0, 1\n");
	getName(reg->place,name_reg);
	printf("\tmove $a0,%s\n", name_reg);
	printf("\tsyscall\n"); 
}
void Read(int reg) {
char name_reg[10];
	printf("\tli $v0, 5\n");
	getName(reg,name_reg);
	printf("\tsyscall\n");
	printf("\tmove %s,$v0\n", name_reg);
	 
}

