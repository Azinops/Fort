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
    INITIALISER_IMAGES_EN_MASSE(fond,nbre_fonds_actuels,"./images/fonts/")
    AFFICHER_CHARGEMENT
    INITIALISERIMAGE(selecCons,"./images/effets/selectionConstruction.png")
    INITIALISERIMAGE(inaccessible,"./images/effets/inaccessible.png")
    INITIALISERIMAGE(debloque,"./images/effets/debloque.png")
    INITIALISER_IMAGES_EN_MASSE(fusee,nbre_fusees_actuel,"./images/fusees/")
    INITIALISER_IMAGES_EN_MASSE(bloc,nbre_blocs_actuels,"./images/blocs/")
    INITIALISER_IMAGES_EN_MASSE(fin_tour,nbre_fin_tour_actuel,"./images/fin_tour/")
    INITIALISER_IMAGES_EN_MASSE(competence_explo,nbre_c_explo_actuels,"./images/competences/explosion/")
    INITIALISER_IMAGES_EN_MASSE(competence_scientifique,nbre_c_explo_actuels,"./images/competences/scientifique/")
    INITIALISER_IMAGES_EN_MASSE(competence_precision,nbre_c_explo_actuels,"./images/competences/precision/")
    INITIALISER_IMAGES_EN_MASSE(images_explosion,nbre_explosion_actuel,"./images/explosion/")
    INITIALISER_IMAGES_EN_MASSE(image_fumee,nbre_fumees_actuel,"./images/fumee/")

    fenetre carte[0];
    initialiser_map(&carte,Xfenetre,Yfenetre,cases_x,cases_y);

    carre blocs[cases_y][cases_x];
    initialiser_blocs(carte[0],&blocs);

    AJUSTER_ECRAN

    point_case souris_case;

    joueur player[2];
    canon bombardiers[2];
    initialiser_joueur(&player,1,bombardiers,taille_explosion_depart);

    objet_anime bouton_fin_tour;
    initialiser_objet_anime(&bouton_fin_tour,nbre_fin_tour_actuel,fin_tour,vitesse_animation_bouton_fin_tour,taille_bouton_fin_tour,Xfenetre/2,taille_bouton_fin_tour_y*taille_bouton_fin_tour/2,taille_bouton_fin_tour_x,taille_bouton_fin_tour_y,1);

    objet_fixe c_explo[nbre_c_explo_actuels];
    objet_fixe c_science[nbre_c_scientifique_actuels];
    objet_fixe c_precision[nbre_c_precision_actuels];
    initialiser_objet_fixe_c(c_explo,competence_explo,taille_competences_m,taille_competences_xy,((XFENETRE-anti_marge_competence_x)/4)*1+anti_marge_competence_x/2,1);
    initialiser_objet_fixe_c(c_science,competence_scientifique,taille_competences_m,taille_competences_xy,((XFENETRE-anti_marge_competence_x)/4)*2+anti_marge_competence_x/2,2);
    initialiser_objet_fixe_c(c_precision,competence_precision,taille_competences_m,taille_competences_xy,((XFENETRE-anti_marge_competence_x)/4)*3+anti_marge_competence_x/2,3);

    item les_stats_blocs[nbre_blocs_actuels];
    initialiser_item(les_stats_blocs,nbre_blocs_actuels);

    objet_anime explosion;
    initialiser_objet_anime(&explosion,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,0.1,0,0,TAILLE_EXPLOSION_X_Y,TAILLE_EXPLOSION_X_Y,0);

    fusee_missile missile_normaux[NBRE_FUSEES+1];
    initialiser_fusees(missile_normaux,NBRE_FUSEES,fusee[1],taille_fusees_normales,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart);

    objet_anime fumee[NBRE_FUMEE];
    initialiser_fumee(fumee,nbre_fumees_actuel,image_fumee,vitese_anim_fumee,taille_initiale_fumee);
    while(!fin)
    {
        OBTENIRMOUSEETKEY
        ESCAPE
        EVENT
        //TIMER = 1/50 sec
        if(event.type==ALLEGRO_EVENT_TIMER)
        {
            afficher_fond(fond[fond_actuel],carte[0]);
            interface_competences(&key,&interface_jeu,&fond_actuel);
            if(interface_jeu==0)
            {
                rentrer_souris_dans_une_case(&souris_case,carte[0],mouse);
                afficher_blocs(carte[0],blocs,bloc);
                afficher_selection(selecCons,souris_case,carte[0]);
                afficher_blocs_selec(selecCons,bloc,&player[joueur_qui_joue],taille_blocs_a_selectionner,carte[0],les_stats_blocs,mouse);
                afficher_objet_anime(&bouton_fin_tour);
                placer_item(mouse,souris_case,blocs,&player[joueur_qui_joue]);
                enlever_carre(blocs,souris_case,mouse,les_stats_blocs);
                joueur_qui_joue=interaction_bouton_fin_tour(&bouton_fin_tour,mouse,joueur_qui_joue);
                gerer_blocs(blocs,vitesse_inversee_gravite,les_stats_blocs,player);
                if(mouse.buttons&1 && relache==1)
                {
                    relache=0;
                    tirer_missile(player[joueur_qui_joue],700,-400,mouse.x,mouse.y,missile_normaux);
                }
                if(!mouse.buttons&1)
                {
                    relache=1;
                }
                pop_fumee(fumee,missile_normaux);
                afficher_objet_anime_en_masse(&fumee,NBRE_FUMEE);
                gerer_fusees(missile_normaux,attraction,blocs);
                afficher_fusees(missile_normaux);
            }
            if(interface_jeu==1)
            {
                connexions(c_explo,nbre_c_explo_actuels,player[joueur_qui_joue]);
                connexions(c_science,nbre_c_scientifique_actuels,player[joueur_qui_joue]);
                connexions(c_precision,nbre_c_precision_actuels,player[joueur_qui_joue]);
                for(i=1;i<=nbre_c_explo_actuels;i++){afficher_objet_fixe(c_explo[i]);}
                for(i=1;i<=nbre_c_scientifique_actuels;i++){afficher_objet_fixe(c_science[i]);}
                for(i=1;i<=nbre_c_precision_actuels;i++){afficher_objet_fixe(c_precision[i]);}
                gerer_competences(mouse,&player[joueur_qui_joue],c_explo);
                gerer_competences(mouse,&player[joueur_qui_joue],c_science);
                gerer_competences(mouse,&player[joueur_qui_joue],c_precision);
                afficher_acces_comptetences(debloque,inaccessible,&player[joueur_qui_joue],c_science);
                afficher_acces_comptetences(debloque,inaccessible,&player[joueur_qui_joue],c_explo);
                afficher_acces_comptetences(debloque,inaccessible,&player[joueur_qui_joue],c_precision);
                selection_objets_jaune(selecCons,c_explo,NBRE_COMPETENCES_EXPLO,mouse);
                selection_objets_jaune(selecCons,c_science,NBRE_COMPETENCES_SCIENCE,mouse);
                selection_objets_jaune(selecCons,c_precision,NBRE_COMPETENCES_PRECISION,mouse);
            }
        }
        al_flip_display();
    }
}
