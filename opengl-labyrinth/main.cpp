
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "gl/glut.h"
#include <cmath>
#include <iostream>
#include <string>
#include <stack>


GLint ScreenWidth = 800,ScreenHeight = 600;
const GLint Row = 50,Column = 60;
char NorthWall[Row][Column],LeftWall[Row][Column],Virgin[Row][Column];

void DrawScene(void);
void RedrawScene(int width,int height);
void MyMouse(int button,int state,int x,int y);
void MyKeyBoard(unsigned char key,int x,int y);
void MyInit(void);

struct GLintPoint {GLint x,y;};
struct ExGrid {GLint i,j,To;};

ExGrid Rat;
std::stack<ExGrid> Unvisited;

bool isVirgin[4];
enum {Top,Bottom,Left,Right};
int cnt;


inline int random(int m) {return rand() % m;}
void drawDot(GLint x,GLint y);

void InitMyth(void);
bool DesignMyth(void);
void DrawMyth(void);
void GridPush(void);
void BreakWall(void);
void MoveGrid(void);



int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(ScreenWidth,ScreenHeight);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Labyrinth");

    glutDisplayFunc(DrawScene);
    glutReshapeFunc(RedrawScene);
    glutMouseFunc(MyMouse);
    glutKeyboardFunc(MyKeyBoard);

    MyInit();
    glutMainLoop();
    return 0;
}

void MyInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); //Background Color : White
    glColor3f(0.0f,0.0f,0.0f);  //Foreground Color : Black
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,ScreenWidth,0.0,ScreenHeight);
}

void drawDot(GLint x,GLint y)
{
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void MyMouse(int button,int state,int x,int y)
{
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        Rat.i = y % (Row - 1) + 1;
        Rat.j = x % (Column - 1);
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        InitMyth();
        DrawMyth();
        glFlush();
        glutSwapBuffers();
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
    while(true)
    {
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        if(!DesignMyth())
            return;
        else
        {
            DrawMyth();
            glFlush();
            glutSwapBuffers();
        }
    }
    }
}

void MyKeyBoard(unsigned char key,int x,int y)
{
    if(key == ' ')
    {
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        if(!DesignMyth()) return;
        DrawMyth();
        glFlush();
        glutSwapBuffers();
    }
}

void DrawScene(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Rat.i = random((Row - 1) + 1);
    Rat.j = random(Column - 1);
    InitMyth();
    DrawMyth();
    glFlush();
    glutSwapBuffers();
}


void RedrawScene(int width,int height)
{

    ScreenWidth = width;
    ScreenHeight= height;

    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawMyth();
    glFlush();
    glutSwapBuffers();
}

void InitMyth(void)
{
    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Column; j++)
        {
            NorthWall[i][j] = (j==Column-1)?0:1;
            LeftWall[i][j] = (i==0)?0:1;
            Virgin[i][j] = (j==Column-1||i==0)?0:1;
        }
    }
}

void DrawMyth(void)
{
    GLdouble Length =std::min((ScreenWidth - 40.0) / (Column - 1.0),(ScreenHeight - 40.0) / (Row - 1.0));

    glBegin(GL_LINES);
        for(int i = 0; i < Row; i++)
        {
            for(int j = 0; j < Column; j++)
            {
                if(NorthWall[i][j] == 1)
                {
                    glVertex2d(20 + Length * j,20 + Length * i);
                    glVertex2d(20 + Length * j + Length,20 + Length * i);
                }
                if(LeftWall[i][j] == 1)
                {
                    glVertex2d(20 + Length * j,20 + Length * i);
                    glVertex2d(20 + Length * j,20 + Length * i - Length);
                }
            }
        }
    glEnd();
    drawDot(20 + (GLint)(Length * (Rat.j + 0.5)),(GLint)(20 + Length * (Rat.i - 0.5)));
}

bool DesignMyth(void)
{


     cnt = 0;
     Rat.To = 4;
     int n;

    Virgin[Rat.i][Rat.j] = 0;
    isVirgin[Top] = isVirgin[Bottom] = isVirgin[Left] = isVirgin[Right] = false;

    if(Rat.i < Row - 1)
        if(Virgin[Rat.i + 1][Rat.j] == 1) isVirgin[Top] = true;
    if(Rat.i > 1)
        if(Virgin[Rat.i - 1][Rat.j] == 1) isVirgin[Bottom] = true;
    if(Rat.j > 0)
        if(Virgin[Rat.i][Rat.j - 1] == 1) isVirgin[Left] = true;
    if(Rat.j < Column - 2)
        if(Virgin[Rat.i][Rat.j + 1] == 1) isVirgin[Right] = true;


    for(int k = 0; k < 4; k++)
        if(isVirgin[k]) cnt++;


    if(cnt == 0)
    {
        if(Unvisited.empty()) return false;
        else
        {
            Rat.i = Unvisited.top().i;
            Rat.j = Unvisited.top().j;
            BreakWall();
            MoveGrid();
            Unvisited.pop();
            return true;
        }
    }
    else
    {
            do
            {
                Rat.To = random(4);
            }
            while(!isVirgin[Rat.To]);
    }



    for(int m = 0; m < 4; m++)
        if(isVirgin[m] && m != Rat.To) GridPush();

    BreakWall();
    MoveGrid();

    DrawMyth();
    return true;
}

void GridPush(void)
{
    ExGrid tmp;
    tmp.i = Rat.i;
    tmp.j = Rat.j;
    tmp.To = Rat.To;
    Unvisited.push(tmp);

}

void BreakWall(void)
{
    switch(Rat.To)
    {
        case Top:
            NorthWall[Rat.i][Rat.j] = 0;
            break;
        case Bottom:
            NorthWall[Rat.i - 1][Rat.j] = 0;
            break;
        case Left:
            LeftWall[Rat.i][Rat.j] = 0;
            break;
        case Right:
            LeftWall[Rat.i][Rat.j + 1] = 0;
            break;
    }
}

void MoveGrid(void)
{
    switch(Rat.To)
    {
        case Top:
            Rat.i++;
            break;
        case Bottom:
            Rat.i--;
            break;
        case Left:
            Rat.j--;
            break;
        case Right:
            Rat.j++;
            break;
    }
}



