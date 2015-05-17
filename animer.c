#include "animer.h"

//extern cases matrice_case[LIGNE][ETAGE][COLONNE];
void animer(){
  if (!monte)
  {
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

    if (tsp == 1 && !enlair){
      vitesse_v = 0.2;                      //sauter
      enlair = 1;
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
  static float montage;


  float new_x = A.x;
  float new_x_ar = A.x_ar;
  float new_x_av = A.x_av;
  float new_z = A.z;
  float new_z_ar = A.z_ar;
  float new_z_av = A.z_av;
  float new_y = A.y;
  float new_y_ap = A.y_ap;
  new_x += (vitesse * cos1) + (vitesse_s * -sin1);
  new_x_ar = new_x - ECART;
  new_x_av = new_x + ECART;
  new_z += (vitesse * sin1) + (vitesse_s * cos1);
  new_z_ar = new_z - ECART;
  new_z_av = new_z + ECART;
  new_y += vitesse_v;
  new_y_ap = new_y + ECART;

  int valeury = A.y/PLAFOND;
  int valeurx = A.x/COTE;
  int valeurz = A.z/COTE;

  int valeurx_av = A.x_av/COTE;
  int valeurnew_x_av = new_x_av/COTE;
  int valeurz_av = A.z_av/COTE;
  int valeurnew_z_av = new_z_av/COTE;
  int valeurx_ar = A.x_ar/COTE;
  int valeurnew_x_ar = new_x_ar/COTE;
  int valeurz_ar = A.z_ar/COTE;
  int valeurnew_z_ar = new_z_ar/COTE;

  if (valeurx < LIGNE && valeurx >= 0 && valeurz < COLONNE && valeurz >= 0)
  {
    if (matrice_case[valeury][valeurx][valeurz_av].mur0 == 1 || matrice_case[valeury][valeurx][valeurz_ar].mur0 == 1)
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
    if (matrice_case[valeury][valeurx][valeurz_av].mur2 == 1 || matrice_case[valeury][valeurx][valeurz_ar].mur2 == 1)
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
    if (matrice_case[valeury][valeurx_av][valeurz].mur1 == 1 || matrice_case[valeury][valeurx_ar][valeurz].mur1 == 1)
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
    if (matrice_case[valeury][valeurx_av][valeurz].mur3 == 1 || matrice_case[valeury][valeurx_ar][valeurz].mur3 == 1)
    {
      zmur2 = valeurz*COTE + COTE;
    }
    else
      zmur2 = 10000;
  }
  else
    zmur2 = 10000;


  int test;


  if ((((xmur - new_x_av) * (xmur - A.x_av)) > 0 && ((xmur - new_x_ar) * (xmur - A.x_ar)) > 0) && ((((xmur2 - new_x_ar) * (xmur2 - A.x_ar)) > 0) && ((xmur2 - new_x_av) * (xmur2 - A.x_av)) > 0))
  {
    test = 1;
  }
  else
  {
    test = 0;
    valeurnew_x_av = valeurx_av;
    valeurnew_x_ar = valeurx_ar;
  }

  if ((((zmur - new_z_av) * (zmur - A.z_av)) > 0 && ((zmur - new_z_ar) * (zmur - A.z_ar)) > 0) && (((zmur2 - new_z_av) * (zmur2 - A.z_av)) > 0 && ((zmur2 - new_z_ar) * (zmur2 - A.z_ar)) > 0))
  {
    if (valeurnew_x_av == valeurnew_x_ar || (matrice_case[valeury][valeurnew_x_av][valeurnew_z_av].mur0 == 0 && matrice_case[valeury][valeurnew_x_ar][valeurnew_z_ar].mur2 == 0))
    {
      A.z = new_z;
      A.z_ar = new_z - ECART;
      A.z_av = new_z + ECART;
    }
    else
    {
      valeurnew_z_av = valeurz_av;
      valeurnew_z_ar = valeurz_ar;
    }
  }
  else
  {
    valeurnew_z_av = valeurz_av;
    valeurnew_z_ar = valeurz_ar;
  }

  if (test)
  {
    if (valeurnew_z_av == valeurnew_z_ar || (matrice_case[valeury][valeurnew_x_av][valeurnew_z_av].mur1 == 0 && matrice_case[valeury][valeurnew_x_ar][valeurnew_z_ar].mur3 == 0))
    {
      A.x = new_x;
      A.x_ar = new_x - ECART;
      A.x_av = new_x + ECART;
    }
  }


  A.x2 = A.x + (cos1*cos2);

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

  if (matrice_case[valeury][valeurx_ar][valeurz_ar].entree == 2 && matrice_case[valeury][valeurx_av][valeurz_av].entree == 2 && vitesse == 0 && vitesse_s == 0 && te == 1)
  {
    monte = 1;
  }

  if(monte && montage <= PLAFOND)
  {
    y_sol += 0.1;
    montage += 0.1;
  }
  else
  {
    montage = 0;
    monte = 0;
    y_sol = valeury * PLAFOND;
  }

  printf("position x: %f, position z: %f, montage: %f\n", A.x, A.z, montage);

  glutPostRedisplay();
}