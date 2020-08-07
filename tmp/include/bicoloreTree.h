#ifndef _BICOLORETREE_H_
#define _BICOLORETREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>

#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

// Création d'un type couleur.
typedef enum { ROUGE , NOIR } couleurNoeud;

// Création de la structure pour le noeud avec les attributs.
typedef struct Noeud_ {
    struct Noeud_ *filsGauche;    
    struct Noeud_ *filsDroite;    
    struct Noeud_ *noeudPere;   
    couleurNoeud   couleur;            
    int            valeur;                    
} Noeud;

// Création d'un noeud par défaut.
#define NIL &noeudParDefault      
Noeud noeudParDefault = { NULL , NULL , NULL , NOIR , 0 };

// Rotation
void  rotationGauche      (Noeud *x);
void  rotationDroite      (Noeud *x);

// Réparation après insertion ou suppression (Trigger)
void  reparationInserer   (Noeud *x);
void  reparationSupprimer (Noeud *x);

// Gestion des noeuds
Noeud *insererNoeud       (int data);
void  supprimerNoeud      (Noeud *z);
Noeud *rechercherNoeud    (int data);

// Autre
void  affichageConsole    (int nbNode);
void  main                (int argc, char **argv);

#endif