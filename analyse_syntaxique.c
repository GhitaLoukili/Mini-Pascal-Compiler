#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\analyse_lexical.h"
#include "headers\analyse_syntaxique.h"
#include "headers\analyse_semantique.h"

int i=0;
int Y =0;
struct T_TAB_IDF TAB_IDFS[100];

void read_car(){
	CUR_CHAR=fgetc(file);
}

void skip_space() {
    while (CUR_CHAR == ' ' || CUR_CHAR == '\n' || CUR_CHAR == '\t') {
        read_car();
    }
}

void read_number() {
    char number[11];
    int j = 0;
    number[j++] = CUR_CHAR;
    read_car();
    while (isdigit(CUR_CHAR)) {
        number[j++] = CUR_CHAR;
        read_car();
    }
    number[j] = '\0';
    CUR_SYMB.token = NUM_TOKEN;
    strcpy(CUR_SYMB.nom, number);
}

void read_word() {
    char word[20];
    int j = 0;
    word[j++] = CUR_CHAR;
    read_car();
    while (isalnum(CUR_CHAR) ) {
        word[j++] = CUR_CHAR;
        read_car();
    }
    word[j] = '\0';
    if (strcmp(word, "program") == 0) {
        CUR_SYMB.token = PROGRAM_TOKEN;
    } else if (strcmp(word, "const") == 0) {
        CUR_SYMB.token = CONST_TOKEN;
    } else if (strcmp(word, "var") == 0) {
        CUR_SYMB.token = VAR_TOKEN;
    } else if (strcmp(word, "Begin") == 0) {
        CUR_SYMB.token = BEGIN_TOKEN;
    } else if (strcmp(word, "end") == 0) {
        CUR_SYMB.token = END_TOKEN;
    } else if (strcmp(word, "if") == 0) {
        CUR_SYMB.token = IF_TOKEN;
    } else if (strcmp(word, "then") == 0) {
        CUR_SYMB.token = THEN_TOKEN;
    } else if (strcmp(word, "while") == 0) {
        CUR_SYMB.token = WHILE_TOKEN;
    } else if (strcmp(word, "do") == 0) {
        CUR_SYMB.token = DO_TOKEN;
    } else if (strcmp(word, "read") == 0) {
        CUR_SYMB.token = READ_TOKEN;
    } else if (strcmp(word, "write") == 0) {
        CUR_SYMB.token = WRITE_TOKEN;
    } else {
        CUR_SYMB.token = ID_TOKEN;
        strcpy(TAB_IDFS[NbrIDFS].nom,word);
    }
    strcpy(CUR_SYMB.nom, word);
}

void read_special() {
    switch (CUR_CHAR) {
        case ';':
            CUR_SYMB.token = PV_TOKEN;
            strcpy(CUR_SYMB.nom, ";");
            read_car();
            break;
        case '.':
            CUR_SYMB.token = PT_TOKEN;
            strcpy(CUR_SYMB.nom, ".");
            read_car();
            break;
        case '+':
            CUR_SYMB.token = PLUS_TOKEN;
            strncat(CUR_SYMB.nom, &CUR_CHAR, 1);
            read_car();
            break;
        case '-':
            CUR_SYMB.token = MOINS_TOKEN;
            strncat(CUR_SYMB.nom, &CUR_CHAR, 1);
            read_car();
            break;
        case '*':
            CUR_SYMB.token = MULT_TOKEN;
            strncat(CUR_SYMB.nom, &CUR_CHAR, 1);
            read_car();
            break;
        case '/':
            CUR_SYMB.token = DIV_TOKEN;
            strncat(CUR_SYMB.nom, &CUR_CHAR, 1);
            read_car();
            break;
        case ',':
            CUR_SYMB.token = VIR_TOKEN;
            strncat(CUR_SYMB.nom, &CUR_CHAR, 1);
            read_car();
            break;
        case ':':
            read_car();
            if (CUR_CHAR == '=') {
                CUR_SYMB.token = AFF_TOKEN;
                strcpy(CUR_SYMB.nom, ":=");
                read_car();
            } else {
                CUR_SYMB.token = ERREUR_TOKEN;
                strcpy(CUR_SYMB.nom, ":");
            }
            break;
        case '<':
            read_car();
            if (CUR_CHAR == '=') {
                CUR_SYMB.token = INFEG_TOKEN;
                strcpy(CUR_SYMB.nom, "<=");
                read_car();
            } else if (CUR_CHAR == '>') {
                CUR_SYMB.token = DIFF_TOKEN;
                strcpy(CUR_SYMB.nom, "<>");
                read_car();
            } else {
                CUR_SYMB.token = INF_TOKEN;
                strcpy(CUR_SYMB.nom, "<");
            }
            break;
        case '>':
            read_car();
            if (CUR_CHAR == '=') {
                CUR_SYMB.token = SUPEG_TOKEN;
                strcpy(CUR_SYMB.nom, ">=");
                read_car();
            } else {
                CUR_SYMB.token = SUP_TOKEN;
                strcpy(CUR_SYMB.nom, ">");
            }
            break;
        case '(':
            CUR_SYMB.token=PO_TOKEN;
            strcpy(CUR_SYMB.nom,"(");
            read_car();
            break;
        case ')':
            CUR_SYMB.token=PF_TOKEN;
            strcpy(CUR_SYMB.nom,")");
            read_car();
            break;
        case '=':
            CUR_SYMB.token=EG_TOKEN;
            strcpy(CUR_SYMB.nom,"=");
            read_car();
            break;
        //todo : correct this case
        case '{':
            read_car();
            if (CUR_CHAR == '*') {
                read_car();
                while (CUR_CHAR != EOF_TOKEN) {
                    if (CUR_CHAR == '*') {
                        read_car();
                        if (CUR_CHAR == '}') {
                            read_car();
                            return;
                        }
                    }
                    read_car();
                }
                if (CUR_CHAR == EOF_TOKEN) {
                    CUR_SYMB.token = EOF_TOKEN;
                }
            } else {
                CUR_SYMB.token = ERREUR_TOKEN;
                strcpy(CUR_SYMB.nom, "ERREUR");
                strncat(CUR_SYMB.nom, &CUR_CHAR, 1);
                read_car();
            }

        case '}':
            CUR_SYMB.token=GUIMF_TOKEN;
            strcpy(CUR_SYMB.nom,"}");
            read_car();
            break;
        case EOF:
            // CUR_SYMB.token=FIN_TOKEN;
            CUR_SYMB.token=EOF_TOKEN;
            read_car();
            break;
        default :
            CUR_SYMB.token = ERREUR_TOKEN;
            strcpy(CUR_SYMB.nom, &CUR_CHAR);
            read_car();
    }
}

void analyse() {
    skip_space();
    if (isalpha(CUR_CHAR)) {
        read_word();
    } else if (isdigit(CUR_CHAR)) {
        read_number();
    } else {
        read_special();
    }
}

void Erreur(enum ERREURS erreur){
    printf("Erreur de compilation :\n");
	switch(erreur){
        case 0:
            printf("\nERREUR----->PROGRAM\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 1:
            printf("\nERREUR----->CONST_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 2:
            printf("\nERREUR----->VAR_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 3:
            printf("\nERREUR----->BEGIN_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 4:
            printf("\nERREUR----->END_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 5:
            printf("\nERREUR----->IF_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 6:
            printf("\nERREUR----->THEN_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 7:
            printf("\nERREUR----->WHILE_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 8:
            printf("\nERREUR----->DO_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 9:
            printf("\nERREUR----->READ_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 10:
            printf("\nERREUR----->WRITE_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 11:
            printf("\nERREUR----->PV_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break; 
        case 12:
            printf("\nERREUR----->PT_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 13:
            printf("\nERREUR----->PLUS_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 14:
            printf("\nERREUR----->MOINS_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 15:
            printf("\nERREUR----->MULT_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 16:
            printf("\nERREUR----->DIV_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 17:
            printf("\nERREUR----->VIR_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 18:
            printf("\nERREUR----->AFF_ERREUR\n,");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 19:
            printf("\nERREUR----->PO_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 20:
            printf("\nERREUR----->PF_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 21:
            printf("\nERREUR----->ID_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 22:
            printf("\nERREUR----->NUM_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 23:
            printf("\nERREUR----->CONST_VAR_BEGIN_ERR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 24:
            printf("\nERREUR----->INST_ERR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 25:
            printf("\nERREUR----->COND_ERR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
        case 26:
            printf("\nERREUR----->EG_ERREUR\n");
            printf("Current Token: %d\n", CUR_SYMB.token);
            printf("Current Lexeme: %s\n", CUR_SYMB.nom);
            break;
    }
}

void Test_Symbole(enum TOKENS stoken,enum ERREURS erreur) {
  if((CUR_SYMB.token==stoken)) {
    analyse();
  }
  else {
    Erreur(erreur);
  }
}

void PROGRAM() {
    Test_Symbole(PROGRAM_TOKEN,PROGRAM_ERREUR);
    Test_Symbole(ID_TOKEN,ID_ERREUR);
    Test_Symbole(PV_TOKEN,PV_ERREUR);
    BLOCK();
    if (CUR_SYMB.token == PT_TOKEN) {
        printf("\nProgram execution completed.\nBRAVO: le programme est correcte!!!\n");
    } else {
        Erreur(PT_ERREUR);
        printf("\nPAS BRAVO: fin de programme incorrecte!!!!\n");
        printf("Current Token: %d\n", CUR_SYMB.token);
        printf("Current Lexeme: %s\n", CUR_SYMB.nom);
        printf("\nCompiler is shutting down...\n");
        exit(EXIT_FAILURE);
    }
}

void BLOCK() {
  CONSTS();
  VARS();
  INSTS();
}

void CONSTS() {
    switch (CUR_SYMB.token) {
        case CONST_TOKEN:
            analyse();
            Test_Symbole(ID_TOKEN,ID_ERREUR);
            Test_Symbole(EG_TOKEN,EG_ERREUR);
            Test_Symbole(NUM_TOKEN,NUM_ERREUR);
            Test_Symbole(PV_TOKEN,PV_ERREUR);
            while (CUR_SYMB.token == ID_TOKEN) {
                Test_Symbole(ID_TOKEN,ID_ERREUR);
                Test_Symbole(EG_TOKEN,EG_ERREUR);
                Test_Symbole(NUM_TOKEN,NUM_ERREUR);
                Test_Symbole(PV_TOKEN,PV_ERREUR);
            };
            if (CUR_SYMB.token == CONST_TOKEN) {
                CONSTS();
            } else {
                VARS();
            }
            break;
        case VAR_TOKEN:
            break;
        case BEGIN_TOKEN:
            break;
        default:
            Erreur(CONST_VAR_BEGIN_ERR);
            break;
    }
}

void VARS() {
    switch (CUR_SYMB.token) {
        case VAR_TOKEN:
            analyse();
            Test_Symbole(ID_TOKEN,ID_ERREUR);
            while (CUR_SYMB.token == VIR_TOKEN) {
                analyse();
                Test_Symbole(ID_TOKEN, ID_ERREUR);
            }
            Test_Symbole(PV_TOKEN, PV_ERREUR);
            // if (CUR_SYMB.token == PV_TOKEN) {
            //     analyse();
            //     if (CUR_SYMB.token == ID_TOKEN) {
            //         analyse();
            //         Test_Symbole(PV_TOKEN, PV_ERREUR);
            //     } else {
            //         break;
            //     }
            // }
            if (CUR_SYMB.token == VAR_TOKEN) {
                VARS();
            }
            if (CUR_SYMB.token == CONST_TOKEN) {
                CONSTS();
            }
            break;
        case BEGIN_TOKEN:
            break;
        default:
            break;
    }
}

void INSTS() {
  Test_Symbole(BEGIN_TOKEN,BEGIN_ERREUR);
  INST();
  while(CUR_SYMB.token == PV_TOKEN ) {
    analyse();
    INST();
  }
  Test_Symbole(END_TOKEN,END_ERREUR);
}

void INST() {
    //INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (CUR_SYMB.token) {
        case BEGIN_TOKEN:
            INSTS();
            break;
        case ID_TOKEN:
            AFFEC();
            break;
        case IF_TOKEN:
            SI();
            break;
        case WHILE_TOKEN:
            TANTQUE();
            break;
        case WRITE_TOKEN:
            ECRIRE();
            break;
        case READ_TOKEN:
            LIRE();
            break;
        case END_TOKEN:
            break;
        default:
            Erreur(INST_ERR);
            break;
    }
}

void AFFEC() {
    Test_Symbole(ID_TOKEN,ID_ERREUR);
    Test_Symbole(AFF_TOKEN,AFF_ERREUR);
    EXPR();
}

void EXPR() {
  TERM();
  while(CUR_SYMB.token == PLUS_TOKEN || CUR_SYMB.token == MOINS_TOKEN) {
    switch (CUR_SYMB.token) {
        case PLUS_TOKEN:
            Test_Symbole(PLUS_TOKEN, PLUS_ERREUR);
            break;
        case MOINS_TOKEN:
            Test_Symbole(MOINS_TOKEN, MOINS_ERREUR);
            break;
        default:
            break;
    }
    TERM();
  }
}

void TERM() {
  FACT();
  while(CUR_SYMB.token== MULT_TOKEN || CUR_SYMB.token == DIV_TOKEN) {
    switch (CUR_SYMB.token) {
        case MULT_TOKEN:
            Test_Symbole(MULT_TOKEN, MULT_ERREUR);
            break;
        case DIV_TOKEN:
            Test_Symbole(DIV_TOKEN, DIV_ERREUR);
            break;
        default:
            break;
    }
    FACT();
  }
}

void FACT() {
    switch (CUR_SYMB.token) {
        case ID_TOKEN:
            Test_Symbole(ID_TOKEN, ID_ERREUR);
            break;
        case NUM_TOKEN:
            Test_Symbole(NUM_TOKEN, NUM_ERREUR);
            break;
        case PO_TOKEN:
            Test_Symbole(PO_TOKEN, PO_ERREUR);
            EXPR();
            Test_Symbole(PF_TOKEN, PF_ERREUR);
            break;
        default:
            break;
    }
}

void SI() {
  Test_Symbole(IF_TOKEN,IF_ERREUR);
  COND();
  Test_Symbole(THEN_TOKEN,THEN_ERREUR);
  INST();
}

void COND() {
  EXPR();
  switch(CUR_SYMB.token) {
    case EG_TOKEN:
        analyse();
        EXPR();
        analyse();
        ;
        break;
    case DIFF_TOKEN:
        analyse();
        EXPR();
        analyse();
        ;
        break;
    case INF_TOKEN:
        EXPR();
        analyse();
        ;
        break;
    case SUP_TOKEN:
        EXPR();
        analyse();
        ;
        break;
    case INFEG_TOKEN:
        analyse();
        EXPR();
        analyse();
        ;
        break;
    case SUPEG_TOKEN:
        analyse();
        EXPR();
        analyse();
        ;
        break;
    default:
        Erreur(COND_ERR);
        ;
        break ;
  }
  EXPR();
}

void TANTQUE() {
  Test_Symbole(WHILE_TOKEN,WHILE_ERREUR);
  COND();
  Test_Symbole(DO_TOKEN,DO_ERREUR);
  if(CUR_SYMB.token==BEGIN_TOKEN){
    INSTS();
  } else {
    INST();
  }
}
 
void ECRIRE() {
  Test_Symbole(WRITE_TOKEN,WRITE_ERREUR);
  Test_Symbole(PO_TOKEN,PO_ERREUR);
  EXPR();
  while(CUR_SYMB.token == VIR_TOKEN) {
    analyse();
    EXPR();
  }
  Test_Symbole(PF_TOKEN,PF_ERREUR);
}

void LIRE() {
  Test_Symbole(READ_TOKEN,READ_ERREUR);
  Test_Symbole(PO_TOKEN,PO_ERREUR);
  Test_Symbole(ID_TOKEN,ID_ERREUR);
  while(CUR_SYMB.token== VIR_TOKEN) {
    analyse();
    Test_Symbole(ID_TOKEN,ID_ERREUR);
  }
  Test_Symbole(PF_TOKEN,PF_ERREUR);
}

void syntaxique() {
    fseek(file, 0, SEEK_SET);
    printf("\n********************************************* ANALYSE SYNTAXIQUE *********************************************\n\n");
    read_car();
    analyse();
    PROGRAM();
    printf("\n********************************************* FIN D'ANALYSE SYNTAXIQUE *********************************************\n\n ");
}

void table_id(){
	switch(CUR_SYMB.token){
		case PROGRAM_TOKEN :
			analyse();
			store_prog();
			break;
		case CONST_TOKEN :
			analyse();
			store_const();
			break;
		case VAR_TOKEN :
			analyse();
			store_var();
			break ;
		default :
			;
			break;
    }
}

void store_prog(){
	while((CUR_SYMB.token!=CONST_TOKEN)&&(CUR_SYMB.token!=VAR_TOKEN)&&(CUR_SYMB.token!=BEGIN_TOKEN)){
		if(CUR_SYMB.token==ID_TOKEN){
			strcpy(TAB_IDFS[i].nom,CUR_SYMB.nom);
			TAB_IDFS[i].TIDF=TPROG;
			i++;
            NbrIDFS++;
		}
		analyse();
	}
	table_id();
}

void store_const(){
	while((CUR_SYMB.token!=PROGRAM_TOKEN)&&(CUR_SYMB.token!=VAR_TOKEN)&&(CUR_SYMB.token!=BEGIN_TOKEN)){
		if(CUR_SYMB.token==ID_TOKEN){
			strcpy(TAB_IDFS[i].nom,CUR_SYMB.nom);
			TAB_IDFS[i].TIDF=TCONST;
			analyse();
			if(CUR_SYMB.token==EG_TOKEN){
				analyse();
                CUR_SYMB.val=atoi(CUR_SYMB.nom);
				TAB_IDFS[i].value=CUR_SYMB.val;
			}
			i++;
            NbrIDFS++;
		}
		analyse();
	}
	table_id();
}

void store_var(){
	while((CUR_SYMB.token!=CONST_TOKEN)&&(CUR_SYMB.token!=PROGRAM_TOKEN)&&(CUR_SYMB.token!=BEGIN_TOKEN)){
		if(CUR_SYMB.token==ID_TOKEN){
            regle2();
			strcpy(TAB_IDFS[i].nom,CUR_SYMB.nom);
			TAB_IDFS[i].TIDF=TVAR;
            i++;
            NbrIDFS++;
		}
		analyse();
	}
	table_id();
}

void affich(){
	regle1();
	regle3();
	regle4();
	regle5();
	if(Y==0){
		printf("\n********************************************* Compilation Semantique Correcte *********************************************\n\n");
	}
	else{
        printf("\n********************************************* Compilation Semantique Incorrecte *********************************************\n\n");
        printf("\nCompiler is shutting down...\n");
        exit(EXIT_FAILURE);
    }
}

void regle1(){
	while(CUR_SYMB.token!=END_TOKEN){
		if(CUR_SYMB.token==ID_TOKEN){
			check();
		}
		analyse();
	}
}

void check(){
	int r=0; 
	for (int j = 0; j <NbrIDFS ; ++j) {
		if(strcmp(CUR_SYMB.nom,TAB_IDFS[j].nom)==0){
			r=1;
		}
	}
	if(r==0){
		printf("%s ---->Erreur: Declaration hors CONST and VAR\n",CUR_SYMB.nom);
		Y=1;
	}
}

void regle2(){
	int r=0;
	for (int j = 0; j <NbrIDFS ; ++j) {
		if(strcmp(CUR_SYMB.nom,TAB_IDFS[j].nom)==0){
			r=1;
		}
	}
	if(r==1){
		printf("%s------>Erreur: Variable deja declare\n",CUR_SYMB.nom);
		Y=1;
	}
}

void regle3(){
    fseek(file, 0, SEEK_SET);
	while(CUR_SYMB.token!=BEGIN_TOKEN) analyse();
	while(CUR_SYMB.token!=PT_TOKEN){
		if(CUR_SYMB.token==ID_TOKEN){
			int r=0; 
			for (int j = 0; j <NbrIDFS ; ++j) {
				if(strcmp(CUR_SYMB.nom,TAB_IDFS[j].nom)==0) {
					r=1;
				}
			}
			if(r==0){
				printf("%s ---->Erreur: Variable non declare \n",CUR_SYMB.nom);
				Y=1;
			}
		}
		analyse();
	}
}

void regle4(){
    fseek(file, 0, SEEK_SET);
    read_car();
	while(CUR_SYMB.token!=BEGIN_TOKEN) {
        analyse();
    }
	while(CUR_SYMB.token!=PT_TOKEN){
		if(CUR_SYMB.token==ID_TOKEN){
			for (int j = 0; j <NbrIDFS ; ++j) {
                if(strcmp(TAB_IDFS[j].nom,CUR_SYMB.nom)==0){
					analyse();
					if(CUR_SYMB.token==AFF_TOKEN){
						analyse();
                        int temp=atoi(CUR_SYMB.nom);
						if(temp!=TAB_IDFS[j].value){
							printf("%s------>Erreur : Une constante ne peut changer de valeur dans le programme\n",TAB_IDFS[j].nom);
							Y=1;
						}
					}
				}
			}
		}
		if(CUR_SYMB.token==READ_TOKEN){
			analyse();
			analyse();
			if(CUR_SYMB.token==ID_TOKEN){
				for (int j = 0; j <NbrIDFS ; ++j) {
					if(strcmp(CUR_SYMB.nom,TAB_IDFS[j].nom)==0){
						if(TAB_IDFS[j].TIDF==1) {
							printf("%s ---------->Erreur: Une constante	ne peut changer de valeur a partir de READ\n",CUR_SYMB.nom);
							Y=1;
						}
					}
				}
			}
		}
		analyse();
	}
}

void regle5(){
    fseek(file, 0, SEEK_SET);
    read_car();
	while(CUR_SYMB.token!=BEGIN_TOKEN) analyse();
	while(CUR_SYMB.token!=PT_TOKEN){
		if(CUR_SYMB.token==ID_TOKEN){
			for (int j = 0; j <NbrIDFS ; ++j) {
				if(strcmp(CUR_SYMB.nom,TAB_IDFS[j].nom)==0){
					if(TAB_IDFS[j].TIDF==0) {
						printf("%s ---------->Erreur: ID du programme non autorise\n",CUR_SYMB.nom);
						Y=1;
					}
				}
			}
		}
		analyse();
	}
}

void semantique() {
    fseek(file, 0, SEEK_SET);
    printf("\n********************************************* ANALYSE SEMANTIQUE *********************************************\n\n");
    read_car();
    analyse();
    table_id();
	affich();
    printf("\n********************************************* FIN D'ANALYSE SEMANTIQUE *********************************************\n\n");
    printf("\nCompiler is shutting down...\n");
}