#include <iostream>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <cmath>
#include "game.cpp"
#include "startingMenu.cpp"

// global variables
Game game;
StartingMenu menu;
int page=0;

void drawBoard() {
    game.drawBoard();
}

void reshape(int w, int h) {
    game.reshape(w, h);
}

void mouseGame(int button, int state, int x, int y) {
    game.handleMouseClick(button,state,x,y);
}
void display() {
    menu.display();
}

void mouseMenu(int button, int state, int x, int y) {
    menu.mouse(button, state, x, menu.getWindowHeight() - y);
    page=menu.getMenuOption();
    glutPostRedisplay(); // Redraw the display after the menu option changes
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ultimate Tic Tac Toe");

    if (page==1){
        glutDisplayFunc(drawBoard);
        glutReshapeFunc(reshape);
        glutMouseFunc(mouseGame);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glutMainLoop();
    }
    if(page==0){

            glutDisplayFunc(display);
            glutMouseFunc(mouseMenu);
            glutMainLoop();
    }
    return 0;
}

