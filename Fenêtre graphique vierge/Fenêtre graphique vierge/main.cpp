

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



#include "stdafx.h"

#define _WINDOW_HEIGHT	500
#define _WINDOW_WIDTH	500

int clicx, clicy;  // clic souris
int cpt = 0;
int monTableauDePointX[10];
int monTableauDePointY[10];

int rectx;
int recty;
int monTableauPointRectX[2];
int monTableauPointRectY[2];
int cptrect = 0;


bool couleur = false;
bool polygone = true;
bool trace_fenetre = false;
bool fenetrage = false;
bool remplissage = false;
bool raz = false;

std::vector<Vector2D> maListDePointPolygone;
std::vector<Vector2D> maListDePointFenetre;



// Menu items
enum MENU_TYPE
{
	MENU_COULEUR,
	MENU_POLYGONE,
	MENU_TRACE_FENETRE,
	MENU_FENETRAGE,
	MENU_REMPLISSAGE,
	MENU_RAZ,
};


// Assign a default value
//MENU_TYPE show = MENU_COULEUR;

/* prototypes de fonctions */
void affichage(void);                             // modélisation
void clavier(unsigned char touche, int x, int y);   // fonction clavier
void mouse(int bouton, int etat, int x, int y);      // fonction souris
void menu(int item);
void methodFenetrage(void);
//
//void sutherland(void);
//
////PARAMETRE SUTHER//
//
//PL;
//PW;
//
//bool coupe(int S, int Pj, int Fi, int Fi + 1);
//bool intersection(int S, int Pj, int Fi, int Fi + 1);
//bool visible(int S, int Fi, int Fi + 1);
//
//
//
//// Sutherland-Hodgman
//
///*Pour chaque point de la window PW*/
//for(i = 1; i < (N3 - 1; ++i)
//{
//	N2 = 0;
//	PS = NULL;
//	for (j = 1; j < N1; ++j)
//	{
//		if (j = 1)
//		{
//			F = Pj;/*Sauver le 1er = dernier sommet*/
//		}
//		else
//		{
//			if (coupe(S, Pj, Fi, Fi + 1))
//			{
//				I = intersection(S, Pj, Fi, Fi + 1);
//				Charger(I, PS);
//				N2++;
//			}
//		}
//		S = Pj;
//		if (visible(S, Fi, Fi + 1))
//		{
//			Charger(S, PS);
//			N2++;
//		}
//	}
//	if (N2 > 0)
//	{
//		/*Traitement du dernier coté de PL*/
//		if (coupe(S, F, Fi, Fi + 1))
//		{
//			I = intersection(S, F, Fi, Fi + 1);
//				Charger(I, PS);
//			N2++;
//		}
//		PL = PS;
//		N1 = N2;
//	}
//}
///* Pour chaque point du polygone PL*/
//
//


















/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
	char **argv){  // argv: tableau de chaines de caractères, argv[0] contient le nom du programme lancé (plus un éventuel chemin)

	

	/* Initialisation de glut et creation de la fenetre */
	glutInit(&argc, argv);                       // Initialisation
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
	glutInitWindowSize(_WINDOW_WIDTH, _WINDOW_HEIGHT);				// dimension fenêtre
	glutInitWindowPosition(100, 100);           // position coin haut gauche
	glutCreateWindow("A vous de jouer!!!");		// nom

	/* Repère 2D délimitant les abscisses et les ordonnées*/
	gluOrtho2D(-_WINDOW_WIDTH / 2, _WINDOW_WIDTH / 2, -_WINDOW_HEIGHT / 2, _WINDOW_HEIGHT / 2);

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
	glutAddMenuEntry("Remise à zéro", MENU_RAZ);
	//glutAddSubMenu("Vert", MENU_COULEUR);
	glutAttachMenu(GLUT_RIGHT_BUTTON);



	/* Entrée dans la boucle principale de glut, traitement des évènements */
	glutMainLoop();         // lancement de la boucle de réception des évènements
	return 0;
}




void affichage(){


	//std::cout << raz << std::endl;
	//std::cout << trace_fenetre << std::endl;



	glClear(GL_COLOR_BUFFER_BIT);
	
	/*   A vous de jouer !!!   */

	// TRACAGE DU POLYGONE
		glColor3f(1.0, 0, 0);

		glBegin(GL_POINTS);

		glVertex2f(clicx, clicy);

		glEnd();


			glBegin(GL_LINE_LOOP);

			for (int i = 0; i < maListDePointPolygone.size(); i++)
			{

				glVertex2f(maListDePointPolygone[i]._x, maListDePointPolygone[i]._y);
			}

			glEnd();
		//}
	//TRACAGE DU FENETRAGE
		glColor3f(0, 1.0, 0);

		glBegin(GL_POINTS);

		glVertex2f(rectx, recty);

		glEnd();
		

		glBegin(GL_LINE_LOOP);

		for (int i = 0; i < maListDePointFenetre.size(); ++i)
		{
			glVertex2f(maListDePointFenetre[i]._x, maListDePointFenetre[i]._y);
		}

		glEnd();

		
		
			
		
		

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
			clicx = x - 250; //on sauvegarde la position de la souris
			clicy = -y + 250;
				

				maListDePointPolygone.push_back(Vector2D(clicx, clicy));
			
		

			affichage();
		}

	}

	if (trace_fenetre == true)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			rectx = x - 250; //on sauvegarde la position de la souris
			recty = -y + 250;
			
			maListDePointFenetre.push_back(Vector2D(rectx, recty));

			
			affichage();
		}
	}

	if (fenetrage == true)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{

		}
		
	}

	if (raz == true)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			maListDePointPolygone.erase(maListDePointPolygone.begin(), maListDePointPolygone.end());
			maListDePointFenetre.erase(maListDePointFenetre.begin(), maListDePointFenetre.end());
			

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
		raz = false;
	}
		break;
	case MENU_POLYGONE:
	{
		couleur = false;
		polygone = true;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = false;
		raz = false;
	}
		break;
	case MENU_TRACE_FENETRE:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = true;
		fenetrage = false;
		remplissage = false;
		raz = false;

	}
		break;
	case MENU_FENETRAGE:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = false;
		fenetrage = true;
		remplissage = false;
		raz = false;
	}
		break;
	case MENU_REMPLISSAGE:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = true;
		raz = false;
	}
		break;
	case MENU_RAZ:	
	{
		couleur = false;
		polygone = false;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = false;
		raz = true;
	}
		break;
	default:
	{
		couleur = false;
		polygone = false;
		trace_fenetre = false;
		fenetrage = false;
		remplissage = false;
		raz = false;
	}
		break;
	}

	glutPostRedisplay();

	return;
}


