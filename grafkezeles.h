#ifndef GRAF_GRAFKEZELES_H
#define GRAF_GRAFKEZELES_H

#include "listak.h"

void csucs_hozzaad(Graf *g, int id);
void csucs_torol(Graf *g, int id);
void el_torol(Graf *g, int c1, int c2);
void el_modosit(Graf *g, int c1, int c2, int s);
void el_letrehoz(Graf *g, int c1, int c2, int s);
Graf *letrehoz_graf();
void felszabadit_graf(Graf *g);

void melysegi_bejaras(Graf *g, int k);

#endif //GRAF_GRAFKEZELES_H
