#include "ecosys.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
    Animal *na = (Animal *)malloc(sizeof(Animal));
    assert(na);
    // printf("alloue : %p\n", na);
    na->x = x;
    na->y = y;
    na->energie = energie;
    na->dir[0] = rand() % 3 - 1;
    na->dir[1] = rand() % 3 - 1;
    na->suivant = NULL;
    return na;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
    assert(animal);
    assert(!animal->suivant);
    animal->suivant = liste;
    return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
    /*A Completer*/
    assert(x >= 0);
    assert(x < SIZE_X);
    assert(y >= 0);
    assert(y < SIZE_Y);
    Animal *a = creer_animal(x, y, energie);
    *liste_animal = ajouter_en_tete_animal(*liste_animal, a);
    // Animal *pa = *liste_animal;
    // while(pa->suivant)
    //   pa = pa->suivant;
    // Animal *a = creer_animal(x, y, energie);
    // pa->suivant = a;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
    /*A Completer*/
    if (*liste == animal) {
        *liste = animal->suivant;
    } else {
        Animal *pt = *liste;
        while (pt->suivant != animal) pt = pt->suivant;
        pt->suivant = pt->suivant->suivant;
    }
    free(animal);
    return;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal *liberer_liste_animaux(Animal *liste) {
    // Animal *suiv = liste->suivant;
    // do {
    //     suiv = liste->suivant;
    //     free(liste);
    //     printf("libere : %p\n", liste);
    //     liste = suiv;
    // } while (liste);
    while (liste) {
        Animal *suiv = liste->suivant;
        free(liste);
        // printf("libere : %p\n", liste);
        liste = suiv;
    }
    return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
    if (!la) return 0;
    return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
    int cpt = 0;
    while (la) {
        ++cpt;
        la = la->suivant;
    }
    return cpt;
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de
 * contenir des erreurs... */
void afficher_ecosys(Animal *liste_predateur, Animal *liste_proie) {
    // printf("afficher_ecosys(%p, %p)\n", (void *)liste_predateur,
    //        (void *)liste_proie);
    unsigned int i, j;
    char ecosys[SIZE_X][SIZE_Y];
    Animal *pa = NULL;

    /* on initialise le tableau */
    for (i = 0; i < SIZE_X; ++i) {
        for (j = 0; j < SIZE_Y; ++j) {
            ecosys[i][j] = ' ';
        }
    }

    /* on ajoute les proies */
    pa = liste_proie;
    while (pa) {
        // printf("%d %d\n", pa->x, pa->y);
        ecosys[pa->x][pa->y] = '*';
        pa = pa->suivant;
    }
    // printf("proies ajoutees\n");
    /* on ajoute les predateurs */
    pa = liste_predateur;
    while (pa) {
        if ((ecosys[pa->x][pa->y] == '@') ||
            (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
            ecosys[pa->x][pa->y] = '@';
        } else {
            ecosys[pa->x][pa->y] = 'O';
        }
        pa = pa->suivant;
    }
    /* on affiche le tableau */
    printf("+");
    for (j = 0; j < SIZE_Y; ++j) {
        printf("-");
    }
    printf("+\n");
    for (i = 0; i < SIZE_X; ++i) {
        printf("|");
        for (j = 0; j < SIZE_Y; ++j) {
            putchar(ecosys[i][j]);
        }
        printf("|\n");
    }
    printf("+");
    for (j = 0; j < SIZE_Y; ++j) {
        printf("-");
    }
    printf("+\n");
    int nbproie = compte_animal_it(liste_proie);
    int nbpred = compte_animal_it(liste_predateur);

    printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}

void clear_screen() {
    printf("\x1b[2J\x1b[1;1H"); /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
    // printf("bouger_animaux(%p)\n", (void *)la);
    Animal *a = la;
    while (a) {
        if ((double)rand() / (double)RAND_MAX <= p_ch_dir) {
            a->dir[0] = rand() % 3 - 1;
            a->dir[1] = rand() % 3 - 1;
        }
        a->x = (a->x + a->dir[0] + SIZE_X) % SIZE_X;
        a->y = (a->y + a->dir[1] + SIZE_Y) % SIZE_Y;
        a = a->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
    /*A Completer*/
    // printf("reproduce(%p)\n", (void *)*liste_animal);
    Animal *a = *liste_animal;
    while (a) {
        if ((double)rand() / (double)RAND_MAX <= p_reproduce) {
            ajouter_animal(a->x, a->y, a->energie / 2, liste_animal);
            a->energie /= 2;
        }
        a = a->suivant;
    }
    // printf("reproduced : %p\n", (void *)*liste_animal);
}

// Animal* supprime_faim(Animal **liste) {
//     while ((*liste) && (*liste)->energie <= 0) {
//         Animal *suiv = (*liste)->suivant;
//         free(*liste);
//         printf("libere : %p\n", (void*)*liste);
//         *liste = suiv;
//     }
//     return *liste;
// }

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/
    bouger_animaux(*liste_proie);
    // printf("bouge !\n");
    Animal *a = *liste_proie;
    while (a) {
        a->energie--;
        a = a->suivant;
    }
    // printf("energie--\n");
    while ((*liste_proie) && (*liste_proie)->energie <= 0) {
        Animal *suiv = (*liste_proie)->suivant;
        free(*liste_proie);
        // printf("libere1 : %p energie %d\n", (void*)*liste_proie, (*liste_proie)->energie);
        *liste_proie = suiv;
    }
    a = *liste_proie;
    while (a) {
        while (a->suivant && a->suivant->energie <= 0) {
            Animal *suiv = a->suivant->suivant;
            free(a->suivant);
            a->suivant = suiv;
            // printf("libere2 : %p energie %d\n", (void*)a->suivant, a->suivant->energie);
        }
        a = a->suivant;
    }
    // printf("supprime_faim\n");
    // printf("*liste_proie = %p\n", (void *)*liste_proie);
    a = *liste_proie;
    while (a) {
        if (monde[a->x][a->y] > 0) {
            a->energie += monde[a->x][a->y];
            monde[a->x][a->y] = temps_repousse_herbe;
        }
        a = a->suivant;
    }
    reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/
    while (l)
        if (l->x == x && l->y == y)
            return l;
        else
            l = l->suivant;
    return NULL;
}

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
    bouger_animaux(*liste_predateur);
    Animal *a = *liste_predateur;
    while (a) {
        a->energie--;
        Animal* proie = animal_en_XY(*liste_proie, a->x, a->y);
        while (proie) {
            a->energie += proie->energie;
            enlever_animal(liste_proie, proie);
            // printf("mangé !\n");
            proie = animal_en_XY(*liste_proie, a->x, a->y);
        }
        a = a->suivant;
    }
    while ((*liste_predateur) && (*liste_predateur)->energie <= 0) {
        Animal *suiv = (*liste_predateur)->suivant;
        free(*liste_predateur);
        *liste_predateur = suiv;
    }
    a = *liste_predateur;
    while (a) {
        while (a->suivant && a->suivant->energie <= 0) {
            Animal *suiv = a->suivant->suivant;
            free(a->suivant);
            a->suivant = suiv;
        }
        a = a->suivant;
    }
    reproduce(liste_predateur, p_reproduce_predateur);
    /*A Completer*/
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) { /*A Completer*/
    for (int i = 0; i < SIZE_X; i++)
        for (int j = 0; j < SIZE_Y; j++)
            monde[i][j]++;
}
