#include "fonctions.h"
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
double round(double variable)
{
     return floor(variable+0.5);
}
void erreur(const char*txt)
{
    ALLEGRO_DISPLAY*d;
    d=al_is_system_installed()?al_get_current_display():NULL;
    al_show_native_message_box(NULL,"ERREUR",txt,NULL,NULL,0);
    exit(EXIT_FAILURE);
}
int retablisseur(int valeur,int valeur_max,int valeur_min)
{
    if(valeur>valeur_max)
    {
        valeur=valeur_min;
    }
    return valeur;
}
double distance(double x1,double y1, double x2, double y2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
int random(int a, int b)
{
    if(a<=0 && b<=0)
    {
        return -random(-b,-a);
    }
    else
    {
        return rand()%(b-a+1) + a;
    }
}
int MOD_CHEAT()
{
    int mod_cheat=0;
    fscanf(fopen("dim.txt", "r"),"MOD CHEAT:%d",&mod_cheat);
    return mod_cheat;
}
double taille_fenetre_x()
{
    static int i=0;
    static int taille=0;
    static double tf=0;
    if(i==0)
    {
        fscanf(fopen("x_fenetre.txt", "r"),"%d",&taille);
        tf=taille+0.00;
        i++;
    }
    return tf;
}
double taille_fenetre_y()
{
    static int y=0;
    static int tailley=0;
    static double tf=0;
    if(y==0)
    {
        fscanf(fopen("y_fenetre.txt", "r"),"%d",&tailley);
        tf=tailley+0.00;
        y++;
    }
    return tf;
}
