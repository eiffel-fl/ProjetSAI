#include "animer.h"

//extern matrice_case[ETAGE][LIGNE][COLONNE];
float yu = 30;
extern joueur A;

void affichage(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glFrustum(-4, 4, -3, 3, 5, 1000);
  gluLookAt(A.x, A.y, A.z, A.x2, A.y2, A.z2, 0, 1, 0);

  afficher_labyrinthe3D();
	
	glutIdleFunc(animer);
  glFlush ();
}

int main(int argc, char* argv[]){
	generer_labyrinthe();
	chercher_entree(0);
	A.x = rand() % LIGNE + COTE/2;
	A.z = rand() % COLONNE + COTE/2;/*
	A.x = (matrice_case[0][randi][randj].A.x + matrice_case[0][randi][randj].C.x) / 2;
	A.z = (matrice_case[0][randi][randj].A.z + matrice_case[0][randi][randj].C.z) / 2;
*/	
	
	printf("A %f et %f\n", matrice_case[0][randi][randj].A.x, matrice_case[0][randi][randj].A.z);
	printf("B %f et %f\n", matrice_case[0][randi][randj].B.x, matrice_case[0][randi][randj].B.z);
	printf("C %f et %f\n", matrice_case[0][randi][randj].C.x, matrice_case[0][randi][randj].C.z);
	printf("D %f et %f\n", matrice_case[0][randi][randj].D.x, matrice_case[0][randi][randj].D.z);
	
	printf("%f et %f\n", A.x, A.z);
	
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);

  glutInitWindowSize(800, 600);
  glutInitWindowPosition(50, 50);

  glutCreateWindow("Labyrinthe");
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
  glutSetCursor(GLUT_CURSOR_NONE);
	
  glutKeyboardFunc(gerer_clavier);
  glutKeyboardUpFunc(gerer_clavier2);
  glutMotionFunc(souris);
  glutPassiveMotionFunc(souris);
  glutDisplayFunc(affichage);

  glutMainLoop();
 
	return 1;
}