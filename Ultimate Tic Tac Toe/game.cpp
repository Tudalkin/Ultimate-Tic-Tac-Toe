#include <iostream>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <cmath>
using namespace std;


class Game{
private:
    bool playerTurnX=true; //which player's turn
    int nextBoardCol=-1; //next board column to play on (-1 if first turn or board won)
    int nextBoardRow=-1; //nect board row to play on
    int boardState[9][9] = {0};  // 0 means empty, 1 means X, 2 means O
    int winner=-1;
    
public:
    void drawX(float x, float y, float size) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(x - size, y - size);
        glVertex2f(x + size, y + size);
        glVertex2f(x + size, y - size);
        glVertex2f(x - size, y + size);
        
        glEnd();
    }
    
    void drawO(float x, float y, float size) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 360; i++) {
            float rad = i * M_PI / 180.0f;
            float cx = x + size * cos(rad);
            float cy = y + size * sin(rad);
            glVertex2f(cx, cy);
        }
        glEnd();
    }
    int checkBoardWon(int row, int col) {
        // Check rows
        for (int i = 0; i < 3; i++) {
            int p = boardState[row*3+i][col*3];
            if (p != 0 && boardState[row*3+i][col*3+1] == p && boardState[row*3+i][col*3+2] == p){
                //bigBoardState[row][col]=p;
                return p;
            }
        }
        
        // Check columns
        for (int i = 0; i < 3; i++) {
            int p = boardState[row*3][col*3+i];
            if (p != 0 && boardState[row*3+1][col*3+i] == p && boardState[row*3+2][col*3+i] == p){
                //bigBoardState[row][col]=p;
                return p;
            }
        }
        
        // Check diagonals
        int p = boardState[row*3][col*3];
        if (p != 0 && boardState[row*3+1][col*3+1] == p && boardState[row*3+2][col*3+2] == p){
            //bigBoardState[row][col]=p;
            return p;
        }
        p = boardState[row*3][col*3+2];
        if (p != 0 && boardState[row*3+1][col*3+1] == p && boardState[row*3+2][col*3] == p){
            //bigBoardState[row][col]=p;
            return p;
        }
        //check for a tie
        bool fullBoard=true;
        for (int i = 0; i < 9; i++) {
            int j = i / 3;
            int k = i % 3;
            if (boardState[row*3+j][col*3+k] == 0) {
                fullBoard = false;
                break;
            }
        }
        if (fullBoard){
            return 3;
        }
        // No winner yet
        return 0;
    }
    int checkGameWon() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            int p = checkBoardWon(i, 0);
            if (p != 0 && p == checkBoardWon(i, 1) && p == checkBoardWon(i, 2)) {
                return p;
            }
        }
        
        // Check columns
        for (int i = 0; i < 3; i++) {
            int p = checkBoardWon(0, i);
            if (p != 0 && p == checkBoardWon(1, i) && p == checkBoardWon(2, i)) {
                return p;
            }
        }
        
        // Check diagonals
        int p = checkBoardWon(0, 0);
        if (p != 0 && p == checkBoardWon(1, 1) && p == checkBoardWon(2, 2)) {
            return p;
        }
        
        p = checkBoardWon(0, 2);
        if (p != 0 && p == checkBoardWon(1, 1) && p == checkBoardWon(2, 0)) {
            return p;
        }
        
        // Check for a tie
        bool fullBoard = true;
        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;
            if (checkBoardWon(row,col) == 0) {
                fullBoard = false;
                break;
            }
        }
        if (fullBoard) {
            return 0;
        }
        
        // Game not over yet
        return -1;
    }
    
    
    void drawSmallBoard(int currentBoardRow,int currentBoardCol)
    {
        if(currentBoardRow==nextBoardRow&&currentBoardCol==nextBoardCol)
            glColor3f(1.0f, 1.0f, 0.0f);
        else
            glColor3f(0.0f, 0.0f, 1.0f);
        
        // Draw vertical lines
        glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.33f);
        glVertex2f(1.0f, 0.33f);
        glVertex2f(-1.0f, -0.33f);
        glVertex2f(1.0f, -0.33f);
        glEnd();
        
        // Draw horizontal lines
        glBegin(GL_LINES);
        glVertex2f(-0.33f, 1.0f);
        glVertex2f(-0.33f, -1.0f);
        glVertex2f(0.33f, 1.0f);
        glVertex2f(0.33f, -1.0f);
        glEnd();
        
        // Draw X's and O's
        float xSize = 0.2f;
        float oSize = 0.25f;
        for (int i = 0; i < 9; i++) {
            int row = i / 3;
            int col = i % 3;
            if(boardState[currentBoardRow*3+row][currentBoardCol*3+col]==1)
                drawX(col * 0.66 - 0.66, row * -0.66 + 0.66,xSize);
            else if (boardState[currentBoardRow*3+row][currentBoardCol*3+col]==2)
                drawO(col * 0.66 - 0.66, row * -0.66 + 0.66, oSize);
            
        }
    }
    
    void drawBoard()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);
        glLineWidth(2.0f);
        
        // Draw vertical lines
        glBegin(GL_LINES);
        glVertex2f(-0.33f, 1.0f);
        glVertex2f(-0.33f, -1.0f);
        glVertex2f(0.33f, 1.0f);
        glVertex2f(0.33f, -1.0f);
        glEnd();
        
        // Draw horizontal lines
        glBegin(GL_LINES);
        glVertex2f(-1.0f, 0.33f);
        glVertex2f(1.0f, 0.33f);
        glVertex2f(-1.0f, -0.33f);
        glVertex2f(1.0f, -0.33f);
        glEnd();
        
        // Draw smaller boards
        for (int i = 0; i < 9; i++) {
            glPushMatrix();
            int row = i / 3;
            int col = i % 3;
            glTranslatef(col * 0.66 - 0.66, row * -0.66 + 0.66, 0.0f);
            glScalef(0.2f, 0.2f, 0.0f);
            float xSize = 1.0f;
            float oSize = 1.1f;
            //draw winner on Board
            //cout<<checkBoardWon(row,col)<<endl;
            switch (checkBoardWon(row,col)) {
                case 0:
                    drawSmallBoard(row,col);
                    break;
                case 1:
                    drawX(col * 0.66 - 0.66*col, row * -0.66 + 0.66*row, xSize);
                    break;
                case 2:
                    drawO(col * 0.66 - 0.66*col, row * -0.66 + 0.66*row, oSize);
                    break;
                case 3:
                    drawSmallBoard(row,col);
                    break;
            }
            glPopMatrix();
        }
        
        glFlush();
    }
    
    void reshape(int w, int h)
    {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
    }
    
    void handleMouseClick(int button, int state, int x, int y) {
        if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) {
            return;
        }
        
        // Convert mouse coordinates to OpenGL coordinates
        float glX = (x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
        float glY = (y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1;
        
        // Find the board and cell that was clicked
        int boardRow = (int)((glY + 1) / 0.66);
        int boardCol = (int)((glX + 1) / 0.66);
        int cellRow = (int)(((glY + 1) - boardRow * 0.66) / 0.22);
        int cellCol = (int)(((glX + 1) - boardCol * 0.66) / 0.22);
        //cout<<boardRow<<" "<<boardCol<<endl;
        //cout<<boardRow * 3 + cellRow<<" "<<boardCol * 3 + cellCol;
        // Check if the clicked cell is empty
        if (boardState[boardRow * 3 + cellRow][boardCol * 3 + cellCol] == 0) {
            //Check if the clicked cell is on the correct board
            if((nextBoardRow==boardRow||nextBoardRow==-1)&&(nextBoardCol==boardCol||nextBoardCol==-1)){
                //Check if the board is won
                if (checkBoardWon(boardRow, boardCol)!=0) {
                    // board is won by the player who just made a move
                    nextBoardRow = -1;
                    nextBoardCol = -1;
                } else {
                    // Set the value in the boardState array
                    boardState[boardRow * 3 + cellRow][boardCol * 3 + cellCol] = playerTurnX ? 1 : 2;
                    // Switch the turn to the other player
                    playerTurnX = !playerTurnX;
                    //set next board to play on
                    nextBoardRow=cellRow;
                    nextBoardCol=cellCol;
                    //checks if the game is finished
                    winner=checkGameWon();
                    switch(winner){
                        case 0:
                            glutSetWindowTitle("Tie!");
                            break;
                        case 1:
                            glutSetWindowTitle("X Wins!");
                            break;
                        case 2:
                            glutSetWindowTitle("O Wins!");
                            break;
                    }
                    // board is won by the player who just made a move
                    if (checkBoardWon(nextBoardRow, nextBoardCol)!=0) {
                        
                        nextBoardRow = -1;
                        nextBoardCol = -1;
                    }
                }
            }
        }
        glutPostRedisplay();
    }
};
