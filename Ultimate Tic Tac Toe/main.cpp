#include <iostream>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <cmath>
#include "game.cpp"


Game game; // Create an instance of the class

void drawBoard() {
    game.drawBoard();
}

void reshape(int w, int h) {
    game.reshape(w, h);
}

void handleMouseClick(int button, int state, int x, int y) {
    game.handleMouseClick(button,state,x,y);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ultimate Tic Tac Toe Board");
    glutDisplayFunc(drawBoard);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouseClick);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    
    return 0;
}

