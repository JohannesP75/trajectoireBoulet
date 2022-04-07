#ifndef BOULET_H_INCLUDED
#define BOULET_H_INCLUDED
#include "io.h"

// Modes de compilation
#define PAS_PERSO
//#define DEBUG_MODE
//#define MODE_LIGNE_COMMANDE
// Fin des modes de compilation

// Définition de constantes
#define START_ABSCISSE 0 // Abscisse de départ du bouler
#define START_ORDONNEE 0 // Ordonnée de départ du boulet
#define G 9.80665 // Constante de gravitation
#define PAS_STANDARD 1

typedef struct t_boulet{
    double x; // Abscisse du boulet
    double y; // Ordonnée du boulet
    double masse; // Masse, en kg, du boulet - inutile pour le moment car frot. pas encore implémentés
} t_boulet;

typedef struct t_vit_init{
    double x; // Abscisse vitesse initiale
    double y; // Ordonnée vitesse initiale
    double norme; // Norme, en m.s-1, de la vitesse initiale
    double angle; // Angle, en radians, du vecteur de la vitesse initiale
} t_vit_init;

typedef struct t_frottements{
    double viscosite; // Viscosité du fluide
} t_frottements;

t_boulet init_boulet(double masse);

t_vit_init init_vit_init(double norme,double angle);

void bouger_boulet(t_boulet* b,t_vit_init v,int t);

double degre_a_radian(double A);

double radian_a_degre(double A);

double calculer_duree_trajet(t_boulet b,t_vit_init v);

double calculer_distance_trajet(t_boulet b,t_vit_init v);

double calculer_pas(t_vit_init v,t_boulet b,int n);

#endif // BOULET_H_INCLUDED