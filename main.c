#include <stdio.h>
#include <stdlib.h>

#include "listak.h"
#include "grafkezeles.h"
#include "fajlkezeles.h"

#include "debugmalloc.h"

enum { BETOLTES = 1, MENTES = 2, EPITO = 3, SZELESSEGI = 4, MELYSEGI = 5, UTKERESES = 6, KILEPES = 7 };
enum { UJ_CSUCS = 'c', CSUCS_TORLES = 'd', EL_LETREHOZAS = 'e', EL_TORLES = 'r', EL_MODOSITAS = 'm', GE_KILEPES = 'q' };

void menu_kiiras() {
    printf("A megjeleno opciok kozul a megfelelo sorszam beirasaval valaszthatsz.\n"
           "1. Betoltes\n"
           "2. Mentes\n"
           "3. Graf-epito\n"
           "4. Szelessegi bejaras\n"
           "5. Melysegi bejaras\n"
           "6. Legrovidebb ut kereses\n"
           "7. Kilepes\n");
}

Graf *betoltes_menu(Graf *g) {
    printf("Add meg a fajl utvonalat:\n");
    char betolt_utvonal[200];
    scanf("%s", betolt_utvonal);
    g = betolt_graf(g, betolt_utvonal);
    printf("Graf betoltve, csucsainak szama: %d, eleinek szama: %d\n", g->csucsok_szama, g->elek_szama);
    return g;
}

void mentes_menu(Graf *g) {
    printf("Add meg a fajl utvonalat:\n");
    char ment_utvonal[200];
    scanf("%s", ment_utvonal);
    bool ment_siker = ment_graf(g, ment_utvonal);
    if (ment_siker) {
        printf("Graf mentve, csucsainak szama: %d, eleinek szama: %d\n", g->csucsok_szama, g->elek_szama);
    } else {
        printf("Nem sikerult elmenteni a grafot!\n");
    }
}

void graf_epito_menu(Graf *g) {
    printf("Mostantol a graf-epitoben vagy!\n");
    char ge_menu = '0';

    do {
        char s1[200];
        int arg1, arg2, arg3;
        gets(s1);
        sscanf(s1, "%c", &ge_menu);

        if (ge_menu == UJ_CSUCS || ge_menu == CSUCS_TORLES) {
            sscanf(s1, "%c %d", &ge_menu, &arg1);
        } else if (ge_menu == EL_TORLES) {
            sscanf(s1, "%c %d %d", &ge_menu, &arg1, &arg2);
        } else if (ge_menu == EL_LETREHOZAS || ge_menu == EL_MODOSITAS) {
            sscanf(s1, "%c %d %d %d", &ge_menu, &arg1, &arg2, &arg3);
        }

        switch (ge_menu) {
            case UJ_CSUCS:
                csucs_hozzaad(g, arg1);
                printf("Csucs \"%d\" hozzaadva\n", arg1);
                break;
            case CSUCS_TORLES:
                csucs_torol(g, arg1);
                printf("Csucs \"%d\" torolve\n", arg1);
                break;
            case EL_LETREHOZAS:
                el_letrehoz(g, arg1, arg2, arg3);
                printf("El \"(%d, %d) w=%d\" letrehozva\n", arg1, arg2, arg3);
                break;
            case EL_TORLES:
                el_torol(g, arg1, arg2);
                printf("El \"(%d, %d)\" torolve\n", arg1, arg2);
                break;
            case EL_MODOSITAS:
                el_modosit(g, arg1, arg2, arg3);
                printf("El \"(%d, %d) w=%d\" modositva\n", arg1, arg2, arg3);
                break;
            case GE_KILEPES:
                printf("Kileptel a graf-epitobol!\n");
                break;
            default:
                break;
        }
    } while (ge_menu != GE_KILEPES);
}

void szelessegi_menu(Graf *g) {
    printf("Add meg a kiindulo csucs szamat:\n");
    int kezdo_szelessegi;
    scanf("%d", &kezdo_szelessegi);
    printf("Add meg a fajl utvonalat, ahova a vegeredmenyt menti a program:\n");
    char szelessegi_utvonal[200];
    scanf("%s", szelessegi_utvonal);
    bool szelessegi_siker = szelessegi_bejaras(g, kezdo_szelessegi, szelessegi_utvonal);
    if (szelessegi_siker) {
        printf("Szelessegi bejaras sikerult, mentve %s fajlba.\n", szelessegi_utvonal);
    } else {
        printf("Nem sikerult a szelessegi bejarast menteni!\n");
    }
}

void melysegi_menu(Graf *g) {
    printf("Add meg a kiindulo csucs szamat:\n");
    int kezdo_melysegi;
    scanf("%d", &kezdo_melysegi);
    printf("Add meg a fajl utvonalat, ahova a vegeredmenyt menti a program:\n");
    char melysegi_utvonal[200];
    scanf("%s", melysegi_utvonal);
    bool melysegi_siker = melysegi_bejaras(g, kezdo_melysegi, melysegi_utvonal);
    if (melysegi_siker) {
        printf("Melysegi bejaras sikerult, mentve %s fajlba.\n", melysegi_utvonal);
    } else {
        printf("Nem sikerult a melysegi bejarast menteni!\n");
    }
}

void utkereses_menu(Graf *g) {
    printf("Add meg a kiindulo csucs szamat:\n");
    int kiindulo;
    scanf("%d", &kiindulo);
    printf("Add meg a cel csucs szamat:\n");
    int cel;
    scanf("%d", &cel);
    printf("Add meg a fajl utvonalat, ahova a vegeredmenyt menti a program:\n");
    char dijkstra_utvonal[200];
    scanf("%s", dijkstra_utvonal);
    bool dijkstra_siker = dijkstra_legrovidebb_ut(g, cel, kiindulo, dijkstra_utvonal);
    if (dijkstra_siker) {
        printf("Legrovidebb utkereses befejezodott, a vegeredmeny mentve %s fajlba.\n", dijkstra_utvonal);
    } else {
        printf("Nem sikerult a legrovidebb utkereses eredmenyet menteni!\n");
    }
}

void foprogram() {
    Graf *graf = letrehoz_ures_graf();
    int menu = 0;

    do {
        menu_kiiras();
        scanf("%d", &menu);

        switch (menu) {
            case BETOLTES:
                graf = betoltes_menu(graf);
                break;
            case MENTES:
                mentes_menu(graf);
                break;
            case EPITO:
                graf_epito_menu(graf);
                break;
            case SZELESSEGI:
                szelessegi_menu(graf);
                break;
            case MELYSEGI:
                melysegi_menu(graf);
                break;
            case UTKERESES:
                utkereses_menu(graf);
                break;
            default:
                break;
        }
    } while (menu != KILEPES);

    felszabadit_graf(graf);
}

int main() {
    foprogram();

    return 0;
}
