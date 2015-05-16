#include "interaction.h"


joueur A = {10, 21, 10, -9, 1, 0, 15, 15, 5, 5, 28}; //Le joueur sera nommé A parce que c'est plus court.

int tz = 0;     //liste des flags correspondant aux touches
int tq = 0;
int ts = 0;
int td = 0;
int tl = 0;
int tr = 0;
int tu = 0;
int tb = 0;
int te = 0;
int tsp = 0;
int a = 1;

int enlair = 0;   //flags supplémentaire (peut-être qu'il y en aura d'autre)
int monte = 0;

float ang = 0;    //ang et ang2 représente respectivement l'angle de vue horizontal et vertical du joueur.
float ang2 = 0;


float x_s1 = 400; //A l'origine, prévu pour la fonction de calcule d'angle.
float y_s1 = 300; //Utiliser pour la hauteur et largeur de la fenêtre, mais en float.


float y_sol = 0;  //sert à determiner la hauteur du sol

float interx;     //variable intermédiaire servant dans le calcul dans le déplacement,
float interz;     //mais concrètement, elles font rien.


float vitesse = 0;      //vitesse est la vitesse du joeueur dans la direction à laquelle if fait face.
float vitesse_s = 0;    //vitesse_s est la vitesse de déplacement sur le coté.
float vitesse_v = 0;    //vitesse_v est la vitesse verticale.

float cos1;
float sin1;         //toutes ces variables-là sont faite pour stocker des valeurs de cos et sin qu'on a à utiliser plusieurs fois.
float cos2;
float sin2;

void souris(int x_s, int y_s){
  ang += (M_PI/ANGLE_MAX) * (x_s - x_s1);
  ang2 += (M_PI/ANGLE_MAX) * -(y_s - y_s1);

  if (ang2 < -((ANGLE_MAX/2)-10) * M_PI/ANGLE_MAX)
  {
    ang2 = -((ANGLE_MAX/2)-10) * M_PI/ANGLE_MAX;
  }

  if (ang2 > ((ANGLE_MAX-20)/2) * M_PI/ANGLE_MAX)
  {
    ang2 = ((ANGLE_MAX-20)/2) * M_PI/ANGLE_MAX;
  }  
}

void gerer_clavier2(unsigned char touche, int xs, int ys){
  if (touche == 'z')
  {
    tz = 0;
  }
  if (touche == 'q')
  {
    tq = 0;
  }
  if (touche == 's')
  {
    ts = 0;
  }
  if (touche == 'd')
  {
    td = 0;
  }
  if (touche == 'j')
  {
    tl = 0;
  }
  if (touche == 'l')
  {
    tr = 0;
  }
  if (touche == 'i')
  {
    tu = 0;
  }
  if (touche == 'k')
  {
    tb = 0;
  }
  if (touche == 32)
  {
    tsp = 0;
  }
  if (touche == 'e')
  {
    te = 0;
  }
}

void gerer_clavier(unsigned char touche, int xs, int ys){
	printf("Touche: %c   Souris: %d %d \n", touche, xs, ys);
  if(touche == 'a')
  {
    a = 1 - a;
  }

  if(touche == 'z'){
    tz = 1;
  }

  if(touche == 'q'){
    tq =1;
  }

	if(touche == 's'){
    ts = 1;
  }

  if(touche == 'd'){
    td = 1;
  }

  if (touche == 'j'){
    tl = 1;
  }

  if (touche == 'l'){
    tr = 1;
  }

  if (touche == 'i'){
    tu = 1;
  }

  if (touche == 'k'){
    tb = 1;
  }

  if (touche == 'e')
  {
    te = 1;
  }

  if (touche == 32){
    tsp = 1;
  }
}