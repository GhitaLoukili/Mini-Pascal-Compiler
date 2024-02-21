#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ANALYSE_SEMANTIQUE_H
#define ANALYSE_SEMANTIQUE_H

extern enum TSYM{
    TPROG,
    TCONST,
    TVAR
} TSYM;

struct T_TAB_IDF {
    char nom[20];
    enum TSYM TIDF;
    int value;
};

extern void table_id();
void store_prog();
void store_const();
void store_var();
extern void affich();
void regle1();
void check();
void regle2();
void regle3();
void regle4();
void regle5();
void semantique();

#endif