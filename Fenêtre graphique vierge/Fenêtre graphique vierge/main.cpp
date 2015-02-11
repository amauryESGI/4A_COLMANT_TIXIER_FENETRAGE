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
#include<iostream>
#include<vector>
#include"Vector2D.h"
#include"Point.h"


int clicx, clicy;  // clic souris

int rectx;
int recty;



bool couleur = false;
bool polygone = true;
bool trace_fenetre = false;
bool fenetrage = false;
bool remplissage = false;
bool raz = false;

std::vector<Point> maListDePointPolygone; 
std::vector<Point> maListDePointFenetre; 
std::vector<Point> monPolygoneFinal;
std::vector<Point> PS;
bool afficherPolygoneClipper;

GLfloat BLUE[3] = { 0.0, 0.0, 1.0 };
GLfloat GREEN[3] = { 0.0, 1.0, 0.0 };
GLfloat RED[3] = { 1.0, 0.0, 0.0 };

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

enum MENU_COLOR
{
	COLOR_RED,
	COLOR_BLUE,
	COLOR_GREEN,
};

// Assign a default value
//MENU_TYPE show = MENU_COULEUR;

/* prototypes de fonctions */
void affichage(void);                             // modélisation
void clavier(unsigned char touche, int x, int y);   // fonction clavier
void mouse(int bouton, int etat, int x, int y);      // fonction souris
void menu(int item);
void submenu(int item);
void methodFenetrage(void);
bool visible(Point P1, Point F1, Point F2, std::vector<Point> list);
bool coupe(Point P1, Point P2, Point F1, Point F2, std::vector<Point> list);
void algorithmeSuthern(std::vector<Point> Window, std::vector<Point> Polygon2Clipp);

//FONCTION DE DESSIN

/*void dessinerPoint(int x, int y, GLfloat* color)
{
	glPushMatrix();
	glColor3fv(color);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glPopMatrix();
}*/

void dessinerPolygon(std::vector<Point> list, GLfloat* color)
{
	if (!list.empty()) 
	{
		glPushMatrix();
		glColor3fv(color);
		glBegin(GL_LINE_LOOP);
		std::vector<Point>::iterator lit;
		for (int i = 0; i < list.size(); i++)
		{
			glVertex2f(list[i]._x, list[i]._y);
		}
		glEnd();
		glPopMatrix();
	}
}





/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
	char **argv){  // argv: tableau de chaines de caractères, argv[0] contient le nom du programme lancé (plus un éventuel chemin)

	/* SECTION DE TEST DE L'ALGO SUTHERLAND*/
/*	maListDePointPolygone.push_back(Point(20,10));
	maListDePointPolygone.push_back(Point(20,-10));
	maListDePointPolygone.push_back(Point(0,-10));

	maListDePointFenetre.push_back(Point(10,10));
	maListDePointFenetre.push_back(Point(30,20));
	maListDePointFenetre.push_back(Point(30,-10));
	maListDePointFenetre.push_back(Point(10,-20));

	/*
	bool maVisibiliteP1 = false;
	maVisibiliteP1 = visible(maListDePointPolygone[0], maListDePointFenetre[0], maListDePointFenetre[1], maListDePointFenetre);
	std::cout << "P1 : " <<  maVisibiliteP1 << std::endl;

	bool maVisibiliteP2 = false;
	maVisibiliteP2 = visible(maListDePointPolygone[1], maListDePointFenetre[2], maListDePointFenetre[1], maListDePointFenetre);
	std::cout << "P2 : " << maVisibiliteP2 << std::endl;

	bool maVisibiliteP3 = false;
	maVisibiliteP3 = visible(maListDePointPolygone[2], maListDePointFenetre[3], maListDePointFenetre[0], maListDePointFenetre);
	std::cout << "P3 : " << maVisibiliteP3 << std::endl;
	*/
	
	

	
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
	int menu_color = glutCreateMenu(menu);
	
	glutAddMenuEntry("Couleur", MENU_COULEUR);
	glutAddMenuEntry("Polygone a découper", MENU_POLYGONE);
	glutAddMenuEntry("Trace fenetre", MENU_TRACE_FENETRE);
	glutAddMenuEntry("Fenetrage", MENU_FENETRAGE);
	glutAddMenuEntry("Remplissage", MENU_REMPLISSAGE);
	glutAddMenuEntry("Remise à zéro", MENU_RAZ);
	//glutAddSubMenu("Vert", MENU_COULEUR);
	//int rgbmenu;
	//rgbmenu = glutCreateMenu(submenu);
	//glutAddSubMenu("RGB Menu",menu_color);
	glutAttachMenu(GLUT_RIGHT_BUTTON);



	/* Entrée dans la boucle principale de glut, traitement des évènements */
	glutMainLoop();         // lancement de la boucle de réception des évènements
	return 0;
}




void affichage(){


	glClear(GL_COLOR_BUFFER_BIT);
	
	

	// TRACAGE DU POLYGONE
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(clicx, clicy);
	glEnd();
	
	

	
	dessinerPolygon(maListDePointPolygone, RED);
	//TRACAGE DU FENETRAGE
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(rectx, recty);
	glEnd();
	dessinerPolygon(maListDePointFenetre, GREEN);
	

	if (afficherPolygoneClipper == true)
	{
		dessinerPolygon(monPolygoneFinal, BLUE);
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
			
				clicx = x - 250; //on sauvegarde la position de la souris
				clicy = -y + 250;


				maListDePointPolygone.push_back(Point(clicx, clicy));



				affichage();
			}
		

	}

	if (trace_fenetre == true)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			rectx = x - 250; //on sauvegarde la position de la souris
			recty = -y + 250;
			
			maListDePointFenetre.push_back(Point(rectx, recty));

			
			affichage();
		}
	}

	if (fenetrage == true)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			algorithmeSuthern(maListDePointFenetre, maListDePointPolygone);
			affichage();
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
	case 'e': //execute
		algorithmeSuthern(maListDePointFenetre, maListDePointPolygone);
		affichage();
		break;
	case 'r': //raz
		maListDePointFenetre.clear();
		maListDePointPolygone.clear();
		monPolygoneFinal.clear();
		affichage();
		break;
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

void submenu(int item)
{
	switch (item)
	{
	case COLOR_RED:
	{
		
	}
		break;
	case COLOR_BLUE:
	{

	}
		break;
	case COLOR_GREEN:
	{

	}
		break;
	}
	glutPostRedisplay();

	return;
}


//Méthode permettant de calculer un vecteur
Vector2D calculerVecteur(Point P1, Point P2)
{
	float x = (P2._x - P1._x);
	float y = (P2._y - P1._y);
	Vector2D vecteur(x, y); 
	return vecteur;
}


//Méthode permattant de calculer le produit scalaire de deux vecteur
float produitScalaire(Vector2D vecteur1, Vector2D vecteur2)
{
	float produitScalaireV1V2 = 0;
	produitScalaireV1V2 = (vecteur1._x*vecteur2._x) + (vecteur1._y*vecteur2._y); 
	return produitScalaireV1V2;
}



Vector2D calculNormaleInterieur(Point F1, Point F2, std::vector<Point> listeDesPoints)
{
	Vector2D vecteurP1P2 = calculerVecteur(F1, F2);
	Point P3;
	
	std::vector<Point>::iterator monIterateur;

	for (monIterateur = listeDesPoints.begin(); monIterateur != listeDesPoints.end(); ++monIterateur)                       // Permet d'obtenir n'importe quel point du polygone qui n'est pas P1 ou P2
	{                                                                   
		if (*monIterateur == F1 || *monIterateur == F2)                                    
			continue;                                                   
		else
		{
			P3 = *monIterateur;
			break;
		}
	}
	Vector2D vecteurP1P3 = calculerVecteur(F1, P3);
	Vector2D normal1(-vecteurP1P2._y, vecteurP1P2._x);                         
	Vector2D normal2(vecteurP1P2._y, -vecteurP1P2._x);                         
	//renvoie la normal1 ou normal2 en fonction du résultat du produit scalaire
	if (0 < produitScalaire(vecteurP1P3, normal1))                            
		return normal1;
	else																		
		return normal2;

}

//Méthode pour vérifier si un point est du coté visible ou non
bool visible(Point P1, Point F1, Point F2, std::vector<Point> list)
{
	bool estVisible = false;
	float resultatProduitScalaire = 0.0;
	Vector2D normaleFenetre = Vector2D(0, 0);
	Vector2D vectortemp = Vector2D(0, 0); 

	normaleFenetre = calculNormaleInterieur(F1, F2, list);
	vectortemp = calculerVecteur(F1, P1);
	resultatProduitScalaire = produitScalaire(vectortemp, normaleFenetre);
	if (resultatProduitScalaire > 0)
	{
		estVisible = true;
	}

	return estVisible;
}

bool coupe(Point P1, Point P2, Point F1, Point F2, std::vector<Point> list)
{
	bool coupe = false;
	bool P1estVisible = false;
	bool P2estVisible = false;
	// On vérifie si le point P1 et P2 sont visibles par F1F2
	P1estVisible = visible(P1, F1, F2, list); 
	P2estVisible = visible(P2, F1, F2, list); 
	if ((P1estVisible && !P2estVisible) || (P2estVisible && !P1estVisible)) 
	{
		coupe = true;
	}

	return coupe;
		
}

Point intersection(Point P1, Point P2, Point F1, Point F2)
{
	Point pointIntersection;
	float s = 0.; 
	float t = 0.; 
	float numS = ((P1._y - F1._y)*(P2._x - P1._x) - (P1._x - F1._x)*(P2._y - P1._y));
	float numT = ((P1._y - F1._y)*(F2._x - F1._x) - (P1._x - F1._x)*(F2._y - F1._y));
	float denominateur = ((P2._x - P1._x)*(F2._y - F1._y) - (P2._y - P1._y)*(F2._x - F1._x));
	if (0. != denominateur || 0. != numS)
	{
		t = numT / denominateur;
		s = numS / denominateur;
		if ((0 <= t && 1 >= t) && (0 <= s && 1 >= s))
		{
			pointIntersection = Point((P1._x + (t*(P2._x - P1._x))), (P1._y + (t*(P2._y - P1._y)))); 
			return pointIntersection;
		}
		else if ((1 < s || 0 > s) && (0 <= t && 1 >= t)) 
		{
			pointIntersection = Point((P1._x + (t*(P2._x - P1._x))), (P1._y + (t*(P2._y - P1._y)))); 
			return pointIntersection;
		}
	}
	return pointIntersection;
}

void algorithmeSuthern(std::vector<Point> Window, std::vector<Point> Polygon2Clipp)
{
	monPolygoneFinal = Polygon2Clipp;                                                           
	Point first;                                                                                
	Point I;
	Point S;
	int i = 0, j = 0;
	std::vector<Point>::iterator wit;                                                             
	std::vector<Point>::iterator pit;                                                            
	for (wit = Window.begin(); wit != Window.end(); ++wit)                                           
	{
		j = 0;
		for (pit = monPolygoneFinal.begin(); pit != monPolygoneFinal.end(); ++pit)                   
		{
			if (0 == j)                                                                         
				first = *pit;                                                                   
			else
			{
				Point next = (*wit == Window.back()) ? Window.front() : (Window[i + 1]);
				if (coupe(S, *pit, *wit, next, Window))                                            
				{
					I = intersection(S, *pit, *wit, next);                                      
					PS.push_back(I);                                                            
				}
			}
			S = *pit;                                                                           
			Point next = (*wit == Window.back()) ? Window.front() : (Window[i + 1]);
			if (visible(S, *wit, next, Window))                                                  
				PS.push_back(S);                                                                

			j++;
		}
		if (!PS.empty())                                                                         
		{
			
			Point next = (*wit == Window.back()) ? Window.front() : (Window[i + 1]);
			if (coupe(S, first, *wit, next, Window))                                              
			{
				I = intersection(S, first, *wit, next);                                         
				PS.push_back(I);                                                                
			}
			monPolygoneFinal = PS;                                                              
			PS.clear();                                                                         
		}
		else
			monPolygoneFinal.clear();                                                           

		i++;
	}
	afficherPolygoneClipper = true;                                                                          
}

//
