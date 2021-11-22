#include <stdio.h>
#include <stdlib.h>

#include "listak.h"
#include "megjelenites.h"
#include "grafkezeles.h"
#include "fajlkezeles.h"

#include "test.h"

#include "debugmalloc.h"

enum { BETOLTES = 1, MENTES = 2, EPITO = 3, SZELESSEGI = 4, MELYSEGI = 5, UTKERESES = 6, KILEPES = 7 };
enum { UJ_CSUCS = 'c', CSUCS_TORLES = 'd', EL_LETREHOZAS = 'e', EL_TORLES = 'r', EL_MODOSITAS = 'm', GE_KILEPES = 'q' };

void graf_epito(Graf *g) {
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

void foprogram() {
    Graf *graf = letrehoz_graf();
    int menu = 0;
    do {
        menu_kiiras();
        scanf("%d", &menu);
        switch (menu) {
            case BETOLTES:
                printf("Add meg a fajl utvonalat:\n");
                char betolt_utvonal[200];
                scanf("%s", betolt_utvonal);
                betolt_graf(graf, betolt_utvonal);
                printf("Graf betoltve, csucsainak szama: %d, eleinek szama: %d\n", graf->csucsok_szama, graf->elek_szama);
                break;
            case MENTES:
                printf("Add meg a fajl utvonalat:\n");
                char ment_utvonal[200];
                scanf("%s", ment_utvonal);
                ment_graf(graf, ment_utvonal);
                printf("Graf mentve, csucsainak szama: %d, eleinek szama: %d\n", graf->csucsok_szama, graf->elek_szama);
                break;
            case EPITO:
                printf("Mostantol a graf-epitoben vagy!\n");
                graf_epito(graf);
                break;
            case SZELESSEGI:
                // szelessegi
                break;
            case MELYSEGI:
                printf("Add meg a kiindulo csucs szamat:\n");
                int kezdo_melysegi;
                scanf("%d", &kezdo_melysegi);
                printf("A bejaras sorrendje: ");
                melysegi_bejaras(graf, kezdo_melysegi);
                break;
            case UTKERESES:
                // utkereses
                break;
            default:
                break;
        }
    } while (menu != KILEPES);

    felszabadit_graf(graf);
}

int main() {
//    unit_test();
    foprogram();

    return 0;
}
