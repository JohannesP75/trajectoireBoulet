#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // To date the creation of .fcb files
#include "physique.h"
#include "io.h"

FILE* creer_fichier_texte(char* nom){
    FILE* f=NULL;
    char* m=malloc((sizeof(FILE_ENDING)+sizeof(LONGUEUR_MAX_NOM_FICHIER)+siezof(DOSSIER_DESTINATION)+1)*sizeof(char));

    m=strcat(DOSSIER_DESTINATION,strcat(nom,FILE_ENDING));
    f=fopen(m,"w");

    if(f==NULL){
        gestion_erreur(ERR_NOM_INVALIDE);
    }
    return f;
}

FILE* creer_fichier_png(char* nom){
    FILE* f=NULL;
    char* m=malloc((sizeof(TYPE_IMAGE)+sizeof(LONGUEUR_MAX_NOM_FICHIER)+siezof(DOSSIER_DESTINATION)+1)*sizeof(char));

    m=strcat(DOSSIER_DESTINATION,strcat(nom,TYPE_IMAGE));
    f=fopen(m,"w");

    if(f==NULL){
        gestion_erreur(ERR_NOM_INVALIDE);
    }
    return f;
}

void ecrire_header_fichier(t_boulet b,t_vit_init v,FILE* f){
    fprintf(f,"Masse du boulet (kg)             : %lf \n",b.masse);
    fprintf(f,"Norme de la vitesse initiale (N) : %lf \n",v.norme);
    fprintf(f,"Angle de la vitesse initiale     : %lf rad - %lf°\n",v.angle,radian_a_degre(v.angle));
    fprintf(f,"\n");
    fprintf(f,"Cycle || x | y\n");
    fprintf(f,"--------------------\n");
}

void ecrire_trajectoire_ds_fichier(t_boulet b,int cycle,FILE* f){
    fprintf(f,"%d || %lf | %lf\n",cycle,b.x,b.y);
}

void ecrire_fin_fichier(FILE* f,t_boulet b,t_vit_init v){
    fprintf(f,"--------------------\n");
    fprintf(f,"\n");
    fprintf(f,"Temps de trajet    : %lf s\n",calculer_duree_trajet(b,v));
    fprintf(f,"Longueur de trajet : %lf m\n",calculer_distance_trajet(b,v));
    fprintf(f,"\n");
    fprintf(f,"####################\n");
}

void fermer_fichier(FILE* f,t_boulet b,t_vit_init v){

    ecrire_fin_fichier(f,b,v);
    int i=fclose(f);

    if(i!=0){
        gestion_erreur(ERR_FERMETURE_FICHIER);
    }
}

void gestion_erreur(int code){
    printf("\tERROR\t");
    
    switch(code){
      case ERR_NOM_INVALIDE:
        printf("Nom du fichier invalide\n");
      break;
      case ERR_OUVER_FICHIER:
        printf("Encombres lors de l'ouverture du fichier\n");
      break;
      case ERR_FERMETURE_FICHIER:
        printf("Encombres lors de la fermeture du fichier\n");
      break;
      case ERR_ARGS_LIGNE_COM:
        printf("Nombre d'arguments invalide\n");
      break;
      default:
        printf("Erreur inconnue\n");
      break;
    }
    
    exit(EXIT_FAILURE);
}

void ecrire_trajectoire_dans_png(t_boulet b,int cycle,FILE* f,){
    unsigned  int  i,j;
    unsigned  char  I[M][N];  /*tableau  à  remplir*/
    f=fopen("viewport.pgm","w");
    fprintf(f,"P2\n#\n%d  %d\n255\n",MAXX,  MAXY);

    for(i=0;i<M;i++){
        for(j=0;j<N;j++){
            fprintf(f,"%d  ",I[i][j]);
        }
    fprintf(f,"\n");
    }
    fclose(f);
}

void gestion_console(t_boulet* b,t_vit_init* v,int* pas,FILE* fich_txt,FILE* fich_png){
    int A,N,masse,n=20;
    char* nom=malloc(LONGUEUR_MAX_NOM_FICHIER*sizeof(char));

    printf("Ce programme détermine la trajectoire d'un boulet de canon apres sa lancée.\n");
    printf("Entrez la masse du boulet (en kg) :\n");
    /* La masse du boulet n'a aucune influence sur la trajectoire d'un boulet,
    si les frottements sont exclus */
    scanf("%lf",&masse);
    printf("Entrez la norme du vecteur initial (en N) :\n");
    scanf("%lf",&N);
    printf("Entrez l'angle du vecteur initial (en degrés) :\n");
    scanf("%lf",&A);
    printf("Entrer le nom du fichier :\n");
    scanf("%s",nom);
    
    if(!tester_validite_nom_fichier(nom)){
    }

#ifdef PAS_PERSO
    printf("Sur conbien de points voulez-vous faire la simulation?\n");
    scanf("%d",&n);
#endif // MODE_LIGNE_COMMANDE

    // Crée le fichier
    fich_txt=creer_fichier_texte(nom);

    // Création du boulet de canon
    b=init_boulet(masse);
    // Initialisation de la vitesse initiale
    v=init_vit_init(N,A);
    // Calcul du pas perso
    pas=calculer_pas(vitesse_init,boulet,n);
}

void init_data_fichier(t_data_fichiers* D){
    D->fichier_texte=NULL;
    D->fichier_image=NULL;
}

void gestion_io(char** argv,int argc,double pas,t_boulet* boulet,t_vit_init* vitesse_init){
#ifndef MODE_LIGNE_COMMANDE
    gestion_console(boulet,vitesse_init,pas)
#else
    gestion_ligne_commande(argv,argc,boulet,vitesse_init,pas);
#endif // MODE_LIGNE_COMMANDE
}

int tester_validite_nom_fichier(char* nom){
  int i;
  int taille=(sizeof(nom)/sizeof(nom[0]));
  
  for(i=0;i<taille;i++){
    if(nom[i]=='/'||nom[i]=='.'){
      return 0; // Le nom est invalide
    }
  }
  
  return 1;
}

#ifdef DEBUG_MODE
void flag_debug(){
    printf("--------\n");
}

void ecrire_trajectoire_ds_console(t_boulet b,int cycle,FILE* f){
    ecrire_trajectoire_ds_fichier(b,cycle,stdout);
}
#endif // DEBUG_MODE

#ifdef MODE_LIGNE_COMMANDE
void gestion_ligne_commande(int argv,char** argc,t_boulet* b,t_vit_init* v,double* pas,FILE* fich_texte,FILE* fich_png){
    char* m=malloc((sizeof(FILE_ENDING)+LONGUEUR_MAX_NOM_FICHIER+1)*sizeof(char));

    switch(argc){
        case CL_NBRE_ARG:
            *v=init_vit_init((double)atof(argc[CL_NORME_VITESSE_INIT]),(double)atof(argc[CL_ANGLE_VITESSE_INIT]));
            *b=init_boulet((double)atof(argc[CL_MASSE_BOULET]));
            fich_texte=creer_fichier_texte(argc[CL_NOM_FICHIER]);
            fich_png=creer_fichier_png(argc[CL_NOM_FICHIER]);
        break;
        default:
            gestion_erreur(ERR_ARGS_LIGNE_COM);
        break;
    }
}
#endif // MODE_LIGNE_COMMANDE