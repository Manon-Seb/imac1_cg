#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#import <time.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 MAX_FRAME_PER_SECS = 60;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4., 4., -3., 3.); // On modifie la matrice de projection en lui disant de projeter à l'écran tous les objets se trouvant entre les bornes -4/4 (x) et -3/3 (y)
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


void drawSquare(int full) {
    /*
    Fonction qui dessine un carré canonique de côté 1, centré sur l'origine.
    */
    if (full == 0) {
        glBegin(GL_LINE_LOOP);
    }
    else {
        glBegin(GL_TRIANGLE_FAN);
    }
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
}


void drawLandmark() {
    /*
    Fonction qui dessine un repère, centré sur (0, 0)
    */
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glColor3ub(0, 255, 0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 1.0);
    glEnd();
}


unsigned int CIRCLE_SUBDIVISIONS = 100;
void drawCircle(int full) {
    /*
    Fonction qui dessine un cercle de diamètre 1, centré sur l'origine.
    */
    if (full == 0) {
        glBegin(GL_LINE_LOOP);
    }
    else {
        glBegin(GL_TRIANGLE_FAN);
    }
    float deltaAngle = 2.0 * M_PI / (float)CIRCLE_SUBDIVISIONS;
    for (int i = 0; i < CIRCLE_SUBDIVISIONS; ++i) {
        float angle = i * deltaAngle;
        float x = 0.5 * cos(angle); // on multiplie par 0.5 pour avoir un diamètre de 1
        float y = 0.5 * sin(angle); // on multiplie par 0.5 pour avoir un diamètre de 1
        glVertex2f(x, y);
    }
    glEnd();
}


int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption("td02 ex 0203", NULL);
    resizeViewport();

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW); // On active la matrice MODELVIEW, celle chargée de la transformation des objets dans l'espace

    int loop = 1;
    float glX = 0, glY = 0;
    float lastPointHoverX = 0, lastPointHoverY = 0, rotateAngle = 0;
    int rightButtonClicked = 0;


    // Variables pour Ex07
    float randomTranslateX = 0, randomTranslateY = 0; // la position actuelle du cube bleu
    float dirX = -4.0 + 8.0 * (rand() / (float) RAND_MAX); // Une première direction aléatoire à atteindre
    float dirY = - (-3.0 + 6.0 * (rand() / (float) RAND_MAX)); // Une première direction aléatoire à atteindre
    int iterationTime = 5.0; // 5secs par déplacement
    Uint32 randomStartTime = SDL_GetTicks(); // Le temps de départ de ce déplacement

    // Boucle d'affichage
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // Code de dessin
        glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer

        // Ex01 : Dessin du repère
        glLoadIdentity(); // On réinitialise la matric MODELVIEW à Identité, annulant ainsi toutes les transformations précédentes
        drawLandmark();

        // Ex02 : Dessin du cercle orange en (1, 2). On utlise pour cela une translation avant de dessiner le cercle.
        glLoadIdentity();
        glColor3ub(255, 127, 0);
        glTranslatef(1, 2, 0);
        drawCircle(1);

        // Ex03 : Carré rouge sur lequel on applique une rotation de 45° puis une translation de 2 sur l'axe des X;
        glLoadIdentity();
        glColor3ub(255, 0, 0);
        glRotatef(45, 0, 0, 1);
        glTranslatef(2, 0, 0);
        drawSquare(1);

        // Ex04 : Même chose en inversant Rotation et Translation. On constate que l'ordre d'execution des transformations est important.
        glLoadIdentity();
        glColor3ub(255, 0, 0);
        glTranslatef(2, 0, 0);
        glRotatef(45, 0, 0, 1);
        drawSquare(1);

        // Ex05 : Carré jaune qui se raplce à l'endroit cliqué. Pour cela, on stocke les coordonnées OpenGL du point cliqué pour les utiliser dans la translation.
        /*glLoadIdentity();
        glColor3ub(255, 255, 0);
        glTranslatef(glX, glY, 0);
        drawSquare(1);*/

        // Ex06 : Un carré similaire qui rotate en fonction du drag & drop. Voir la boucle d'event pour le calcul de "rotateAngle"
        // Commenter l'Ex05 avant de décommenter l'Ex06
        glLoadIdentity();
        glColor3ub(255, 255, 0);
        glTranslatef(glX, glY, 0);
        glRotatef(rotateAngle, 0, 0, 1);
        drawSquare(1);

        // Ex07 : Cube qui se déplace aléatoirement dans la fenêtre
        
        // Toutes les "iterationTime" secondes, on choisis une nouvelle destination
        if (startTime - randomStartTime > iterationTime * 1000.0) {
            // Je choisis une destination alétoire dans la fenêtre
            float dstX = -4.0 + 8.0 * (rand() / (float) RAND_MAX);
            float dstY = - (-3.0 + 6.0 * (rand() / (float) RAND_MAX));
            // Je calcule la direction à prendre pour atteindre le point.
            dirX = dstX - randomTranslateX; // randomTranslateX = la dernière destination à atteindre, donc la position actuelle.
            dirY = dstY - randomTranslateY; // randomTranslateY = la dernière destination à atteindre, donc la position actuelle.
            randomStartTime = startTime; // Le temps de départ de ce déplacement
        }

        glLoadIdentity();
        glColor3ub(0, 0, 255);
        // Je calcule la portion de déplacement à effectuer pour ce tour de boucle
        float deltaX = dirX / (iterationTime * MAX_FRAME_PER_SECS);
        float deltaY = dirY / (iterationTime * MAX_FRAME_PER_SECS);
        // J'ajoute ce déplacement à la position du cube
        randomTranslateX += deltaX;
        randomTranslateY += deltaY;
        glTranslatef(randomTranslateX, randomTranslateY, 0);
        drawSquare(1);

        // Boucle traitant les evenements
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }

            switch(e.type) {

                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        // On récupère les coordonnées de pixel pour les transformer en coordonnées OpenGL.
                        // Attention : On doit utiliser la valeur des bornes de la projection dans le calcul (-4, 4 et -3, 3);
                        glX = -4 + 8. * e.button.x / WINDOW_WIDTH;
                        glY = -(-3 + 6. * e.button.y / WINDOW_HEIGHT);
                    }
                    else if (e.button.button == SDL_BUTTON_RIGHT) {
                        // On détecte la fin du drag & drop
                        rightButtonClicked = 0;
                    }
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == SDL_BUTTON_RIGHT) {
                        // Lorsqu'on clique la première fois avec le bouton gauche, on enregistre la position de ce clic.
                        lastPointHoverX = -4 + 8. * e.button.x / WINDOW_WIDTH;
                        lastPointHoverY = -(-3 + 6. * e.button.y / WINDOW_HEIGHT);
                        printf("lastPointHoverX %f, lastPointHoverY %f\n", lastPointHoverX, lastPointHoverY);
                        rightButtonClicked = 1;
                    }
                    break;

                case SDL_MOUSEMOTION:

                    if (rightButtonClicked) {

                        /*
                            A chaque mouvement de la souris, on chercher à calculer l'angle formé avec le mouvement précédent.

                            Pour cela, on définit 2 vecteurs :
                            - U, le vecteur formé par l'origine du carré et le premier point cliqué
                            - V, le vecteur formé par l'origine du carré et le point courrant survolé

                            On peut ensuite retrouver l'angle formé entre ces deux angles en utilisant la formule trigonométrique suivante :
                            cosinus de l'angle = scalUV / (normU * normV)
                            où scalUV est le produit scalaire entre U et V, et normU/V est la norme respective de chacun des vecteurs

                            On peut finalement retrouver l'angle en appelant la fonction acos (arc-cosinus) qui renvoie l'angle à partir d'un cosinus.

                            Pour terminer, on transforme la valeur de l'angle obtenue en degré.

                            En dernier lieu, on inverse l'angle en fonction du "sens du mouvement". Pour cela, on utilise le signe du produit vectoriel entre deux angles (en 2D).
                            Si l'angle formé entre les deux vecteurs est horaire, alors le produit vectoriel 2D est négatif, et inversement.
                        */

                        // On récupère le point couramment survolé
                        float currentPointHoverX = -4 + 8. * e.button.x / WINDOW_WIDTH;
                        float currentPointHoverY = -(-3 + 6. * e.button.y / WINDOW_HEIGHT);

                        // On construit les vecteur U et V en fonction de la position du carré et la position des points cliqués et survolés
                        // Rappel : les coordonnées d'un vecteur AB sont : (Bx - Ax) et (By - Ay)
                        
                        // Vecteur Carré - Point cliqué (ou point survolé précédent)
                        float Ux = lastPointHoverX - glX;
                        float Uy = lastPointHoverY - glY;

                        // Vecteur Carré - Point survolé
                        float Vx = currentPointHoverX - glX;
                        float Vy = currentPointHoverY - glY;

                        // On calcule la norme des vecteurs
                        // Rappel : La norme d'un vecteur A(x, y) vaut RacineCarrée(x * x, y * y)
                        float normU = sqrt(Ux * Ux + Uy * Uy);
                        float normV = sqrt(Vx * Vx + Vy * Vy);

                        // Si on a survolé l'origine du cube, on stop net car la suite entrainerait des divisions par 0
                        if (normU * normV == 0) {
                            continue;
                        }

                        // On calcule le produit scalaire entre U et V
                        // Rappel : Le produit scalaire entre deux vecteurs A et B vaut Ax * Bx + Ay * By
                        float scalUY = Ux * Vx + Uy * Vy;

                        // On calcule le cosinus de l'angle formé entre les deux vecteurs
                        float cosDelta = scalUY / (normU * normV);
                        float delta = acos(cosDelta);

                        // On transforme cette valeur d'angle en degré
                        float angle = delta * 360.0 / (2 * M_PI);

                        // On calcule le produit vectoriel 2D pour trouver le "sens" de l'angle
                        // Produit Vectoriel 2D = Ax * By - Ay * Bx
                        if (Ux * Vy - Uy * Vx < 0.0) {
                            angle = - angle;
                        }

                        // On ajoute cette valeur d'angle à la valeur globale de l'angle
                        rotateAngle += angle;
                        if (rotateAngle > 360.0) {
                            rotateAngle -= 360.0;
                        }
                        if (rotateAngle < -360.0) {
                            rotateAngle += 360.0;
                        }

                        // On enregistre le point courant comme étant le point précédent (pour la boucle suivante)
                        lastPointHoverX = currentPointHoverX;
                        lastPointHoverY = currentPointHoverY;
                    }

                    break;

                case SDL_KEYDOWN:

                    switch(e.key.keysym.sym) {

                        case SDLK_q:
                            loop = 0;

                        default:
                            break;
                    }

                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
