#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "fonctions.h"
#include "affichage.h"
#include "objets.h"
#include "tailles_images.h"
void afficher_fond(ALLEGRO_BITMAP* bitmap,fenetre f,int j)
{
    al_draw_scaled_rotated_bitmap(bitmap,0,0,0,0,f.Xfenetre/taille_fond_x,f.Yfenetre/taille_fond_y,0,j);
}
void afficher_blocs(fenetre f,carre c[NBRE_CASES_Y][NBRE_CASES_X],ALLEGRO_BITMAP* bitmap[])
{
    int i=0;
    int j=0;
    for(i=0;i<f.cases_x;i++)
    {
        for(j=0;j<f.cases_y;j++)
        {
            if(c[j][i].id!=0)
            {
                al_draw_scaled_rotated_bitmap(bitmap[c[j][i].id],0,0,c[j][i].x,c[j][i].y,(f.Xfenetre/f.cases_x)/taille_materiau,(f.Yfenetre/f.cases_y)/taille_materiau,0,c[j][i].au_joueur);
            }
        }
    }
}
void afficher_selection(ALLEGRO_BITMAP* bitmap,point_case souris,fenetre f)
{
    al_draw_scaled_rotated_bitmap(bitmap,0,0,souris.x*(f.Xfenetre/f.cases_x),souris.y*(f.Yfenetre/f.cases_y),(f.Xfenetre/f.cases_x)/taille_selec,(f.Yfenetre/f.cases_y)/taille_selec,0,0);
}
void afficher_blocs_selec(ALLEGRO_BITMAP* selec,ALLEGRO_BITMAP* blocs[],joueur* j,double taille,fenetre f,item it[],ALLEGRO_MOUSE_STATE mouse,ALLEGRO_BITMAP* explications[])
{
    int i;
    int n=1;
    int c=0;
    for(i=1;i<=it[1].nbre_blocs_actuel;i++)
    {
        if(it[i].placable==1)
        {
            al_draw_scaled_rotated_bitmap(blocs[i],0,0,f.Xfenetre-(taille_materiau*taille)*n,0,taille,taille,0,0);
            al_draw_scaled_rotated_bitmap(selec,0,0,f.Xfenetre-(taille_materiau*taille)*(j->n_item_placable_sel),0,taille,taille,0,0);
            if(mouse.x>f.Xfenetre-(taille_materiau*taille)*n && mouse.x<f.Xfenetre-(taille_materiau*taille)*(n-1) && mouse.y>0 && mouse.y<taille_materiau*taille)
            {
                al_draw_scaled_rotated_bitmap(selec,0,0,f.Xfenetre-(taille_materiau*taille)*n,0,taille,taille,0,0);
                c=i;
                if(mouse.buttons&1)
                {
                    j->id_selectionee=i;
                    j->n_item_placable_sel=n;
                }
            }
            n+=1;
        }
        if(c!=0)
        {
            al_draw_scaled_rotated_bitmap(explications[c],taille_indication_bloc_x,0,mouse.x,mouse.y,1,1,0,0);
        }
    }
}
void afficher_objet_anime(objet_anime* o)
{
    if(o->existence==1)
    {
        if(o->animation[0]==1)
        {
            o->compteur_animation+=o->vitesse_animation;
            if(o->compteur_animation>o->animation[2])
            {
                o->animation[0]=0;
                o->compteur_animation=1;
                o->etat_animation=o->animation[3];
            }
            else
            {
                o->etat_animation=round(o->compteur_animation);
            }
        }
        al_draw_scaled_rotated_bitmap(o->bitmap[o->etat_animation],0,0,o->x-o->taille_x*o->taille/2*COEF_PIXEL_X,o->y-o->taille_y*o->taille/2*COEF_PIXEL_Y,o->taille*COEF_PIXEL_X,o->taille*COEF_PIXEL_Y,o->angle,0);
    }
}
void afficher_objet_anime_en_masse(objet_anime o[],int nbre_objets)
{
    int i;
    for(i=0;i<=nbre_objets;i++)
    {
        if(o[i].existence==1)
        {
            if(o[i].animation[0]==1)
            {
                o[i].compteur_animation+=o[i].vitesse_animation;
                if(o[i].compteur_animation>o[i].animation[2])
                {
                    o[i].animation[0]=0;
                    o[i].compteur_animation=1;
                    o[i].etat_animation=o[i].animation[3];
                }
                else
                {
                    o[i].etat_animation=round(o[i].compteur_animation);
                }
            }
            al_draw_scaled_rotated_bitmap(o[i].bitmap[o[i].etat_animation],0,0,o[i].x-o[i].taille_x*o[i].taille/2*COEF_PIXEL_X,o[i].y-o[i].taille_y*o[i].taille/2*COEF_PIXEL_Y,o[i].taille*COEF_PIXEL_X,o[i].taille*COEF_PIXEL_Y,o[i].angle,0);
        }
    }
}
void interface_competences(CLAVIER,int* interface_du_jeu,int* fond,SOURIS,ALLEGRO_BITMAP* selection_jaune,joueur j,ALLEGRO_FONT* police)
{
    double jsp=round(100*COEF_PIXEL_Y)/100;
    static int a=0;
    if(!al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_TAB) && a==1)
        {
            a=0;
        }
    if(*interface_du_jeu==0)
    {
        if(passer_souris_sur_carre(mouse,XFENETRE/5,TAILLE_ECRITUR_SCORE*COEF_PIXEL_Y,XFENETRE/5+taille_barre_xp_x*COEF_PIXEL_X,TAILLE_ECRITUR_SCORE*COEF_PIXEL_Y+taille_barre_xp_y*COEF_PIXEL_Y))
        {
            al_draw_scaled_rotated_bitmap(selection_jaune,0,0,XFENETRE/5,TAILLE_ECRITUR_SCORE*COEF_PIXEL_Y,COEF_PIXEL_X*taille_barre_xp_x/taille_selec,jsp*taille_barre_xp_y/taille_selec,0,0);
            al_draw_textf(police,BLEU,XFENETRE/5+taille_barre_xp_x*COEF_PIXEL_X/2,TAILLE_ECRITUR_SCORE*COEF_PIXEL_Y+taille_barre_xp_y*COEF_PIXEL_Y,ALLEGRO_ALIGN_CENTRE,"XP: %.0f/%.0f",j.xp,j.xp_pour_lvlup);
        }
        if((al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_TAB) || (passer_souris_sur_carre(mouse,XFENETRE/5,TAILLE_ECRITUR_SCORE,XFENETRE/5+taille_barre_xp_x*COEF_PIXEL_X,TAILLE_ECRITUR_SCORE+taille_barre_xp_y*COEF_PIXEL_Y) && mouse.buttons&1)) && a==0)
        {
            *fond=2;
            *interface_du_jeu=1;
            a=1;
        }
    }
    if(*interface_du_jeu==1)
    {
        if((al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_TAB) || al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_ESCAPE) || mouse.buttons&2) && a==0)
        {
            *fond=1;
            *interface_du_jeu=0;
            a=1;
        }
    }
}
void afficher_objet_fixe(objet_fixe o)
{
    if(o.existence==1){al_draw_scaled_rotated_bitmap(o.bitmap,o.taille_x/2,o.taille_y/2,o.x,o.y,o.tailleX*COEF_PIXEL_X,o.tailleY*COEF_PIXEL_Y,o.angle,0);}
}
void afficher_objet_fixe_en_masse(objet_fixe o[],int nbre_objets)
{
    int i;
    for(i=0;i<=nbre_objets;i++)
    {
        if(o[i].existence==1)
        {
            al_draw_scaled_rotated_bitmap(o[i].bitmap,o[i].taille_x/2*COEF_PIXEL_X,o[i].taille_y/2*COEF_PIXEL_Y,o[i].x,o[i].y,o[i].tailleX*COEF_PIXEL_X,o[i].tailleY*COEF_PIXEL_Y,o[i].angle,0);
        }
    }
}
void afficher_objet_fixe_en_masse_c(objet_fixe o[],int nbre_objets)
{
    int i;
    for(i=0;i<=nbre_objets;i++)
    {
        if(o[i].existence==1)
        {
            al_draw_scaled_rotated_bitmap(o[i].bitmap,o[i].taille_x/2,o[i].taille_y/2,o[i].x,o[i].y,o[i].tailleX,o[i].tailleY,o[i].angle,0);
        }
    }
}
void tracer_ligne_entre_objets(objet_fixe o1, objet_fixe o2,double epaisseur, ALLEGRO_COLOR couleur)
{
    al_draw_line(o1.x,o1.y,o2.x,o2.y,couleur,epaisseur*(o1.tailleX+o1.tailleY/2)+(o2.tailleY+o1.tailleY/2)/2);
}
void connexions(objet_fixe o[],int nbre_objets,joueur jo)
{
    int i;
    int j;
    for(i=1;i<=NBRE_COMPETENCES_EXPLO;i++)
    {
        for(j=1;j<=NBRE_LIAISONS_COMPTENCES_MAX;j++)
        {
            if(o[i].utile2[j]!=0)
            {
                if(o[i].id==1 && i!=8)
                {
                    if(jo.explosion_debloques[i]!=2)
                    {
                        tracer_ligne_entre_objets(o[i],o[o[i].utile2[j]],taille_liaisons,JAUNE_FONCE);
                    }
                    else
                    {
                        tracer_ligne_entre_objets(o[i],o[o[i].utile2[j]],taille_liaisons,JAUNE);
                    }
                }
                if(o[i].id==2)
                {
                    if(jo.science_debloques[i]!=2)
                    {
                        tracer_ligne_entre_objets(o[i],o[o[i].utile2[j]],taille_liaisons,JAUNE_FONCE);
                    }
                    else
                    {
                        tracer_ligne_entre_objets(o[i],o[o[i].utile2[j]],taille_liaisons,JAUNE);
                    }
                }
                if(o[i].id==3)
                {
                    if(jo.precision_debloques[i]!=2)
                    {
                        tracer_ligne_entre_objets(o[i],o[o[i].utile2[j]],taille_liaisons,JAUNE_FONCE);
                    }
                    else
                    {
                        tracer_ligne_entre_objets(o[i],o[o[i].utile2[j]],taille_liaisons,JAUNE);
                    }
                }
            }
        }

    }
}
void afficher_acces_comptetences(ALLEGRO_BITMAP* debloque,ALLEGRO_BITMAP* inaccessible,joueur* j,objet_fixe o[])
{
    int i=1;
    for(i=1;i<=NBRE_COMPETENCES_EXPLO;i++)
    {
        if(o[i].id==1)
        {
            if(j->explosion_debloques[i]>=0 && j->explosion_debloques[i]<1)
            {
                al_draw_scaled_rotated_bitmap(inaccessible,0,0,o[i].x-o[i].taille_x*o[i].tailleX/2,o[i].y-o[i].taille_y*o[i].tailleY/2,TAILLE_COMPETENCE*o[i].tailleX/taille_inaccessible,TAILLE_COMPETENCE*o[i].tailleY/taille_inaccessible,0,0);
            }
            if(j->explosion_debloques[i]==2)
            {
                al_draw_scaled_rotated_bitmap(debloque,0,0,o[i].x-o[i].taille_x*o[i].tailleX/2,o[i].y-o[i].taille_y*o[i].tailleY/2,TAILLE_COMPETENCE*o[i].tailleX/taille_inaccessible,TAILLE_COMPETENCE*o[i].tailleY/taille_inaccessible,0,0);
            }
        }
        if(o[i].id==2)
        {
            if(j->science_debloques[i]>=0 && j->science_debloques[i]<1)
            {
                al_draw_scaled_rotated_bitmap(inaccessible,0,0,o[i].x-o[i].taille_x*o[i].tailleX/2,o[i].y-o[i].taille_y*o[i].tailleY/2,TAILLE_COMPETENCE*o[i].tailleX/taille_inaccessible,TAILLE_COMPETENCE*o[i].tailleY/taille_inaccessible,0,0);
            }
            if(j->science_debloques[i]==2)
            {
                al_draw_scaled_rotated_bitmap(debloque,0,0,o[i].x-o[i].taille_x*o[i].tailleX/2,o[i].y-o[i].taille_y*o[i].tailleY/2,TAILLE_COMPETENCE*o[i].tailleX/taille_inaccessible,TAILLE_COMPETENCE*o[i].tailleY/taille_inaccessible,0,0);
            }
        }
        if(o[i].id==3)
        {
            if(j->precision_debloques[i]>=0 && j->precision_debloques[i]<1)
            {
                al_draw_scaled_rotated_bitmap(inaccessible,0,0,o[i].x-o[i].taille_x*o[i].tailleX/2,o[i].y-o[i].taille_y*o[i].tailleY/2,TAILLE_COMPETENCE*o[i].tailleX/taille_inaccessible,TAILLE_COMPETENCE*o[i].tailleY/taille_inaccessible,0,0);
            }
            if(j->precision_debloques[i]==2)
            {
                al_draw_scaled_rotated_bitmap(debloque,0,0,o[i].x-o[i].taille_x*o[i].tailleX/2,o[i].y-o[i].taille_y*o[i].tailleY/2,TAILLE_COMPETENCE*o[i].tailleX/taille_inaccessible,TAILLE_COMPETENCE*o[i].tailleY/taille_inaccessible,0,0);
            }
        }
    }
}
void selection_objets_jaune(ALLEGRO_BITMAP* selection_jaune,objet_fixe o[],int nombre_objets,SOURIS)
{
    int i;
    for(i=1;i<=nombre_objets;i++)
    {
        if(toucher_objet_fixe(mouse,o[i]))
        {
            al_draw_scaled_rotated_bitmap(selection_jaune,0,0,o[i].x-o[i].taille_x*o[i].tailleX/2,o[i].y-o[i].taille_y*o[i].tailleY/2,o[i].taille_x*o[i].tailleX/taille_selec,o[i].taille_y*o[i].tailleY/taille_selec,0,0);
        }
    }
}
void selection_objet_jaune(ALLEGRO_BITMAP* selection_jaune,objet_fixe o,SOURIS)
{
    if(toucher_objet_fixe(mouse,o))
    {
        al_draw_scaled_rotated_bitmap(selection_jaune,0,0,o.x-o.taille_x*o.tailleX/2*COEF_PIXEL_X,o.y-o.taille_y*o.tailleY/2*COEF_PIXEL_Y,o.taille_x*o.tailleX/taille_selec*COEF_PIXEL_X,o.taille_y*o.tailleY/taille_selec*COEF_PIXEL_Y,0,0);
    }
}
void afficher_fusees(fusee_missile f[])
{
    int i;
    for(i=0;i<=NBRE_FUSEES;i++)
    {
        if(f[i].fusee.existence==1)
        {
            if(f[i].explosion.animation[0]==0)
            {
                afficher_objet_fixe(f[i].fusee);
            }
            if(f[i].explosion.animation[0]==1)
            {
                afficher_objet_anime(&f[i].explosion);
            }
        }
    }
}
int afficher_inventaire_et_renvoyer_id_item_si_clic(ALLEGRO_BITMAP* inventaire,ALLEGRO_BITMAP* case_inv,int nbre_cases_x,int nbre_cases_y,double taille,double x,double y,ALLEGRO_BITMAP* icones[],joueur jo, ALLEGRO_BITMAP* selection,SOURIS,int item_selectione_initial,ALLEGRO_FONT* police,ALLEGRO_COLOR couleur,item_missile missiles[],ALLEGRO_BITMAP* explications[])
{
    int i;
    int j;
    int a=0;
    int id_touche;
    a=item_selectione_initial;
    al_draw_scaled_rotated_bitmap(inventaire,taille_inventaire_x/2,taille_inventaire_y/2,x,y,taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y),taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y),0,0);
    for(i=1;i<=nbre_cases_x;i++)
    {
        for(j=1;j<=nbre_cases_y;j++)
        {
            al_draw_scaled_rotated_bitmap(case_inv,taille_case_x/2,taille_case_y/2,x-taille_inventaire_x/2*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)+i*taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)-taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(2*(nbre_cases_x+nbre_cases_y)),y-taille_inventaire_y/2*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)+j*taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)-taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(2*(nbre_cases_x+nbre_cases_y)),0.8*taille/(nbre_cases_x+nbre_cases_y)*taille_inventaire_x/taille_case_x,0.8*taille/(nbre_cases_x+nbre_cases_y)*taille_inventaire_y/taille_case_y,0,0);
            if(jo.inventaire[i+(j-1)*nbre_cases_x]!=0)
            {
                al_draw_scaled_rotated_bitmap(icones[jo.inventaire[i+(j-1)*nbre_cases_x]],taille_icones_x/2,taille_icones_y/2,x-taille_inventaire_x/2*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)+i*taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)-taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(2*(nbre_cases_x+nbre_cases_y)),y-taille_inventaire_y/2*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)+j*taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)-taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(2*(nbre_cases_x+nbre_cases_y)),0.8*taille/(nbre_cases_x+nbre_cases_y),0.8*taille/(nbre_cases_x+nbre_cases_y),0,0);
                if(jo.inventaire[i+(j-1)*nbre_cases_x]==jo.id_missile_selectione)
                {
                    al_draw_scaled_rotated_bitmap(selection,taille_case_x/2,taille_case_y/2,x-taille_inventaire_x/2*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)+i*taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)-taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(2*(nbre_cases_x+nbre_cases_y)),y-taille_inventaire_y/2*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)+j*taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)-taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(2*(nbre_cases_x+nbre_cases_y)),0.8*taille/(nbre_cases_x+nbre_cases_y)*taille_inventaire_x/taille_case_x,0.8*taille/(nbre_cases_x+nbre_cases_y)*taille_inventaire_y/taille_case_y,0,0);
                }
                al_draw_textf(police,couleur,-3*taille_case_x/2*COEF_PIXEL_X+taille_case_x*0.8*taille/(nbre_cases_x+nbre_cases_y)+x-taille_inventaire_x/2*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)+i*taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)-taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(2*(nbre_cases_x+nbre_cases_y)),taille_case_y*0.8*taille/(nbre_cases_x+nbre_cases_y)+y-taille_inventaire_y/2*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)+j*taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)-taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(2*(nbre_cases_x+nbre_cases_y))-3*COEF_PIXEL_Y,0,"%.0f pts",missiles[jo.inventaire[i+(j-1)*nbre_cases_x]].prix);
            }
            if(passer_souris_sur_carre(mouse,-taille_case_x*0.8*taille/(nbre_cases_x+nbre_cases_y)+x-taille_inventaire_x/2*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)+i*taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)-taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(2*(nbre_cases_x+nbre_cases_y))
                                       ,-taille_case_y*0.8*taille/(nbre_cases_x+nbre_cases_y)+y-taille_inventaire_y/2*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)+j*taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)-taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(2*(nbre_cases_x+nbre_cases_y))
                                       ,taille_case_x*0.8*taille/(nbre_cases_x+nbre_cases_y)+x-taille_inventaire_x/2*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)+i*taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)-taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(2*(nbre_cases_x+nbre_cases_y))
                                       ,taille_case_y*0.8*taille/(nbre_cases_x+nbre_cases_y)+y-taille_inventaire_y/2*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)+j*taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)-taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(2*(nbre_cases_x+nbre_cases_y))))
            {
                al_draw_scaled_rotated_bitmap(selection,taille_case_x/2,taille_case_y/2,x-taille_inventaire_x/2*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)+i*taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(nbre_cases_x+nbre_cases_y)-taille_inventaire_x/(nbre_cases_x)*taille*nbre_cases_x/(2*(nbre_cases_x+nbre_cases_y)),y-taille_inventaire_y/2*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)+j*taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(nbre_cases_x+nbre_cases_y)-taille_inventaire_y/(nbre_cases_y)*taille*nbre_cases_y/(2*(nbre_cases_x+nbre_cases_y)),0.8*taille/(nbre_cases_x+nbre_cases_y)*taille_inventaire_x/taille_case_x,0.8*taille/(nbre_cases_x+nbre_cases_y)*taille_inventaire_y/taille_case_y,0,0);
                id_touche=jo.inventaire[i+(j-1)*nbre_cases_x];
                if(mouse.buttons&1 && jo.inventaire[i+(j-1)*nbre_cases_x]!=0)
                {
                    a=jo.inventaire[i+(j-1)*nbre_cases_x];
                }
            }
        }
    }
    if(id_touche!=0)
    {
        al_draw_scaled_rotated_bitmap(explications[id_touche],0,0,mouse.x,mouse.y,1,1,0,0);
    }
    return a;
}
void afficher_scores(ALLEGRO_FONT* police,ALLEGRO_COLOR couleur,joueur j,double x)
{
    int points_entiers=round(j.points_destruction);
    al_draw_textf(police,couleur,x,0,0,"Points:");
    al_draw_textf(police,couleur,x,TAILLE_ECRITUR_SCORE*COEF_PIXEL_Y,0,"%d",points_entiers);
}
void afficher_tune(ALLEGRO_FONT* police,ALLEGRO_COLOR couleur,joueur j)
{
    int tune_entiers=round(j.tune);
    al_draw_textf(police,couleur,0,-1,0,"Argent: %d",tune_entiers);
}
void afficher_barre_xp(ALLEGRO_BITMAP* barre[],joueur j,ALLEGRO_COLOR couleur,ALLEGRO_FONT* police)
{
    double jsp_pk_ca_bug=round(YFENETRE*100/950)/100;
    al_draw_textf(police,couleur,XFENETRE/4,-1,0,"Niveau: %d",j.niveau);
    al_draw_tinted_scaled_rotated_bitmap_region(barre[1],0,0,taille_barre_xp_x,taille_barre_xp_y,al_map_rgba_f(1,1,1,1),0,0,XFENETRE/5,TAILLE_ECRITUR_SCORE*COEF_PIXEL_Y,COEF_PIXEL_X,jsp_pk_ca_bug,0,0);
    al_draw_tinted_scaled_rotated_bitmap_region(barre[2],0,0,j.xp/j.xp_pour_lvlup*taille_barre_xp_x,taille_barre_xp_y,al_map_rgba_f(1,1,1,1),0,0,XFENETRE/5,TAILLE_ECRITUR_SCORE*COEF_PIXEL_Y,COEF_PIXEL_X,jsp_pk_ca_bug,0,0);
}
void afficher_pts_competences(joueur j,ALLEGRO_COLOR couleur,ALLEGRO_FONT* police)
{
    al_draw_textf(police,couleur,XFENETRE/3-20*COEF_PIXEL_X,0,0,"Points disponibles: %d",j.pts_competences);
}
void afficher_pointeur_souris(joueur j,SOURIS,ALLEGRO_BITMAP* pointeur)
{
    double jsp_pk_ca_bug=round(YFENETRE*100/950)/100;
    double jsp_pk_ca_bugx=round(XFENETRE*100/1662.5)/100;
    if(j.id_missile_selectione==9 || j.id_missile_selectione==10)
    {
        al_draw_scaled_rotated_bitmap(pointeur,taille_cible_x_y/2,taille_cible_x_y/2,mouse.x,mouse.y,COEF_PIXEL_X,jsp_pk_ca_bug,0,0);
    }
}
void afficher_conseil(joueur j,ALLEGRO_COLOR couleur,ALLEGRO_FONT* police)
{
    if(j.canon_place==2 && j.compteur_tour_replacer_canon>=NRBE_TOURS_POUR_REPLACER_CANON)
    {
        al_draw_textf(police,couleur,XFENETRE/4,YFENETRE/4,0,"Joueur %d, vous pouvez replacer votre canon",1+j.n_joueur);
    }
}
void afficher_explications_competences(objet_fixe c1[],objet_fixe c2[],objet_fixe c3[],ALLEGRO_BITMAP* explications[],SOURIS)
{
    int i;
    double jsp_pk_ca_bug=1;
    for(i=1;i<=NBRE_COMPETENCES_EXPLO;i++)
    {
        if(toucher_objet_fixe(mouse,c1[i]))
        {
            al_draw_scaled_rotated_bitmap(explications[i],0,0,mouse.x,mouse.y,taille_indication_competences,jsp_pk_ca_bug*taille_indication_competences,0,0);
        }
    }
    for(i=1;i<=NBRE_COMPETENCES_SCIENCE;i++)
    {
        if(toucher_objet_fixe(mouse,c2[i]))
        {
            al_draw_scaled_rotated_bitmap(explications[8+i],0,0,mouse.x,mouse.y,taille_indication_competences,jsp_pk_ca_bug*taille_indication_competences,0,0);
        }
    }
    for(i=1;i<=NBRE_COMPETENCES_PRECISION;i++)
    {
        if(toucher_objet_fixe(mouse,c3[i]))
        {
            al_draw_scaled_rotated_bitmap(explications[16+i],taille_indication_competences_x,0,mouse.x,mouse.y,taille_indication_competences,jsp_pk_ca_bug*taille_indication_competences,0,0);
        }
    }
}
