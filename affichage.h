#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDE
#include "objets.h"
#include "dimensions.h"
void afficher_fond(ALLEGRO_BITMAP* bitmap,fenetre f);
void afficher_blocs(fenetre f,carre c[NBRE_CASES_Y][NBRE_CASES_X],ALLEGRO_BITMAP* bitmap[]);
void afficher_selection(ALLEGRO_BITMAP* bitmap,point_case souris,fenetre f);
void afficher_blocs_selec(ALLEGRO_BITMAP* selec,ALLEGRO_BITMAP* blocs[],joueur* j,double taille,fenetre f,item it[],ALLEGRO_MOUSE_STATE mouse);
void afficher_objet_anime(objet_anime* o);

#endif // AFFICHAGE_H_INCLUDED
