#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDE
#include "objets.h"
#include "dimensions.h"
void afficher_fond(ALLEGRO_BITMAP* bitmap,fenetre f);
void afficher_blocs(fenetre f,carre c[NBRE_CASES_Y][NBRE_CASES_X],ALLEGRO_BITMAP* bitmap[]);
void afficher_selection(ALLEGRO_BITMAP* bitmap,point_case souris,fenetre f);
void afficher_blocs_selec(ALLEGRO_BITMAP* selec,ALLEGRO_BITMAP* blocs[],joueur* j,double taille,fenetre f,item it[],ALLEGRO_MOUSE_STATE mouse);
void afficher_objet_anime(objet_anime* o);
void interface_competences(CLAVIER,int* interface_du_jeu,int* fond);
void afficher_objet_fixe(objet_fixe o);
void tracer_ligne_entre_objets(objet_fixe o1, objet_fixe o2,double epaisseur, ALLEGRO_COLOR couleur);
void connexions(objet_fixe o[],int nbre_objets,joueur j);
void afficher_acces_comptetences(ALLEGRO_BITMAP* debloque,ALLEGRO_BITMAP* inaccessible,joueur* j,objet_fixe o[]);
void selection_objets_jaune(ALLEGRO_BITMAP* selection_jaune,objet_fixe o[],int nombre_objets,SOURIS);
void afficher_fusees(fusee_missile f[]);
void afficher_objet_anime_en_masse(objet_anime o[],int nbre_objets);
#endif // AFFICHAGE_H_INCLUDED
