#ifndef DIMENSIONS_H_INCLUDED
#define DIMENSIONS_H_INCLUDED
//POUR PC LYCEE: 1260*720  1366x768
#define XFENETRE taille_fenetre_x()
#define YFENETRE taille_fenetre_y()

#define FPS 50

#define COEF_PIXEL_X XFENETRE/1662.5
#define COEF_PIXEL_Y YFENETRE/950

#define TAILLE_CASE_X XFENETRE/NBRE_CASES_X
#define TAILLE_CASE_Y YFENETRE/NBRE_CASES_Y

#define NBRE_CASES_X 70
#define NBRE_CASES_Y 40

#define NBRE_ANIM_MAXIMAL 60

#define NRBE_TOURS_POUR_REPLACER_CANON 3

//BLOCS
#define NBRE_BLOCS_ACTUEL 10
#define PV_CANON 500

//COMPETENCES
#define NBRE_COMPETENCES_EXPLO 8
#define NBRE_COMPETENCES_SCIENCE 8
#define NBRE_COMPETENCES_PRECISION 8
#define TAILLE_COMPETENCE 100
#define NBRE_COLONE_COMPETENCE 4
#define NBRE_LIAISONS_COMPTENCES_MAX 4

//FUMEE
#define NBRE_FUSEES 20
#define NBRE_MISSILE_NUCLAIRES 10;
#define NBRE_FUMEE 500
#define TAILLE_FUMEE_XY 50
#define FREQUENCE_APPARITION_FUMEE 0.7
#define COEF_FUSEE_FUMEE_TAILLE 2;

//MISSILES
#define COEF_REDUC_DEGAT_EXPLOSION 0.3
#define COEF_TAILLE_EXPLO_DEGATS 90

#define PUISSANCE_TIR_INITIALE 6000
#define PUISSANCE_TIR_OBUS_ROUGE 12000
#define PUISSANCE_MISSILE_TELEGUIDE PUISSANCE_TIR_INITIALE*5
#define PUISSANCE_TIR_TAUPINIER PUISSANCE_TIR_INITIALE*2.2
#define PUISSANCE_CANON_INITIALE 900
#define PUISSANCE_BOMBE_XP PUISSANCE_TIR_INITIALE*6
#define PUISSANCE_MISSILE_CIBLE PUISSANCE_TIR_INITIALE*3
#define PUISSANCE_MISSILE_STOP PUISSANCE_TIR_INITIALE*4
#define PUISSANCE_TIRS_DROITS PUISSANCE_TIR_INITIALE*2
#define PUISSANCE_MISSILE_SNIPER PUISSANCE_TIR_INITIALE*2
#define PUISSANCE_CONTOURNEUR PUISSANCE_TIR_INITIALE*1.7

#define PORTEE_INITIALE 2*XFENETRE/NBRE_CASES_X
#define PORTEE_TIR_OBUS_ROUGE 3*XFENETRE/NBRE_CASES_X
#define PORTEE_BOMBE_XP 5*XFENETRE/NBRE_CASES_X

#define PUISSANCE_CANON_STOP 600

#define TAILLE_EXPLOSION_INIT 0.12
#define TAILLE_EXPLOSION_X_Y 1000
#define TAILLE_FUSEE_X_Y 200

#define NBRE_TYPES_MISSILES 11

#define PRIX_MISSILES_CIBLE 8
#define PRIX_CONTOURNEUR 20

#define VITESSE_MISSILE_TELEGUIDE 500
#define VITESSE_TAUPIENIER 30
#define TEMPS_CREUSAGE_TAUPINIER 220

//PARTIULES EXPLOSION
#define NBRE_PARTICULES_EXPLOSION_MAX 200
#define NBRE_PARTICULE_POP 80
#define VITESSE_PARTICULE 30
#define NBRE_FUMEE_EXPLOSION 10
#define PRECISION_EXPLOSION_PARTICULE 200

#define LONGEUR_LIGNE_TIR 100
#define LARGEUR_LIGNE_TIR 3

//INVENTAIRE
#define NBRE_CASES_INVENTAIRE 24

//PALIER_COMPETENCE EXPLO
#define PUISSANCE_TIR_n1 11000/PUISSANCE_TIR_INITIALE
#define PUISSANCE_TIR_n2 14000/PUISSANCE_TIR_INITIALE
#define PUISSANCE_TIR_n3 19000/PUISSANCE_TIR_INITIALE
#define PUISSANCE_TIR_NUCLEAIRE 1000000
#define PORTEE_TIR_n1 1.5
#define PORTEE_TIR_n2 2.5
#define PORTEE_TIR_n3 3
#define PORTEE_TIR_NSUP 40



#define PI 3.14159265358979323846264338327950288419716939937510

//PRECISION
#define NBRE_TIRS_COMPETENCE_7_PRECISION 3
#define TAILLE_LIGNE_VISEE_AVION 2

//POUR LA ROGRAMMATION
#define MOD_CHEAT_JUSTE_POUR_COMPETENCE 0

//CONSTRUCTION
#define POINT_CONSTRUCTION_PAR_TOUR 60
#define TAILLE_ECRITUR_SCORE 36

#endif // DIMENSIONS_H_INCLUDED
