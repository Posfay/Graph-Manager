#ifndef GRAF_LISTAK_H
#define GRAF_LISTAK_H

typedef struct SzomszedsagiListaElem {
    int csucs;
    int suly;
    struct SzomszedsagiListaElem *elozo, *kov;
} SzomszedsagiListaElem;

typedef struct SzomszedsagiLista {
    struct SzomszedsagiListaElem *elso, *utolso;
} SzomszedsagiLista;

typedef struct Csucs {
    int id;
    SzomszedsagiLista *szomszedok;
} Csucs;

typedef struct CsucsListaElem {
    Csucs *csucs;
    struct CsucsListaElem *elozo, *kov;
} CsucsListaElem;

typedef struct CsucsLista {
    struct CsucsListaElem *elso, *utolso;
} CsucsLista;

typedef struct Graf {
    CsucsLista *csucsok;
    int csucsok_szama;
    int elek_szama;
} Graf;

SzomszedsagiLista *beszur_szomszedsagi_lista(SzomszedsagiLista *l, int csucs, int suly);
SzomszedsagiListaElem *keres_szomszedsagi_lista(SzomszedsagiLista *l, int csucs);
void torol_szomszedsagi_lista(SzomszedsagiLista *l, int csucs);
void felszabadit_szomszedsagi_lista(SzomszedsagiLista *l);

CsucsLista *beszur_csucs_lista(CsucsLista *l, Csucs *csucs);
CsucsListaElem *keres_csucs_lista(CsucsLista *l, int csucs);
void torol_csucs_lista(CsucsLista *l, int csucs);
void felszabadit_csucs_lista(CsucsLista *l);

#endif //GRAF_LISTAK_H
