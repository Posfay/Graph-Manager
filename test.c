#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "test.h"
#include "listak.h"
#include "grafkezeles.h"
#include "fajlkezeles.h"

#include "debugmalloc.h"

static void test_szomszedsagi() {
    SzomszedsagiLista *l = NULL;
    l = beszur_szomszedsagi_lista(l, 3, 4);
    assert(l->elso->kov == l->utolso->elozo);
    assert(l->elso->kov->csucs == 3);
    assert(l->elso->kov->suly == 4);
    l = beszur_szomszedsagi_lista(l, 1, 3);
    assert(l->elso->kov->csucs == 1);
    assert(l->elso->kov->suly == 3);
    l = beszur_szomszedsagi_lista(l, 2, 5);
    assert(l->elso->kov->kov->csucs == 2);
    assert(l->elso->kov->kov->suly == 5);
    felszabadit_szomszedsagi_lista(l);
    printf("Szomszedsagi lista mukodik\n");
}

static void test_csucs() {
    SzomszedsagiLista *sl = NULL;
    sl = beszur_szomszedsagi_lista(sl, 2, 3);
    CsucsLista *l = NULL;
    Csucs *c = malloc(sizeof(Csucs));
    *c = (Csucs) {1, sl};
    l = beszur_csucs_lista(l, c);
    assert(l->elso->kov == l->utolso->elozo);
    assert(l->elso->kov->csucs->id == 1);
    assert(l->elso->kov->csucs->szomszedok == sl);
    assert(l->elso->kov->csucs->szomszedok->elso->kov->csucs == 2);
    assert(l->elso->kov->csucs->szomszedok->elso->kov->suly == 3);
    felszabadit_csucs_lista(l);
    printf("Csucs lista mukodik\n");
}

static void test_graf() {
    Graf *g = letrehoz_ures_graf();
    csucs_hozzaad(g, 1);
    csucs_hozzaad(g, 0);
    assert(g->csucsok_szama == 2);
    assert(g->elek_szama == 0);
    assert(g->csucsok->elso->kov->csucs->id == 0);
    assert(g->csucsok->utolso->elozo->csucs->id == 1);
    el_letrehoz(g, 1, 0, 4);
    assert(g->elek_szama == 1);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->csucs == 1);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->suly == 4);
    assert(g->csucsok->utolso->elozo->csucs->szomszedok->elso->kov->csucs == 0);
    assert(g->csucsok->utolso->elozo->csucs->szomszedok->elso->kov->suly == 4);
    el_modosit(g, 0, 1, 3);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->csucs == 1);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->suly == 3);
    assert(g->csucsok->utolso->elozo->csucs->szomszedok->elso->kov->csucs == 0);
    assert(g->csucsok->utolso->elozo->csucs->szomszedok->elso->kov->suly == 3);
    el_torol(g, 1, 0);
    assert(g->elek_szama == 0);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov == g->csucsok->elso->kov->csucs->szomszedok->utolso);
    assert(g->csucsok->utolso->elozo->csucs->szomszedok->elso->kov == g->csucsok->utolso->elozo->csucs->szomszedok->utolso);
    csucs_torol(g, 0);
    assert(g->csucsok_szama == 1);
    assert(g->csucsok->elso->kov->csucs->id == 1);
    assert(g->csucsok->utolso->elozo->csucs->id == 1);
    assert(g->csucsok->elso->kov == g->csucsok->utolso->elozo);
    csucs_torol(g, 1);
    assert(g->csucsok_szama == 0);
    assert(g->csucsok->elso->kov == g->csucsok->utolso);
    felszabadit_graf(g);
    printf("Graf struktura fuggvenyei mukodnek\n");
}

static void test_fajlkezeles() {
    Graf *g = letrehoz_ures_graf();
    betolt_graf(g, "g.txt");
    assert(g->csucsok_szama == 3);
    assert(g->elek_szama == 2);
    assert(g->csucsok->elso->kov->csucs->id == 0);
    assert(g->csucsok->elso->kov->kov->csucs->id == 1);
    assert(g->csucsok->utolso->elozo->csucs->id == 2);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->csucs == 1);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->suly == 4);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->kov->csucs == 2);
    assert(g->csucsok->elso->kov->csucs->szomszedok->elso->kov->kov->suly == 2);
    assert(g->csucsok->elso->kov->kov->csucs->szomszedok->elso->kov->csucs == 0);
    assert(g->csucsok->elso->kov->kov->csucs->szomszedok->elso->kov->suly == 4);
    assert(g->csucsok->utolso->elozo->csucs->szomszedok->elso->kov->csucs == 0);
    assert(g->csucsok->utolso->elozo->csucs->szomszedok->elso->kov->suly == 2);
    felszabadit_graf(g);
    printf("Graf betoltes mukodik\n");
}

static void test_csucs_sor() {
    CsucsSor *s = NULL;
    Graf *g = letrehoz_ures_graf();
    csucs_hozzaad(g, 1);
    csucs_hozzaad(g, 0);
    s = push_csucs_sor(s, g->csucsok->elso->kov->csucs);
    assert(s->db == 1);
    s = push_csucs_sor(s, g->csucsok->utolso->elozo->csucs);
    assert(s->db == 2);
    assert(!ures_csucs_sor(s));
    Csucs *c = pop_csucs_sor(s);
    assert(c->id == 0);
    assert(s->db == 1);
    c = pop_csucs_sor(s);
    assert(c->id == 1);
    assert(s->db == 0);
    assert(ures_csucs_sor(s));
    felszabadit_graf(g);
    felszabadit_csucs_sor(s);
    printf("Csucs sor mukodik\n");
}

void unit_test() {
    test_szomszedsagi();
    test_csucs();
    test_graf();
    test_fajlkezeles();
    test_csucs_sor();
}
