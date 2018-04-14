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
            c[j][i].au_joueur=-1;
            if(c[j][i].id==1)
            {
                c[j][i].pv=100;
            }
            if(c[j][i].id==2)
            {
                c[j][i].pv=200;
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
            if(c[j][i].id==5)
            {
                c[j][i].pv=600;
            }
            if(c[j][i].id==6)
            {
                c[j][i].pv=50;
            }
            if(c[j][i].id==7)
            {
                c[j][i].pv=150;
            }
            if(c[j][i].id==8)
            {
                c[j][i].pv=400;
            }
            if(c[j][i].id==9)
            {
                c[j][i].pv=350;
            }
            if(c[j][i].id==10)
            {
                c[j][i].pv=20;
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
void initialiser_joueur(joueur j[],int jmax,canon canon_j[],double taille_explosion_init)
{
    int i;
    int k;
    for(i=0;i<=jmax;i++)
    {
        j[i].id_selectionee=1;
        j[i].n_item_placable_sel=1;
        j[i].n_joueur=i;
        j[i].bombardier=canon_j[i];
        j[i].canon_place=0;
        j[i].taille_explosion=taille_explosion_init;
        for(k=1;k<=NBRE_COMPETENCES_EXPLO;k++)
        {
            j[i].explosion_debloques[k]=0;
        }
        for(k=1;k<=NBRE_COMPETENCES_SCIENCE;k++)
        {
            j[i].science_debloques[k]=0;
        }
        for(k=1;k<=NBRE_COMPETENCES_PRECISION;k++)
        {
            j[i].precision_debloques[k]=0;
        }
        j[i].explosion_debloques[1]=1;
        j[i].science_debloques[1]=1;
        j[i].precision_debloques[1]=1;
    }
    j[0].fini_de_jouer=0;
    j[1].fini_de_jouer=1;
}
void initialiser_item(item i[],int nbre_blocs_actuel)
{
    int j;
    int n=1;
    for(j=1;j<=nbre_blocs_actuel;j++)
    {
        i[j].id=j;
        i[j].nbre_blocs_actuel=nbre_blocs_actuel;
        if(j==1 || j==5 || (j>=7 && j<=8) || j==10)
            i[j].soumis_a_la_gravite=1;
        else
            i[j].soumis_a_la_gravite=0;
        if(j==4 || j==9)
        {
            i[j].soumis_a_la_gravite=3;
        }
        if(j==1 || j==4 || j==5 || j==5 || (j>=7 && j<=10))
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
void initialiser_objet_anime(objet_anime* o,int images_max,ALLEGRO_BITMAP* images_animees[],double vitesse_animation,double taille,double x,double y,int taille_x,int taille_y,int existence)
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
    o->angle=0;
    o->existence=existence;
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
void initialiser_objet_fixe(objet_fixe* o,ALLEGRO_BITMAP* image,double taille,double x,double y,int taille_x,int taille_y)
{
    o->taille_x=taille_x;
    o->taille_y=taille_y;
    o->taille=taille;
    o->x=x;
    o->y=y;
    o->bitmap=image;
    o->angle=0;
}
void initialiser_objet_fixe_en_masse(objet_fixe o[],ALLEGRO_BITMAP* image,double taille,double x,double y,int taille_x,int taille_y,int nbre_objets)
{
    int i;
    for(i=1;i<=nbre_objets;i++)
    {
        o[i].taille_x=taille_x;
        o[i].taille_y=taille_y;
        o[i].taille=taille;
        o[i].x=x;
        o[i].y=y;
        o[i].bitmap=image;
        o[i].angle=0;
    }
}
void mettre_id(objet_fixe o[],int id)
{
    int k;
    for(k=0;k<=NBRE_COMPETENCES_EXPLO;k++)
    {
        o[k].id=id;
    }
}
void initialiser_objet_fixe_c(objet_fixe o[],ALLEGRO_BITMAP* image[],double taille,int taille_xy,double x,int id)
{
    int k;
    int i;
    int n;
    for(k=1;k<=NBRE_COMPETENCES_EXPLO;k++)
        {
        mettre_id(o,id);
        o[k].taille_x=taille_xy;
        o[k].taille_y=taille_xy;
        o[k].taille=taille;
        o[k].angle=0;
        o[k].existence=1;
        for(i=1;i<=4;i++){o[k].utile2[i]=0;}
        if(k==1)
        {
            o[k].y=YFENETRE/(NBRE_COLONE_COMPETENCE+1);
            o[k].x=x;
            o[k].utile2[1]=2;
            o[k].utile2[2]=3;
        }
        if(k>=2 && k<=3)
        {
            o[k].y=(YFENETRE/(NBRE_COLONE_COMPETENCE+1))*2;
            n=k-2;
            o[k].utile2[1]=6-2*n;
            o[k].utile2[2]=7-2*n;
            o[k].x=x+(2*(k-2)-1)*(taille_xy*o[k].taille);
        }
        if(k>=4 && k<=7)
        {
            if(k>=5 && k<=6)
            {
                o[k].utile2[1]=8;
            }
            o[k].y=(YFENETRE/(NBRE_COLONE_COMPETENCE+1))*3;
            n=k-5;
            if(n<=0){n-=1;}
            o[k].x=x+(n/(abs(n)))*(taille_xy*o[k].taille/2)-(n)*(taille_xy*o[k].taille*1.2);
        }
        if(k==8)
        {
            o[k].y=(YFENETRE/(NBRE_COLONE_COMPETENCE+1))*4;
            o[k].x=x;
        }
        o[k].bitmap=image[k];
    }
}
void initialiser_fusees(fusee_missile f[],int nbre_fusees,ALLEGRO_BITMAP* image_fusee,double taille_fusees,int nbre_explosion,ALLEGRO_BITMAP* explosions[],double vitesse_anim_explosion,double taille_explosion)
{
    int i;
    for(i=0;i<=nbre_fusees;i++)
    {
        f[i].fusee.existence=0;
        f[i].inclinaison=0;
        initialiser_objet_fixe(&f[i].fusee,image_fusee,taille_fusees,0,0,TAILLE_FUSEE_X_Y,TAILLE_FUSEE_X_Y);
        initialiser_objet_anime(&f[i].explosion,nbre_explosion,explosions,vitesse_anim_explosion,taille_explosion,0,0,TAILLE_EXPLOSION_X_Y,TAILLE_EXPLOSION_X_Y,1);
        f[i].vx=0;
        f[i].vy=0;
        f[i].explosion_en_cours=0;
        f[i].compteur_fumee=0;

    }
}
void initialiser_fumee(objet_anime o[],int nbre_fumee,ALLEGRO_BITMAP* fumees[],double vitesse_anim,double taille)
{
    int i;
    for(i=0;i<=NBRE_FUMEE;i++)
    {
        initialiser_objet_anime(&o[i],nbre_fumee,fumees,vitesse_anim,taille,0,0,TAILLE_FUMEE_XY,TAILLE_FUMEE_XY,0);
    }
}
