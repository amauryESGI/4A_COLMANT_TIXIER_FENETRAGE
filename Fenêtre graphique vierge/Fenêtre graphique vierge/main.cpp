

/*******************************************************/
/*					didac.c							   */
/*******************************************************/
/*													   */
/*	Préambule OpenGL sous Glut			               */
/*  ESGI : 2I année 						           */
/*													   */
/*******************************************************/
/*													   */
/*  Fenêtre graphique 2D vierge                        */
/*  Evènement souris actif, q pour quitter             */
/*													   */
/*******************************************************/



#include<windows.h>
#include<glut.h>
#include<stdlib.h>
#include<stdio.h>

int x0, y0;  // clic souris
int cpt = 0;
int monTableauDePointX[10];
int monTableauDePointY[10];

int rectx;
int recty;
int monTableauPointRectX[2];
int monTableauPointRectY[2];
int cptrect = 0;
/*
int* maListeDePointX[1];
int maListeDePointXBis[1];
int _size = 0;
*/

bool couleur = false;
bool polygone = true;
bool trace_fenetre = false;
bool fenetrage = false;
bool remplissage = false;
bool raz = false;

// Menu items
enum MENU_TYPE
{
	MENU_COULEUR,
	MENU_POLYGONE,
	MENU_TRACE_FENETRE,
	MENU_FENETRAGE,
	MENU_REMPLISSAGE,
};


// Assign a default value
//MENU_TYPE show = MENU_COULEUR;

/* prototypes de fonctions */
void affichage(void);                             // modélisation
void clavier(unsigned char touche, int x, int y);   // fonction clavier
void mouse(int bouton, int etat, int x, int y);      // fonction souris
void menu(int item);

/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
	char **argv){  // argv: tableau de chaines de caractères, argv[0] contient le nom du programme lancé (plus un éventuel chemin)

	for (int i = 0; i<sizeof(monTableauDePointX) / sizeof(*monTableauDePointX); i++)
	{
		monTableauDePointX[i] = NULL;
	}
	for (int i = 0; i<sizeof(monTableauDePointY) / sizeof(*monTableauDePointY); i++)
	{
		monTableauDePointY[i] = NULL;
	}

	for (int i = 0; i<sizeof(monTableauPointRectX) / sizeof(*monTableauPointRectX); i++)
	{
		monTableauPointRectX[i] = NULL;
	}

	for (int i = 0; i<sizeof(monTableauPointRectY) / sizeof(*monTableauPointRectY); i++)
	{
		monTableauPointRectY[i] = NULL;
	}



	/* Initialisation de glut et creation de la fenetre */
	glutInit(&argc, argv);                       // Initialisation
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
	glutInitWindowSize(500, 500);                // dimension fenêtre
	glutInitWindowPosition(100, 100);           // position coin haut gauche
	glutCreateWindow("A vous de jouer!!!");  // nom

	/* Repère 2D délimitant les abscisses et les ordonnées*/
	gluOrtho2D(-250.0, 250.0, -250.0, 250.0);

	/* Initialisation d'OpenGL */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0, 0); // couleur: blanc
	glPointSize(2.0);               // taille d'un point: 2px

	/* Enregistrement des fonctions de rappel
	=> initialisation des fonctions callback appelées par glut */
	glutDisplayFunc(affichage);
	glutKeyboardFunc(clavier);
	glutMouseFunc(mouse);

	/* rq: le callback de fonction (fonction de rappel) est une fonction qui est passée en argument à une
	autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en même temps)
	alors qu'il ne les connaît pas par avance.*/

	glutCreateMenu(menu);
	glutAddMenuEntry("Couleur", MENU_COULEUR);
	glutAddMenuEntry("Polygone a découper", MENU_POLYGONE);
	glutAddMenuEntry("Trace fenetre", MENU_TRACE_FENETRE);
	glutAddMenuEntry("Fenetrage", MENU_FENETRAGE);
	glutAddMenuEntry("Remplissage", MENU_REMPLISSAGE);

	glutAttachMenu(GLUT_RIGHT_BUTTON);



	/* Entrée dans la boucle principale de glut, traitement des évènements */
	glutMainLoop();         // lancement de la boucle de réception des évènements
	return 0;
}




void affichage(){


	printf(couleur ? " couleur true" : " couleur false");
	printf(polygone ? " polygone true" : " polygone false");
	printf(trace_fenetre ? " trace_fenetre true" : " trace_fenetre false");
	printf(fenetrage ? " fenetrage true" : " fenetrage false");
	printf(remplissage ? " remplissage true" : " remplissage false");




	glClear(GL_COLOR_BUFFER_BIT);


	/*   A vous de jouer !!!   */

	// TRACAGE DU POLYGONE
	if (polygone == true)
	{
		glBegin(GL_POINTS);

		glVertex2f(x0, y0);

		glEnd();


		if (monTableauDePointX[2] != NULL && monTableauDePointY[2] != NULL)
		{
			glBegin(GL_LINE_LOOP);

			for (int i = 0; i<sizeof(monTableauDePointX) / sizeof(*monTableauDePointX); i++)
			{
				if (monTableauDePointX[i] != NULL && monTableauDePointY[i] != NULL)
				{
					glVertex2f(monTableauDePointX[i], monTableauDePointY[i]);
				}

			}
			glEnd();
		}
	}

	//TRACAGE DU FENETRAGE
	if (fenetrage == true)
	{
		glBegin(GL_POINTS);

		glVertex2f(rectx, recty);

		glEnd();

		if (monTableauPointRectX[1] != NULL && monTableauPointRectY[1] != NULL)
		{
			glRectd(monTableauPointRectX[0], monTableauPointRectY[0], monTableauPointRectX[1], monTableauPointRectY[1]);

		}

	}

	// On force l'affichage du résultat
	glFlush();
}




void mouse(int button, int state, int x, int y)
{

	if (polygone == true)
	{


		// Si on appuie sur le bouton de gauche
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			x0 = x - 250; //on sauvegarde la position de la souris
			y0 = -y + 250;
			if (cpt<10)
			{
				monTableauDePointX[cpt] = x0;
				monTableauDePointY[cpt] = y0;

			}
			cpt++;

			affichage();
		}

	}

	if (fenetrage == true)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			rectx = x - 250; //on sauvegarde la position de la souris
			recty = -y + 250;
			if (cptrect<3)
			{
				monTableauPointRectX[cptrect] = rectx;
				monTableauPointRectY[cptrect] = recty;

			}
			cptrect++;

			affichage();
		}
	}


}



/* Evènement du clavier */
void clavier(unsigned char touche, int x, int y){
	switch (touche){

	case 'q':/* Quitter le programme */
		exit(0);
	}
}

void menu(int item)
{
	switch (item)
	{
	case MENU_COULEUR:
	{
		couleur = true;
		polygone = false;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = false;

	}
		break;
	case MENU_POLYGONE:
	{
		couleur = false;
		polygone = true;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = false;

	}
		break;
	case MENU_TRACE_FENETRE:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = true;
		fenetrage = false;
		remplissage = false;

	}
		break;
	case MENU_FENETRAGE:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = false;
		fenetrage = true;
		remplissage = false;

	}
		break;
	case MENU_REMPLISSAGE:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = true;

	}
		break;
	default:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = false;

	}
		break;
	}

	glutPostRedisplay();

	return;
}

