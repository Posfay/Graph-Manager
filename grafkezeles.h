#ifndef GRAF_GRAFKEZELES_H
#define GRAF_GRAFKEZELES_H

#include "listak.h"

typedef struct Graf {
    CsucsLista *csucsok;
    int csucsok_szama;
    int elek_szama;
} Graf;

void csucs_hozzaad(Graf *g, int id);
void csucs_torol(Graf *g, int id);
void el_torol(Graf *g, int c1, int c2);
void el_modosit(Graf *g, int c1, int c2, int s);
void el_letrehoz(Graf *g, int c1, int c2, int s);
Graf *letrehoz_ures_graf();
void felszabadit_graf(Graf *g);

bool melysegi_bejaras(Graf *g, int k, char *fajlnev);
bool szelessegi_bejaras(Graf *g, int k, char *fajlnev);
bool dijkstra_legrovidebb_ut(Graf *g, int a, int b, char *fajlnev);

#endif //GRAF_GRAFKEZELES_H
