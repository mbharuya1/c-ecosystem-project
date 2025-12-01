#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "ecosys.h"
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

void fprint_animals(FILE *f, Animal *a) {
    while (a) {
        fprintf(f, "x=%d y=%d dir=[%d %d] e=%f\n", a->x, a->y, a->dir[0],
                a->dir[1], a->energie);
        a = a->suivant;
    }
}

void ecrire_ecosys(const char *nom_ficher, Animal *liste_predateur,
                   Animal *liste_proie) {
    FILE *f = fopen(nom_ficher, "w");
    assert(f != NULL);
    fprintf(f, "<proies>\n");
    Animal *proie = liste_proie;
    fprint_animals(f, liste_proie);
    fprintf(f, "</proies>\n");
    fprintf(f, "<predateurs>\n");
    Animal *predateur = liste_predateur;
    fprint_animals(f, liste_predateur);
    fprintf(f, "</predateurs>\n");
    fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur,
                 Animal **liste_proie) {
    FILE *f = fopen(nom_fichier, "r");
    assert(f);
    char buffer[256];
    fgets(buffer, 256, f);
    putc('<', stderr);
    fputs(buffer, stderr);
    putc('>', stderr);
    
    assert(strncmp(buffer, "<proies>", strlen("<proies>")) == 0);
    int x_lu, y_lu, dir0, dir1;
    float e_lu;
    fgets(buffer, 256, f);
    while (strncmp(buffer, "</proies>", strlen("</proies>")) != 0) {
        sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0,
               &dir1, &e_lu);
        ajouter_animal(x_lu, y_lu, e_lu, liste_proie);
        (*liste_proie)->dir[0] = dir0;
        (*liste_proie)->dir[1] = dir1;
        fgets(buffer, 256, f);
    }
    fgets(buffer, 256, f);
    assert(strncmp(buffer, "<predateurs>", strlen("<predateurs>")) == 0);
    fgets(buffer, 256, f);
    while (strncmp(buffer, "</predateurs>", strlen("</predateurs>")) != 0) {
        sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f\n", &x_lu, &y_lu, &dir0,
               &dir1, &e_lu);
        ajouter_animal(x_lu, y_lu, e_lu, liste_predateur);
        (*liste_predateur)->dir[0] = dir0;
        (*liste_predateur)->dir[1] = dir1;
        fgets(buffer, 256, f);
    }
    fclose(f);
}

int main(void) {
    int energie = 10;
    srand(time(NULL));
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    Animal *deuxieme_predateur;
    for (int i = 0; i < 3; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie, &liste_proie);
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, energie,
                       &liste_predateur);
        if (i == 1) {
            deuxieme_predateur = liste_predateur;
            printf("à enlever : (%d, %d)\n", deuxieme_predateur->x,
                   deuxieme_predateur->y);
        }
    }
    afficher_ecosys(liste_predateur, liste_proie);
    ecrire_ecosys("sys.txt", liste_predateur, liste_proie);

    enlever_animal(&liste_predateur, deuxieme_predateur);
    afficher_ecosys(liste_predateur, liste_proie);

    liste_predateur = liberer_liste_animaux(liste_predateur);
    liste_proie = liberer_liste_animaux(liste_proie);
    afficher_ecosys(liste_predateur, liste_proie);

    lire_ecosys("sys.txt", &liste_predateur, &liste_proie);
    afficher_ecosys(liste_predateur, liste_proie);
    liste_predateur = liberer_liste_animaux(liste_predateur);
    liste_proie = liberer_liste_animaux(liste_proie);
    return 0;
}
