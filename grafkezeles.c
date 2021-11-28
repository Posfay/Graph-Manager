#include <stdlib.h>

#include "grafkezeles.h"

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

Graf *letrehoz_ures_graf() {
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

static int *init_volt(Graf *g) {
    int *volt = malloc(g->csucsok_szama * 2 * sizeof(int));
    CsucsListaElem *cse = g->csucsok->elso->kov;
    for (int i = 0; i < g->csucsok_szama; i++) {
        volt[2 * i] = cse->csucs->id;
        volt[2 * i + 1] = 0;
        cse = cse->kov;
    }
    return volt;
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

static void melysegi_rekurziv(Graf *g, int k, FILE *fp, int *volt) {
    fprintf(fp, "%d\n", k);
    megjelol_elem_volt(volt, g->csucsok_szama, k);
    Csucs *c = keres_csucs_lista(g->csucsok, k)->csucs;

    for (SzomszedsagiListaElem *sze = c->szomszedok->elso->kov; sze != c->szomszedok->utolso; sze = sze->kov) {
        if (!elem_volt(volt, g->csucsok_szama, sze->csucs)) {
            melysegi_rekurziv(g, sze->csucs, fp, volt);
        }
    }
}

bool melysegi_bejaras(Graf *g, int k, char *fajlnev) {
    FILE *fp = fopen(fajlnev, "wt");
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        return false;
    }

    int *volt = init_volt(g);

    melysegi_rekurziv(g, k, fp, volt);

    fclose(fp);
    free(volt);
    return true;
}

bool szelessegi_bejaras(Graf *g, int k, char *fajlnev) {
    FILE *fp = fopen(fajlnev, "wt");
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        return false;
    }

    int *volt = init_volt(g);
    CsucsSor *s = NULL;
    megjelol_elem_volt(volt, g->csucsok_szama, k);
    Csucs *c = keres_csucs_lista(g->csucsok, k)->csucs;
    s = push_csucs_sor(s, c);

    while (!ures_csucs_sor(s)) {
        c = pop_csucs_sor(s);
        fprintf(fp, "%d\n", c->id);

        for (SzomszedsagiListaElem *sze = c->szomszedok->elso->kov; sze != c->szomszedok->utolso; sze = sze->kov) {
            if (!elem_volt(volt, g->csucsok_szama, sze->csucs)) {
                megjelol_elem_volt(volt, g->csucsok_szama, sze->csucs);
                s = push_csucs_sor(s, keres_csucs_lista(g->csucsok, sze->csucs)->csucs);
            }
        }
    }

    fclose(fp);
    free(volt);
    felszabadit_csucs_sor(s);
    return true;
}

static int *init_tav(Graf *g, int a) {
    int *tav = malloc(g->csucsok_szama * 2 * sizeof(int));
    CsucsListaElem *cse = g->csucsok->elso->kov;
    for (int i = 0; i < g->csucsok_szama; i++) {
        tav[2 * i] = cse->csucs->id;
        if (cse->csucs->id == a) {
            tav[2 * i + 1] = 0;
        } else {
            tav[2 * i + 1] = INT_MAX;
        }
        cse = cse->kov;
    }
    return tav;
}

static int *init_elozo(Graf *g) {
    int *elozo = malloc(g->csucsok_szama * 2 * sizeof(int));
    CsucsListaElem *cse = g->csucsok->elso->kov;
    for (int i = 0; i < g->csucsok_szama; i++) {
        elozo[2 * i] = cse->csucs->id;
        elozo[2 * i + 1] = -1;
        cse = cse->kov;
    }
    return elozo;
}

static int leker_tav_i(int *tav, int hossz, int e) {
    for (int i = 0; i < hossz; i++) {
        if (tav[2 * i] == e) {
            return 2 * i;
        }
    }
}

static int leker_min_tav_i(int *tav, int *volt, int hossz) {
    int min = INT_MAX;
    int min_i;
    for (int i = 0; i < hossz; i++) {
        // min tavval rendelkezo csucs, ami meg nem volt
        if ((volt[2 * i + 1] == 0) && (tav[2 * i + 1] <= min)) {
            min = tav[2 * i + 1];
            min_i = 2 * i;
        }
    }
    return min_i;
}

static void legrovidebb_ut_fajlba(int *tav, int *elozo, int hossz, int cel, FILE *fp) {
    int c = leker_tav_i(tav, hossz, cel);
    if (elozo[c + 1] != -1) {
        fprintf(fp, "%d\n", tav[c + 1]);
        while (elozo[c + 1] != -1) {
            fprintf(fp, "%d\n", elozo[c]);
            c = elozo[c + 1];
        }
        fprintf(fp, "%d\n", elozo[c]);
    } else {
        fprintf(fp, "Nincs utvonal\n");
    }
}

bool dijkstra_legrovidebb_ut(Graf *g, int a, int b, char *fajlnev) {
    FILE *fp = fopen(fajlnev, "wt");
    if (fp == NULL) {
        perror("Fajl megnyitasa sikertelen");
        return false;
    }

    int *volt = init_volt(g);
    int *tav = init_tav(g, a);
    int *elozo = init_elozo(g);
    int volt_db = 0;

    while (volt_db < g->csucsok_szama) {
        int min_i = leker_min_tav_i(tav, volt, g->csucsok_szama);

        // elertuk a celpontot, befejezhetjuk a legrovidebb utkeresest
        if (volt[min_i] == b) {
            break;
        }

        Csucs *c = keres_csucs_lista(g->csucsok, volt[min_i])->csucs;
        int tav_c = tav[min_i + 1];
        // megjelol elem volt
        volt[min_i + 1] = 1;
        volt_db++;

        // nem osszefuggo a kiinduloponttal, nincs ertelme a legrovidebb utnak ide, atugorjuk
        if (tav_c == INT_MAX) {
            continue;
        }

        for (SzomszedsagiListaElem *sze = c->szomszedok->elso->kov; sze != c->szomszedok->utolso; sze = sze->kov) {
            if (!elem_volt(volt, g->csucsok_szama, sze->csucs)) {
                int uj_tav = tav_c + sze->suly;
                int sze_tav_i = leker_tav_i(tav, g->csucsok_szama, sze->csucs);
                if (uj_tav < tav[sze_tav_i + 1]) {
                    tav[sze_tav_i + 1] = uj_tav;
                    elozo[sze_tav_i + 1] = min_i;
                }
            }
        }
    }

    legrovidebb_ut_fajlba(tav, elozo, g->csucsok_szama, b, fp);

    fclose(fp);
    free(volt);
    free(tav);
    free(elozo);
    return true;
}
