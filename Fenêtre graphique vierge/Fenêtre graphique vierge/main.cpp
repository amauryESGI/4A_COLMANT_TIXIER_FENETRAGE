

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
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

int x0, y0;  // clic souris
int cpt = 0;
int monTableauDePointX[10];
int monTableauDePointY[10];

int* maListeDePointX[1];
int maListeDePointXBis[1];
int _size = 0;

bool couleur, polygone, trace_fenetre, fenetrage , remplissage ;

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
MENU_TYPE show = MENU_COULEUR;

/* prototypes de fonctions */
void affichage(void);                             // modélisation
void clavier(unsigned char touche,int x,int y);   // fonction clavier
void mouse(int bouton,int etat,int x,int y);      // fonction souris
void menu(int item);

/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
		  char **argv){  // argv: tableau de chaines de caractères, argv[0] contient le nom du programme lancé (plus un éventuel chemin)

    for(int i=0;i<sizeof(monTableauDePointX)/sizeof(*monTableauDePointX);i++)
{
    monTableauDePointX[i]=NULL;
}
for(int i=0;i<sizeof(monTableauDePointY)/sizeof(*monTableauDePointY);i++)
{
    monTableauDePointY[i]=NULL;
}




	/* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(500, 500);                // dimension fenêtre
	glutInitWindowPosition (100, 100);           // position coin haut gauche
	glutCreateWindow("A vous de jouer!!!");  // nom

	/* Repère 2D délimitant les abscisses et les ordonnées*/
	gluOrtho2D(-250.0,250.0,-250.0,250.0);

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
    glutAddMenuEntry("Couleur",MENU_COULEUR);
    glutAddMenuEntry("Polygone a découper",MENU_POLYGONE);
    glutAddMenuEntry("Trace fenetre",MENU_TRACE_FENETRE);
    glutAddMenuEntry("Fenetrage",MENU_FENETRAGE);
    glutAddMenuEntry("Remplissage",MENU_REMPLISSAGE);

    glutAttachMenu(GLUT_RIGHT_BUTTON);



	/* Entrée dans la boucle principale de glut, traitement des évènements */
    glutMainLoop();         // lancement de la boucle de réception des évènements
    return 0;
}




void affichage(){


glClear(GL_COLOR_BUFFER_BIT);


/*   A vous de jouer !!!   */


glBegin(GL_POINTS);

glVertex2f(x0,y0);

glEnd();


if(monTableauDePointX[3] != NULL && monTableauDePointY[3] != NULL)
{
    glBegin(GL_LINE_LOOP);

    for(int i=0;i<sizeof(monTableauDePointX)/sizeof(*monTableauDePointX);i++)
    {
        if(monTableauDePointX[i]!=NULL && monTableauDePointY[i]!=NULL )
        {
            glVertex2f(monTableauDePointX[i],monTableauDePointY[i]);
        }

    }


    glEnd();
}





// On force l'affichage du résultat
glFlush();
}


void mouse(int button,int state,int x,int y)
{

	// Si on appuie sur le bouton de gauche
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x0 = x - 250; //on sauvegarde la position de la souris
		y0 = -y + 250;
        if(cpt<10)
        {
            monTableauDePointX[cpt] = x0;
            monTableauDePointY[cpt] = y0;

            //mon nouveau code
/*
                _size++;
                int maListeDePointXtest[_size];
                for(int i = 0; i<_size;i++)
                {
                    maListeDePointXtest[i] = maListeDePointX[*(i)];
                }
                int* maListeDePointX[_size];
                for(int i = 0; i<_size;i++)
                {
                    maListeDePointX[*(i)] = maListeDePointXtest[i];
                }
                for(int i = 0; i<_size;i++)
                {
                   // printf(char(*maListeDePointX[i]));
                }

*/
            //DA END

        }
        cpt++;

		affichage();
	}



}



/* Evènement du clavier */
void clavier(unsigned char touche,int x,int y){
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

            }
        case MENU_POLYGONE:
            {

            }
        case MENU_TRACE_FENETRE:
            {

            }
        case MENU_FENETRAGE:
            {

            }
        case MENU_REMPLISSAGE:
                {
                        show = (MENU_TYPE) item;
                }
                break;
        default:
                {       /* Nothing */       }
                break;
        }

        glutPostRedisplay();

        return;
}

