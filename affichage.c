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
void afficher_fond(ALLEGRO_BITMAP* bitmap,fenetre f)
{
    al_draw_scaled_rotated_bitmap(bitmap,0,0,0,0,f.Xfenetre/taille_fond_x,f.Yfenetre/taille_fond_y,0,0);
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
                al_draw_scaled_rotated_bitmap(bitmap[c[j][i].id],0,0,c[j][i].x,c[j][i].y,(f.Xfenetre/f.cases_x)/taille_materiau,(f.Yfenetre/f.cases_y)/taille_materiau,0,0);
            }
        }
    }
}
void afficher_selection(ALLEGRO_BITMAP* bitmap,point_case souris,fenetre f)
{
    al_draw_scaled_rotated_bitmap(bitmap,0,0,souris.x*(f.Xfenetre/f.cases_x),souris.y*(f.Yfenetre/f.cases_y),(f.Xfenetre/f.cases_x)/taille_selec,(f.Yfenetre/f.cases_y)/taille_selec,0,0);
}
void afficher_blocs_selec(ALLEGRO_BITMAP* selec,ALLEGRO_BITMAP* blocs[],joueur* j,double taille,fenetre f,item it[],ALLEGRO_MOUSE_STATE mouse)
{
    int i;
    int n=1;
    for(i=1;i<=it[1].nbre_blocs_actuel;i++)
    {
        if(it[i].placable==1)
        {
            al_draw_scaled_rotated_bitmap(blocs[i],0,0,f.Xfenetre-(taille_materiau*taille)*n,0,taille,taille,0,0);
            al_draw_scaled_rotated_bitmap(selec,0,0,f.Xfenetre-(taille_materiau*taille)*(j->n_item_placable_sel),0,taille,taille,0,0);
            if(mouse.x>f.Xfenetre-(taille_materiau*taille)*n && mouse.x<f.Xfenetre-(taille_materiau*taille)*(n-1) && mouse.y>0 && mouse.y<taille_materiau*taille)
            {
                al_draw_scaled_rotated_bitmap(selec,0,0,f.Xfenetre-(taille_materiau*taille)*n,0,taille,taille,0,0);
                if(mouse.buttons&1)
                {
                    j->id_selectionee=i;
                    j->n_item_placable_sel=n;
                }
            }
            n+=1;
        }
    }
}
void afficher_objet_anime(objet_anime* o)
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
    al_draw_scaled_rotated_bitmap(o->bitmap[o->etat_animation],0,0,o->x,o->y,o->taille,o->taille,0,0);
}
void interface_competences(CLAVIER,int* interface_du_jeu,int* fond)
{
    static int a=0;
    if(!al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_TAB) && a==1)
        {
            a=0;
        }
    if(*interface_du_jeu==0)
    {
        if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_TAB) && a==0)
        {
            *fond=2;
            *interface_du_jeu=1;
            a=1;
        }
    }
    if(*interface_du_jeu==1)
    {
        if(al_key_down(ALLEGRO_KEYBOARD_STATE,ALLEGRO_KEY_TAB) && a==0)
        {
            *fond=1;
            *interface_du_jeu=0;
            a=1;
        }
    }
}
void afficher_objet_fixe(objet_fixe o)
{
    al_draw_scaled_rotated_bitmap(o.bitmap,0,0,o.x,o.y,o.taille,o.taille,0,0);
}
void tracer_ligne_entre_objets(objet_fixe o1, objet_fixe o2,double epaisseur, ALLEGRO_COLOR couleur)
{
    al_draw_line(o1.x+o1.taille_x*o1.taille/2,o1.y+o1.taille_y*o1.taille/2,o2.x+o2.taille_x*o2.taille/2,o2.y+o2.taille_y*o2.taille/2,couleur,epaisseur);
}
void connexions(objet_fixe o[],int nbre_objets)
{
    int i;
    int j;
    for(i=1;i<=NBRE_COMPETENCES_EXPLO;i++)
    {
        for(j=1;j<=NBRE_LIAISONS_COMPTENCES_MAX;j++)
        {
            if(o[i].utile2[j]!=0)
            {
                tracer_ligne_entre_objets(o[i],o[o[i].utile2[j]],taille_liaisons,JAUNE);
            }
        }

    }
}
