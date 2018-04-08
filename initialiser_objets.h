#ifndef INITIALISER_OBJETS_H_INCLUDED
#define INITIALISER_OBJETS_H_INCLUDED
#include "objets.h"
#include "dimensions.h"
void initialiser_blocs(fenetre f,carre c[NBRE_CASES_Y][NBRE_CASES_X]);
void initialiser_map(fenetre f[],double Xfen,double Yfen,int cases_max_x,int cases_map_y);
void initialiser_joueur(joueur j[],int jmax);
void initialiser_item(item i[],int nbre_blocs_actuel);
void initialiser_objet_anime(objet_anime* o,int images_max,ALLEGRO_BITMAP* images_animees[],double vitesse_animation,double taille,double x,double y,int taille_x,int taille_y);
#endif // INITIALISER_OBJETS_H_INCLUDED
