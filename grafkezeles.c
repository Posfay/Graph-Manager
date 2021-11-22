#include <stdlib.h>

#include "grafkezeles.h"
#include "listak.h"

#include "debugmalloc.h"

void csucs_hozzaad(Graf *g, int id) {
    Csucs *c = malloc(sizeof(Csucs));
    c->id = id;
    c->szomszedok = NULL;
    g->csucsok = beszur_csucs_lista(g->csucsok, c);
    g->csucsok_szama += 1;
}

void csucs_torol(Graf *g, int id) {
    Csucs *c = keres_csucs_lista(g->csucsok, id)->csucs;
    for (SzomszedsagiListaElem *e = c->szomszedok->elso->kov; e != c->szomszedok->utolso; e = e->kov) {
        Csucs *szomszed = keres_csucs_lista(g->csucsok, e->csucs);
        torol_szomszedsagi_lista(szomszed->szomszedok, id);
        g->elek_szama -= 1;
    }
    torol_csucs_lista(g->csucsok, id);
    g->csucsok_szama -= 1;
}

void el_torol(Graf *g, int c1, int c2) {
    Csucs *csucs1 = keres_csucs_lista(g->csucsok, c1)->csucs;
    Csucs *csucs2 = keres_csucs_lista(g->csucsok, c2)->csucs;
    torol_szomszedsagi_lista(csucs1->szomszedok, c2);
    torol_szomszedsagi_lista(csucs2->szomszedok, c1);
    g->elek_szama -= 1;
}

void el_modosit(Graf *g, int c1, int c2, int s) {
    Csucs *csucs1 = keres_csucs_lista(g->csucsok, c1)->csucs;
    Csucs *csucs2 = keres_csucs_lista(g->csucsok, c2)->csucs;
    SzomszedsagiListaElem *e1 = keres_szomszedsagi_lista(csucs2->szomszedok, c1);
    SzomszedsagiListaElem *e2 = keres_szomszedsagi_lista(csucs1->szomszedok, c2);
    e1->suly = s;
    e2->suly = s;
}

void el_letrehoz(Graf *g, int c1, int c2, int s) {
    Csucs *csucs1 = keres_csucs_lista(g->csucsok, c1)->csucs;
    Csucs *csucs2 = keres_csucs_lista(g->csucsok, c2)->csucs;
    csucs1->szomszedok = beszur_szomszedsagi_lista(csucs1->szomszedok, c2, s);
    csucs2->szomszedok = beszur_szomszedsagi_lista(csucs2->szomszedok, c1, s);
    g->elek_szama += 1;
}

Graf *letrehoz_graf() {
    Graf *g = malloc(sizeof(Graf));
    g->csucsok_szama = 0;
    g->elek_szama = 0;
    g->csucsok = NULL;
    return g;
}

void felszabadit_graf(Graf *g) {
    if (g == NULL) {
        return;
    }
    felszabadit_csucs_lista(g->csucsok);
    free(g);
}

static void megjelol_elem_volt(int *volt, int hossz, int e) {
    for (int i = 0; i < hossz; i++) {
        if (volt[2 * i] == e) {
            volt[2 * i + 1] = 1;
            return;
        }
    }
}

static bool elem_volt(int *volt, int hossz, int e) {
    for (int i = 0; i < hossz; i++) {
        if (volt[2 * i] == e) {
            return volt[2 * i + 1] == 1;
        }
    }
    return false;
}

static void melysegi_rekurziv(Graf *g, int k, int *volt) {
    printf("%d ", k);
    megjelol_elem_volt(volt, g->csucsok_szama, k);
    Csucs *c = keres_csucs_lista(g->csucsok, k)->csucs;
    for (SzomszedsagiListaElem *sze = c->szomszedok->elso->kov; sze != c->szomszedok->utolso; sze = sze->kov) {
        if (!elem_volt(volt, g->csucsok_szama, sze->csucs)) {
            melysegi_rekurziv(g, sze->csucs, volt);
        }
    }
}

void melysegi_bejaras(Graf *g, int k) {
    int *volt = malloc(g->csucsok_szama * 2 * sizeof(int));
    CsucsListaElem *cse = g->csucsok->elso->kov;
    for (int i = 0; i < g->csucsok_szama; i++) {
        volt[2 * i] = cse->csucs->id;
        volt[2 * i + 1] = 0;
        cse = cse->kov;
    }
    melysegi_rekurziv(g, k, volt);
    printf("\n");
    free(volt);
}
