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
	int enlever_tempo=bloc1->enleve_tempo;
    int au_joueur=bloc1->au_joueur;

	bloc1->id=bloc2->id;
	bloc1->etat=bloc2->etat;
	bloc1->pv=bloc2->pv;
	bloc1->compteur_gravite=bloc2->compteur_gravite;
    bloc1->enleve_tempo=bloc2->enleve_tempo;
    bloc1->au_joueur=bloc2->au_joueur;

	bloc2->id=id;
	bloc2->etat=etat;
	bloc2->pv=pv;
	bloc2->compteur_gravite=compteur_gravite;
	bloc2->enleve_tempo=enlever_tempo;
	bloc2->au_joueur=au_joueur;
}
void placer_item(ALLEGRO_MOUSE_STATE mouse,point_case souris,carre blocs[NBRE_CASES_Y][NBRE_CASES_X],joueur* j,item i[],int tour)
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
                	if((j->id_selectionee==5 && tour==0) || (j->canon_place==2 && j->compteur_tour_replacer_canon>=NRBE_TOURS_POUR_REPLACER_CANON && j->id_selectionee==5))
                	{
                    	if(j->canon_place==1)
                    	{
                        	switcher_deux_blocs(&blocs[j->bombardier.yi][j->bombardier.xi],&blocs[souris.y][souris.x]);
                    	}
                    	else
                    	{
                        	blocs[souris.y][souris.x].id=j->id_selectionee;
                        	j->canon_place=1;
                        	blocs[souris.y][souris.x].au_joueur=j->n_joueur;
                        	blocs[souris.y][souris.x].pv=i[blocs[souris.y][souris.x].id].pv;
                    	}
                    	j->bombardier.xi=souris.x;
                    	j->bombardier.yi=souris.y;
                    	j->bombardier.pv=blocs[j->bombardier.yi][j->bombardier.xi].pv;
                	}
                	if(j->id_selectionee==6 && tour==0)
                	{
                    	if(j->coeur_pose==1)
                    	{
                        	switcher_deux_blocs(&blocs[j->coeur_yi][j->coeur_xi],&blocs[souris.y][souris.x]);
                    	}
                    	else
                    	{
                        	blocs[souris.y][souris.x].id=j->id_selectionee;
                        	j->coeur_pose=1;
                        	blocs[souris.y][souris.x].au_joueur=j->n_joueur;
                        	blocs[souris.y][souris.x].pv=i[blocs[souris.y][souris.x].id].pv;
                    	}
                    	j->coeur_xi=souris.x;
                    	j->coeur_yi=souris.y;
                	}
                	if(j->id_selectionee!=5 && j->id_selectionee!=6)
                	{
                    	if(j->tune>=i[j->id_selectionee].prix)
                    	{
                            blocs[souris.y][souris.x].id=j->id_selectionee;
                            blocs[souris.y][souris.x].pv=i[blocs[souris.y][souris.x].id].pv;
                            blocs[souris.y][souris.x].pv_initiaux=i[blocs[souris.y][souris.x].id].pv;
                            blocs[souris.y][souris.x].au_joueur=j->n_joueur;
                            j->tune-=i[j->id_selectionee].prix;
                    	}
                	}
                    blocs[souris.y][souris.x].enleve_tempo=0;
            	}
        	}
    	}
	}
}
int clic_objet_fixe(SOURIS,objet_fixe o)
{
	if(mouse.x>o.x-o.taille_x*o.tailleX/2*COEF_PIXEL_X && mouse.y>o.y-o.taille_y*o.tailleY/2*COEF_PIXEL_Y && mouse.x<o.x+o.taille_x*o.tailleX/2*COEF_PIXEL_X && mouse.y<o.y+o.taille_y*o.tailleY/2*COEF_PIXEL_Y && mouse.buttons&1)
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
	if(mouse.x>o.x-o.taille_x*o.taille/2*COEF_PIXEL_X && mouse.y>o.y-o.taille_y*o.taille/2*COEF_PIXEL_Y && mouse.x<o.x+o.taille_x*o.taille/2*COEF_PIXEL_X && mouse.y<o.y+o.taille_y*o.taille/2*COEF_PIXEL_Y && mouse.buttons&1)
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
	if(mouse.x>o.x-o.taille_x*o.taille/2*COEF_PIXEL_X && mouse.y>o.y-o.taille_y*o.taille/2*COEF_PIXEL_Y && mouse.x<o.x+o.taille_x*o.taille/2*COEF_PIXEL_X && mouse.y<o.y+o.taille_y*o.taille/2*COEF_PIXEL_Y)
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
	if(mouse.x>o.x-(o.taille_x*o.tailleX/2)*COEF_PIXEL_X && mouse.y>o.y-(o.taille_y*o.tailleY/2)*COEF_PIXEL_Y && mouse.x<o.x+(o.taille_x*o.tailleX/2)*COEF_PIXEL_X && mouse.y<o.y+(o.taille_y*o.tailleY/2)*COEF_PIXEL_Y)
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
int interaction_bouton_fin_tour(objet_anime* bouton,SOURIS,int quel_joueur_joue,joueur j[],int* n_tour,item_missile missiles[],carre c[NBRE_CASES_Y][NBRE_CASES_X],CLAVIER)
{
	int i;
	int q;
	int x;
	int y;
	q=quel_joueur_joue;
	if((clic_objet(mouse,*bouton)==1 || al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_ENTER)) && bouton->animation[0]==0)
	{
    	for(i=0;i<=1;i++)
    	{
        	j[i].points_destruction_debut_tour=j[i].points_destruction;
        	j[i].nbre_tirs=0;
        	if(*n_tour!=0-MOD_CHEAT())
        	{
            	j[i].id_missile_selectione=1;
                j->missile_selectione=missiles[1].missile;
        	}
        	else
        	{
            	j[i].id_missile_selectione=0;
        	}
    	}
    	animer_objet(bouton,3,18,1);
    	if(quel_joueur_joue==1)
    	{
        	quel_joueur_joue=0;
    	}
    	else
    	{
        	quel_joueur_joue=1;
    	}
    	for(x=1;x<=NBRE_CASES_X;x++)
        {
            for(y=1;y<=NBRE_CASES_Y;y++)
            {
                if(c[y][x].au_joueur==quel_joueur_joue && c[y][x].id==7)
                {
                    c[y][x].enleve_tempo=1;
                }
                if(c[y][x].au_joueur!=quel_joueur_joue && c[y][x].id==7)
                {
                    c[y][x].enleve_tempo=0;
                }
            }
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
	if(q==1 && quel_joueur_joue==0)
	{
	    for(i=0;i<=1;i++)
        {
            *n_tour+=1;
            j[i].compteur_tour_replacer_canon+=1;
            j[i].tune+=POINT_CONSTRUCTION_PAR_TOUR*j[i].coef_gain_tune;
            j[i].id_missile_selectione=1;
            j->missile_selectione=missiles[1].missile;
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
            	}
            	if(bloc[j][i].id==6)
            	{
                	if(bloc[j][i].x<XFENETRE/2)
                	{
                    	a=0;
                	}
                	if(bloc[j][i].x>XFENETRE/2)
                	{
                    	a=1;
                	}
                	jo[a].coeur_xi=i;
                	jo[a].coeur_yi=j;
            	}
        	}
    	}
	}
}
void enlever_carre(carre bloc[NBRE_CASES_Y][NBRE_CASES_X],point_case p,SOURIS,item i[],joueur* j,int n_tour)
{
	if(mouse.buttons&2)
	{
    	if(i[bloc[p.y][p.x].id].placable==1 && i[bloc[p.y][p.x].id].id!=5 && i[bloc[p.y][p.x].id].id!=6 && n_tour==0)
    	{
        	j->tune+=i[bloc[p.y][p.x].id].prix;
        	bloc[p.y][p.x].id=0;
        	bloc[p.y][p.x].etat=1;
        	bloc[p.y][p.x].pv=0;
    	}
	}
}
void gerer_competences(SOURIS,joueur* j,objet_fixe o[],carre blocs[NBRE_CASES_Y][NBRE_CASES_X])
{
	int i=1;
	int k;
	if(o[i].id==1)
	{
    	for(i=1;i<=NBRE_COMPETENCES_EXPLO;i++)
    	{
        	if(clic_objet_fixe(mouse,o[i]))
        	{
            	if(j->explosion_debloques[i]==1 && j->pts_competences>=1)
            	{
                	j->explosion_debloques[i]=2;
                	j->pts_competences-=1;
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
                	if(i==5)
                    {
                        ajouter_missile_dans_inventaire(j,2);
                    }
                    if(i==8)
                    {
                        ajouter_missile_dans_inventaire(j,3);
                    }
                    if(i==4)
                    {
                        j->nbre_tirs_max=3;
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
            	if(j->science_debloques[i]==1 && j->pts_competences>=1)
            	{
                	j->science_debloques[i]=2;
                	j->pts_competences-=1;
                	if(i==3)
                    {
                        j->coef_xp=1.6;
                    }
                    if(i==1)
                    {
                        j->coef_xp=1.2;
                        j->coef_gain_tune=1.2;
                    }
                    if(i==4)
                    {
                        j->coef_xp=2.2;
                    }
                    if(i==5)
                    {
                        ajouter_missile_dans_inventaire(j,6);
                    }
                    if(i==7)
                    {
                        j->coef_gain_tune=2;
                    }
                    if(i==6)
                    {
                        blocs[j->coeur_yi][j->coeur_xi].pv*=1.5;
                    }
                    if(i==8)
                    {
                        ajouter_missile_dans_inventaire(j,4);
                    }
                    if(i==2)
                    {
                        ajouter_missile_dans_inventaire(j,5);
                    }
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
            	if(j->precision_debloques[i]==1 && j->pts_competences>=1)
            	{
                	j->precision_debloques[i]=2;
                	j->pts_competences-=1;
                	if(i==3)
                    {
                        ajouter_missile_dans_inventaire(j,7);
                    }
                    if(i==4)
                    {
                        ajouter_missile_dans_inventaire(j,8);
                    }
                    if(i==2)
                    {
                        ajouter_missile_dans_inventaire(j,9);
                    }
                    if(i==6)
                    {
                        ajouter_missile_dans_inventaire(j,10);
                    }
                    if(i==8)
                    {
                        ajouter_missile_dans_inventaire(j,11);
                    }
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
int collision_objet_fixe_carre(objet_fixe o,carre c[NBRE_CASES_Y][NBRE_CASES_X],int joueur_qui_joue)
{
	int xi=floor((o.x)/XFENETRE*NBRE_CASES_X);
	int yi=floor((o.y)/YFENETRE*NBRE_CASES_Y);
	if(c[yi][xi].id!=0 && c[yi][xi].enleve_tempo==0)
	{
    	if(c[yi][xi].id==5 && c[yi][xi].au_joueur==joueur_qui_joue)
    	{
    	    return 0;
    	}
    	else
    	{
        	return 1;
    	}
	}
	else
	{
    	return 0;
	}
}
void gerer_fusees(fusee_missile f[],double attraction,carre c[NBRE_CASES_Y][NBRE_CASES_X],objet_fixe p[],int joueur_qui_joue,joueur j[],CLAVIER)
{
	int x;
	int y;
	int i;
	for(i=0;i<=NBRE_FUSEES;i++)
	{
    	if(f[i].fusee.existence==1)
    	{
    	    f[i].compteur_depuis_tir+=1;
    	    if(f[i].id==8 && al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_SPACE) && f[i].compteur_depuis_tir>20)
            {
                f[i].utile1=1;
                f[i].vx/=1.4;
                f[i].vy=0;
            }
        	if(f[i].explosion.animation[0]==0)
        	{
            	f[i].chrono+=1;
            	if(f[i].id!=4 && f[i].id!=7 && (f[i].id!=8 || f[i].utile1==1) && f[i].id!=9 && f[i].id!=10)
                {
                    f[i].vy+=attraction;
                }
                if(f[i].id==4)
                {
                    if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_UP))
                    {
                        f[i].vx=10*COEF_PIXEL_X;
                        f[i].vy=-VITESSE_MISSILE_TELEGUIDE;
                    }
                    if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_DOWN))
                    {
                        f[i].vx=10*COEF_PIXEL_X;
                        f[i].vy=VITESSE_MISSILE_TELEGUIDE;
                    }
                    if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_LEFT))
                    {
                        f[i].vx=-VITESSE_MISSILE_TELEGUIDE;
                        f[i].vy=0.1*COEF_PIXEL_Y;
                    }
                    if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_RIGHT))
                    {
                        f[i].vx=VITESSE_MISSILE_TELEGUIDE;
                        f[i].vy=0.1*COEF_PIXEL_Y;
                    }
                }
                if(f[i].id==5 && f[i].utile1==1)
                {
                    f[i].vx=VITESSE_TAUPIENIER*(1-2*joueur_qui_joue);
                    f[i].vy=0;
                    f[i].utile2+=1;
                    if(f[i].chrono>=TEMPS_CREUSAGE_TAUPINIER)
                    {
                        f[i].utile2=0;
                        f[i].utile1=2;
                    }
                }
                f[i].fusee.x+=f[i].vx/FPS*COEF_PIXEL_X;
                f[i].fusee.y+=f[i].vy/FPS*COEF_PIXEL_Y;
                f[i].fusee.angle=atan(f[i].vy/f[i].vx)+PI/2*(f[i].vx/abs(f[i].vx));

        	}
        	if(f[i].fusee.y>0)
            {
                if(f[i].explosion_en_cours==0 && (collision_objet_fixe_carre(f[i].fusee,c,joueur_qui_joue)==1 && f[i].fusee.y>0 && f[i].id!=11 || (f[i].id==11 && al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_SPACE) && f[i].chrono>=10)))
                {
                    if(f[i].id==5 && f[i].utile1==0)
                    {
                        f[i].utile1=1;
                    }
                    if(f[i].id!=5 || (f[i].id==5 && f[i].utile1==2))
                    {
                        f[i].explosion_en_cours=1;
                        f[i].vx=0;
                        f[i].vy=0;
                        f[i].explosion.x=f[i].fusee.x;
                        f[i].explosion.y=f[i].fusee.y;
                        f[i].chrono=0;
                        if(f[i].puissance_explosion<=PUISSANCE_TIR_n3*PUISSANCE_TIR_INITIALE)
                        {
                            pop_particules(p,f[i].explosion.x,f[i].explosion.y,NBRE_PARTICULE_POP*sqrt(f[i].puissance_explosion)/sqrt(PUISSANCE_TIR_INITIALE),VITESSE_PARTICULE*sqrt(f[i].puissance_explosion)/sqrt(PUISSANCE_TIR_INITIALE));
                        }
                        for(x=1;x<=NBRE_CASES_X-1;x++)
                        {
                            for(y=1;y<=NBRE_CASES_Y-1;y++)
                            {
                                if(distance(f[i].explosion.x,f[i].explosion.y,x*XFENETRE/NBRE_CASES_X,y*YFENETRE/NBRE_CASES_Y)<=f[i].portee_explosion)
                                {
                                    if(j->explosion_debloques[3]==2 && (c[y][x].id==7 || c[y][x].id==1 || c[y][x].id==4))
                                    {
                                            c[y][x].pv/=1.3;
                                    }
                                    c[y][x].pv-=f[i].puissance_explosion/(pow(distance(f[i].fusee.x,f[i].fusee.y,(x+0.5)*XFENETRE/NBRE_CASES_X,(y+0.5)*YFENETRE/NBRE_CASES_Y)*COEF_REDUC_DEGAT_EXPLOSION,2));
                                    if(c[y][x].pv<=0 && c[y][x].id!=0)
                                    {
                                        j[joueur_qui_joue].points_destruction+=c[y][x].pv_initiaux*j[joueur_qui_joue].coef_points/100*f[i].coef_xp;
                                        j[joueur_qui_joue].xp+=c[y][x].pv_initiaux*j[joueur_qui_joue].coef_xp*f[i].coef_xp;
                                    }
                                }
                            }

                        }
                        animer_objet(&f[i].explosion,1,f[i].explosion.nbre_images_max,f[i].explosion.nbre_images_max);
                    }
                }
            }
        	if(f[i].fusee.y>YFENETRE || f[i].fusee.x>XFENETRE || f[i].fusee.x<0)
        	{
            	f[i].fusee.existence=0;
            	f[i].utile1=0;
            	f[i].utile2=0;
        	}
        	if(f[i].explosion.animation[0]==0 && f[i].explosion_en_cours==1)
        	{
            	f[i].fusee.existence=0;
            	f[i].explosion_en_cours=0;
            	f[i].puissance_explosion=f[i].puissance_explosion_initiale;
            	f[i].utile1=0;
            	f[i].utile2=0;
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
	f[n].utile1=0;
	f[n].utile2=0;
	f[n].compteur_depuis_tir=0;
	if(f[n].id!=3)
	{
    	f[n].puissance_explosion=f[n].puissance_explosion_initiale*j.puissance_tir;
	}
	else
	{
    	f[n].puissance_explosion=f[n].puissance_explosion_initiale;
	}
	f[n].portee_explosion=j.portee_tir*f[n].portee_explosion_initiale;
	f[n].explosion.taille=COEF_TAILLE_EXPLO_DEGATS*f[n].taille_initiale*(pow(f[n].puissance_explosion,0.5))/PUISSANCE_TIR_INITIALE;
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
                    	o[n].x=f[i].fusee.x+random(-10,10)*sqrt(f[i].puissance_explosion)/FPS;
                    	o[n].y=f[i].fusee.y+random(-10,10)*sqrt(f[i].puissance_explosion)/FPS;
                    	o[n].taille=f[i].fusee.tailleX*COEF_FUSEE_FUMEE_TAILLE;
                    	animer_objet(&o[n],random(2,7),o[i].nbre_images_max,o[i].nbre_images_max);
                    	n=retablisseur(n+1,NBRE_FUMEE,0);
                	}
            	}
            	else
            	{
                	o[n].taille=f[i].fusee.tailleX*COEF_FUSEE_FUMEE_TAILLE;
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
void deplacer_seul_objet_fixe_constament(objet_anime o,double vitesse_x,double vitesse_y)
{
	int i;
    if(o.existence==1)
    {
        o.x+=vitesse_x*COEF_PIXEL_X;
        o.y+=vitesse_y*COEF_PIXEL_Y;
        if(o.x<=0 || o.y<=0 || o.x>=XFENETRE || o.y>=YFENETRE)
        {
            o.existence=0;
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
void tirs_de_cannon(CLAVIER,joueur* j,SOURIS,double attraction)
{
    int x;
	static int appuye=0;
	if(j->canon_place==1)
    {
        al_draw_line((j->bombardier.xi+0.5)*TAILLE_CASE_X,(j->bombardier.yi+0.5)*TAILLE_CASE_Y,(j->bombardier.xi+0.5)*TAILLE_CASE_X+LONGEUR_LIGNE_TIR*cos(j->angle_tir),(j->bombardier.yi+0.5)*TAILLE_CASE_Y+LONGEUR_LIGNE_TIR*sin(j->angle_tir),ROUGE,LARGEUR_LIGNE_TIR);
        if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_UP))
        {
            j->angle_tir-=0.01*(1-2*j->n_joueur);
        }
        if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_DOWN))
        {
            j->angle_tir+=0.01*(1-2*j->n_joueur);
        }
        if(j->id_missile_selectione==10)
        {
            j->angle_tir=atan(((j->bombardier.yi+0.5)*TAILLE_CASE_Y-mouse.y)/((j->bombardier.xi+0.5)*TAILLE_CASE_X-mouse.x));
            if(mouse.x<(j->bombardier.xi+0.5)*TAILLE_CASE_X)
            {
                j->angle_tir+=PI;
            }
        }
        if(j->precision_debloques[5]==2 && j->id_missile_selectione!=4 && j->id_missile_selectione!=7 && j->id_missile_selectione!=8 && j->id_missile_selectione!=9 && j->id_missile_selectione!=10)
        {
            if(j->n_joueur==0)
            {
                for(x=(j->bombardier.xi+0.5)*TAILLE_CASE_X;x<=XFENETRE+(j->bombardier.xi+0.5)*TAILLE_CASE_X;x+=10*COEF_PIXEL_X)
                {
                    double VX0=cos(j->angle_tir)*j->puissance_tir_cannon;
                    double VY0=sin(j->angle_tir)*j->puissance_tir_cannon;
                    double xmx0=x-((j->bombardier.xi+0.5)*TAILLE_CASE_X);
                    al_draw_circle(x,(j->bombardier.yi+0.5)*TAILLE_CASE_Y+VY0*COEF_PIXEL_Y*xmx0/(VX0*COEF_PIXEL_X)+round((COEF_PIXEL_X)*(attraction*FPS*pow(xmx0,2))/(2*pow(VX0*COEF_PIXEL_X,2))*10000)/10000,1,BLANC,2);
                }
            }
            else
            {
                for(x=(j->bombardier.xi+0.5)*TAILLE_CASE_X;x>=0;x-=10*COEF_PIXEL_X)
                {
                    double VX0=cos(j->angle_tir)*j->puissance_tir_cannon;
                    double VY0=sin(j->angle_tir)*j->puissance_tir_cannon;
                    double xmx0=x-((j->bombardier.xi+0.5)*TAILLE_CASE_X);
                    al_draw_circle(x,(j->bombardier.yi+0.5)*TAILLE_CASE_Y+VY0*COEF_PIXEL_Y*xmx0/(VX0*COEF_PIXEL_X)+round((COEF_PIXEL_X)*(attraction*FPS*pow(xmx0,2))/(2*pow(VX0*COEF_PIXEL_X,2))*10000)/10000,1,BLANC,2);
                }
            }
        }
        if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_SPACE) && appuye==0 && j->id_missile_selectione!=0 && (j->nbre_tirs<j->nbre_tirs_max || MOD_CHEAT==1 || (j->precision_debloques[7]==2 && j->nbre_tirs<NBRE_TIRS_COMPETENCE_7_PRECISION)))
        {
            appuye=1;
            if(j->nbre_tirs==0 || MOD_CHEAT==1)
            {
                if(j->id_missile_selectione!=8 && j->id_missile_selectione!=9)
                {
                    tirer_missile(*j,cos(j->angle_tir)*j->puissance_tir_cannon,sin(j->angle_tir)*j->puissance_tir_cannon,(j->bombardier.xi+0.5)*TAILLE_CASE_X,(j->bombardier.yi+0.5)*TAILLE_CASE_Y,j->missile_selectione);
                }
                if(j->id_missile_selectione==8)
                {
                    tirer_missile(*j,cos(j->angle_tir)*PUISSANCE_CANON_STOP,sin(j->angle_tir)*PUISSANCE_CANON_STOP,(j->bombardier.xi+0.5)*TAILLE_CASE_X,(j->bombardier.yi+0.5)*TAILLE_CASE_Y,j->missile_selectione);
                }
                if(j->id_missile_selectione==9)
                {
                    if(j->largueur_lance==0)
                    {
                        j->largueur_lance=1;
                        j->avion->existence=1;
                        j->avion->x=XFENETRE*j->n_joueur;
                        j->avion->y=YFENETRE/7;
                        j->nbre_tirs-=1;
                    }
                    else
                    {
                        tirer_missile(*j,(1-j->n_joueur*2)*sqrt(2)*j->puissance_tir_cannon/1.5,sqrt(2)*j->puissance_tir_cannon/1.5,j->avion->x,j->avion->y,j->missile_selectione);
                    }
                }
            }
            else
            {
                if(j->id_missile_selectione==1)
                {
                    tirer_missile(*j,cos(j->angle_tir)*j->puissance_tir_cannon,sin(j->angle_tir)*j->puissance_tir_cannon,(j->bombardier.xi+0.5)*TAILLE_CASE_X,(j->bombardier.yi+0.5)*TAILLE_CASE_Y,j->missile_selectione);
                }
                if(j->id_missile_selectione==9 && j->points_destruction>PRIX_MISSILES_CIBLE && j->precision_debloques[7]==2 && j->nbre_tirs<=2)
                {
                    j->points_destruction-=PRIX_MISSILES_CIBLE;
                    tirer_missile(*j,(1-j->n_joueur*2)*sqrt(2)*j->puissance_tir_cannon/1.5,sqrt(2)*j->puissance_tir_cannon/1.5,j->avion->x,j->avion->y,j->missile_selectione);
                }
            }
            j->nbre_tirs+=1;
        }
        if(!al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_SPACE))
        {
            appuye=0;
        }
        if(j->precision_debloques[1]==2)
        {
            al_draw_line((j->bombardier.xi+0.5)*TAILLE_CASE_X,(j->bombardier.yi+0.5)*TAILLE_CASE_Y+YFENETRE/NBRE_CASES_Y,(j->bombardier.xi+0.5)*TAILLE_CASE_X+LONGEUR_LIGNE_TIR*j->puissance_tir_cannon/PUISSANCE_CANON_INITIALE,(j->bombardier.yi+0.5)*TAILLE_CASE_Y+YFENETRE/NBRE_CASES_Y,JAUNE,LARGEUR_LIGNE_TIR);
            if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_LEFT))
            {
                j->puissance_tir_cannon-=5;
                if(j->puissance_tir_cannon<0)
                {
                    j->puissance_tir_cannon+=5;
                }
            }
            if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_RIGHT))
            {
                j->puissance_tir_cannon+=5;
                if(j->puissance_tir_cannon>1.5*PUISSANCE_CANON_INITIALE)
                {
                    j->puissance_tir_cannon-=5;
                }
            }
        }
    }
}
void gerer_bouton_inventaire(objet_fixe* o,ALLEGRO_BITMAP* selection_jaune,SOURIS,
                         	ALLEGRO_BITMAP* inventaire,ALLEGRO_BITMAP* case_inv,int nbre_cases_x,
                         	int nbre_cases_y,double taille,double x,double y,ALLEGRO_BITMAP* icones[],
                        	joueur* j,ALLEGRO_BITMAP* selection,item_missile missiles[],int n_tour,
                        	ALLEGRO_FONT* police,ALLEGRO_COLOR couleur,CLAVIER,ALLEGRO_BITMAP* explications[])
{
	static int b=0;
	int c=0;
	static int clic;
	int id;
	int id_missile_selectione_depart=j->id_missile_selectione;
	static int d=0;
	selection_objet_jaune(selection_jaune,*o,mouse);
	if(n_tour!=0-MOD_CHEAT() && (j->nbre_tirs==0 || MOD_CHEAT()==1))
	{
	    if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_ESCAPE))
        {
            b=0;
        }
    	if(clic_objet_fixe(mouse,*o) && clic==0)
    	{
        	clic=1;
        	if(b==1)
        	{
            	b=0;
            	c=1;
        	}
        	if(b==0 && c==0)
        	{
            	b=1;
        	}
    	}
    	if(b==1)
    	{
        	id=j->id_missile_selectione;
        	j->id_missile_selectione=afficher_inventaire_et_renvoyer_id_item_si_clic(inventaire,case_inv,nbre_cases_x,nbre_cases_y,taille,x,y,icones,*j,selection,mouse,id,police,couleur,missiles,explications,&b,clic);
        	if(round(j->points_destruction_debut_tour)>=missiles[id].prix)
            {
                j->points_destruction=j->points_destruction_debut_tour-missiles[id].prix;
                if(id!=0)
                {
                    j->missile_selectione=missiles[id].missile;
                }
            }
            else
            {
                j->id_missile_selectione=1;
            }
    	}
    	if(d==1)
        {
            d=0;
            b=0;
        }
        if(j->id_missile_selectione!=id_missile_selectione_depart)
        {
            d=1;
        }
    	if(!clic_objet_fixe(mouse,*o))
    	{
        	clic=0;
    	}
	}
}
int passer_souris_sur_carre(SOURIS,double x1 ,double y1, double x2,double y2)
{
	if(mouse.x>=x1 && mouse.y>=y1 && mouse.x<=x2 && mouse.y<=y2)
	{
    	return 1;
	}
	else
	{
    	return 0;
	}
}

void gere_xp(joueur j[])
{
    int i;
    for(i=0;i<=1;i++)
    {
        if(j[i].xp>=j[i].xp_pour_lvlup)
        {
            j[i].xp-=j[i].xp_pour_lvlup;
            j[i].pts_competences+=1;
            j[i].niveau+=1;
            j[i].xp_pour_lvlup*=j[i].coef_xp_lvl_sup;
        }
    }
}
void ajouter_missile_dans_inventaire(joueur* j,int id_item)
{
    int a=0;
    int i;
    for(i=1;i<=NBRE_CASES_INVENTAIRE;i++)
    {
        if(j->inventaire[i]==0 && a==0)
        {
            a=1;
            j->inventaire[i]=id_item;
        }
    }
}
void enlever_tempo_blocs_bois(carre c[NBRE_CASES_Y][NBRE_CASES_X],joueur j,CLAVIER)
{
    int x;
    int y;
    static int appu=0;
    if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_ENTER) && appu==0)
    {
        appu=1;
        for(x=0;x<=NBRE_CASES_X-1;x++)
        {
            for(y=0;y<=NBRE_CASES_Y-1;y++)
            {
                if(c[y][x].id==7 && c[y][x].au_joueur==j.n_joueur && c[y][x].enleve_tempo==0)
                {
                    c[y][x].enleve_tempo=1;
                }
                else
                {
                    c[y][x].enleve_tempo=0;
                }
            }
        }
    }
    if(!al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_ENTER) && appu==1)
    {
        appu=0;
    }
}
void gerer_victoire(joueur j[],carre c[NBRE_CASES_Y][NBRE_CASES_X],int joueur_qui_joue,int tour,int* fond,ALLEGRO_COLOR couleur,ALLEGRO_FONT* police)
{
    int i;
    static int p1=0;
    static int p0=0;
    *fond=1;
    if(tour>=1)
    {
        j[joueur_qui_joue].bombardier.pv=c[j[joueur_qui_joue].bombardier.yi][j[joueur_qui_joue].bombardier.xi].pv;
        if(c[j[1].bombardier.yi][j[1].bombardier.xi].id==0 && p1==0)
        {
            p1=1;
            j[1].canon_place=2;
            j[1].compteur_tour_replacer_canon=0;
        }
        if(c[j[0].bombardier.yi][j[0].bombardier.xi].id==0 && p0==0)
        {
            p0=1;
            j[0].canon_place=2;
            j[0].compteur_tour_replacer_canon=0;
        }
        if(c[j[0].coeur_yi][j[0].coeur_xi].id!=6)
        {
            printf("    VICTOIRE DU JOUEUR   2");
            *fond=4;
            al_draw_textf(police,couleur,XFENETRE/8,YFENETRE/4,0,"VICTOIRE DU JOUEUR DE DROITE");
        }
        if(c[j[1].coeur_yi][j[1].coeur_xi].id!=6)
        {
            printf("    VICTOIRE DU JOUEUR   1");
            al_draw_textf(police,couleur,XFENETRE/8,YFENETRE/4,0,"VICTOIRE DU JOUEUR DE GAUCHE");
            *fond=4;
        }
        if(j[1].canon_place==1)
        {
            p1=0;
        }
        if(j[0].canon_place==1)
        {
            p0=0;
        }
    }
}
void gerer_largueur(joueur* j)
{
    j->avion->flag=1-j->n_joueur;
    if(j->avion->existence==1)
    {
        j->avion->x+=(1-2*j->n_joueur)*j->puissance_tir_cannon*sqrt(2)/(3*FPS);
        if(j->avion->x<0 || j->avion->x>XFENETRE)
        {
            j->avion->existence=0;
            j->largueur_lance=0;
        }
    }
}
