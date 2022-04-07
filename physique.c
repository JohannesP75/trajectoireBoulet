#include <stdlib.h>
#include <math.h>
#include "physique.h"
#include "io.h"

t_boulet init_boulet(double masse){
    t_boulet b;

    b.x=START_ABSCISSE;
    b.y=START_ORDONNEE;
    b.masse=masse;

    return b;
}

t_vit_init init_vit_init(double norme,double angle){
    t_vit_init v;

    v.norme=norme;
    v.angle=degre_a_radian(angle);
    v.x=norme*cos(v.angle);
    v.y=angle*sin(v.angle);

    return v;
}

void bouger_boulet(t_boulet* b,t_vit_init v,int t){
    b->x=v.norme*cos(v.angle)*t;
    b->y=(v.norme*sin(v.angle)-(G/2)*t)*t;
}

double degre_a_radian(double A){
    return A*(M_PI/180);
}

double radian_a_degre(double A){
    return A*(180/M_PI);
}

double calculer_duree_trajet(t_boulet b,t_vit_init v){
    return (2*v.norme*sin(v.angle))/G;
}

double calculer_distance_trajet(t_boulet b,t_vit_init v){
    return (2*pow(v.norme,2)*cos(v.angle)*sin(v.angle))/G;
}

double calculer_pas(t_vit_init v,t_boulet b,int n){
#ifdef PAS_PERSO
    return ((calculer_duree_trajet(b,v)/n)<PAS_STANDARD)?PAS_STANDARD:(calculer_duree_trajet(b,v)/n);
#else
    return PAS_STANDARD;
#endif
}