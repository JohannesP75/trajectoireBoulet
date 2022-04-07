#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
#include <stdio.h>
#include "physique.h"

#define LONGUEUR_MAX_NOM_FICHIER 20
#define FILE_ENDING ".fcb" /* ".fcb" veut dire "Fichier de Calculs Ballistiques" */
#define TYPE_IMAGE ".png"
#define DOSSIER_DESTINATION "data/"

// Dimensions de l'image, en pixels
#define LARG_IMAG 150
#define LONG_IMAG 120

enum ligne_commande{
    CL_NOM_PROG,
    CL_MASSE_BOULET,
    CL_NORME_VITESSE_INIT,
    CL_ANGLE_VITESSE_INIT,
    CL_NOM_FICHIER,
    CL_NBRE_ARG
};

enum code_d_erreur{
  ERR_NOM_INVALIDE,
  ERR_OUVER_FICHIER,
  ERR_FERMETURE_FICHIER,
  ERR_ARGS_LIGNE_COM
}

typedef struct t_data_fichiers{
    FILE* fichier_texte;
    FILE* fichier_image;
}t_data_fichiers;

FILE* creer_fichier_texte(char* nom);

FILE* creer_fichier_png(char* nom)

void ecrire_trajectoire_dans_png(t_boulet b,int cycle,FILE* f);

void ecrire_header_fichier(t_boulet b,t_vit_init v,FILE* f);

void ecrire_trajectoire_ds_fichier(t_boulet b,int cycle,FILE* f);

void ecrire_fin_fichier(FILE* f,t_boulet b,t_vit_init v);

void fermer_fichier(FILE* f,t_boulet b,t_vit_init v);

void gestion_erreur(int code);

void gestion_console(t_boulet* b,t_vit_init* v,int* pas,FILE* fich_texte,FILE* fich_png);

void init_data_fichier(t_data_fichiers* D);

void gestion_io(char** argv,int argc,double pas,t_boulet* boulet,t_vit_init* vitesse_init);

int tester_validite_nom_fichier(char* nom);

#ifdef DEBUG_MODE

void flag_debug();

void ecrire_trajectoire_ds_console(t_boulet b,int cycle,FILE* fich_texte,FILE* fich_png);

#endif // DEBUG_MODE

#ifdef MODE_LIGNE_COMMANDE

void gestion_ligne_commande(int argv,char** argc,t_boulet* b,t_vit_init* v,double* pas,char* nom_projet);

#endif // MODE_LIGNE_COMMANDE

#endif // IO_H_INCLUDED