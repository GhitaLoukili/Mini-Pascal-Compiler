#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers\analyse_lexical.h"

char CUR_CHAR;
struct code CUR_SYMB;
FILE *file;
int NbrIDFS=0;

void Lread_car(){
    // Une fonction qui lit un caractère du fichier
	CUR_CHAR=fgetc(file);
}

char * trans(enum TOKENS token){
    // Une fonction qui retourne le nom du token
	switch(token){
		case PROGRAM_TOKEN:
			return "PROGRAM_TOKEN";
		case CONST_TOKEN:
			return "CONST_TOKEN";
		case VAR_TOKEN:
			return "VAR_TOKEN";
		case BEGIN_TOKEN:
			return "BEGIN_TOKEN";
		case END_TOKEN:
			return "END_TOKEN";
		case IF_TOKEN:
			return "IF_TOKEN";
		case THEN_TOKEN:
			return "THEN_TOKEN";
		case WHILE_TOKEN:
			return "WHILE_TOKEN";
		case DO_TOKEN:
			return "DO_TOKEN";
		case READ_TOKEN:
			return "READ_TOKEN";
		case WRITE_TOKEN:
			return "WRITE_TOKEN";
		case PV_TOKEN:
			return "PV_TOKEN";
		case PT_TOKEN:
			return "PT_TOKEN";
		case PLUS_TOKEN:
			return "PLUS_TOKEN";
		case MOINS_TOKEN:
			return "MOINS_TOKEN";
		case MULT_TOKEN:
			return "MULT_TOKEN";
		case DIV_TOKEN:
			return "DIV_TOKEN";
		case VIR_TOKEN:
			return "VIR_TOKEN";
		case AFF_TOKEN:
			return "AFF_TOKEN";
		case EG_TOKEN:
			return "EG_TOKEN";
		case INF_TOKEN:
			return "INF_TOKEN";
		case INFEG_TOKEN:
			return "INFEG_TOKEN";
		case SUP_TOKEN:
			return "SUP_TOKEN";
		case SUPEG_TOKEN:
			return "SUPEG_TOKEN";
		case DIFF_TOKEN:
			return "DIFF_TOKEN";
		case PO_TOKEN:
			return "PO_TOKEN";
		case PF_TOKEN:
			return "PF_TOKEN";
		case FIN_TOKEN:
			return "FIN_TOKEN";
		case ID_TOKEN:
			return "ID_TOKEN";
		case NUM_TOKEN:
			return "NUM_TOKEN";
		case ERREUR_TOKEN:
			return "ERREUR_TOKEN";
		case NULL_TOKEN:
			return "NULL_TOKEN";
		case GUIMO_TOKEN:
			return "GUIMO_TOKEN";
		case GUIMF_TOKEN:
			return "GUIMF_TOKEN";
		case EOF_TOKEN:
			return "EOF_TOKEN";
		default:
			return "UNKNOWN TOKEN";
	}
}

void Lskip_space() {
    // Une fonction qui saute les espaces, les tabulations et les retours à la ligne
    while (CUR_CHAR == ' ' || CUR_CHAR == '\n' || CUR_CHAR == '\t') {
        Lread_car();
    }
}

void Lread_number() {
    // Une fonction qui lit un nombre
    char number[11];
    int j = 0;
    number[j++] = CUR_CHAR;
    Lread_car();
    while (isdigit(CUR_CHAR) && j < 10) {
        number[j++] = CUR_CHAR;
        Lread_car();
        if (j == 10 && isdigit(CUR_CHAR)) {
            CUR_SYMB.token = ERREUR_TOKEN;
            strcpy(CUR_SYMB.nom, "ERR");
            while (isdigit(CUR_CHAR)) {
                Lread_car();
            }
            return;
        }
    }
    number[j] = '\0';
    CUR_SYMB.token = NUM_TOKEN;
    strcpy(CUR_SYMB.nom, number);
}

void Lread_word() {
    // Une fonction qui lit un mot
    char word[20];
    int j = 0;
    word[j++] = CUR_CHAR;
    Lread_car();
    while (isalnum(CUR_CHAR) ) {
        word[j++] = CUR_CHAR;
        Lread_car();
        if (j == 20 && isalnum(CUR_CHAR)) {
            CUR_SYMB.token = ERREUR_TOKEN;
            strcpy(CUR_SYMB.nom, "ERR");
            while (isalnum(CUR_CHAR)) {
                Lread_car();
            }
            return;
        }
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
    }
    strcpy(CUR_SYMB.nom, word);
}

void Lread_special() {
    // Une fonction qui lit un caractère spécial
    switch (CUR_CHAR) {
        case ';':
            CUR_SYMB.token = PV_TOKEN;
            strcpy(CUR_SYMB.nom, ";");
            Lread_car();
            break;
        case '.':
            CUR_SYMB.token = PT_TOKEN;
            strcpy(CUR_SYMB.nom, ".");
            Lread_car();
            break;
        case '+':
            CUR_SYMB.token = PLUS_TOKEN;
            strcpy(CUR_SYMB.nom, "+");
            Lread_car();
            break;
        case '-':
            CUR_SYMB.token = MOINS_TOKEN;
            strcpy(CUR_SYMB.nom, "-");
            Lread_car();
            break;
        case '*':
            CUR_SYMB.token = MULT_TOKEN;
            strcpy(CUR_SYMB.nom, "*");
            Lread_car();
            break;
        case '/':
            CUR_SYMB.token = DIV_TOKEN;
            strcpy(CUR_SYMB.nom, "/");
            Lread_car();
            break;
        case ',':
            CUR_SYMB.token = VIR_TOKEN;
            strcpy(CUR_SYMB.nom, ",");
            Lread_car();
            break;
        case ':':
            Lread_car();
            if (CUR_CHAR == '=') {
                CUR_SYMB.token = AFF_TOKEN;
                strcpy(CUR_SYMB.nom, ":=");
                Lread_car();
            } else {
                CUR_SYMB.token = ERREUR_TOKEN;
                strcpy(CUR_SYMB.nom, ":");
            }
            break;
        case '<':
            Lread_car();
            if (CUR_CHAR == '=') {
                CUR_SYMB.token = INFEG_TOKEN;
                strcpy(CUR_SYMB.nom, "<=");
                Lread_car();
            } else if (CUR_CHAR == '>') {
                CUR_SYMB.token = DIFF_TOKEN;
                strcpy(CUR_SYMB.nom, "<>");
                Lread_car();
            } else {
                CUR_SYMB.token = INF_TOKEN;
                strcpy(CUR_SYMB.nom, "<");
            }
            break;
        case '>':
            Lread_car();
            if (CUR_CHAR == '=') {
                CUR_SYMB.token = SUPEG_TOKEN;
                strcpy(CUR_SYMB.nom, ">=");
                Lread_car();
            } else {
                CUR_SYMB.token = SUP_TOKEN;
                strcpy(CUR_SYMB.nom, ">");
            }
            break;
        case '(':
            CUR_SYMB.token=PO_TOKEN;
            strcpy(CUR_SYMB.nom,"(");
            Lread_car();
            break;
        case ')':
            CUR_SYMB.token=PF_TOKEN;
            strcpy(CUR_SYMB.nom,")");
            Lread_car();
            break;
        case '=':
            CUR_SYMB.token=EG_TOKEN;
            strcpy(CUR_SYMB.nom,"=");
            Lread_car();
            break;
        //todo : correct this case
        case '{':
            Lread_car();
            if (CUR_CHAR == '*') {
                Lread_car();
                while (CUR_CHAR != EOF_TOKEN) {
                    if (CUR_CHAR == '*') {
                        Lread_car();
                        if (CUR_CHAR == '}') {
                            Lread_car();
                            return;
                        }
                    }
                    Lread_car();
                }
                if (CUR_CHAR == EOF_TOKEN) {
                    CUR_SYMB.token = EOF_TOKEN;
                }
            } else {
                CUR_SYMB.token = ERREUR_TOKEN;
                strcpy(CUR_SYMB.nom, "ERR");
                Lread_car();
            }

        case '}':
            CUR_SYMB.token=GUIMF_TOKEN;
            strcpy(CUR_SYMB.nom,"}");
            Lread_car();
            break;
        case EOF:
            CUR_SYMB.token=EOF_TOKEN;
            Lread_car();
            break;
        default :
            CUR_SYMB.token = ERREUR_TOKEN;
            strncat(CUR_SYMB.nom, &CUR_CHAR, 1);
            Lread_car();
    }
}

void Lanalyse() {
    Lskip_space();
    if (isalpha(CUR_CHAR)) {
        Lread_word();
    } else if (isdigit(CUR_CHAR)) {
        Lread_number();
    } else {
        Lread_special();
    }
}

void opn_file(char *filename){
	file=fopen(filename,"r");
	if (file == NULL) {
		printf("Failed to open file\n");
		return;
	}
	printf("\nFile opened successfully\n\n");
}

void lexical() {
    printf("\n********************************************* ANALYSE LEXICALE *********************************************\n\n");
    Lread_car();
	do {
		Lanalyse();
		printf("%s\n ",trans(CUR_SYMB.token));
	} while (CUR_CHAR!=EOF && CUR_CHAR!=FIN_TOKEN);

    printf("\n********************************************* FIN D'ANALYSE LEXICALE *********************************************\n\n");
}

// int main(int argc, char const *argv[])
// {
//     opn_file("C:/Users/HP/OneDrive/Documents/GitHub/Mini-Pascal-Compiler/test/test1.p");
//     lexical();
//     fclose(file);
//     return 0;
// }
