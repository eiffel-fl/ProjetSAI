#include "animer.h"

//extern cases matrice_case[LIGNE][ETAGE][COLONNE];
void animer(){
  if(tz == 1){
    if(vitesse <= V_MAX){
      vitesse += V_ACC;       //si on avance(qu'on appuie sur z, quoi), on augmente la vitesse jusqu'à atteindre la vitesse max.
    }
  }
  else{
    if(vitesse > 0 && !enlair){
      vitesse -= V_ACC;
      if (vitesse < 0)        //sinon, si on est pas en l'air, on décélerre jusqu'à 0.
      {
        vitesse = 0;
      }
    }
  }
  
  if(ts == 1){
    if(vitesse >= -V_MAX)
      vitesse -= V_ACC;
  }
  else{
    if(vitesse < 0 && !enlair){       //même principe si on recule
      vitesse += V_ACC;
      if (vitesse > 0)
      {
        vitesse = 0;
      }
    }
  }
  
  if(td == 1){
    if(vitesse_s <= V_MAX)
      vitesse_s += V_ACC;
  }
  else{
    if(vitesse_s > 0 && !enlair)      //même chose, mais pour les pas de coté.
    {
      vitesse_s -= V_ACC;
      if(vitesse_s < 0)
        vitesse_s = 0;
    }
  }
  
  if(tq == 1){
    if(vitesse_s >= -V_MAX)
      vitesse_s -= V_ACC;
  }
  else{
    if(vitesse_s < 0 && !enlair)      //idem
    {
      vitesse_s += V_ACC;
      if (vitesse_s > 0)
        vitesse_s = 0;
    }
  }

  if (tl == 1)
  {
    ang -= M_PI/ANGLE_MAX;
    A.x2 = A.x + (cos(ang)*cos(ang2));
    A.z2 = A.z + (sin(ang)*cos(ang2));    // pour changer d'angle de vue avec les touches ijkl (respectivement tu, tl, tb, tr)
  }

  if (tr == 1)
  {
    ang += M_PI/ANGLE_MAX;
    A.x2 = A.x + (cos(ang)*cos(ang2));
    A.z2 = A.z + (sin(ang)*cos(ang2));    // pour changer d'angle de vue avec les touches ijkl (respectivement tu, tl, tb, tr)
  }

  if (tu == 1)
  {
    if (ang2 < (ANGLE_MAX-10)/2 * M_PI/ANGLE_MAX)
    {
      ang2 += M_PI/ANGLE_MAX;             // pour changer d'angle de vue avec les touches ijkl (respectivement tu, tl, tb, tr)
    }
  }

  if (tb == 1)
  {
    if (ang2 > -(ANGLE_MAX-10)/2 * M_PI/ANGLE_MAX)
    {
      ang2 -= M_PI/ANGLE_MAX;             // pour changer d'angle de vue avec les touches ijkl (respectivement tu, tl, tb, tr)
    }
  }

  if (tsp == 1 && !enlair){
    vitesse_v = 0.2;                      //sauter
    enlair = 1;
  }

  glutWarpPointer(LARGEUR_FENETRE/2, HAUTEUR_FENETRE/2);  //reset la souris au centre de l'écran.

  cos1 = cos(ang);
  sin1 = sin(ang);
  cos2 = cos(ang2);
  sin2 = sin(ang2);
  if(vitesse_v > -0.4)
  vitesse_v -= 0.001;

  float xmur = 10000;                    //valeur pour le mur test, par défaut mis à 1000.
  float xmur2 = 10000;
  float zmur = 10000;
  float zmur2 = 10000;
  float y_plaf = 1000;

  float xmur_ar = 10000;
  float xmur_av = 10000;
  float zmur_ar = 10000;
  float zmur_av = 10000;
  float xmur2_ar = 10000;
  float xmur2_av = 10000;
  float zmur2_ar = 10000;
  float zmur2_av = 10000;


  float new_x = A.x;
  float new_x_ar = A.x_ar;
  float new_x_av = A.x_av;
  float new_z = A.z;
  float new_z_ar = A.z_ar;
  float new_z_av = A.z_av;
  float new_y = A.y;
  float new_y_ap = A.y_ap;
  new_x += (vitesse * cos1) + (vitesse_s * -sin1);
  new_x_ar = new_x - 5;
  new_x_av = new_x + 5;
  new_z += (vitesse * sin1) + (vitesse_s * cos1);
  new_z_ar = new_z - 5;
  new_z_av = new_z + 5;
  new_y += vitesse_v;
  new_y_ap = new_y + 5;

  int valeur0 = A.y/PLAFOND;
  int valeurx = A.x/COTE;
  int valeurz = A.z/COTE;

  int valeurx_av = A.x_av/COTE;
  int valeurz_av = A.z_av/COTE;
  int valeurx_ar = A.x_ar/COTE;
  int valeurz_ar = A.z_ar/COTE;

  if (valeurx < LIGNE && valeurx >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx][valeurz_av].mur0 == 1 || matrice_case[valeur0][valeurx][valeurz_ar].mur0 == 1)
    {
      xmur = valeurx*COTE;
    }
    else
      xmur = 10000;
  }
  else
    xmur =10000;

  if (valeurx < LIGNE && valeurx >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx][valeurz_av].mur2 == 1 || matrice_case[valeur0][valeurx][valeurz_ar].mur2 == 1)
    {
      xmur2 = valeurx*COTE + COTE;
    }
    else
      xmur2 = 10000;
  }
  else
    xmur2 = 10000;

  if (valeurx < LIGNE && valeurx >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx_av][valeurz].mur1 == 1 || matrice_case[valeur0][valeurx_ar][valeurz].mur1 == 1)
    {
      zmur = valeurz*COTE;
    }
    else
      zmur = 10000;
  }
  else
    zmur = 10000;

  if (valeurx < LIGNE && valeurx >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx_av][valeurz].mur3 == 1 || matrice_case[valeur0][valeurx_ar][valeurz].mur3 == 1)
    {
      zmur2 = valeurz*COTE + COTE;
    }
    else
      zmur2 = 10000;
  }
  else
    zmur2 = 10000;
//av
  /*
  if (valeurx_av < LIGNE && valeurx_av >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx_av][valeurz].mur0 == 1 || matrice_case[valeur0][valeurx_av][valeurz].mur0 == 1)
    {
      xmur_av = valeurx_av*COTE;
    }
    else
      xmur_av = 10000;
  }
  else
    xmur_av = 10000;

  if (valeurx_av < LIGNE && valeurx_av >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx_av][valeurz_av].mur2 == 1 || matrice_case[valeur0][valeurx_av][valeurz_ar].mur2 == 1)
    {
      xmur2_av = valeurx_av*COTE + COTE;
    }
    else
      xmur2_av = 10000;
  }
  else
    xmur2_av = 10000;

  if (valeurx < LIGNE && valeurx >= 0 && valeurz_av < COLONNE && valeurz_av >= 0)
  {
    if (matrice_case[valeur0][valeurx_av][valeurz_av].mur1 == 1 || matrice_case[valeur0][valeurx_ar][valeurz_av].mur1 == 1)
    {
      zmur_av = valeurz_av*COTE;
    }
    else
      zmur_av = 10000;
  }

  if (valeurx < LIGNE && valeurx >= 0 && valeurz_av < COLONNE && valeurz_av >= 0)
  {
    if (matrice_case[valeur0][valeurx][valeurz_av].mur3 == 1)
    {
      zmur2_av = valeurz_av*COTE + COTE;
    }
    else
      zmur2_av = 10000;
  }
//ap
  if (valeurx_ar < LIGNE && valeurx_ar >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx_ar][valeurz].mur0 == 1)
    {
     xmur_ar = valeurx_ar*COTE;
    }
  }

  if (valeurx_ar < LIGNE && valeurx_ar >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeur0][valeurx_ar][valeurz].mur2 == 1)
    {
     xmur2_ar = valeurx_ar*COTE + COTE;
    }
  }

  if (valeurx < LIGNE && valeurx >= 0 && valeurz_ar < COLONNE && valeurz_ar >= 0)
  {
    if (matrice_case[valeur0][valeurx][valeurz_ar].mur1 == 1)
    {
     zmur_ar = valeurz_ar*COTE;
    }
  }

  if (valeurx < LIGNE && valeurx >= 0 && valeurz_ar < COLONNE && valeurz_ar >= 0)
  {
    if (matrice_case[valeur0][valeurx][valeurz_ar].mur3 == 1)
    {
     zmur2_ar = valeurz_ar*COTE + COTE;
    }
  }*/

  /*printf("xmur: %f, xmur2: %f,\nzmur: %f, zmur2: %f\n", xmur, xmur2, zmur, zmur2);
  printf("xmur_av: %f, xmur_ar: %f,\nzmur_av: %f, zmur_ar: %f\n", xmur_av, xmur_ar, zmur_av, zmur_ar);*/
  /*
  printf("xmur_av: %f, xmur2_av: %f,\nzmur_av: %f, zmur2_av: %f\n", xmur_av, xmur2_av, zmur_av, zmur2_av);
  printf("xmur_ar: %f, xmur2_ar: %f,\nzmur_ar: %f, zmur2_ar: %f\n", xmur_ar, xmur2_ar, zmur_ar, zmur2_ar);*/
  
/*
  if (A.x > COTE*2 && A.x < COTE*3 && A.z > 0 && A.z < PLAFOND)
  {
    y_sol = (A.x-COTE*2)*PLAFOND/COTE;
    y_plaf = y_sol + PLAFOND + A.x - COTE*2 - 5;
    xmur = COTE*2 + (A.x - COTE*2) - (A.y - y_plaf) + 5;
  }
  else if(A.x > COTE*3 && A.x < COTE*4 && A.z > 0 && A.z < COTE && A.y > 50){//On adapte quelques valeur de collision test ici, en fonction de la position du joueur.
    xmur = COTE*4;
    y_sol = PLAFOND;
  }
  else if(A.x > 0 && A.x < COTE && A.z > 0 && A.z < COTE*2 && A.y > 0){
    xmur = 0;
    y_sol = 0;
  }
  else
  {*/
    y_sol = 0;
//  }



/*
  if (((xmur - new_x_av) * (xmur - A.x_av)) > 0 && ((xmur - new_x_ar) * (xmur - A.x_ar)) > 0)
  {
    if (((xmur2 - new_x_av) * (xmur2 - A.x_av)) > 0 && ((xmur2 - new_x_ar) * (xmur2 - A.x_ar)) > 0)
    {*/
/*
  if (((xmur_av - new_x_av) * (xmur_av - A.x_av)) > 0 && ((xmur_ar - new_x_ar) * (xmur_ar - A.x_ar)) > 0)
  {
    if (((xmur2_av - new_x_av) * (xmur2_av - A.x_av)) > 0 && ((xmur2_ar - new_x_ar) * (xmur2_ar - A.x_ar)) > 0)
    {
      A.x = new_x;
      A.x_ar = new_x - 5;
      A.x_av = new_x + 5;
    }
  }
*/
  if (((xmur - new_x_av) * (xmur - A.x_av)) > 0 && ((xmur - new_x_ar) * (xmur - A.x_ar)) > 0)
  {
    if (((xmur2 - new_x_ar) * (xmur2 - A.x_ar)) > 0 && ((xmur2 - new_x_av) * (xmur2 - A.x_av)) > 0)
    {
      if ((int)new_z_av/COTE == (int)new_z_ar/COTE || matrice_case[0][(int)new_x_av/COTE][(int)new_z_av/COTE].mur1 == 0)
      {
        if ((int)new_z_av/COTE == (int)new_z_ar/COTE || matrice_case[0][(int)new_x_ar/COTE][(int)new_z_ar/COTE].mur3 == 0)
        {
          A.x = new_x;
          A.x_ar = new_x - 5;
          A.x_av = new_x + 5;
        }
      }
    }
  }

  A.x2 = A.x + (cos1*cos2);

  if (((zmur - new_z_av) * (zmur - A.z_av)) > 0 && ((zmur - new_z_ar) * (zmur - A.z_ar)) > 0)
  {
    if (((zmur2 - new_z_av) * (zmur2 - A.z_av)) > 0 && ((zmur2 - new_z_ar) * (zmur2 - A.z_ar)) > 0)
    {
      if ((int)new_x_av/COTE == (int)new_x_ar/COTE || matrice_case[0][(int)new_x_av/COTE][(int)new_z_av/COTE].mur0 == 0)
      {
        if ((int)new_x_av/COTE == (int)new_x_ar/COTE || matrice_case[0][(int)new_x_ar/COTE][(int)new_z_ar/COTE].mur2 == 0)
        {
          A.z = new_z;
          A.z_ar = new_z - 5;
          A.z_av = new_z + 5;
        }
      }
    }
  }

  if (((y_plaf - new_y_ap) * (y_plaf - A.y_ap)) > 0)
  {
    A.y = new_y;
    A.y_ap = new_y_ap;
  }
  else{
    vitesse_v = 0;
  }

  A.z2 = A.z + (sin1*cos2);
  A.y2 = A.y + sin2;

  if (A.y < y_sol + 20.9)
  {
    vitesse_v = 0.02 * ((y_sol+21) - A.y);
    enlair = 0;
  }

  else if (A.y < y_sol + 21)
  {
    vitesse_v = 0;
    enlair = 0;
    A.y = y_sol + 21;
  }

  if (A.y > y_sol + 21)
  {
    enlair = 1;
  }

  printf("position x: %f, position z: %f\n", A.x, A.z);

  glutPostRedisplay();
}