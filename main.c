#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "physique.h"

/*
    Projet commencé le mardi 6 janvier 2015 par:
        - BOCOS Nicolas
        - FOMO-POUALEU Julien
        - BELAROUCI Hedi
*/

int main(int argv,char** argc){
    int i=0;
    int t=0;
    double pas=0;

#ifdef PAS_PERSO
    int n;
#endif // PAS_PERSO

    t_boulet boulet;
    t_vit_init vitesse_init;
    FILE* fichier=NULL;
    FILE* fich_image=NULL;
    t_data_fichiers data={NULL,NULL};
    
    gestion_io(argv,argc,pas,&boulet,&vitesse_init); // Gere les entrées/sorties avec l'utilisateur

    ecrire_header_fichier(boulet,vitesse_init,fichier);

    printf("La simulation est en cours...\n");
#ifdef DEBUG_MODE
    printf("%lf\n",pas);
#endif // DEBUG_MODE

    do{
        ecrire_trajectoire_ds_fichier(boulet,i,fichier);
        ecrire_trajectoire_dans_png(boulet,i,fich_image);

        t+=pas;
#ifdef DEBUG_MODE
        ecrire_trajectoire_ds_console(boulet,i,fichier);
        printf("%lf\n",pas);
#endif // DEBUG_MODE
        bouger_boulet(&boulet,vitesse_init,t);

#ifdef DEBUG_MODE
        flag_debug();
#endif // DEBUG_MODE

        i++;
    }while(boulet.y>=0);

    fermer_fichier(fichier,boulet,vitesse_init);
    printf("La simulation est finie!\n");

    return EXIT_SUCCESS;
}