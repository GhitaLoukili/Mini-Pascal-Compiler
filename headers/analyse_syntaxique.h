#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ANALYSE_SYNTAXIQUE_H
#define ANALYSE_SYNTAXIQUE_H

enum ERREURS{
  PROGRAM_ERREUR,CONST_ERREUR,VAR_ERREUR,BEGIN_ERREUR,END_ERREUR,IF_ERREUR,THEN_ERREUR,WHILE_ERREUR,
  DO_ERREUR,READ_ERREUR,WRITE_ERREUR,PV_ERREUR,PT_ERREUR,PLUS_ERREUR,MOINS_ERREUR,MULT_ERREUR,
  DIV_ERREUR,VIR_ERREUR,AFF_ERREUR,
  PO_ERREUR,PF_ERREUR,ID_ERREUR,NUM_ERREUR,CONST_VAR_BEGIN_ERR,INST_ERR,COND_ERR,EG_ERREUR
};

void Test_Symbole(enum TOKENS stoken,enum ERREURS erreur);
void PROGRAM();
void BLOCK();
void CONSTS() ;
void VARS();
void INSTS();
void INST();
void AFFEC();
void EXPR();
void TERM();
void FACT();
void SI();
void COND();
void TANTQUE();
void LIRE();
void ECRIRE();

void read_car();
void skip_space();
void read_word();
void read_number();
void read_special();
void analyse();
void syntaxique();

#endif