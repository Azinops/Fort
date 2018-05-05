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
void placer_item(ALLEGRO_MOUSE_STATE mouse,point_case souris,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],joueur* j,item i[])
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
                    }
                    else
                    {
                        blocs[souris.y][souris.x].id=j->id_selectionee;
                        blocs[souris.y][souris.x].pv=i[blocs[souris.y][souris.x].id].pv;
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
                bloc[j][i].pv=1;
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
                    jo[a].bombardier.x=(XFENETRE/NBRE_CASES_X)*(i+1.5);
                    jo[a].bombardier.y=(YFENETRE/NBRE_CASES_Y)*(j+0.5);
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
                    if(i==1)
                    {
                        j->puissance_tir=PUISSANCE_TIR_n1;
                        j->portee_tir=PORTEE_TIR_n1;
                    }
                    if(i==2)
                    {
                        j->puissance_tir=PUISSANCE_TIR_n2;
                        j->portee_tir=PORTEE_TIR_n2;
                    }
                    if(i==6)
                    {
                        j->portee_tir=PORTEE_TIR_NSUP;
                    }
                    if(i==7)
                    {
                        j->puissance_tir=PUISSANCE_TIR_n3;
                        j->portee_tir=PORTEE_TIR_n3;
                    }
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
void gerer_fusees(fusee_missile f[],double attraction,carre c[NBRE_CASES_Y][NBRE_CASES_X],objet_fixe p[])
{
    int x;
    int y;
    int i;
    for(i=0;i<=NBRE_FUSEES;i++)
    {
        if(f[i].fusee.existence==1)
        {
            if(f[i].explosion.animation[0]==0)
            {
                f[i].vy+=attraction;
                f[i].fusee.x+=f[i].vx/50*COEF_PIXEL_X;
                f[i].fusee.y+=f[i].vy/50*COEF_PIXEL_Y;
                f[i].fusee.angle=atan(f[i].vy/f[i].vx)+PI/2*(f[i].vx/abs(f[i].vx));
            }
            if(collision_objet_fixe_carre(f[i].fusee,c)==1 && f[i].explosion_en_cours==0)
            {
                f[i].explosion_en_cours=1;
                f[i].vx=0;
                f[i].vy=0;
                f[i].explosion.x=f[i].fusee.x;
                f[i].explosion.y=f[i].fusee.y;
                pop_particules(p,f[i].explosion.x,f[i].explosion.y,NBRE_PARTICULE_POP*sqrt(f[i].puissance_explosion)/sqrt(PUISSANCE_TIR_INITIALE),VITESSE_PARTICULE*sqrt(f[i].puissance_explosion)/sqrt(PUISSANCE_TIR_INITIALE));
                for(x=1;x<=NBRE_CASES_X-1;x++)
                {
                    for(y=1;y<=NBRE_CASES_Y-1;y++)
                    {
                        if(distance(f[i].explosion.x,f[i].explosion.y,x*XFENETRE/NBRE_CASES_X,y*YFENETRE/NBRE_CASES_Y)<=f[i].portee_explosion)
                        {
                            c[y][x].pv-=f[i].puissance_explosion/(pow(distance(f[i].fusee.x,f[i].fusee.y,x*XFENETRE/NBRE_CASES_X,y*YFENETRE/NBRE_CASES_Y)*COEF_REDUC_DEGAT_EXPLOSION,2));
                        }
                    }

                }
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
    f[n].puissance_explosion=j.puissance_tir;
    f[n].portee_explosion=j.portee_tir;
    f[n].explosion.taille=COEF_TAILLE_EXPLO_DEGATS*TAILLE_EXPLOSION_INIT*(pow(j.puissance_tir,0.5))/PUISSANCE_TIR_INITIALE;
    n=retablisseur(n+1,NBRE_FUSEES,1);
}
void pop_fumee(objet_anime o[],fusee_missile f[])
{
    static int n=0;
    int i;
    int j;
    for(i=0;i<=NBRE_FUSEES;i++)
    {
        if(f[i].fusee.existence==1)
        {
            f[i].compteur_fumee+=FREQUENCE_APPARITION_FUMEE;
            if(f[i].compteur_fumee>=1)
            {
                f[i].compteur_fumee=0;
                o[n].existence=1;
                if(f[i].explosion_en_cours==0)
                {
                    o[n].x=f[i].fusee.x;
                    o[n].y=f[i].fusee.y;
                }
                if(f[i].explosion_en_cours==1)
                {
                    for(j=0;j<=NBRE_FUMEE_EXPLOSION*sqrt(f[i].puissance_explosion)/sqrt(PUISSANCE_TIR_INITIALE);j++)
                    {
                        o[n].x=f[i].fusee.x+random(-10,10)*sqrt(f[i].puissance_explosion)/50;
                        o[n].y=f[i].fusee.y+random(-10,10)*sqrt(f[i].puissance_explosion)/50;
                        o[n].taille=f[i].fusee.taille*COEF_FUSEE_FUMEE_TAILLE;
                        animer_objet(&o[n],random(2,7),o[i].nbre_images_max,o[i].nbre_images_max);
                        n=retablisseur(n+1,NBRE_FUMEE,0);
                    }
                }
                else
                {
                    o[n].taille=f[i].fusee.taille*COEF_FUSEE_FUMEE_TAILLE;
                    animer_objet(&o[n],1,o[i].nbre_images_max,o[i].nbre_images_max);
                    n=retablisseur(n+1,NBRE_FUMEE,0);
                }
            }
        }
    }
}
void deplacer_objet_constament(objet_anime o[],int nbre_objets,double vitesse_x,double vitesse_y)
{
    int i;
    for(i=0;i<=nbre_objets;i++)
    {
        if(o[i].existence==1)
        {
            o[i].x+=vitesse_x*COEF_PIXEL_X;
            o[i].y+=vitesse_y*COEF_PIXEL_Y;
            if(o[i].x<=0 || o[i].y<=0 || o[i].x>=XFENETRE || o[i].y>=YFENETRE)
            {
                o[i].existence=0;
            }
        }
    }
}
void deplacer_objet_fixe_constament(objet_fixe o[],int nbre_objets)
{
    int i;
    for(i=0;i<=nbre_objets;i++)
    {
        if(o[i].existence==1)
        {
            o[i].x+=o[i].vitesse_x*COEF_PIXEL_X;
            o[i].y+=o[i].vitesse_y*COEF_PIXEL_Y;
            if(o[i].x<=0 || o[i].y<=0 || o[i].x>=XFENETRE || o[i].y>=YFENETRE)
            {
                o[i].existence=0;
            }
        }
    }
}
void pop_particules(objet_fixe o[],double x,double y,int nbre_particules,double vitesse)
{
    static int n=1;
    int i;
    for(i=0;i<=nbre_particules;i++)
    {
        o[i].existence=1;
        o[i].x=x;
        o[i].y=y;
        o[i].angle=(round(random(-PRECISION_EXPLOSION_PARTICULE/2,PRECISION_EXPLOSION_PARTICULE/2))/PRECISION_EXPLOSION_PARTICULE)*(2*PI);
        o[i].vitesse_x=cos(o[i].angle)*vitesse;
        o[i].vitesse_y=sin(o[i].angle)*vitesse;
        n=retablisseur(n+1,NBRE_PARTICULES_EXPLOSION_MAX,0);
    }
}
void tirs_de_cannon(CLAVIER,joueur j)
{
    if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_SPACE))
    {
        tirer_missile(j,cos(j.angle_tir)*j.puissance_tir_cannon,sin(j.angle_tir)*j.puissance_tir_cannon,j.bombardier.x,j.bombardier.y,j.missile_selectione);
    }
}
