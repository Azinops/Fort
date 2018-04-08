#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "initialiser_objets.h"
#include "fonctions.h"
#include "map.h"
void initialiser_blocs(fenetre f,carre c[NBRE_CASES_Y][NBRE_CASES_X])
{
    int i=0;
    int j=0;
    for(i=0;i<f.cases_x;i++)
    {
        for(j=0;j<f.cases_y;j++)
        {
            c[j][i].xi=i;
            c[j][i].yi=j;
            c[j][i].x=i*(f.Xfenetre/f.cases_x);
            c[j][i].y=j*(f.Yfenetre/f.cases_y);
            c[j][i].id=MAP_ID[0][j][i];
            c[j][i].pv=1;
            c[j][i].compteur_gravite=1;
            if(c[j][i].id==1)
            {
                c[j][i].pv=100;
            }
            if(c[j][i].id==2)
            {
                c[j][i].pv=300;
            }
            if(c[j][i].id==3)
            {
                c[j][i].pv=250;
            }
            if(c[j][i].id==4)
            {
                c[j][i].pv=300;
            }
            if(c[j][i].id==5)
            {
                c[j][i].pv=600;
            }
        }
    }
}
void initialiser_map(fenetre f[],double Xfen,double Yfen,int cases_max_x,int cases_map_y)
{
    f[0].cases_x=cases_max_x;
    f[0].cases_y=cases_map_y;
    f[0].Xfenetre=Xfen;
    f[0].Yfenetre=Yfen;
}
void initialiser_joueur(joueur j[],int jmax)
{
    int i;
    for(i=0;i<=jmax;i++)
    {
        j[i].id_selectionee=1;
        j[i].n_item_placable_sel=1;
    }
    j[0].n_joueur=0;
    j[1].n_joueur=1;
}
void initialiser_item(item i[],int nbre_blocs_actuel)
{
    int j;
    int n=1;
    for(j=1;j<=nbre_blocs_actuel;j++)
    {
        i[j].id=j;
        i[j].nbre_blocs_actuel=nbre_blocs_actuel;if(j==4)
        {
            i[j].soumis_a_la_gravite=3;
        }
        if(j==1 || j==5)
            i[j].soumis_a_la_gravite=1;
        else
            i[j].soumis_a_la_gravite=0;
        if(j==4)
            i[j].soumis_a_la_gravite=3;
        if(j==1 || j==4 || j==5)
        {
            i[j].placable=1;
            i[j].n_placable=n;
            n+=1;
        }
        else
        {
            i[j].placable=0;
        }
    }
    i[1].nbre_item_placable=n-1;
}
void initialiser_objet_anime(objet_anime* o,int images_max,ALLEGRO_BITMAP* images_animees[],double vitesse_animation,double taille,double x,double y,int taille_x,int taille_y)
{
    o->taille_x=taille_x;
    o->taille_y=taille_y;
    o->etat_animation=1;
    o->taille=taille;
    o->vitesse_animation=vitesse_animation;
    o->x=x;
    o->y=y;
    o->nbre_images_max=images_max;
    o->compteur_animation=1;
    int i;
    for(i=0;i<=3;i++)
    {
        o->animation[i]=0;
    }
    for(i=1;i<=images_max;i++)
    {
        o->bitmap[i]=images_animees[i];
    }
}
