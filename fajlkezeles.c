#include <stdio.h>
#include <stdlib.h>

#include "fajlkezeles.h"

#include "debugmalloc.h"

Graf *betolt_graf(Graf *g, char* fajlnev) {
    // kitakaritja az elozoleg betoltott grafot a memoriabol
    felszabadit_graf(g);
    g = letrehoz_ures_graf();

    FILE *fp = fopen(fajlnev, "rt");
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        return NULL;
    }

    int csucsok, elek;
    fscanf(fp, "%d %d", &csucsok, &elek);
    for (int i = 0; i < elek; i++) {
        int c1, c2, s;
        fscanf(fp, "%d %d %d", &c1, &c2, &s);
        CsucsListaElem *ce1 = keres_csucs_lista(g->csucsok, c1);
        CsucsListaElem *ce2 = keres_csucs_lista(g->csucsok, c2);

        if (ce1 == NULL) {
            csucs_hozzaad(g, c1);
        }
        if (ce2 == NULL) {
            csucs_hozzaad(g, c2);
        }
        el_letrehoz(g, c1, c2, s);
    }

    fclose(fp);
    return g;
}

bool ment_graf(Graf *g, char* fajlnev) {
    FILE *fp = fopen(fajlnev, "wt");
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        return false;
    }

    fprintf(fp, "%d %d\n", g->csucsok_szama, g->elek_szama);
    for (CsucsListaElem *cse = g->csucsok->elso->kov; cse != g->csucsok->utolso; cse = cse->kov) {
        Csucs *c = cse->csucs;
        for (SzomszedsagiListaElem *sze = c->szomszedok->elso->kov; sze != c->szomszedok->utolso; sze = sze->kov) {
            if (sze->csucs > c->id) {
                fprintf(fp, "%d %d %d\n", c->id, sze->csucs, sze->suly);
            }
        }
    }

    fclose(fp);
    return true;
}
