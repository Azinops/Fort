#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "objets.h"
#include "fonctions.h"
void placer_bloc(ALLEGRO_MOUSE_STATE mouse,carre c[NBRE_CASES_Y][NBRE_CASES_X],joueur j,fenetre f)
{
    int x;
    int y;
    if(mouse.buttons&1)
    {
        x=round(mouse.x/f.cases_x);
        y=round(mouse.x/f.cases_x);
    }
}
void rentrer_souris_dans_une_case(point_case* souris,fenetre f,ALLEGRO_MOUSE_STATE mouse)
{
    souris->x=floor(mouse.x/f.Xfenetre*f.cases_x);
    souris->y=floor(mouse.y/f.Yfenetre*f.cases_y);
}
void switcher_deux_blocs(carre* bloc1,carre* bloc2)
{
    int id=bloc1->id;
    int etat=bloc1->etat;
    int pv=bloc1->pv;
    int compteur_gravite=bloc1->compteur_gravite;


    bloc1->id=bloc2->id;
    bloc1->etat=bloc2->etat;
    bloc1->pv=bloc2->pv;
    bloc1->compteur_gravite=bloc2->compteur_gravite;


    bloc2->id=id;
    bloc2->etat=etat;
    bloc2->pv=pv;
    bloc2->compteur_gravite=compteur_gravite;
}
void placer_item(ALLEGRO_MOUSE_STATE mouse,point_case souris,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],joueur* j)
{
    if(mouse.buttons&1)
    {
        if(blocs[souris.y][souris.x].id==0 && blocs[souris.y][souris.x].x!=0 && blocs[souris.y][souris.x].y!=NBRE_CASES_Y && blocs[souris.y][souris.x].x!=NBRE_CASES_X && blocs[souris.y][souris.x].y!=0)
        {
            if(blocs[souris.y-1][souris.x].id==0 && blocs[souris.y][souris.x-1].id==0 && blocs[souris.y+1][souris.x].id==0 && blocs[souris.y][souris.x+1].id==0)
            {}
            else
            {
                if(mouse.x*(1-j->n_joueur*2)<(1-j->n_joueur*2)*(XFENETRE/2))
                {
                    if(j->id_selectionee==5)
                    {
                        if(j->canon_place==1)
                        {
                            switcher_deux_blocs(&blocs[j->bombardier.yi][j->bombardier.xi],&blocs[souris.y][souris.x]);
                        }
                        else
                        {
                            blocs[souris.y][souris.x].id=j->id_selectionee;
                            j->canon_place=1;
                        }
                        j->bombardier.xi=souris.x;
                        j->bombardier.yi=souris.y;
                        j->bombardier.x=mouse.x;
                        j->bombardier.y=mouse.y;
                    }
                    else
                    {
                        blocs[souris.y][souris.x].id=j->id_selectionee;
                        blocs[souris.y][souris.x].au_joueur=j->n_joueur;
                    }
                }
            }
        }
    }
}
int clic_objet_fixe(SOURIS,objet_fixe o)
{
    if(mouse.x>o.x-o.taille_x*o.taille/2 && mouse.y>o.y-o.taille_y*o.taille/2 && mouse.x<o.x+o.taille_x*o.taille/2 && mouse.y<o.y+o.taille_y*o.taille/2 && mouse.buttons&1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int clic_objet(SOURIS,objet_anime o)
{
    if(mouse.x>o.x-o.taille_x*o.taille/2 && mouse.y>o.y-o.taille_y*o.taille/2 && mouse.x<o.x+o.taille_x*o.taille/2 && mouse.y<o.y+o.taille_y*o.taille/2 && mouse.buttons&1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int toucher_objet(SOURIS,objet_anime o)
{
    if(mouse.x>o.x-o.taille_x*o.taille/2 && mouse.y>o.y-o.taille_y*o.taille/2 && mouse.x<o.x+o.taille_x*o.taille/2 && mouse.y<o.y+o.taille_y*o.taille/2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int toucher_objet_fixe(SOURIS,objet_fixe o)
{
    if(mouse.x>o.x-o.taille_x*o.taille/2 && mouse.y>o.y-o.taille_y*o.taille/2 && mouse.x<o.x+o.taille_x*o.taille/2 && mouse.y<o.y+o.taille_y*o.taille/2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void animer_objet(objet_anime* o,int image_depart,int image_fin_anim,int image_a_mettre_apres_animation)
{
    o->animation[0]=1;
    o->animation[1]=image_depart;
    o->etat_animation=image_depart;
    o->compteur_animation=image_depart;
    o->animation[2]=image_fin_anim;
    o->animation[3]=image_a_mettre_apres_animation;
}
int interaction_bouton_fin_tour(objet_anime* bouton,SOURIS,int quel_joueur_joue)
{
    if(clic_objet(mouse,*bouton)==1 && bouton->animation[0]==0)
    {
        animer_objet(bouton,3,18,1);
        if(quel_joueur_joue==1)
        {
            quel_joueur_joue=0;
        }
        else
        {
            quel_joueur_joue=1;
        }
    }
    else
    {
        if(toucher_objet(mouse,*bouton)==1)
        {
            bouton->etat_animation=2;
        }
        else
        {
            bouton->etat_animation=1;
        }
    }
    return quel_joueur_joue;
}

void gerer_blocs(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],int vitesse_inv_gravite,item it[],joueur jo[])
{
    int a;
    int i=0;
    int j=0;
    for(i=0;i<=NBRE_CASES_X-1;i++)
    {
        for(j=0;j<=NBRE_CASES_Y-1;j++)
        {
            if(bloc[j][i].pv<=0)
            {
                bloc[j][i].id=0;
                bloc[j][i].au_joueur=-1;
            }
            if(it[bloc[j][i].id].soumis_a_la_gravite==1)
            {
                if(bloc[j+1][i].id==0)
                {
                    if(it[bloc[j-1][i].id].soumis_a_la_gravite!=3 && it[bloc[j][i+1].id].soumis_a_la_gravite!=3 && it[bloc[j][i-1].id].soumis_a_la_gravite!=3)
                    {
                        bloc[j][i].compteur_gravite=retablisseur(bloc[j][i].compteur_gravite+1,vitesse_inv_gravite,1);
                        if(bloc[j][i].compteur_gravite==vitesse_inv_gravite)
                        {
                            switcher_deux_blocs(&bloc[j][i],&bloc[j+1][i]);
                        }
                    }
                }
                if(bloc[j][i].id==5)
                {
                    if(bloc[j][i].x<XFENETRE/2)
                    {
                        a=0;
                    }
                    if(bloc[j][i].x>XFENETRE/2)
                    {
                        a=1;
                    }
                    jo[a].bombardier.xi=i;
                    jo[a].bombardier.yi=j;
                    jo[a].bombardier.x=(XFENETRE/NBRE_CASES_X)*i;
                    jo[a].bombardier.y=(YFENETRE/NBRE_CASES_Y)*j;
                }
            }
        }
    }
}
void enlever_carre(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],point_case p,SOURIS,item i[])
{
    if(mouse.buttons&2)
    {
        if(i[bloc[p.y][p.x].id].placable==1)
        {
            bloc[p.y][p.x].id=0;
            bloc[p.y][p.x].etat=1;
            bloc[p.y][p.x].pv=0;
        }
    }
}
void gerer_competences(SOURIS,joueur* j,objet_fixe o[])
{
    int i=1;
    int k;
    if(o[i].id==1)
    {
        for(i=1;i<=NBRE_COMPETENCES_EXPLO;i++)
        {
            if(clic_objet_fixe(mouse,o[i]))
            {
                if(j->explosion_debloques[i]==1)
                {
                    j->explosion_debloques[i]=2;
                    for(k=1;k<=NBRE_LIAISONS_COMPTENCES_MAX;k++)
                    {
                        if(o[i].utile2[k]!=0)
                        {
                            if(o[i].utile2[k]==8)
                            {
                                j->explosion_debloques[o[i].utile2[k]]+=0.5;
                            }
                            else
                            {
                                j->explosion_debloques[o[i].utile2[k]]=1;
                            }
                        }
                    }
                }
            }
        }
    }
    if(o[i].id==2)
    {
        for(i=1;i<=NBRE_COMPETENCES_SCIENCE;i++)
        {
            if(clic_objet_fixe(mouse,o[i]))
            {
                if(j->science_debloques[i]==1)
                {
                    j->science_debloques[i]=2;
                    for(k=1;k<=NBRE_LIAISONS_COMPTENCES_MAX;k++)
                    {
                        if(o[i].utile2[k]!=0)
                        {
                            if(o[i].utile2[k]==8)
                            {
                                j->science_debloques[o[i].utile2[k]]+=0.5;
                            }
                            else
                            {

                                j->science_debloques[o[i].utile2[k]]=1;
                            }
                        }
                    }
                }
            }
        }
    }
    if(o[i].id==3)
    {
        for(i=1;i<=NBRE_COMPETENCES_PRECISION;i++)
        {
            if(clic_objet_fixe(mouse,o[i]))
            {
                if(j->precision_debloques[i]==1)
                {
                    j->precision_debloques[i]=2;
                    for(k=1;k<=NBRE_LIAISONS_COMPTENCES_MAX;k++)
                    {
                        if(o[i].utile2[k]!=0)
                        {
                            if(o[i].utile2[k]==8)
                            {
                                j->precision_debloques[o[i].utile2[k]]+=0.5;
                            }
                            else
                            {
                                j->precision_debloques[o[i].utile2[k]]=1;
                            }
                        }
                    }
                }
            }
        }
    }
}
int collision_objet_fixe_carre(objet_fixe o,carre c[NBRE_CASES_Y][NBRE_CASES_X])
{
    int xi=floor((o.x)/XFENETRE*NBRE_CASES_X);
    int yi=floor((o.y)/YFENETRE*NBRE_CASES_Y);
    if(c[yi][xi].id!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void gerer_fusees(fusee_missile f[],double attraction,carre c[NBRE_CASES_Y][NBRE_CASES_X])
{
    int i;
    for(i=0;i<=NBRE_FUSEES;i++)
    {
        if(f[i].fusee.existence==1)
        {
            if(f[i].explosion.animation[0]==0)
            {
                f[i].vy+=attraction;
                f[i].fusee.x+=f[i].vx/50;
                f[i].fusee.y+=f[i].vy/50;
                f[i].fusee.angle=atan(f[i].vy/f[i].vx)+PI/2*(f[i].vx/abs(f[i].vx));
            }
            if(collision_objet_fixe_carre(f[i].fusee,c)==1 && f[i].explosion_en_cours==0)
            {
                f[i].explosion_en_cours=1;
                f[i].vx=0;
                f[i].vy=0;
                f[i].explosion.x=f[i].fusee.x;
                f[i].explosion.y=f[i].fusee.y;
                animer_objet(&f[i].explosion,1,f[i].explosion.nbre_images_max,f[i].explosion.nbre_images_max);
            }
            if(f[i].fusee.y>YFENETRE || f[i].fusee.x>XFENETRE || f[i].fusee.x<0)
            {
                f[i].fusee.existence=0;
            }
            if(f[i].explosion.animation[0]==0 && f[i].explosion_en_cours==1)
            {
                f[i].fusee.existence=0;
                f[i].explosion_en_cours=0;
            }
        }
    }
}
void tirer_missile(joueur j,double vx,double vy,double x,double y,fusee_missile f[])
{
    static int n=1;
    f[n].vx=vx;
    f[n].vy=vy;
    f[n].fusee.existence=1;
    f[n].fusee.x=x;
    f[n].fusee.y=y;
    f[n].explosion.taille=j.taille_explosion;
    n=retablisseur(n+1,NBRE_FUSEES,1);
}
void pop_fumee(objet_anime o[],fusee_missile f[])
{
    static int n=0;
    int i;
    for(i=0;i<=NBRE_FUSEES;i++)
    {
        if(f[i].fusee.existence==1)
        {
            f[i].compteur_fumee+=FREQUENCE_APPARITION_FUMEE;
            if(f[i].compteur_fumee>=1)
            {
                f[i].compteur_fumee=0;
                o[n].existence=1;
                o[n].x=f[i].fusee.x;
                o[n].y=f[i].fusee.y;
                o[n].taille=f[i].fusee.taille*COEF_FUSEE_FUMEE_TAILLE;
                animer_objet(&o[n],1,o[i].nbre_images_max,o[i].nbre_images_max);
                n=retablisseur(n+1,NBRE_FUMEE,0);
            }
        }
    }
}
