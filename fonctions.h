#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#define VIOLET al_map_rgb(130,80,200)
#define VERTC al_map_rgb(165,230,20)
#define NOIR al_map_rgb(0,0,0)
#define CYAN al_map_rgb(0,255,255)
#define ROUGE al_map_rgb(255,0,0)
#define FINPARENTHESE }

#define COMPTEUR(comp, t_max) comp+=1;\
                          if(comp>=t_max)\
                          {\
                              comp=1;
#define VOIRSISABUG(variable) printf(" %d",variable);
#define VOIRSISABUGDOUBLE(variable)   printf(" %.2f",variable);
#define INITIALISERIMAGE(nom,passage) ALLEGRO_BITMAP*nom;\
                                    printf("%s",chemin);\
                                    printf("%s",chemin);\
                                    nom=al_load_bitmap(passage); \
                                    if (!nom)\
                                    {\
                                        printf(":   ERREUR:BITMAP PAS CHARGE\n");\
                                        erreur("al_load_bitmap()");\
                                    }\
                                    else\
                                    {\
                                        printf(":   loaded \n");\
                                    }
#define INITIALISER_IMAGES_EN_MASSE(nom,nombreImages,passage)   ALLEGRO_BITMAP*nom[nombreImages];\
                                                            for(i=1; i<=nombreImages; i++)\
                                                            {\
                                                                sprintf(chemin,"%s%d.png",passage,i);\
                                                                printf("%s",chemin);\
                                                                nom[i]=al_load_bitmap(chemin);\
                                                                if (!nom[i])\
                                                                {\
                                                                    printf(":   ERREUR:BITMAP PAS CHARGE\n");\
                                                                    erreur("al_load_bitmap()");\
                                                                }\
                                                                else\
                                                                {\
                                                                    printf(":   loaded \n");\
                                                                }\
                                                            }
#define ESCAPE if(al_key_down(&key,ALLEGRO_KEY_ESCAPE))\
                fin=1;

#define INITIALISER_BIBLIOTHEQUE double X0=0;\
    double Y0=0;\
    ALLEGRO_DISPLAY*display;\
    ALLEGRO_FONT*arial72;\
    ALLEGRO_EVENT_QUEUE*queue;\
    ALLEGRO_TIMER*timer;\
    if(!al_init_image_addon())\
        erreur("al_init_image_addon()");\
    if(!al_init())\
        erreur("al_init()");\
    if(!al_install_keyboard())\
        erreur("al_install_keyboard()");\
    display=al_create_display(Xfenetre,Yfenetre);\
    if(!display)\
        erreur("creation display");\
    if(!al_install_mouse())\
        erreur("al_install_mouse()");\
    al_init_font_addon();\
    if(!al_init_ttf_addon())\
        erreur("al_init_ttf_addon()");\
    arial72 = al_load_font("./tff/arial.ttf",72,0);\
    if(!arial72)\
        erreur("al_load_font()");\
    if(!al_init_primitives_addon())\
        erreur("al_primitives_addon()");\
    queue=al_create_event_queue();\
    if(!queue)\
        erreur("al_create_event_queue()");\
    timer=al_create_timer((1.0/50));\
    if(!timer)\
        erreur("al_create_timer()");\
    ALLEGRO_KEYBOARD_STATE key;\
    ALLEGRO_MOUSE_STATE mouse;\
    ALLEGRO_COLOR vertc =al_map_rgba(165,230,20,0);\
    ALLEGRO_COLOR rouge =al_map_rgba(255,0,0,255);\
    ALLEGRO_COLOR rougefonce =al_map_rgba(100,50,20,255);\
    ALLEGRO_COLOR noir =al_map_rgba(0,0,0,255);\
    ALLEGRO_COLOR bleuClair =al_map_rgba(51,204,255,255);\
    ALLEGRO_COLOR bleu =al_map_rgba(0,0,255,0);\
    ALLEGRO_COLOR vert =al_map_rgba(51,153,0,0);\
    ALLEGRO_COLOR blancbi =al_map_rgba(230,230,230,0);\
    ALLEGRO_COLOR blanc =al_map_rgba(255,255,255,0);\
    ALLEGRO_COLOR violet =al_map_rgba(130,80,200,0);\
    ALLEGRO_COLOR jaune =al_map_rgba(255,255,0,255);\
    ALLEGRO_COLOR jaune_fonce =al_map_rgba(150,150,0,255);\
    ALLEGRO_COLOR jaunetrans =al_map_rgba(255,255,0,0);\
    ALLEGRO_COLOR gris =al_map_rgba(150,150,150,255);\
    ALLEGRO_COLOR orange =al_map_rgba(255,102,0,150);\
    ALLEGRO_COLOR beige =al_map_rgba(234,193,138,255);\
    al_register_event_source(queue,al_get_keyboard_event_source());\
    al_register_event_source(queue,al_get_timer_event_source(timer));\
    al_register_event_source(queue,al_get_mouse_event_source());\
    al_start_timer(timer);\
    al_flip_display();\
    al_get_mouse_state(&mouse);\
    al_get_keyboard_state(&key);
#define JAUNE_FONCE al_map_rgba(120,120,0,255)
#define JAUNE al_map_rgba(255,255,0,255)
#define SOURIS ALLEGRO_MOUSE_STATE mouse
#define CLAVIER int ALLEGRO_KEYBOARD_STATE
double round(double variable);
void erreur(const char*txt);
int retablisseur(int valeur,int valeur_max,int valeur_min);
double distance(double x1,double y1, double x2, double y2);
int random(int a, int b);
#endif // FONCTIONS_H_INCLUDED
