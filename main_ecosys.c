#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include "ecosys.h"

#define NB_PROIES 80
#define NB_PREDATEURS 10
#define T_WAIT 5000

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir = 0.5;
float p_reproduce_proie = 0.23;
float p_reproduce_predateur = 0.15;
int temps_repousse_herbe = -30;

int main(void) {
    srand(time(NULL));
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    int monde[SIZE_X][SIZE_Y];
    memset(monde, 0, sizeof(monde));

    // // Exercice 5.1
    // ajouter_animal(0, 0, 3, &liste_proie);
    // liste_proie->dir[0] = 1;
    // liste_proie->dir[1] = 1;
    // afficher_ecosys(NULL, liste_proie);
    // for (int i = 0; i < 3; i++) {
    //   rafraichir_proies(&liste_proie, monde);
    //   afficher_ecosys(NULL, liste_proie);
    // }
    // liberer_liste_animaux(liste_proie);

    // Exercice 5.2
    for (int i = 0; i < NB_PROIES; i++) 
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 20, &liste_proie);
    for (int i = 0; i < NB_PREDATEURS; i++) 
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 50, &liste_predateur);

    struct timespec sleepTime;
    sleepTime.tv_sec = 0;
    sleepTime.tv_nsec = T_WAIT*1000;

    FILE *f = fopen("Evol_Pop.txt", "w");
    for (int i = 0; i < 3000 && (liste_proie || liste_predateur); i++) {
        afficher_ecosys(liste_predateur, liste_proie);
        rafraichir_proies(&liste_proie, monde);
        rafraichir_predateurs(&liste_predateur, &liste_proie);
        rafraichir_monde(monde);
        fflush(stdout);
        nanosleep(&sleepTime, NULL);
        fprintf(f, "%d %d %d\n", i, compte_animal_it(liste_proie),
            compte_animal_it(liste_predateur));
    }
    afficher_ecosys(liste_predateur, liste_proie);
    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur);
    fclose(f);

    return 0;
}
