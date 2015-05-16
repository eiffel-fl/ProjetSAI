#include "labyrinthe.h"
#include <math.h>
#define ANGLE_MAX 1200


struct struct_joueur{
  float x;
  float y;
  float z;
  float x2;
  float y2;
  float z2;
  float x_av;
  float z_av;
  float x_ar;
  float z_ar;
  float y_ap;
};

typedef struct struct_joueur joueur;

extern joueur A;

extern int tz;     //liste des flags correspondant aux touches
extern int tq;
extern int ts;
extern int td;
extern int tl;
extern int tr;
extern int tu;
extern int tb;
extern int te;
extern int tsp;
extern int a;

extern int enlair;   //flags supplémentaire (peut-être qu'il y en aura d'autre)
extern int monte;

extern float ang;    //ang et ang2 représente respectivement l'angle de vue horizontal et vertical du joueur.
extern float ang2;


extern float x_s1; //A l'origine, prévu pour la fonction de calcule d'angle.
extern float y_s1; //Utiliser pour la hauteur et largeur de la fenêtre, mais en float.


extern float y_sol;  //sert à determiner la hauteur du sol

extern float interx;     //variable intermédiaire servant dans le calcul dans le déplacement,
extern float interz;     //mais concrètement, elles font rien.


extern float vitesse;      //vitesse est la vitesse du joeueur dans la direction à laquelle if fait face.
extern float vitesse_s;    //vitesse_s est la vitesse de déplacement sur le coté.
extern float vitesse_v;    //vitesse_v est la vitesse verticale.

extern float cos1;
extern float sin1;         //toutes ces variables-là sont faite pour stocker des valeurs de cos et sin qu'on a à utiliser plusieurs fois.
extern float cos2;
extern float sin2;

void souris(int, int);
void gerer_clavier2(unsigned char, int, int);
void gerer_clavier(unsigned char, int, int);