#include "labyrinthe.h"


//cases matrice_case[ETAGE][LIGNE][COLONNE];
void afficher_labyrinthe(){
	int i;
	int j;

	printf("ETAGE %d\n", numero_etage);
	for(i = 0; i < LIGNE; i++){
		for(j = 0; j < COLONNE; j++){
			printf("%d-%d ",matrice_case[numero_etage][i][j].numero, matrice_case[numero_etage][i][j].grille);
		}
		printf("\n");
	}
	printf("\n");
}

void afficher_labyrinthe3D(){
	int i;
	int j;

	for(numero_etage = 0; numero_etage < ETAGE; numero_etage++){
		for(i = 0; i < LIGNE; i++){
			for(j = 0; j < COLONNE; j++){
				afficher_case(i, j);
			}
		}
	}
}

void afficher_case(int i, int j){
	int code = 0;
	point A = matrice_case[numero_etage][i][j].A;
	point B = matrice_case[numero_etage][i][j].B;
	point C = matrice_case[numero_etage][i][j].C;
	point D = matrice_case[numero_etage][i][j].D;

	if(matrice_case[numero_etage][i][j].entree == 2)
			glColor3f(219,0,115); // "sortie"
		else
			glColor3f(0.3, 0.3, 0.3);

	if(matrice_case[numero_etage][i][j].mur0){
		code += 100;
	}
	if(matrice_case[numero_etage][i][j].mur1){
		code += 1000;
	}
	if (matrice_case[numero_etage][i][j].mur2)
	{
		code += 1;
	}
	if (matrice_case[numero_etage][i][j].mur3)
	{
		code += 10;
	}
	glBegin(GL_QUADS);
	creer_tube(code, i, numero_etage, j);
	glEnd();
}

void initialiser_matrice(){
	cases case_courante;
	int i;
	int j;

	int x = 0;
	int z = 0;

	int num = 1;

	case_courante.mur0 = 1;
	case_courante.mur1 = 1;
	case_courante.mur2 = 1;
	case_courante.mur3 = 1;
	case_courante.grille = 0;

	for(i = 0; i < LIGNE; i++){
		for(j = 0; j < COLONNE; j++){
			matrice_case[numero_etage][i][j] = case_courante;
			matrice_case[numero_etage][i][j].numero = num;
			num++;

			matrice_case[numero_etage][i][j].A.x = x;
			matrice_case[numero_etage][i][j].A.y = y;
			matrice_case[numero_etage][i][j].A.z = z + COTE;

			matrice_case[numero_etage][i][j].B.x = x + COTE;
			matrice_case[numero_etage][i][j].B.y = y;
			matrice_case[numero_etage][i][j].B.z = z + COTE;

			matrice_case[numero_etage][i][j].C.x = x + COTE;
			matrice_case[numero_etage][i][j].C.y = y;
			matrice_case[numero_etage][i][j].C.z = z;

			matrice_case[numero_etage][i][j].D.x = x;
			matrice_case[numero_etage][i][j].D.y = y;
			matrice_case[numero_etage][i][j].D.z = z;

			x += COTE;
		}

		x = 0;
		z -= COTE;
	}
}

int cases_pas_meme_nombre_et_grillage(){
	int i;
	int j;
	int fini = 0;

	for(i = 0; i < LIGNE; i++){
		for(j = 0; j < COLONNE; j++){
			if(matrice_case[numero_etage][i][j].grille == 0){
				if(((i - 1) < 0) || (matrice_case[numero_etage][i][j].numero == matrice_case[numero_etage][i - 1][j].numero)){
					if(((j - 1) < 0) || (matrice_case[numero_etage][i][j].numero == matrice_case[numero_etage][i][j - 1].numero)){
						if(((i + 1) >= LIGNE) || (matrice_case[numero_etage][i][j].numero == matrice_case[numero_etage][i + 1][j].numero)){
							if(((j + 1) >= COLONNE) || (matrice_case[numero_etage][i][j].numero == matrice_case[numero_etage][i][j + 1].numero)){
									matrice_case[numero_etage][i][j].grille = 1;
							}
						}
					}
				}
			}
			if(matrice_case[numero_etage][i][j].numero != matrice_case[numero_etage][0][0].numero)
					fini = 1;
		}
	}
	return fini;
}

void cases_aleatoire(){
	do{
		randi = rand() % LIGNE;
		randj = rand() % COLONNE;
	} while(matrice_case[numero_etage][randi][randj].grille);
}

void cases_aleatoire2(){
	do{
		randi = rand() % LIGNE;
		randj = rand() % COLONNE;
	} while(matrice_case[numero_etage][randi][randj].entree == 1);
}

int case_aleatoire_voisine(){
	int r;
	while(1){
		r = rand() % 4;
		switch(r){
			case 0:
				if((randi - 1 >= 0) && (matrice_case[numero_etage][randi][randj].numero != matrice_case[numero_etage][randi - 1][randj].numero))
					return r;
				break;
			case 1:
				if((randj - 1 >= 0) && (matrice_case[numero_etage][randi][randj].numero != matrice_case[numero_etage][randi][randj - 1].numero))
					return r;
				break;
			case 2:
				if((randi + 1 < LIGNE) && (matrice_case[numero_etage][randi][randj].numero != matrice_case[numero_etage][randi + 1][randj].numero))
					return r;
				break;
			case 3:
				if((randj + 1 < COLONNE) && (matrice_case[numero_etage][randi][randj].numero != matrice_case[numero_etage][randi][randj + 1].numero))
					return r;
				break;
		}
	}
}

void supprimer_mur(int r){
	switch(r){
		case 0:
			if(matrice_case[numero_etage][randi][randj].mur0 != 0){
				matrice_case[numero_etage][randi][randj].mur0 = 0;
				matrice_case[numero_etage][randi - 1][randj].mur2 = 0;
			}
			else{
				printf("mur0 déjà cassé\n");
			}
			break;
		case 1:
			if(matrice_case[numero_etage][randi][randj].mur1 != 0){
				matrice_case[numero_etage][randi][randj].mur1 = 0;
				matrice_case[numero_etage][randi][randj - 1].mur3 = 0;
			}
			else{
				printf("mur1 déjà cassé\n");
			}
			break;
		case 2:
			if(matrice_case[numero_etage][randi][randj].mur2 != 0){
				matrice_case[numero_etage][randi][randj].mur2 = 0;
				matrice_case[numero_etage][randi + 1][randj].mur0 = 0;
			}
			else{
				printf("mur2 déjà cassé\n");
			}
			break;
		case 3:
			if(matrice_case[numero_etage][randi][randj].mur3 != 0){
				matrice_case[numero_etage][randi][randj].mur3 = 0;
				matrice_case[numero_etage][randi][randj + 1].mur1 = 0;
			}
			else{
				printf("mur3 déjà cassé\n");
			}
			break;
	}
}

void mettre_au_numero(int r){
	switch(r){
		case 0:
			mettre_au_numero_bis(matrice_case[numero_etage][randi][randj].numero, matrice_case[numero_etage][randi - 1][randj].numero);
			break;
		case 1:
			mettre_au_numero_bis(matrice_case[numero_etage][randi][randj].numero, matrice_case[numero_etage][randi][randj - 1].numero);
			break;
		case 2:
			mettre_au_numero_bis(matrice_case[numero_etage][randi][randj].numero, matrice_case[numero_etage][randi + 1][randj].numero);
			break;
		case 3:
			mettre_au_numero_bis(matrice_case[numero_etage][randi][randj].numero, matrice_case[numero_etage][randi][randj + 1].numero);
			break;
	}
}

void mettre_au_numero_bis(int numero, int numero_voisine){
	int i;
	int j;

	for(i = 0; i < LIGNE; i++){
		for(j = 0; j < COLONNE; j++){
			if(matrice_case[numero_etage][i][j].numero == numero_voisine)
				matrice_case[numero_etage][i][j].numero = numero;
		}
	}
}

void generer_etage(){
	int r;

	while(cases_pas_meme_nombre_et_grillage()){
		do
			cases_aleatoire();
		while(matrice_case[numero_etage][randi][randj].grille);
		r = case_aleatoire_voisine();
		supprimer_mur(r);
		mettre_au_numero(r);
	}

	if(numero_etage == 0){
		randi = rand() % LIGNE;
		randj = rand() % COLONNE;

		matrice_case[numero_etage][randi][randj].entree = 1;

		cases_aleatoire2();

		matrice_case[numero_etage][randi][randj].entree = 2;
	}
	else{
		//chercher la case sortie en dessous
		//faire entree actuelle = sortie en dessous
		chercher_sortie(numero_etage - 1);
		matrice_case[numero_etage][randi][randj].entree = 1;

		//choisir aléatoirement la sortie
		cases_aleatoire2();
		matrice_case[numero_etage][randi][randj].entree = 2;
	}
}

void chercher_entree(int etage){
	int i;
	int j;

	for(i = 0; i < LIGNE; i++){
		for(j = 0; j < COLONNE; j++){
			if(matrice_case[etage][i][j].entree == 1){
				randi = i;
				randj = j;
			}
		}
	}
}

void chercher_sortie(int etage){
	int i;
	int j;

	for(i = 0; i < LIGNE; i++){
		for(j = 0; j < COLONNE; j++){
			if(matrice_case[etage][i][j].entree == 2){
				randi = i;
				randj = j;
			}
		}
	}
}

void generer_ascenceur(float x, float y, float z, float montage){
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.3, 0.3);
	creer_face(3, x, y + montage, z);
	glEnd();
}

void generer_labyrinthe(){
	y = 0;

	srand(time(NULL));

	for(numero_etage = 0; numero_etage < ETAGE; numero_etage++){
		initialiser_matrice();
		generer_etage();

		y += COTE ;
	}
}

void creer_tube(int type, int x, int y, int z){
  //Rappel des codes: le premier chiffre correspond au mur du bas, le second au mur de gauche,le troisième au mur du haut et le quatrième au mur de droite.
// 	printf("%d %d et %d\n", x, y, z);
  switch(type){
    case 0:
      //pas de mur. code 0000
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);
      break;

    case 1000:
      //un seul mur. code 1000
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);
      break;

    case 100:
      //un seul mur. code 0100
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);
      break;

    case 10:
      //un seul mur. code 0010
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 1:
      //un seul mur. code 0001
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

			glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);
      break;

    case 1010:
      //tube couloir, code 1010
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

			glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);

			glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 101:
      //tube couloir, code 0101
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);
      break;

    case 1100:
      //couloir tournant. accès: z, x. code: 1100
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);
      break;

    case 11:
      //couloir tournant. accès: -z, -x. code 0011
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);

      glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 110:
      //couloir tournant. accès: -z, x. code 0110
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 1001:
      //couloir tournant. accès: z, -x. code 1001
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);

      glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);
      break;

    case 1111:
      //Que des murs. code 1111
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);

      glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 111:
      //trois murs, accès -z. code 0111
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);

      glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 1011:
      //trois murs, accès -x. code 1011
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);

      glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 1101:
      //trois murs, accès z. code 1101
      //creer_face(3, x*COTE, y*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(1, x*COTE+COTE-0.001, y*PLAFOND, z*COTE);

      glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);
      break;

    case 1110:
      //trois murs, accès x. code 1110
      //creer_face(3, x*COTE, y*PLAFOND*PLAFOND+PLAFOND, z*COTE);

			if(matrice_case[y][x][z].entree != 1 || y == 0)
				creer_face(3, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 1, 0);
      creer_face(1, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0, 0, 1);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(1, 0, 0);
      creer_face(2, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    case 111111:
      //couloir pente/escalier de -x à x
      //creer_face(5, x*COTE, y*PLAFOND+PLAFOND, z*COTE);


      creer_face(5, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(4, x*COTE, y*PLAFOND, z*COTE);

      glColor3f(0.1, 0.1, 0.1);
      creer_face(4, x*COTE, y*PLAFOND, z*COTE+COTE-0.001);
      break;

    default:
      fprintf(stderr, "erreur! code = %d\n", type);
      break;
  }
}

void creer_face(int type, float x, float y, float z){

  switch(type){
    case 1:                                 //Face sur l'axe des x.
      glVertex3f(x, y+PLAFOND, z);
      glVertex3f(x, y+PLAFOND, z+COTE);
      glVertex3f(x, y, z+COTE);
      glVertex3f(x, y, z);
      break;

    case 2:                                 //Face sur l'axe des z.
      glVertex3f(x, y+PLAFOND, z);
      glVertex3f(x+COTE, y+PLAFOND, z);
      glVertex3f(x+COTE, y, z);
      glVertex3f(x, y, z);
      break;

    case 3:                                 //Face sur l'axe des y.
      glVertex3f(x+COTE, y, z+COTE);
      glVertex3f(x+COTE, y, z);
      glVertex3f(x, y, z);
      glVertex3f(x, y, z+COTE);
      break;

    case 4:                                 //Face d'escalier sur l'axe des z. (Là où on mettrait une rembarde)
      glVertex3f(x, y+PLAFOND, z);
      glVertex3f(x+COTE, y+PLAFOND*2, z);
      glVertex3f(x+COTE, y+PLAFOND, z);
      glVertex3f(x, y, z);
      break;

    case 5:                                 //Face d'escalier sur l'axe des y. (Les escalier eux-même)
      glVertex3f(x+COTE, y+PLAFOND, z+COTE);
      glVertex3f(x+COTE, y+PLAFOND, z);
      glVertex3f(x, y, z);
      glVertex3f(x, y, z+COTE);
      break;
  }
}
