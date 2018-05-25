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
	double pv_initiaux;
	int enleve_tempo;
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
	double tailleX;
	double tailleY;
	int taille_x;
	int taille_y;
	int utile;
	int utile2[NBRE_LIAISONS_COMPTENCES_MAX]; //POUR COMPETENCES:  [5,7,0,0] <-- FAIT DES LIAISON AVEC COMPETENCE 5 ET 7
	double angle;
	int existence;
	double vitesse_x;
	double vitesse_y;
	int flag;
}objet_fixe;
typedef struct
{
	objet_anime canon_anime;
	int xi;
	int yi;
	double pv;
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
	double chrono;
	double puissance_explosion_initiale;
	double portee_explosion_initiale;
	double taille_initiale;
	int id;
	int prix;
	double coef_xp;
	double compteur_depuis_tir;
	int utile1; //POUR TAUPINER: 0:NORMAL  1:CREUSE LE TROU   2:EXPLOSE  | POUR MISSILE_STOP: 0:CONTINU  1:GRAVITE
	double utile2; //POUR TAUPINER: chrono creusage
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
	double precision_debloques[NBRE_COMPETENCES_PRECISION]; //0: PAS DEBLOQUE   1:DEBLOQUABLE	2:DEBLOQUE
	int fini_de_jouer;
	double taille_explosion;
	double puissance_tir;
	double portee_tir;
	double vx_fusee;
	double vy_fusee;
	double puissance_tir_cannon;
	double angle_tir;
	fusee_missile* missile_selectione;
	int inventaire[NBRE_CASES_INVENTAIRE*2];
	int n_competence_ocupee;
	int id_missile_selectione;
	double points_destruction;
	double xp;
	double coef_xp;
	double coef_points;
	double points_destruction_debut_tour;
	int nbre_tirs;
	int nbre_tirs_max;
	double tune;
    double coef_gain_tune;
    double xp_pour_lvlup;
    int pts_competences;
    int niveau;
    double coef_xp_lvl_sup;
    int coeur_xi;
    int coeur_yi;
    int coeur_pose;
    int compteur_tour_replacer_canon;
    objet_fixe* avion;
    int largueur_lance;
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
	int soumis_a_la_gravite; //  0:NON	1:OUI   2:COLLANT
	int enleve_tempo;
	int prix;
}item;
typedef struct
{
	int id;
	double prix;
	fusee_missile* missile;
}item_missile;
void placer_item(ALLEGRO_MOUSE_STATE mouse,point_case souris,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],joueur* j,item i[],int tour);
int clic_objet(SOURIS,objet_anime o);
int toucher_objet(SOURIS,objet_anime o);
int interaction_bouton_fin_tour(objet_anime* bouton,SOURIS,int quel_joueur_joue,joueur j[],int* n_tour,item_missile missiles[],carre c[NBRE_CASES_Y][NBRE_CASES_X],CLAVIER);
void animer_objet(objet_anime* o,int image_depart,int image_fin_anim,int image_a_mettre_apres_animation);
void gerer_blocs(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],int vitesse_inv_gravite,item it[],joueur jo[]);
void switcher_deux_blocs(carre* bloc1,carre* bloc2);
void enlever_carre(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],point_case p,SOURIS,item i[],joueur* j,int n_tour);
void gerer_competences(SOURIS,joueur* j,objet_fixe o[],carre blocs[NBRE_CASES_Y][NBRE_CASES_X]);
int toucher_objet_fixe(SOURIS,objet_fixe o);
void gerer_fusees(fusee_missile f[],double attraction,carre c[NBRE_CASES_Y][NBRE_CASES_X],objet_fixe p[],int joueur_qui_joue,joueur j[],CLAVIER);
int collision_objet_fixe_carre(objet_fixe o,carre c[NBRE_CASES_Y][NBRE_CASES_X],int joueur_qui_joue);
void tirer_missile(joueur j,double vx,double vy,double x,double y,fusee_missile f[]);
void pop_fumee(objet_anime o[],fusee_missile f[]);
void deplacer_objet_constament(objet_anime o[],int nbre_objets,double vitesse_x,double vitesse_y);
void deplacer_seul_objet_fixe_constament(objet_anime o,double vitesse_x,double vitesse_y);
void deplacer_objet_fixe_constament(objet_fixe o[],int nbre_objets);
void pop_particules(objet_fixe o[],double x,double y,int nbre_particules,double vitesse);
void tirs_de_cannon(CLAVIER,joueur* j,SOURIS,double attraction);
void gerer_bouton_inventaire(objet_fixe* o,ALLEGRO_BITMAP* selection_jaune,SOURIS,ALLEGRO_BITMAP* inventaire,ALLEGRO_BITMAP* case_inv,int nbre_cases_x,int nbre_cases_y,double taille,double x,double y,ALLEGRO_BITMAP* icones[],joueur* j,ALLEGRO_BITMAP* selection,item_missile missiles[],int n_tour,ALLEGRO_FONT* police,ALLEGRO_COLOR couleur,CLAVIER,ALLEGRO_BITMAP* explications[]);
int passer_souris_sur_carre(SOURIS,double x1 ,double y1, double x2,double y2);
void gere_xp(joueur j[]);
void ajouter_missile_dans_inventaire(joueur* j,int id_item);
void enlever_tempo_blocs_bois(carre c[NBRE_CASES_Y][NBRE_CASES_X],joueur j,CLAVIER);
void gerer_victoire(joueur j[],carre c[NBRE_CASES_Y][NBRE_CASES_X],int joueur_qui_joue,int tour,int* fond,ALLEGRO_COLOR couleur,ALLEGRO_FONT* police);
void gerer_largueur(joueur* j);
#endif // OBJETS_H_INCLUDED


