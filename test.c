#include "animer.h"

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
	
	A.x = randi * COTE + COTE/2;
	A.z = randj * COTE + COTE/2;

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