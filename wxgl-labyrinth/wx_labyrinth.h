#ifndef _WX_LABYRINTH_H_
#define _WX_LABYRINTH_H_

#include "wx/glcanvas.h"

#include <gl/glu.h>
#include <cmath>
#include <iostream>
#include <string>
#include <stack>

// TODO Globals are evil
const GLint Row = 50,Column = 60;
char NorthWall[Row][Column],LeftWall[Row][Column],Virgin[Row][Column];

struct GLintPoint {GLint x,y;};
struct ExGrid {GLint i,j,To;};

// the rendering context used by all GL canvases
class LabyrinthGLContext : public wxGLContext
{
public:
    LabyrinthGLContext(wxGLCanvas *canvas);

    void SetCurrent(const wxGLCanvas & canvas)
    {
        wxGLContext::SetCurrent(canvas);

        m_canvas = const_cast<wxGLCanvas *>(&canvas);
    }

private:

    wxGLCanvas * m_canvas;

private:

    ExGrid Rat;
    std::stack<ExGrid> Unvisited;

    enum {Top,Bottom,Left,Right};

    GLint m_width, m_height;

    GLdouble m_length;

public:

    void StepDraw()
    {
        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        if(!DesignLabyrinth()) return;
        DrawLabyrinth();
        glFlush();
        m_canvas->SwapBuffers();
    }

    void DynamicDraw()
    {
        while(true)
        {
            glClearColor(1.0,1.0,1.0,1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            if(!DesignLabyrinth())
                return;
            else
            {
                DrawLabyrinth();
                glFlush();
                m_canvas->SwapBuffers();
            }
        }
    }

    void DrawScene(void)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Rat.i = random((Row - 1) + 1);
        Rat.j = random(Column - 1);
        m_length = std::min((m_width - 40.0) / (Column - 1.0),(m_height - 40.0) / (Row - 1.0));

        InitLabyrinth();
        DrawLabyrinth();
        glFlush();

        m_canvas->SwapBuffers();
    }

    void RedrawScene(int width,int height)
    {
        m_width = width;
        m_height = height;

        glClearColor(1.0,1.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        //gluOrtho2D(0.0,m_width,0.0,m_height);

        glViewport(0, 0, m_width, m_height);

        DrawLabyrinth();
        glFlush();
        m_canvas->SwapBuffers();
    }

    void SetSize(const wxSize & size)
    {
        m_width = size.GetWidth();
        m_height = size.GetHeight();
    }

private:

    inline int random(int m) {return rand() % m;}
    void drawDot(GLint x,GLint y)
    {
        glPointSize(5.0);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
    }

    void MyInit(void)
    {
        glClearColor(1.0,1.0,1.0,0.0); //Background Color : White
        glColor3f(0.0f,0.0f,0.0f);  //Foreground Color : Black
        glPointSize(1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//        gluOrtho2D(0.0,m_width,0.0,m_height);
        gluOrtho2D(m_width,0.0,m_height,0.0);
    }

    void InitLabyrinth(void)
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

    void DrawLabyrinth(void)
    {
        //m_length =std::min((m_width - 40.0) / (Column - 1.0),(m_height - 40.0) / (Row - 1.0));

        glBegin(GL_LINES);
            for(int i = 0; i < Row; i++)
            {
                for(int j = 0; j < Column; j++)
                {
                    if(NorthWall[i][j] == 1)
                    {
                        glVertex2d(20 + m_length * j,20 + m_length * i);
                        glVertex2d(20 + m_length * j + m_length,20 + m_length * i);
                    }
                    if(LeftWall[i][j] == 1)
                    {
                        glVertex2d(20 + m_length * j,20 + m_length * i);
                        glVertex2d(20 + m_length * j,20 + m_length * i - m_length);
                    }
                }
            }
        glEnd();
        drawDot(20 + (GLint)(m_length * (Rat.j + 0.5)),(GLint)(20 + m_length * (Rat.i - 0.5)));
    }

    bool DesignLabyrinth(void)
    {
        bool isVirgin[4];
        int cnt;


        cnt = 0;
        Rat.To = 4;

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

        DrawLabyrinth();
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

};

// Define a new application type
class LabyrinthApp : public wxApp
{
public:
    LabyrinthApp() { m_glContext = NULL; }

    // Returns the shared context used by all frames and sets it as current for
    // the given canvas.
    LabyrinthGLContext& GetContext(wxGLCanvas *canvas);

    // virtual wxApp methods
    virtual bool OnInit();
    virtual int OnExit();

private:
    // the GL context we use for all our windows
    LabyrinthGLContext *m_glContext;
};

// Define a new frame type
class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void OnClose(wxCommandEvent& event);
    void OnNewWindow(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

class MainGLCanvas : public wxGLCanvas
{
public:
    MainGLCanvas(wxWindow *parent);

private:
    void OnPaint(wxPaintEvent& event);
    void OnKeyDown(wxKeyEvent& event);
//    void OnSize(wxSizeEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif // _WX_LABYRINTH_H_
