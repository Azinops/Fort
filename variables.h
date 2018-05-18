#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED
#define OBTENIRMOUSEETKEY al_get_mouse_state(&mouse);\
                         al_get_keyboard_state(&key);
#define EVENT ALLEGRO_EVENT event;\
        al_wait_for_event(queue,&event);
#include "dimensions.h"
//FENETRE
double Xfenetre=XFENETRE    ;
double Yfenetre=YFENETRE;
int cases_x=NBRE_CASES_X;
int cases_y=NBRE_CASES_Y;
//PIF
int fin=0;
int i=1;
int j=1;
char chemin[256];

//AFFICHAGE
int fond_actuel=1;
int taille_blocs_a_selectionner=3*COEF_PIXEL_X;

//TOUT
double vitesse_inversee_gravite=4;
int interface_jeu=0; //   0:ZONE COMBAT   1:COMPETENCES
int temps=0;
int relache=1;
int tour=0;

//IMAGES ACTUELLES
int nbre_fonds_actuels=3;
int nbre_blocs_actuels=NBRE_BLOCS_ACTUEL;
int nbre_fin_tour_actuel=18;
int nbre_c_explo_actuels=NBRE_COMPETENCES_EXPLO;
int nbre_c_precision_actuels=NBRE_COMPETENCES_PRECISION;
int nbre_c_scientifique_actuels=NBRE_COMPETENCES_SCIENCE;
int joueur_qui_joue=0;
int nbre_explosion_actuel=9;
int nbre_fusees_actuel=3;
int nbre_fumees_actuel=10;
int nbre_particules_explosion_actuel=1;
int nbre_icones_fusees_actuels=3;
int nbre_explosion_nucleaire_actuel=37;
int nbre_barre_xp_actuel=2;

//FUSEES
double taille_fusees_normales=0.2;
double taille_obus_rouge=0.21;
double taille_bombe_nucleaires=0.2;
double attraction = 15;

//FUMEE
double vitese_anim_fumee=0.2;
double taille_initiale_fumee=0.5;
double vitesse_deplacement_fumee_x=0.1;
double vitesse_deplacement_fumee_y=-1;

double taille_particules_explosion=0.2;
double taille_particules_explosion_x=50;
double taille_particules_explosion_y=50;

//EXPLOSION
double vitesse_anim_explo=0.5;
double taille_explosion_depart=TAILLE_EXPLOSION_INIT;
double taille_explosion_nucleaire=TAILLE_EXPLOSION_INIT*0.4;

//FONDS
int taille_fond_chargement_x=1200;
int taille_fond_chargement_y=800;

//COMPETTENCES
double taille_competences_c=1;
int taille_competences_xy=TAILLE_COMPETENCE;
int anti_marge_competence_x=-600;

//BOUTON FIN TOUR
double vitesse_animation_bouton_fin_tour=0.5;
double taille_bouton_fin_tour=0.8;
int taille_bouton_fin_tour_x=300;
int taille_bouton_fin_tour_y=100;

//BOUTON INVENTAIRE
double tailleX_bouton_invenaire=1.5;
double tailleY_bouton_invenaire=1.5;
double taille_bouton_invenaire_x=50;
double taille_bouton_invenaire_y=50;
double distance_fin_tour_inventaire=50;

//INVENTAIRE
double taille_inventaire=10;
int nbre_cases_x_inventaire=4;
int nbre_cases_y_inventaire=6;
#endif // VARIABLES_H_INCLUDED
