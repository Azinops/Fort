#ifndef OBJETS_H_INCLUDED
#define OBJETS_H_INCLUDED
#include "dimensions.h"
#include "fonctions.h"
typedef struct
{
    double x;
    double y;
    int xi;
    int yi;
    int id;
    int etat;
    double pv;
    int compteur_gravite;
}carre;
typedef struct
{
    double Xfenetre;
    double Yfenetre;
    int cases_x;
    int cases_y;
}fenetre;
typedef struct
{
    int id_selectionee;
    int n_joueur;
    int n_item_placable_sel;
}joueur;
void placer_bloc(ALLEGRO_MOUSE_STATE mouse,carre c[NBRE_CASES_Y][NBRE_CASES_X],joueur j,fenetre f);
typedef struct
{
    int x;
    int y;
}point_case;
void rentrer_souris_dans_une_case(point_case* souris,fenetre f,ALLEGRO_MOUSE_STATE mouse);
typedef struct
{
    int id;
    int placable;
    int nbre_blocs_actuel;
    int n_placable;
    double taille_image_selection;
    int nbre_item_placable;
    int soumis_a_la_gravite; //  0:NON    1:OUI   2:COLLANT
}item;
void placer_item(ALLEGRO_MOUSE_STATE mouse,point_case souris,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],joueur j);
typedef struct
{
    double x;
    double y;
    ALLEGRO_BITMAP* bitmap[NBRE_ANIM_MAXIMAL];
    int etat_animation;
    double vitesse_animation;
    double taille;
    int nbre_images_max;
    int taille_x;
    int taille_y;
    int animation[4]; //0:ANIMATION OUI/NON  1:DEPART DE L'ANIMATION:quelle image  2:FIN ANIMATION:quelle image 3:METTRE A QUELLE IMAGE APRES ANIMATION
    double compteur_animation;
}objet_anime;
int clic_objet(SOURIS,objet_anime o);
int toucher_objet(SOURIS,objet_anime o);
int interaction_bouton_fin_tour(objet_anime* bouton,SOURIS,int quel_joueur_joue);
void animer_objet(objet_anime* o,int image_depart,int image_fin_anim,int image_a_mettre_apres_animation);
void gerer_blocs(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],int vitesse_inv_gravite,item it[]);
void switcher_deux_blocs(carre* bloc1,carre* bloc2);
void enlever_carre(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],point_case p,SOURIS,item i[]);
#endif // OBJETS_H_INCLUDED
