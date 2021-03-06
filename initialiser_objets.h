#ifndef INITIALISER_OBJETS_H_INCLUDED
#define INITIALISER_OBJETS_H_INCLUDED
#include "objets.h"
#include "dimensions.h"
void initialiser_blocs(fenetre f,carre c[NBRE_CASES_Y][NBRE_CASES_X],item it[]);
void initialiser_map(fenetre f[],double Xfen,double Yfen,int cases_max_x,int cases_map_y);
void initialiser_joueur(joueur j[],int jmax,canon canon_j[],double taille_explosion_init,fusee_missile* missile_initiaux,objet_fixe* avion);
void initialiser_item(item i[],int nbre_blocs_actuel);
void initialiser_objet_anime(objet_anime* o,int images_max,ALLEGRO_BITMAP* images_animees[],double vitesse_animation,double taille,double x,double y,int taille_x,int taille_y,int existence);
void initialiser_objet_fixe(objet_fixe* o,ALLEGRO_BITMAP* image,double tailleX,double tailleY,double x,double y,int taille_x,int taille_y,int existence);
void initialiser_objet_fixe_c(objet_fixe o[],ALLEGRO_BITMAP* image[],double taille,int taille_xy,double x,int id);
void mettre_id(objet_fixe o[],int id);
void initialiser_objet_fixe_en_masse(objet_fixe o[],ALLEGRO_BITMAP* image,double tailleX,double tailleY,double x,double y,int taille_x,int taille_y,int nbre_objets);
void initialiser_fusees(fusee_missile f[],int nbre_fusees,ALLEGRO_BITMAP* image_fusee,double taille_fusees,int nbre_explosion,ALLEGRO_BITMAP* explosions[],double vitesse_anim_explosion,double taille_explosion,double puissance,double portee,item_missile it[],double coef_xp,double taille_x_y_explosion);
void initialiser_fumee(objet_anime o[],int nbre_fumee,ALLEGRO_BITMAP* fumees[],double vitesse_anim,double taille);
void initialiser_items_missiles(item_missile it[]);
void base_auto_j1(CLAVIER,joueur* j,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],item it[],int n_tour,int joueur_qui_joue);
void base_auto_j2(CLAVIER,joueur* j,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],item it[],int n_tour,int joueur_qui_joue);
#endif // INITIALISER_OBJETS_H_INCLUDED
