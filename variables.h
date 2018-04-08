#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED
#define OBTENIRMOUSEETKEY al_get_mouse_state(&mouse);\
                         al_get_keyboard_state(&key);
#define EVENT ALLEGRO_EVENT event;\
        al_wait_for_event(queue,&event);
#include "dimensions.h"
//FENETRE
double Xfenetre=XFENETRE;
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
int taille_blocs_a_selectionner=8;

//TOUT
double vitesse_inversee_gravite=4;

//IMAGES ACTUELLES
int nbre_fonds_actuels=1;
int nbre_blocs_actuels=5;
int nbre_fin_tour_actuel=18;

int joueur_qui_joue=0;
//BOUTON FIN TOUR
double vitesse_animation_bouton_fin_tour=0.5;
double taille_bouton_fin_tour=0.8;
int taille_bouton_fin_tour_x=300;
int taille_bouton_fin_tour_y=100;
#endif // VARIABLES_H_INCLUDED
