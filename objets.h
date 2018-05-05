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
    int au_joueur;
}carre;
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
    float angle;
    int existence;
}objet_anime;
typedef struct
{
    double x;
    double y;
    int id;
    ALLEGRO_BITMAP* bitmap;
    double taille;
    int taille_x;
    int taille_y;
    int utile;
    int utile2[NBRE_LIAISONS_COMPTENCES_MAX]; //POUR COMPETENCES:  [5,7,0,0] <-- FAIT DES LIAISON AVEC COMPETENCE 5 ET 7
    double angle;
    int existence;
    double vitesse_x;
    double vitesse_y;
}objet_fixe;
typedef struct
{
    objet_anime canon_anime;
    int xi;
    int yi;
    double x;
    double y;
}canon;
typedef struct
{
    double Xfenetre;
    double Yfenetre;
    int cases_x;
    int cases_y;
}fenetre;
typedef struct
{
    objet_fixe fusee;
    objet_anime explosion;
    float inclinaison;
    double vx;
    double vy;
    int explosion_en_cours;
    double compteur_fumee;
    double puissance_explosion;
    double portee_explosion;
}fusee_missile;
typedef struct
{
    int id_selectionee;
    int n_joueur;
    int n_item_placable_sel;
    canon bombardier;
    int canon_place;
    double explosion_debloques[NBRE_COMPETENCES_EXPLO];
    double science_debloques[NBRE_COMPETENCES_SCIENCE];
    double precision_debloques[NBRE_COMPETENCES_PRECISION]; //0: PAS DEBLOQUE   1:DEBLOQUABLE    2:DEBLOQUE
    int fini_de_jouer;
    double taille_explosion;
    double puissance_tir;
    double portee_tir;
    double vx_fusee;
    double vy_fusee;
    double puissance_tir_cannon;
    double angle_tir;
    fusee_missile* missile_selectione;
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
    double pv;
    int placable;
    int nbre_blocs_actuel;
    int n_placable;
    double taille_image_selection;
    int nbre_item_placable;
    int soumis_a_la_gravite; //  0:NON    1:OUI   2:COLLANT
}item;
void placer_item(ALLEGRO_MOUSE_STATE mouse,point_case souris,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],joueur* j,item i[]);
int clic_objet(SOURIS,objet_anime o);
int toucher_objet(SOURIS,objet_anime o);
int interaction_bouton_fin_tour(objet_anime* bouton,SOURIS,int quel_joueur_joue);
void animer_objet(objet_anime* o,int image_depart,int image_fin_anim,int image_a_mettre_apres_animation);
void gerer_blocs(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],int vitesse_inv_gravite,item it[],joueur jo[]);
void switcher_deux_blocs(carre* bloc1,carre* bloc2);
void enlever_carre(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],point_case p,SOURIS,item i[]);
void gerer_competences(SOURIS,joueur* j,objet_fixe o[]);
int toucher_objet_fixe(SOURIS,objet_fixe o);
void gerer_fusees(fusee_missile f[],double attraction,carre c[NBRE_CASES_Y][NBRE_CASES_X],objet_fixe p[]);
int collision_objet_fixe_carre(objet_fixe o,carre c[NBRE_CASES_Y][NBRE_CASES_X]);
void tirer_missile(joueur j,double vx,double vy,double x,double y,fusee_missile f[]);
void pop_fumee(objet_anime o[],fusee_missile f[]);
void deplacer_objet_constament(objet_anime o[],int nbre_objets,double vitesse_x,double vitesse_y);
void deplacer_objet_fixe_constament(objet_fixe o[],int nbre_objets);
void pop_particules(objet_fixe o[],double x,double y,int nbre_particules,double vitesse);
void tirs_de_cannon(CLAVIER,joueur j);
#endif // OBJETS_H_INCLUDED
