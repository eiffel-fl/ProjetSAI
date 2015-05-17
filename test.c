#include "animer.h"

float yu = 30;
extern joueur A;

float MatSpec[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float MatDif[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float LightPos[4];
float LightDir[3];
float ambientLight[4] = {0.025,0.025,0.025,1};
float Light1Dif[4] = {0.5f, 0.5f, 0.5f, 1.0f};
float Light1Spec[4] = {0.8f, 0.8f, 0.8f, 1.0f};

void affichage(){
	LightPos[0] = A.x2;
	LightPos[1] = A.y2;
	LightPos[2] = A.z2;
	LightPos[3] = 1;

	LightDir[0] = A.x2 - A.x;
	LightDir[1] = A.y2 - A.y;
	LightDir[2] = A.z2 - A.z;

	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDif);

	glEnable(GL_COLOR_MATERIAL);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light1Dif); 	//Et ceux de la lumière
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light1Spec);

	glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LightDir);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 5);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 30);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glFrustum(-4, 4, -3, 3, 5, 1000);
  gluLookAt(A.x, A.y, A.z, A.x2, A.y2, A.z2, 0, 1, 0);


	afficher_labyrinthe3D();

	extern int monte;
	extern float montage;
	int cx;
	int cy;
	int cz;

	if (monte)
	{
		cx = A.x/COTE;
		cz = A.z/COTE;
		cy = A.y/PLAFOND;
		if (matrice_case[cy][cx][cz].entree == 1)
		{
			generer_ascenceur(cx * COTE, cy * PLAFOND - PLAFOND, cz * COTE, montage);
		}
		else
		{
			generer_ascenceur(cx * COTE, cy * PLAFOND, cz * COTE, montage);
		}
	}

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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
  glutSetCursor(GLUT_CURSOR_NONE);


	glutKeyboardFunc(gerer_clavier);
	glutKeyboardUpFunc(gerer_clavier2);
	glutMotionFunc(souris);
	glutPassiveMotionFunc(souris);
	glutDisplayFunc(affichage);

	glutMainLoop();

	return 1;
}