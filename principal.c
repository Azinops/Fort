#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "principal.h"
#include "fonctions.h"
#include "variables.h"
#include "affichage.h"
#include "objets.h"
#include "initialiser_objets.h"
void jeu()
{
    INITIALISER_BIBLIOTHEQUE
    INITIALISERIMAGE(selecCons,"./images/effets/selectionConstruction.png")
    INITIALISER_IMAGES_EN_MASSE(fond,nbre_fonds_actuels,"./images/fonts/")
    INITIALISER_IMAGES_EN_MASSE(bloc,nbre_blocs_actuels,"./images/blocs/")
    INITIALISER_IMAGES_EN_MASSE(fin_tour,nbre_fin_tour_actuel,"./images/fin_tour/")
    fenetre carte[0];
    initialiser_map(&carte,Xfenetre,Yfenetre,cases_x,cases_y);
    carre blocs[cases_y][cases_x];
    initialiser_blocs(carte[0],&blocs);
    point_case souris_case;
    joueur player[2];
    initialiser_joueur(&player,1);
    item les_stats_blocs[nbre_blocs_actuels];
    initialiser_item(les_stats_blocs,nbre_blocs_actuels);
    objet_anime bouton_fin_tour;
    initialiser_objet_anime(&bouton_fin_tour,nbre_fin_tour_actuel,fin_tour,vitesse_animation_bouton_fin_tour,taille_bouton_fin_tour,Xfenetre/2-(taille_bouton_fin_tour_x/2)*taille_bouton_fin_tour,0,taille_bouton_fin_tour_x,taille_bouton_fin_tour_y);

    while(!fin)
    {
        OBTENIRMOUSEETKEY
        ESCAPE
        EVENT
        //TIMER = 1/50 sec
        if(event.type==ALLEGRO_EVENT_TIMER)
        {
            rentrer_souris_dans_une_case(&souris_case,carte[0],mouse);
            afficher_fond(fond[1],carte[0]);
            afficher_blocs(carte[0],blocs,bloc);
            afficher_selection(selecCons,souris_case,carte[0]);
            afficher_blocs_selec(selecCons,bloc,&player[joueur_qui_joue],taille_blocs_a_selectionner,carte[0],les_stats_blocs,mouse);
            afficher_objet_anime(&bouton_fin_tour);
            placer_item(mouse,souris_case,blocs,player[joueur_qui_joue]);
            enlever_carre(blocs,souris_case,mouse,les_stats_blocs);
            joueur_qui_joue=interaction_bouton_fin_tour(&bouton_fin_tour,mouse,joueur_qui_joue);
            gerer_blocs(blocs,vitesse_inversee_gravite,les_stats_blocs);
            al_flip_display();
        }
    }
}
