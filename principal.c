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
#include <windows.h>
void jeu()
{
    int taille_blocs_a_selectionner=3*COEF_PIXEL_X;
    double Xfenetre=XFENETRE  ;
    double Yfenetre=YFENETRE;
    int cases_x=NBRE_CASES_X;
    int cases_y=NBRE_CASES_Y;
    INITIALISER_BIBLIOTHEQUE
    INITIALISER_IMAGES_EN_MASSE(fond,nbre_fonds_actuels,"./images/fonts/")
    AFFICHER_CHARGEMENT
    INITIALISERIMAGE(image_bouton_inventaire,"./images/boutons/inventaire.png")
    INITIALISERIMAGE(selecCons,"./images/effets/selectionConstruction.png")
    INITIALISERIMAGE(inaccessible,"./images/effets/inaccessible.png")
    INITIALISERIMAGE(debloque,"./images/effets/debloque.png")
    INITIALISERIMAGE(inventaire,"./images/inventaire/inventaire.png")
    INITIALISERIMAGE(case_inventaire,"./images/inventaire/case.png")
    INITIALISERIMAGE(cible,"./images/effets/cible.png")
    INITIALISERIMAGE(selection_inventaire,"./images/inventaire/selection.png")
    INITIALISERIMAGE(largueur,"./images/trucs/avion_largueur.png")
    INITIALISER_IMAGES_EN_MASSE(indictaions_competences,NBRE_COMPETENCES_EXPLO+NBRE_COMPETENCES_PRECISION+NBRE_COMPETENCES_SCIENCE,"./images/explications_competences/")
    INITIALISER_IMAGES_EN_MASSE(indictaion_competences,4,"./images/explications_competences/")
    INITIALISER_IMAGES_EN_MASSE(indictaion_competencess,2,"./images/explications_competences/")
    INITIALISER_IMAGES_EN_MASSE(fusee,nbre_fusees_actuel,"./images/fusees/")
    INITIALISER_IMAGES_EN_MASSE(bloc,nbre_blocs_actuels,"./images/blocs/")
    INITIALISER_IMAGES_EN_MASSE(fin_tour,nbre_fin_tour_actuel,"./images/fin_tour/")
    INITIALISER_IMAGES_EN_MASSE(competence_explo,nbre_c_explo_actuels,"./images/competences/explosion/")
    INITIALISER_IMAGES_EN_MASSE(competence_scientifique,nbre_c_explo_actuels,"./images/competences/scientifique/")
    INITIALISER_IMAGES_EN_MASSE(competence_precision,nbre_c_explo_actuels,"./images/competences/precision/")
    INITIALISER_IMAGES_EN_MASSE(images_explosion,nbre_explosion_actuel,"./images/explosion/")
    INITIALISER_IMAGES_EN_MASSE(image_fumee,nbre_fumees_actuel,"./images/fumee/")
    INITIALISER_IMAGES_EN_MASSE(particules_explosion,nbre_particules_explosion_actuel,"./images/particules_explosion/")
    INITIALISER_IMAGES_EN_MASSE(icones_fusees,nbre_fusees_actuel,"./images/icones_inventaires/")
    INITIALISER_IMAGES_EN_MASSE(explosion_nucleaire,nbre_explosion_nucleaire_actuel,"./images/explosion_nucleaire/")
    INITIALISER_IMAGES_EN_MASSE(barre_xp,nbre_barre_xp_actuel,"./images/barre_xp/")
    INITIALISER_IMAGES_EN_MASSE(deflagration,nbre_deflagration_actuel,"./images/deflagration/")
    INITIALISER_IMAGES_EN_MASSE(indication_blocs,nbre_blocs_actuels,"./images/explications_blocs/")
    INITIALISER_IMAGES_EN_MASSE(explications_fusees,nbre_fusees_actuel,"./images/explications_fusees/")
    INITIALISERIMAGE(image_bouton_menu,"./images/effets/bouton_jouer.png")
    INITIALISERIMAGE(image_bouton_quite,"./images/effets/bouton_quitter.png")
    fenetre carte[0];
    initialiser_map(&carte,Xfenetre,Yfenetre,cases_x,cases_y);

    carre blocs[cases_y][cases_x];

    AJUSTER_ECRAN

    point_case souris_case;

    joueur player[2];
    canon bombardiers[2];

    objet_fixe avion_largueur;
    initialiser_objet_fixe(&avion_largueur,largueur,taille_avion_largueur,taille_avion_largueur,0,0,taille_largueur_x,taille_largueur_x,0);

    objet_anime bouton_fin_tour;
    initialiser_objet_anime(&bouton_fin_tour,nbre_fin_tour_actuel,fin_tour,vitesse_animation_bouton_fin_tour,taille_bouton_fin_tour,Xfenetre/2,taille_bouton_fin_tour_y*taille_bouton_fin_tour/2*COEF_PIXEL_Y,taille_bouton_fin_tour_x,taille_bouton_fin_tour_y,1);

    objet_fixe c_explo[nbre_c_explo_actuels+1];
    objet_fixe c_science[nbre_c_scientifique_actuels+1];
    objet_fixe c_precision[nbre_c_precision_actuels+1];
    initialiser_objet_fixe_c(c_explo,competence_explo,taille_competences_c*COEF_PIXEL_X,taille_competences_xy,((XFENETRE-anti_marge_competence_x)/4)*1+anti_marge_competence_x/2,1);
    initialiser_objet_fixe_c(c_science,competence_scientifique,taille_competences_c*COEF_PIXEL_X,taille_competences_xy,((XFENETRE-anti_marge_competence_x)/4)*2+anti_marge_competence_x/2,2);
    initialiser_objet_fixe_c(c_precision,competence_precision,taille_competences_c*COEF_PIXEL_X,taille_competences_xy,((XFENETRE-anti_marge_competence_x)/4)*3+anti_marge_competence_x/2,3);

    item les_stats_blocs[nbre_blocs_actuels];
    initialiser_item(les_stats_blocs,nbre_blocs_actuels);
    initialiser_blocs(carte[0],&blocs,les_stats_blocs);

    item_missile les_stats_misssiles[NBRE_TYPES_MISSILES+1];
    initialiser_items_missiles(les_stats_misssiles);

    objet_anime explosion;
    initialiser_objet_anime(&explosion,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,0.1,0,0,TAILLE_EXPLOSION_X_Y,TAILLE_EXPLOSION_X_Y,0);

    objet_fixe particule_explosion[NBRE_PARTICULES_EXPLOSION_MAX];
    initialiser_objet_fixe_en_masse(particule_explosion,particules_explosion[1],taille_particules_explosion,taille_particules_explosion,0,0,taille_particules_explosion_x,taille_particules_explosion_y,NBRE_PARTICULES_EXPLOSION_MAX);

    fusee_missile missile_normaux[NBRE_FUSEES+1];
    initialiser_fusees(missile_normaux,NBRE_FUSEES,fusee[1],taille_fusees_normales,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_TIR_INITIALE,PORTEE_INITIALE,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    fusee_missile obus_rouges[NBRE_FUSEES+1];
    initialiser_fusees(obus_rouges,NBRE_FUSEES,fusee[2],taille_obus_rouge,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_TIR_OBUS_ROUGE,PORTEE_TIR_OBUS_ROUGE,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    fusee_missile bombe_nucleaire[NBRE_FUSEES+1];
    initialiser_fusees(bombe_nucleaire,NBRE_FUSEES,fusee[3],taille_bombe_nucleaires,nbre_explosion_nucleaire_actuel,explosion_nucleaire,vitesse_anim_explo*0.5,taille_explosion_nucleaire,PUISSANCE_TIR_NUCLEAIRE,PORTEE_TIR_NSUP,les_stats_misssiles,coef_xp_missile_nucleaire,TAILLE_EXPLOSION_X_Y);

    fusee_missile missile_teleguide[NBRE_FUSEES+1];
    initialiser_fusees(missile_teleguide,NBRE_FUSEES,fusee[4],taille_missile_teleguide,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_MISSILE_TELEGUIDE,PORTEE_INITIALE*2,les_stats_misssiles,coef_xp_missile_teleguide,TAILLE_EXPLOSION_X_Y);

    fusee_missile taupinier[NBRE_FUSEES+1];
    initialiser_fusees(taupinier,NBRE_FUSEES,fusee[5],taille_taupinier,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_TIR_TAUPINIER,PORTEE_INITIALE,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    fusee_missile bombe_xp[NBRE_FUSEES+1];
    initialiser_fusees(bombe_xp,NBRE_FUSEES,fusee[6],taille_bombe_xp,nbre_deflagration_actuel,deflagration,vitesse_anim_deflagration,taille_explosion_xp,PUISSANCE_BOMBE_XP,PORTEE_BOMBE_XP,les_stats_misssiles,coef_xp_bombe_xp,taille_x_y_explosion_xp);

    fusee_missile tirs_droits[NBRE_FUSEES+1];
    initialiser_fusees(tirs_droits,NBRE_FUSEES,fusee[7],taille_fusees_droites,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_TIRS_DROITS,PORTEE_INITIALE*1.5,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    fusee_missile missile_stop[NBRE_FUSEES+1];
    initialiser_fusees(missile_stop,NBRE_FUSEES,fusee[8],taille_fusees_stop,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_MISSILE_STOP,PORTEE_INITIALE*2,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    fusee_missile missile_cible[NBRE_FUSEES+1];
    initialiser_fusees(missile_cible,NBRE_FUSEES,fusee[9],taille_fusees_cible,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_MISSILE_CIBLE,PORTEE_INITIALE*2,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    fusee_missile missile_sniper[NBRE_FUSEES+1];
    initialiser_fusees(missile_sniper,NBRE_FUSEES,fusee[10],taille_fusees_sniper,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_MISSILE_SNIPER,PORTEE_INITIALE,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    fusee_missile contourneur[NBRE_FUSEES+1];
    initialiser_fusees(contourneur,NBRE_FUSEES,fusee[11],taille_contourneur,nbre_explosion_actuel,images_explosion,vitesse_anim_explo,taille_explosion_depart,PUISSANCE_CONTOURNEUR,PORTEE_INITIALE,les_stats_misssiles,coef_xp_missile_initial,TAILLE_EXPLOSION_X_Y);

    objet_anime fumee[NBRE_FUMEE];
    initialiser_fumee(fumee,nbre_fumees_actuel,image_fumee,vitese_anim_fumee,taille_initiale_fumee);
    initialiser_joueur(&player,1,bombardiers,taille_explosion_depart,&missile_normaux,&avion_largueur);

    objet_fixe bouton_inventaire;
    initialiser_objet_fixe(&bouton_inventaire,image_bouton_inventaire,tailleX_bouton_invenaire,tailleY_bouton_invenaire,Xfenetre/2+(distance_fin_tour_inventaire+taille_bouton_fin_tour_x/2*taille_bouton_fin_tour+tailleX_bouton_invenaire*taille_bouton_invenaire_x/2)*COEF_PIXEL_X,(tailleY_bouton_invenaire*taille_bouton_invenaire_y/2)*COEF_PIXEL_Y,taille_bouton_invenaire_y,taille_bouton_invenaire_y,1);

    objet_fixe bouton_menu;
    initialiser_objet_fixe(&bouton_menu,image_bouton_menu,3*COEF_PIXEL_X,3*COEF_PIXEL_Y,Xfenetre/3,Yfenetre/2+COEF_PIXEL_Y*20,taille_bouton_quitter_et_jouer_x,taille_bouton_quitter_et_jouer_y,1);
    fond_actuel=5;
    objet_fixe bouton_quite;
    initialiser_objet_fixe(&bouton_quite,image_bouton_quite,3*COEF_PIXEL_X,3*COEF_PIXEL_Y,2*Xfenetre/3,Yfenetre/2+COEF_PIXEL_Y*20,taille_bouton_quitter_et_jouer_x,taille_bouton_quitter_et_jouer_y,1);

    while(at_charge<=(2/FPS))//CHARGEMENT: ATTENDRE UN PEU POUR PAS QUE CA BUG
    {
        EVENT
        at_charge+=1;
    }

    while(bouton_menu.existence==1)  //MENU
    {
        OBTENIRMOUSEETKEY
        ESCAPE
        EVENT
        afficher_fond(fond[fond_actuel],carte[0],joueur_qui_joue);
        afficher_objet_fixe(bouton_menu);
        afficher_objet_fixe(bouton_quite);
        if(clic_objet_fixe(mouse,bouton_menu))
        {
            bouton_menu.existence=0;
        }
        if(clic_objet_fixe(mouse,bouton_quite))
        {
            bouton_menu.existence=0;
            fin=1;
        }
        selection_objet_jaune(selecCons,bouton_menu,mouse);
        selection_objet_jaune(selecCons,bouton_quite,mouse);
        al_flip_display();
    }


    while(!fin)
    {
        OBTENIRMOUSEETKEY
        ESCAPE
        EVENT
        //TIMER = 1/FPS sec
        if(event.type==ALLEGRO_EVENT_TIMER)
        {
            afficher_fond(fond[fond_actuel],carte[0],joueur_qui_joue);
            if(interface_jeu==0) //JEU NORMAL
            {
                gerer_victoire(player,blocs,joueur_qui_joue,tour,&fond_actuel,rouge,arial66);
                joueur_qui_joue=interaction_bouton_fin_tour(&bouton_fin_tour,mouse,joueur_qui_joue,player,&tour,les_stats_misssiles,blocs,&key);
                afficher_tune(arial36,rougefonce,player[joueur_qui_joue]);
                afficher_scores(arial36,jaune,player[joueur_qui_joue],Xfenetre/2+(distance_fin_tour_inventaire+taille_bouton_fin_tour_x/2*taille_bouton_fin_tour+tailleX_bouton_invenaire*taille_bouton_invenaire_x)*COEF_PIXEL_X);
                rentrer_souris_dans_une_case(&souris_case,carte[0],mouse);
                afficher_objet_fixe_en_masse(particule_explosion,NBRE_PARTICULES_EXPLOSION_MAX);
                afficher_blocs(carte[0],blocs,bloc);
                afficher_selection(selecCons,souris_case,carte[0]);
                afficher_blocs_selec(selecCons,bloc,&player[joueur_qui_joue],taille_blocs_a_selectionner,carte[0],les_stats_blocs,mouse,indication_blocs);
                afficher_objet_anime(&bouton_fin_tour);
                afficher_barre_xp(barre_xp,player[joueur_qui_joue],bleuClair,arial36);
                afficher_conseil(player[joueur_qui_joue],rouge,arial36);
                placer_item(mouse,souris_case,blocs,&player[joueur_qui_joue],les_stats_blocs,tour);
                enlever_carre(blocs,souris_case,mouse,les_stats_blocs,&player[joueur_qui_joue],tour);
                gerer_blocs(blocs,vitesse_inversee_gravite,les_stats_blocs,player);
                tirs_de_cannon(&key,&player[joueur_qui_joue],mouse,attraction);
                deplacer_objet_constament(fumee,NBRE_FUMEE,vitesse_deplacement_fumee_x,vitesse_deplacement_fumee_y);
                afficher_objet_anime_en_masse(&fumee,NBRE_FUMEE);
                gerer_fusees(player[joueur_qui_joue].missile_selectione,attraction,blocs,particule_explosion,joueur_qui_joue,player,&key);
                pop_fumee(fumee,player[joueur_qui_joue].missile_selectione);
                afficher_fusees(player[joueur_qui_joue].missile_selectione);
                deplacer_objet_fixe_constament(particule_explosion,NBRE_PARTICULES_EXPLOSION_MAX);
                afficher_objet_fixe(bouton_inventaire);
                gerer_bouton_inventaire(&bouton_inventaire,selecCons,mouse,inventaire,case_inventaire,
                                        nbre_cases_x_inventaire,nbre_cases_y_inventaire,taille_inventaire,Xfenetre/2,Yfenetre/2,
                                        icones_fusees,&player[joueur_qui_joue],selection_inventaire,les_stats_misssiles,tour,
                                        arial22,noir,&key,explications_fusees);
                gere_xp(player);
                afficher_pointeur_souris(player[joueur_qui_joue],mouse,cible);
                afficher_pv_coeur_et_canon(blocs,player[joueur_qui_joue],mouse,souris_case,arial36,tour);
                afficher_objet_fixe(avion_largueur);
                base_auto_j1(&key,&player[0],blocs,les_stats_blocs,tour,joueur_qui_joue);
                base_auto_j2(&key,&player[1],blocs,les_stats_blocs,tour,joueur_qui_joue);
                gerer_largueur(&player[joueur_qui_joue]);
                debut=entrer_dans_le_jeu(fond,debut,0.4,nbre_fonds_actuels,&key);
            }
            if(interface_jeu==1) //INTERFACE COMPETENCE
            {
                afficher_pts_competences(player[joueur_qui_joue],jaune,arial66);
                connexions(c_explo,nbre_c_explo_actuels,player[joueur_qui_joue]);
                connexions(c_science,nbre_c_scientifique_actuels,player[joueur_qui_joue]);
                connexions(c_precision,nbre_c_precision_actuels,player[joueur_qui_joue]);
                afficher_objet_fixe_en_masse_c(c_explo,NBRE_COMPETENCES_EXPLO);
                afficher_objet_fixe_en_masse_c(c_science,NBRE_COMPETENCES_SCIENCE);
                afficher_objet_fixe_en_masse_c(c_precision,NBRE_COMPETENCES_PRECISION);
                gerer_competences(mouse,&player[joueur_qui_joue],c_explo,blocs);
                gerer_competences(mouse,&player[joueur_qui_joue],c_science,blocs);
                gerer_competences(mouse,&player[joueur_qui_joue],c_precision,blocs);
                afficher_acces_comptetences(debloque,inaccessible,&player[joueur_qui_joue],c_science);
                afficher_acces_comptetences(debloque,inaccessible,&player[joueur_qui_joue],c_explo);
                afficher_acces_comptetences(debloque,inaccessible,&player[joueur_qui_joue],c_precision);
                selection_objets_jaune(selecCons,c_explo,NBRE_COMPETENCES_EXPLO,mouse);
                selection_objets_jaune(selecCons,c_science,NBRE_COMPETENCES_SCIENCE,mouse);
                selection_objets_jaune(selecCons,c_precision,NBRE_COMPETENCES_PRECISION,mouse);
                afficher_explications_competences(c_explo,c_science,c_precision,indictaions_competences,mouse);
            }
            interface_competences(&key,&interface_jeu,&fond_actuel,mouse,selecCons,player[joueur_qui_joue],arial36);
        }
        al_flip_display();
    }
}
