#include <stdlib.h>
#include <stdio.h>
#include "GL/gl.h"
#include "GL/glut.h"
#define ETAGE 2
#define LIGNE 6
#define COLONNE 6
#define COTE 40
#define PLAFOND 40

typedef struct s_point{
	float x;
	float y;
	float z;
} point;

typedef struct s_case{
	point A;
	point B;
	point C;
	point D;
	
	int mur0;
	int mur1;
	int mur2;
	int mur3;
	
	int grille;
	int numero;
	int entree;
} cases;


int numero_etage;
int y;
int randi;
int randj;

cases matrice_case[ETAGE][LIGNE][COLONNE];


void afficher_labyrinthe(); //Affiche le labyrinthe en console (utiliser pour débugger)
void afficher_labyrinthe3D(); //Affiche le labyrinthe en 3D (en réalite appel pour chaque case la fonction afficher_case())
void afficher_case(int, int); //Affiche la case de coordonnées (i, j) dans la matrice
void initialiser_matrice(); //Initialise la matrice de case en mettant les booléens mur à 1, en donnant un numéro par case, en créant les points, etc.
int cases_pas_meme_nombre_et_grillage(); //Parcourt la matrice et vérifie que les cases n'ont pas le même numéro (l'algorithme s'arrête quand elles ont le même numéro), de plus on grillera aussi une case (une case est grillée si les cases autours sont inaccessibles ou qu'elles ont le même numéro)
void cases_aleatoire(); //Tire aléatoirement une case non grillée
void cases_aleatoire2(); //Tire aléatoirement une case qui ne soit pas l'entrée
void chercher_entree(int); //Cherche la case à l'étage spécifiée qui est l'entrée
void chercher_sortie(int); //Cherche la case à l'étage spécifiée qui est la sortie
int case_aleatoire_voisine(); //Tire aléatoirement une case voisine de la case choisie
void supprimer_mur(int); //Selon le nombre aléatoire renvoyé par case_aleatoire_voisine() on cassera le mur associé
void mettre_au_numero(int ); //Selon le nombre aléatoire renvoyé par case_aleatoire_voisine on prendra le numero associé 
void mettre_au_numero_bis(int, int); //Quand on casse un mur, on met au même numéro les 2 cases nouvellement liées mais on propage aussi cette mise au numéro avec les voisines de la voisine
void generer_etage(); //Algorithme qui générera le labyrinthe aléatoirement
void generer_labyrinthe();
void creer_tube(int type, int x, int y, int z);
void creer_face(int type, float x, float y, float z);