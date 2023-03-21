// startingMenu.cpp

//#include <GLUT/glut.h>
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <string>

class StartingMenu {
private:
int windowHeight;
int menuOption;
public:
StartingMenu();
void display();
void mouse(int button, int state, int x, int y);
int getWindowHeight() const;
int getMenuOption() const;
};
StartingMenu::StartingMenu() {
windowHeight = 500;
menuOption = 0;
}

void StartingMenu::display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Title
    glRasterPos2i(180, 350);
    std::string title = "Ultimate Tic Tac Toe";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    // Menu options
    glRasterPos2i(220, 250);
    std::string option1 = "1. Play";
    for (char c : option1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2i(220, 200);
    std::string option2 = "2. Instructions";
    for (char c : option2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2i(220, 150);
    std::string option3 = "3. Exit";
    for (char c : option3) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glFlush();
}

void StartingMenu::mouse(int button, int state, int x, int y) {
if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
if (y >= 250 && y <= 280) {
menuOption = 1;
} else if (y >= 200 && y <= 230) {
menuOption = 2;
} else if (y >= 150 && y <= 180) {
menuOption = 3;
}
}
}

int StartingMenu::getWindowHeight() const {
return windowHeight;
}

int StartingMenu::getMenuOption() const {
return menuOption;
}
