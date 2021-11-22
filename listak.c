#include <stdlib.h>

#include "listak.h"

#include "debugmalloc.h"

SzomszedsagiLista *beszur_szomszedsagi_lista(SzomszedsagiLista *l, int csucs, int suly) {
    SzomszedsagiListaElem *uj = malloc(sizeof(SzomszedsagiListaElem));
    uj->csucs = csucs;
    uj->suly = suly;
    if (l == NULL) {
        SzomszedsagiLista *uj_l = malloc(sizeof(SzomszedsagiLista));
        uj_l->elso = malloc(sizeof(SzomszedsagiListaElem));
        uj_l->utolso = malloc(sizeof(SzomszedsagiListaElem));
        uj_l->elso->kov = uj;
        uj_l->elso->elozo = NULL;
        uj_l->utolso->elozo = uj;
        uj_l->utolso->kov = NULL;
        uj->elozo = uj_l->elso;
        uj->kov = uj_l->utolso;
        return uj_l;
    }
    SzomszedsagiListaElem *e = l->elso->kov;
    while (e != l->utolso && e->csucs < csucs) {
        e = e->kov;
    }
    uj->elozo = e->elozo;
    uj->kov = e;
    e->elozo->kov = uj;
    e->elozo = uj;
    return l;
}

SzomszedsagiListaElem *keres_szomszedsagi_lista(SzomszedsagiLista *l, int csucs) {
    if (l == NULL) {
        return NULL;
    }
    SzomszedsagiListaElem *e = l->elso->kov;
    while (e != l->utolso && e->csucs != csucs) {
        e = e->kov;
    }
    if (e == l->utolso) {
        return NULL;
    } else {
        return e;
    }
}

void torol_szomszedsagi_lista(SzomszedsagiLista *l, int csucs) {
    SzomszedsagiListaElem *e = keres_szomszedsagi_lista(l, csucs);
    if (e != NULL) {
        SzomszedsagiListaElem *t = e;
        t->elozo->kov = t->kov;
        t->kov->elozo = t->elozo;
        free(t);
    }
}

void felszabadit_szomszedsagi_lista(SzomszedsagiLista *l) {
    if (l == NULL) {
        return;
    }
    SzomszedsagiListaElem *e = l->elso;
    while (e != NULL) {
        SzomszedsagiListaElem *e2 = e;
        e = e->kov;
        free(e2);
    }
    free(l);
}

CsucsLista *beszur_csucs_lista(CsucsLista *l, Csucs *csucs) {
    CsucsListaElem *uj = malloc(sizeof(CsucsListaElem));
    uj->csucs = csucs;
    if (l == NULL) {
        CsucsLista *uj_l = malloc(sizeof(CsucsLista));
        uj_l->elso = malloc(sizeof(CsucsListaElem));
        uj_l->utolso = malloc(sizeof(CsucsListaElem));
        uj_l->elso->kov = uj;
        uj_l->elso->elozo = NULL;
        uj_l->utolso->elozo = uj;
        uj_l->utolso->kov = NULL;
        uj->elozo = uj_l->elso;
        uj->kov = uj_l->utolso;
        return uj_l;
    }
    CsucsListaElem *e = l->elso->kov;
    while (e != l->utolso && e->csucs->id < csucs->id) {
        e = e->kov;
    }
    uj->elozo = e->elozo;
    uj->kov = e;
    e->elozo->kov = uj;
    e->elozo = uj;
    return l;
}

CsucsListaElem *keres_csucs_lista(CsucsLista *l, int csucs) {
    if (l == NULL) {
        return NULL;
    }
    CsucsListaElem *e = l->elso->kov;
    while (e != l->utolso && e->csucs->id != csucs) {
        e = e->kov;
    }
    if (e == l->utolso) {
        return NULL;
    } else {
        return e;
    }
}

void torol_csucs_lista(CsucsLista *l, int csucs) {
    CsucsListaElem *e = keres_csucs_lista(l, csucs);
    if (e != NULL) {
        CsucsListaElem *t = e;
        t->elozo->kov = t->kov;
        t->kov->elozo = t->elozo;
        felszabadit_szomszedsagi_lista(t->csucs->szomszedok);
        free(t->csucs);
        free(t);
    }
}

void felszabadit_csucs_lista(CsucsLista *l) {
    if (l == NULL) {
        return;
    }
    CsucsListaElem *e = l->elso->kov;
    while (e != l->utolso) {
        CsucsListaElem *e2 = e;
        e = e->kov;
        felszabadit_szomszedsagi_lista(e2->csucs->szomszedok);
        free(e2->csucs);
        free(e2);
    }
    free(l->elso);
    free(l->utolso);
    free(l);
}
