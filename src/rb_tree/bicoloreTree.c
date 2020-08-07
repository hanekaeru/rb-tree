
#include "bicoloreTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>

Noeud *racine = NIL; 
bool afficherConsole = false;      

/**
 * void rotationGauche()
 * @param Noeud x
 * Fonction qui permet de faire une rotation gauche.
 */
void rotationGauche(Noeud *x) {

    if(afficherConsole == true){
        printf("-!- Rotation gauche effectuee sur -> %d \n",x->valeur);
    }

    Noeud *y = x->filsDroite;

    x->filsDroite = y->filsGauche;

    if (y->filsGauche != NIL) {
        y->filsGauche->noeudPere = x;
    }

    if (y != NIL) {
        y->noeudPere = x->noeudPere;
    }

    if (x->noeudPere) {
        if (x == x->noeudPere->filsGauche)
            x->noeudPere->filsGauche = y;
        else
            x->noeudPere->filsDroite = y;
    } else {
        racine = y;
    }

    y->filsGauche = x;
    if (x != NIL) x->noeudPere = y;

}

/**
 * void rotationDroite()
 * @param Noeud x
 * Fonction qui permet de faire une rotation droite.
 */
void rotationDroite(Noeud *x) {

    if(afficherConsole == true){
        printf("-!- Rotation droite effectuee sur -> %d \n",x->valeur);
    }

    Noeud *y = x->filsGauche;

    x->filsGauche = y->filsDroite;

    if (y->filsDroite != NIL) {
        y->filsDroite->noeudPere = x;
    }

    if (y != NIL) {
        y->noeudPere = x->noeudPere;
    }

    if (x->noeudPere) {
        if (x == x->noeudPere->filsDroite) {
            x->noeudPere->filsDroite = y;
        } else {
            x->noeudPere->filsGauche = y;
        }
    } else {
        racine = y;
    }

    y->filsDroite = x;

    if (x != NIL) {
        x->noeudPere = y;
    }

}

/**
 * void reparationInserer()
 * @param Noeud x
 * Fonction qui permet de réparer notre arbre après une insertion de noeud.
 */
void reparationInserer(Noeud *x) {

    if(afficherConsole == true){
        printf("-/- Reparation insertion -> %d \n",x->valeur);
    }

    while (x != racine && x->noeudPere->couleur == ROUGE) {

        if (x->noeudPere == x->noeudPere->noeudPere->filsGauche) {

            Noeud *y = x->noeudPere->noeudPere->filsDroite;

            if (y->couleur == ROUGE) {
                x->noeudPere->couleur = NOIR;
                y->couleur = NOIR;
                x->noeudPere->noeudPere->couleur = ROUGE;
                x = x->noeudPere->noeudPere;

            } else {

                if (x == x->noeudPere->filsDroite) {
                    x = x->noeudPere;
                    rotationGauche(x);
                }

                x->noeudPere->couleur = NOIR;
                x->noeudPere->noeudPere->couleur = ROUGE;
                rotationDroite(x->noeudPere->noeudPere);

            }

        } else {

            Noeud *y = x->noeudPere->noeudPere->filsGauche;

            if (y->couleur == ROUGE) {
                x->noeudPere->couleur = NOIR;
                y->couleur = NOIR;
                x->noeudPere->noeudPere->couleur = ROUGE;
                x = x->noeudPere->noeudPere;
            } else {

                if (x == x->noeudPere->filsGauche) {
                    x = x->noeudPere;
                    rotationDroite(x);
                }

                x->noeudPere->couleur = NOIR;
                x->noeudPere->noeudPere->couleur = ROUGE;
                rotationGauche(x->noeudPere->noeudPere);
            }
        }
    }
    racine->couleur = NOIR;
}

/**
 * void reparationSupprimer()
 * @param Noeud x
 * Fonction qui permet de réparer notre arbre après une suppression de noeud.
 */
void reparationSupprimer(Noeud *x) {

    if(afficherConsole == true){
        printf("-/- Reparation supression -> %d\n", x->valeur);
    }

    while (x != racine && x->couleur == NOIR) {

        if (x == x->noeudPere->filsGauche) {

            Noeud *w = x->noeudPere->filsDroite;

            if (w->couleur == ROUGE) {
                w->couleur = NOIR;
                x->noeudPere->couleur = ROUGE;
                rotationGauche (x->noeudPere);
                w = x->noeudPere->filsDroite;
            }

            if (w->filsGauche->couleur == NOIR && w->filsDroite->couleur == NOIR) {
                w->couleur = ROUGE;
                x = x->noeudPere;
            } else {

                if (w->filsDroite->couleur == NOIR) {
                    w->filsGauche->couleur = NOIR;
                    w->couleur = ROUGE;
                    rotationDroite (w);
                    w = x->noeudPere->filsDroite;
                }

                w->couleur = x->noeudPere->couleur;
                x->noeudPere->couleur = NOIR;
                w->filsDroite->couleur = NOIR;
                rotationGauche (x->noeudPere);
                x = racine;
            }
        } else {

            Noeud *w = x->noeudPere->filsGauche;

            if (w->couleur == ROUGE) {
                w->couleur = NOIR;
                x->noeudPere->couleur = ROUGE;
                rotationDroite (x->noeudPere);
                w = x->noeudPere->filsGauche;
            }

            if (w->filsDroite->couleur == NOIR && w->filsGauche->couleur == NOIR) {
                w->couleur = ROUGE;
                x = x->noeudPere;
            } else {

                if (w->filsGauche->couleur == NOIR) {
                    w->filsDroite->couleur = NOIR;
                    w->couleur = ROUGE;
                    rotationGauche (w);
                    w = x->noeudPere->filsGauche;
                }

                w->couleur = x->noeudPere->couleur;
                x->noeudPere->couleur = NOIR;
                w->filsGauche->couleur = NOIR;
                rotationDroite (x->noeudPere);
                x = racine;

            }
        }
    }
    x->couleur = NOIR;
}

/**
 * void insererNoeud()
 * @param int valeur
 * Fonction qui permet d'insérer un noeud dans notre arbre.
 */
Noeud *insererNoeud(int valeur) {

    if(afficherConsole == true){
        printf("-+- Insertion d'un nouveau noeud -> %d \n",valeur);
    }

    Noeud *noeudActuel, *noeudPere, *x;
    noeudActuel = racine;
    noeudPere = 0;

    while (noeudActuel != NIL) {

        if (compEQ(valeur, noeudActuel->valeur)) {
            return (noeudActuel);
        }

        noeudPere = noeudActuel;

        if(compLT(valeur, noeudActuel->valeur)) {
            noeudActuel = noeudActuel->filsGauche;
        } else {
            noeudActuel = noeudActuel->filsDroite;
        }

    }

    if ((x = malloc (sizeof(*x))) == 0) {
        printf ("Memoire insuffisante pour la fonction -> insererNoeud\n");
        exit(1);
    }

    x->valeur = valeur;
    x->noeudPere = noeudPere;
    x->filsGauche = NIL;
    x->filsDroite = NIL;
    x->couleur = ROUGE;

    if(noeudPere) {

        if(compLT(valeur, noeudPere->valeur)) {
            noeudPere->filsGauche = x;
        } else {
            noeudPere->filsDroite = x;
        }
    } else {
        racine = x;
    }

    reparationInserer(x);
    return(x);

}

/**
 * void insererNoeud()
 * @param Noeud z
 * Fonction qui permet d'insérer un noeud dans notre arbre.
 */
void supprimerNoeud(Noeud *z) {

    if(afficherConsole == true){
        printf("-X- Suppression d'un noeud -> %d \n", z->valeur);
    }

    Noeud *x, *y;

    if (!z || z == NIL) {
        return;
    }

    if (z->filsGauche == NIL || z->filsDroite == NIL) {
        y = z;
    } else {
        y = z->filsDroite;
        while (y->filsGauche != NIL) y = y->filsGauche;
    }

    if (y->filsGauche != NIL) {
        x = y->filsGauche;
    } else {
        x = y->filsDroite;
    }

    x->noeudPere = y->noeudPere;

    if (y->noeudPere) {
        if (y == y->noeudPere->filsGauche) {
            y->noeudPere->filsGauche = x;
        } else {
            y->noeudPere->filsDroite = x;
        }
    } else {
        racine = x;
    }

    if (y != z) {
        z->valeur = y->valeur;
    }

    if (y->couleur == NOIR && y != racine) {
        reparationSupprimer (x);
    }

    free (y);
}

/**
 * void rechercherNoeud()
 * @param int valeur
 * Fonction qui permet de rechercher un noeud dans notre arbre.
 */
Noeud *rechercherNoeud(int valeur) {

    Noeud *noeudActuel = racine;

    while(noeudActuel != NIL) {

        if(compEQ(valeur, noeudActuel->valeur)) {
            return (noeudActuel);
        } else {

            if(compLT(valeur, noeudActuel->valeur)) {
                noeudActuel = noeudActuel->filsGauche;
            } else {
                noeudActuel = noeudActuel->filsDroite;
            }

        }
            
    }
        
    return(0);
}

/**
 * void afficherConsoleFunc()
 * @param int nbNoeud
 * Fonction qui permet de gérer l'arbre avec un nombre X de noeuds qui sera affiché dans la console.
 */
void afficherConsoleFunc(int nbNoeud)
{
    afficherConsole = true;
    int a,cpt;
    Noeud *t;
    srand(time(NULL));
    for (cpt = nbNoeud; cpt; cpt--) {
        a = rand() %100 + 1;
        if ((t = rechercherNoeud(a)) != NULL) {
            supprimerNoeud(t);
            cpt = cpt + 2;
        } else {
            insererNoeud(a);
        }
    }
    afficherConsole = false;
}

/**
 * void main()
 * @param int argc
 * @param char argv
 * Fonction qui permet d'exécuter le code développé ci-dessus.
 */
void main(int argc, char **argv) {
    int choix = 0;
    do
    {
        printf("-- Arbres bicolores | Licence 3 Informatique --\n");
        printf("\n-- Menu                                      --\n");
        printf("1) Générer un arbre aléatoire | Affichage des opérations\n");
        printf("2) Afficher le temps d'execution\n");
        printf("\nQue voulez-vous faire ? (1-2) : ");
        scanf("%d", &choix); 
    } while(0 > choix && choix >= 2 );
    int nbNoeud = 0;

    // Génération d'un arbre aléatoire + affichage des opération.
    if(choix == 1){
        printf("-- 1 | Arbre aléatoire + Opérations --\n");
        do {
            printf("\nNombre de noeuds : ");
            scanf("%d", &nbNoeud);
        } while(0 > nbNoeud);
        afficherConsoleFunc(nbNoeud);
    }

    // Mesurer le temps d'exécution d'insertion et de suppression de X noeuds dans un arbre.
    if(choix == 2){
        nbNoeud = 10;
        int tabNbNoeuds[7] = {100,200,500,1000,5000,10000,100000};
        int x;
        FILE * fichier = NULL;
        fichier = fopen("temps.dat", "w");
            if (fichier != NULL) {
            for (x = 0; x<8; x++){

                nbNoeud = tabNbNoeuds[x];
                time_t start, end;
                double tempsTotal;
                time(&start);
                int a,cpt;
                Noeud *t;
                for (cpt = nbNoeud; cpt; cpt--) {
                    a = rand();
                    if ((t = rechercherNoeud(a)) != NULL) {
                        supprimerNoeud(t);
                        cpt = cpt+2;
                    } else {
                        insererNoeud(a);
                    }
                }
                time(&end);
                tempsTotal=difftime(end, start);

                printf("Execution en -> %f secondes ", tempsTotal);
                printf(" pour %d noeuds\n",nbNoeud);
             
                fprintf(fichier, "    %d ", nbNoeud);
                fprintf(fichier, "%f\n",tempsTotal);
            }
            fclose(fichier);
            system("gnuplot -persist -e \" plot 'temps.dat' u 1:2 w l\"");
        }else{
            printf("Oops ! Erreur dans l'écriture des valeurs !\n");
        }
    }
    
}
