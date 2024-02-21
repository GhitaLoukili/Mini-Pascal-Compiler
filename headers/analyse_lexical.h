#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern FILE * file;
extern char CUR_CHAR;
extern int NbrIDFS;

enum TOKENS{
  PROGRAM_TOKEN,
  CONST_TOKEN,
  VAR_TOKEN,
  BEGIN_TOKEN,
  END_TOKEN,
  IF_TOKEN,
  THEN_TOKEN,
  WHILE_TOKEN,
  DO_TOKEN,
  READ_TOKEN,
  WRITE_TOKEN,
  PV_TOKEN,     //;
  PT_TOKEN,     //,
  PLUS_TOKEN,
  MOINS_TOKEN,
  MULT_TOKEN,
  DIV_TOKEN,
  VIR_TOKEN,    //,
  AFF_TOKEN,
  EG_TOKEN,     //=
  INF_TOKEN,
  INFEG_TOKEN,
  SUP_TOKEN,
  SUPEG_TOKEN,
  DIFF_TOKEN,
  PO_TOKEN,
  PF_TOKEN,
  FIN_TOKEN,
  ID_TOKEN,
  NUM_TOKEN,
  ERREUR_TOKEN,
  NULL_TOKEN,
  GUIMO_TOKEN,    //"
  GUIMF_TOKEN,    //"
  EOF_TOKEN
};

struct code{
  enum TOKENS token ;
  char nom[20];
  int val;
}; 

extern struct code CUR_SYMB;

extern void opn_file(char *filename);
void Lread_car();
void Lskip_space();
void Lread_word();
void Lread_number();
void Lread_special();
void Lanalyse();
void lexical();

char * trans(enum TOKENS token);