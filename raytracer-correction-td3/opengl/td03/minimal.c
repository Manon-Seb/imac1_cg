#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2., 2., -2., 2.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


unsigned int CIRCLE_SUBDIVISIONS = 100;
float PI = 3.14159265359;

void drawCircle(int full) {
    float deltaAngle = 2.0 * PI / CIRCLE_SUBDIVISIONS;
    if (full == 0) {
        glBegin(GL_LINE_LOOP);
    }
    else {
        glBegin(GL_TRIANGLE_FAN);
    }
    
    for (int i = 0; i < CIRCLE_SUBDIVISIONS; ++i) {
        float angle = i * deltaAngle;
        float x = cos(angle);
        float y = sin(angle);
        glVertex2f(x, y);
    }
    glEnd();    
}

void drawSquare(int full) {
    if (full == 0) {
        glBegin(GL_QUADS);
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

void drawRoundedSquare() {
     
     float circleRadius = 0.1f;

    // draw vertical square

    glPushMatrix();
    glScalef(1.0, 1.0 - 2.0 * circleRadius, 1.0);
    drawSquare(1);
    glPopMatrix();

    // draw horizontal square

    glPushMatrix();
    glScalef(1.0 - 2.0 * circleRadius, 1.0, 1.0);
    drawSquare(1);
    glPopMatrix();

    // draw circles

    glPushMatrix();
    glTranslatef(-0.5f + circleRadius, 0.5f - circleRadius, 0.0);
    glScalef(circleRadius, circleRadius, 1.0);
    drawCircle(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f - circleRadius, 0.5f - circleRadius, 0.0);
    glScalef(circleRadius, circleRadius, 1.0);
    drawCircle(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f + circleRadius, -0.5f + circleRadius, 0.0);
    glScalef(circleRadius, circleRadius, 1.0);
    drawCircle(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f - circleRadius, -0.5f + circleRadius, 0.0);
    glScalef(circleRadius, circleRadius, 1.0);
    drawCircle(1);
    glPopMatrix();

}

GLuint createFirstArmList() {

    float firstCircleRadius = 0.2f;
    float secondCircleRadius = 0.10f;
    float armSize = 0.6f;

    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

    // first circle
    glPushMatrix();
    glScalef(firstCircleRadius, firstCircleRadius, 1.0f);
    drawCircle(1);
    glPopMatrix();

    // second circle
    glPushMatrix();
    glTranslatef(armSize, 0.0, 0.0);
    glScalef(secondCircleRadius, secondCircleRadius, 1.0f);
    drawCircle(1);
    glPopMatrix();

    // quad between cricles
    glBegin(GL_QUADS);
    glVertex2f(0.0, firstCircleRadius);
    glVertex2f(armSize, secondCircleRadius);
    glVertex2f(armSize, -secondCircleRadius);
    glVertex2f(0.0, -firstCircleRadius);
    glEnd();

    glEndList();
    return id;

}

GLuint createSecondArmList() {

    float roundedSquareSize = 0.1f;
    float armWidth = 0.5f;
    float armHeight = 0.06f;

    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

    // left rounded square
    glPushMatrix();
    glScalef(roundedSquareSize, roundedSquareSize, 1.0);
    drawRoundedSquare();
    glPopMatrix();

    // right rounded square
    glPushMatrix();
    glTranslatef(armWidth, 0.0, 0.0);
    glScalef(roundedSquareSize, roundedSquareSize, 1.0);
    drawRoundedSquare();
    glPopMatrix();

    // center square
    glPushMatrix();
    glTranslatef(armWidth / 2.0, 0.0, 0.0);
    glScalef(armWidth, armHeight, 1.0);
    drawSquare(1);
    glPopMatrix();

    glEndList();
    return id;

}

GLuint createThirdArmList() {

    float roundedSquareSize = 0.06f;
    float armWidth = 0.4f;
    float armHeight = 0.04f;
    float circleRadius = 0.04f;

    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

    // draw rounded square

    glPushMatrix();
    glScalef(roundedSquareSize, roundedSquareSize, 1.0);
    drawRoundedSquare();
    glPopMatrix();

    // draw center square

    glPushMatrix();
    glTranslatef(armWidth / 2.0, 0.0, 0.0);
    glScalef(armWidth, armHeight, 1.0);
    drawSquare(1);
    glPopMatrix();

    // draw circle

    glPushMatrix();
    glTranslatef(armWidth, 0.0, 0.0);
    glScalef(circleRadius, circleRadius, 1.0);
    drawCircle(1);
    glPopMatrix();

    glEndList();
    return id;

}

int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("td03", NULL);

    resizeViewport();

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    int loop = 1;
    float alphaAngle = 45.0; // deg
    float betaAngle = -10.0; // deg
    float thetaAngle = 18.0; // deg

    GLuint firstArmListID = createFirstArmList();
    GLuint secondArmListID = createSecondArmList();
    GLuint thirdArmListID = createThirdArmList();

    int thirdArmCount = 3;

    while(loop) {

        Uint32 startTime = SDL_GetTicks();
        
        /* Code de dessin */

        glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer

        glColor3ub(255, 0, 0);
        
        glPushMatrix();
        glRotatef(alphaAngle, 0, 0, 1);
        glCallList(firstArmListID);

            glPushMatrix();
            glTranslatef(0.6, 0, 0);
            glRotatef(betaAngle, 0, 0, 1);
            glColor3ub(0, 255, 0);
            glCallList(secondArmListID);

                glPushMatrix();
                glColor3ub(0, 255, 255);
                glTranslatef(0.5f, 0, 0);
                glRotatef(thetaAngle, 0, 0, 1);

                for (int i = 0; i < thirdArmCount; ++i) {
                    glRotatef(360.0 / thirdArmCount, 0, 0, 1);        
                    glCallList(thirdArmListID);
                }

                glPopMatrix();

            glPopMatrix();

        glPopMatrix();


        alphaAngle = alphaAngle + 1.0;
        betaAngle = betaAngle - 2.0;
        thetaAngle = thetaAngle + 2.0;


        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }

            switch(e.type) {

                case SDL_MOUSEBUTTONUP:
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


    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
