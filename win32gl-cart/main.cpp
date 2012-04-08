#include <windows.h>
#include <gl/gl.h>
//#include <gl/glu.h>
#include <cmath>
#include <iostream>
#include <iomanip> 
#include <string>
#include <sstream>

using namespace std;

//stringstream iostr; 
//string tmp; 

const float origin_position_z = -4.5;
float position = fabs(origin_position_z);
float position_x = 0,position_y = 0,position_z = origin_position_z;

float velocity = 0;
float velocity_x = 0,velocity_y = 0,velocity_z = 0;

float theta_y = 0,theta_x = 0,theta_z = 0;
float beta_z = 0.0f,omiga_z = -1.0f;

float delta = 0.01;

bool Ldown = false;
bool Rdown = false;
POINT RatPt;

bool AltLight = false;
int AltMode = 0;
int AltColor = 0;


int meWndWidth = 1024,meWndHeight = 768;

enum {Circle = 1,Cube,Quad,CoordArr,Sphere};



float m_lightAmb[4] = {0.2,0.4,0.6,1.0};
float m_lightDif[4] = {0.8,0.9,0.5,1.0};
float m_lightSpe[4] = {1.0,0.8,1.0,1.0};
float m_lightPos[4] = {5.0,0.0,5.0,1.0};
float * m_light[4] = {m_lightAmb,m_lightDif,m_lightSpe,m_lightPos};
float m_materialAmb[4] = {0.2,0.6,0,1.0};
float m_materialDif[4] = {0.8,0.2,1.0,1.0};
float m_materialSpe[4] = {1.0,1.0,1.0,1.0};
float m_matShininess = 10.0f;
float * m_material[4] = {m_materialAmb,m_materialDif,m_materialSpe,m_lightPos};


inline float PositionCalc()
{
    return sqrt(position_x*position_x+position_y*position_y+(position_z - origin_position_z)*(position_z - origin_position_z));

}

inline float VelocityCalc()
{
    return sqrt(velocity_x*velocity_x+velocity_y*velocity_y+velocity_z*velocity_z);

}

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

void CreateLights()
{
    glLightfv(GL_LIGHT0,GL_AMBIENT,m_lightAmb);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,m_lightDif);
    glLightfv(GL_LIGHT0,GL_SPECULAR,m_lightSpe);
    glLightfv(GL_LIGHT0,GL_POSITION,m_lightPos);
    //glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,50.0f);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void CreateMaterial()
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,m_materialAmb);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,m_materialDif);
    glMaterialfv(GL_FRONT,GL_SPECULAR,m_materialSpe);
    glMaterialf(GL_FRONT,GL_SHININESS,m_matShininess);
}


void DefineLists()
{
    
    GLint i,j,k;
    GLdouble s,t,x,y,z,twopi;
    GLdouble PI = 3.141592653589793238462643383279;
    twopi = 2 * PI;
    GLdouble scale = 0.5;
    
    //Circle
    glNewList(Circle,GL_COMPILE);
    
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
    
    for(i = 0;i < 64;i++)
    {
        glBegin(GL_QUAD_STRIP);
            for(j = 0;j <= 64;j++)
            {
                for(k = 1;k >= 0;k--)
                {
                    s = (i + k) % 64 + 0.5;
                    t = j % 64;
                    
                    x = (1 + 0.1 * cos(s * twopi /64)) * cos(t * twopi /64) * scale;
                    y = (1 + 0.1 * cos(s * twopi /64)) * sin(t * twopi /64) * scale;
                    z = 0.1 * sin(s * twopi / 64) * scale;
                    
                    glColor3f(x / scale,y / scale,z / scale);
                    
                    glVertex3f(x,y,z);
                }
            }
        glEnd();
    }
    
    glEndList();
    
    //Cube
    const float Cube_Length = 0.5f;
    glNewList(Cube,GL_COMPILE);
    //CreateMaterial();
        //Front
        glBegin(GL_QUADS);
            glColor3f(1.0f,0.0f,0.0f);
            glNormal3f(0.0f,0.0f,1.0f);
            glVertex3f(-Cube_Length,Cube_Length,Cube_Length);
            glVertex3f(-Cube_Length,-Cube_Length,Cube_Length);
            glVertex3f(Cube_Length,-Cube_Length,Cube_Length);
            glVertex3f(Cube_Length,Cube_Length,Cube_Length);
            
        glEnd();
        //Back
        glBegin(GL_QUADS);
            glColor3f(0.0f,1.0f,0.0f);
            glNormal3f(0.0f,0.0f,-1.0f);
            glVertex3f(-Cube_Length,Cube_Length,-Cube_Length);
            glVertex3f(Cube_Length,Cube_Length,-Cube_Length);
            glVertex3f(Cube_Length,-Cube_Length,-Cube_Length);
            glVertex3f(-Cube_Length,-Cube_Length,-Cube_Length);
        glEnd();
        //Left
        glBegin(GL_QUADS);
            glColor3f(0.0f,0.0f,1.0f);
            glNormal3f(-1.0f,0.0f,0.0f);
            glVertex3f(-Cube_Length,-Cube_Length,Cube_Length);
            glVertex3f(-Cube_Length,Cube_Length,Cube_Length);
            glVertex3f(-Cube_Length,Cube_Length,-Cube_Length);
            glVertex3f(-Cube_Length,-Cube_Length,-Cube_Length);
        glEnd();
        
        ///*
        //Right
        glBegin(GL_QUADS);
            glColor3f(1.0f,1.0f,0.0f);
            glNormal3f(1.0f,0.0f,0.0f);
            glVertex3f(Cube_Length,-Cube_Length,Cube_Length);
            glVertex3f(Cube_Length,-Cube_Length,-Cube_Length);
            glVertex3f(Cube_Length,Cube_Length,-Cube_Length);
            glVertex3f(Cube_Length,Cube_Length,Cube_Length);
        glEnd();
        //*/
        
        //Bottom
        glBegin(GL_QUADS);
            glColor3f(1.0f,0.0f,1.0f);
            glNormal3f(0.0f,-1.0f,1.0f);
            glVertex3f(-Cube_Length,-Cube_Length,Cube_Length);
            glVertex3f(Cube_Length,-Cube_Length,Cube_Length);
            glVertex3f(Cube_Length,-Cube_Length,-Cube_Length);
            glVertex3f(-Cube_Length,-Cube_Length,-Cube_Length);
        glEnd();
        //Top
        glBegin(GL_QUADS);
            glColor3f(0.0f,1.0f,1.0f);
            glNormal3f(0.0f,1.0f,0.0f);
            glVertex3f(-Cube_Length,Cube_Length,Cube_Length);
            glVertex3f(Cube_Length,Cube_Length,Cube_Length);
            glVertex3f(Cube_Length,Cube_Length,-Cube_Length);
            glVertex3f(-Cube_Length,Cube_Length,-Cube_Length);
        glEnd();
    glEndList();
    
    //Quad
    glNewList(Quad,GL_COMPILE);

    
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);    
    
    glBegin(GL_QUADS);
                
        glColor3f (1.0f, 0.0f, 0.0f);
        glNormal3f(0.0f,0.0f,1.0f);
        glVertex3f (-0.3f,0.3f,0.0f);
        glColor3f (0.0f, 1.0f, 0.0f);
        glVertex3f (-0.3f,-0.3f,0.0f);
        glColor3f (0.0f, 0.0f, 1.0f);
        glVertex3f (0.3f,-0.3f,0.0f);
        glColor3f (1.0f, 1.0f, 1.0f);
        glVertex3f (0.3f,0.3f,0.0f);
                    
    glEnd();
    
    //glEnable(GL_LINE_SMOOTH);
    //glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
                
    glBegin(GL_LINES);
        glColor3f (0.0f, 0.0f, 0.0f);
        glVertex3f (-0.3f,0.3f,0.0f);
        glVertex3f (0.3f,-0.3f,0.0f);
        glVertex3f (-0.3f,-0.3f,0.0f);
        glVertex3f (0.3f,0.3f,0.0f);
        
                    
                    
    glEnd();
    glEndList();
    
    glNewList(CoordArr,GL_COMPILE);
    
    glBegin(GL_LINES);
        glColor3f (0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(3.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,3.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,3.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex4fv(m_lightPos);
    glEnd();
    glEndList();
    
    glNewList(Sphere,GL_COMPILE);
    {
        double x,y,z;
        const double R = 3.0;
        glBegin(GL_QUAD_STRIP);
        for(x = - R; x <= R; x += 0.1)
        {
            for(y = -R; y <= R; y += 0.1)
                {
                    z = sqrt(R * R - x * x -y * y);
                    glColor3d(x,y,z);
                    glNormal3d(x / R,y / R,z / R);
                    glVertex3d(x,y,z);

                }
        }
        glEnd();
        
    }
        
    glEndList();
    
}




/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_HAND);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);
    
    DEVMODE DevMode;
    EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&DevMode);
    DevMode.dmPelsWidth = meWndWidth;
    DevMode.dmPelsHeight = meWndHeight;
    ChangeDisplaySettings(&DevMode,CDS_FULLSCREEN);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "Win32 OpenGL Cart", 
      //WS_CAPTION | 
      WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, meWndWidth, meWndHeight,
      NULL, NULL, hInstance, NULL);
      
    SetTimer(hWnd,1,7,NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
    
    DefineLists();
    

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
            if (msg.message == WM_LBUTTONDOWN)
            {
                Ldown = true;
            }
            if (msg.message == WM_LBUTTONUP)
            {
                Ldown = false;
            }
            if (msg.message == WM_RBUTTONDOWN)
            {
                Rdown = true;
            }
            if (msg.message == WM_RBUTTONUP)
            {
                Rdown = false;
            }
            if (msg.message == WM_MOUSEMOVE)
            {
                RatPt = msg.pt;
                ScreenToClient(hWnd,&RatPt);
            }
            
        }
        else
        {
            if(Ldown && !Rdown)
            {
                position_x = RatPt.x / (meWndWidth + 0.0) * 2.0 -1.0;
                position_y = - RatPt.y / (meWndHeight + 0.0) * 2.0 +1.0;
                position_z = origin_position_z;
                velocity_x = 0;
                velocity_y = 0;
                velocity_z = 0;
                //ostringstream iostr;
                //iostr << msg.pt.x << "," << msg.pt.y;
                //MessageBox(hWnd,iostr.str().c_str(),"CurrentPosition",MB_OK); 
            }
            if(Rdown && !Ldown)
            {
                float _x = RatPt.x / (meWndWidth + 0.0) * 2.0 -1.0;
                float _y = - RatPt.y / (meWndHeight + 0.0) * 2.0 +1.0;
                theta_y = _x * 360;
                theta_x = _y * 360;
                position_x = 0;
                position_y = 0;
                position_z = origin_position_z;
                velocity_x = 0;
                velocity_y = 0;
                velocity_z = 0;
                //ostringstream iostr;
                //iostr << msg.pt.x << "," << msg.pt.y;
                //MessageBox(hWnd,iostr.str().c_str(),"CurrentPosition",MB_OK); 
            }
            if(!Rdown && !Ldown)
            {
                float _x = RatPt.x / (meWndWidth + 0.0) * 2.0 - 1.0;
                float _y = - RatPt.y / (meWndHeight + 0.0) * 2.0 + 1.0;
                theta_y = _x * 360;
                theta_x = _y * 360;

                //ostringstream iostr;
                //iostr << msg.pt.x << "," << msg.pt.y;
                //MessageBox(hWnd,iostr.str().c_str(),"CurrentPosition",MB_OK); 
            }
            
            
            /* OpenGL animation code goes here */

            //Init
            glClearColor (0.0f,0.0f,0.0f, 1.0f);
            glClear (GL_COLOR_BUFFER_BIT);
            glClearDepth(1.0f);
            glClear (GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_AUTO_NORMAL);
            glEnable(GL_NORMALIZE);
            //Anti-alias
            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
            
            
            
            //fill
            glPolygonMode(GL_FRONT,GL_FILL);

            //MatrixMode
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            //CreateLights();
            glFrustum(-1.0,1.0,-1.0,1.0,3.0,50.0);
            glViewport(0,-(meWndWidth - meWndHeight) / 2,meWndWidth,meWndWidth);
            
            glShadeModel(GL_SMOOTH);

            glPushMatrix ();
            
                glColor3f (1.0f, 0.0f, 0.0f);
                
                /*glBegin(GL_LINES);
                    glColor3f(1.0,0.0,0.0);
                    glVertex3f(0.0,0.0,0.0);
                    glVertex4fv(m_lightPos);
                glEnd();*/
                
                glTranslatef(position_x,position_y,position_z);
                glRotatef(theta_x,1.0f,0.0f,0.0f);
                glRotatef(theta_y,0.0f,1.0f,0.0f);
                glRotatef(90.0f,0.0f,1.0f,0.0f);
                //glCallList(CoordArr);
                //CreateLights();
                glScalef(2.0f,1.0f,1.0f);
                glCallList(Cube);

                CreateMaterial();
                //glutSolidSphere(0.5,25,25);
                glScalef(0.5f,1.0f,1.0f);
                
                

                glPushMatrix();
                    
                    glTranslatef(0.5f,-0.5f,0.55f);
                    glRotatef(theta_z,0.0f,0.0f,1.0f);
                    glScalef(0.5f,0.5f,0.5f);
                    glCallList(Circle);
                    
                glPopMatrix();
                
                glPushMatrix();
                    
                    glTranslatef(-0.5f,-0.5f,0.55f);
                    glRotatef(theta_z,0.0f,0.0f,1.0f);
                    glScalef(0.5f,0.5f,0.5f);
                    glCallList(Quad);
                    
                glPopMatrix();
                
                glPushMatrix();
                    
                    glTranslatef(0.5f,-0.5f,-0.55f);
                    glRotatef(theta_z,0.0f,0.0f,1.0f);
                    glScalef(0.5f,0.5f,0.5f);
                    glCallList(Circle);
                    
                glPopMatrix();
                
                glPushMatrix();
                
                    glTranslatef(-0.5f,-0.5f,-0.55f);
                    glRotatef(theta_z,0.0f,0.0f,1.0f);
                    glScalef(0.5f,0.5f,0.5f);
                    glCallList(Circle);
                    
                glPopMatrix();                                                                

                
                
                
            glPopMatrix ();
            glFinish();

            SwapBuffers (hDC);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);
    
    KillTimer(hWnd,1);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;
        
    case WM_TIMER:
                    
        position_x += velocity_x;
        position_y += velocity_y;
        position_z += velocity_z;
        theta_z += omiga_z;
        omiga_z += beta_z;
        return 0;
        
    case WM_MOUSEWHEEL:
        {
            WORD fwKeys = LOWORD(wParam);    // key flags
            short zDelta = (short) HIWORD(wParam);    // wheel rotation
            //xPos = (short) LOWORD(lParam);    // horizontal position of pointer
            //yPos = (short) HIWORD(lParam);    // vertical position of pointer
            if(zDelta > 0)
            {
                switch(fwKeys)
                {
                    case MK_SHIFT:
                        if(AltLight)
                            m_light[AltMode][AltColor] += 0.2;
                        else
                            m_material[AltMode][AltColor] += 0.2;
                        return 0;
                    default:
                        velocity_z -= delta;
                        return 0;  
                }
          
            }
            else
            {
                switch(fwKeys)
                {
                    case MK_SHIFT:
                        if(AltLight)
                            m_light[AltMode][AltColor] -= 0.2;
                        else
                            m_material[AltMode][AltColor] -= 0.2;
                        return 0;
                    default:
                        velocity_z += delta;
                        return 0;  
                }
            }
        }

        /*iostr << lParam; 
        iostr >> tmp; 
        MessageBox(hWnd,tmp.c_str(),"Wheel!",MB_OK);
        iostr.setstate(ios::badbit);
        iostr.sync(); 
        iostr.flush();
        iostr.clear(); */
        return 0;
        

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        case VK_UP:
            velocity_y += delta;
            return 0;
        case VK_DOWN:
            velocity_y -= delta;
            return 0;
        case VK_LEFT:
            velocity_x -= delta;
            return 0;
        case VK_RIGHT:
            velocity_x += delta;
            return 0;
        case 'W':
            velocity_z -= delta;
            return 0;
        case 'S':
            velocity_z += delta;
            return 0;
        case 'A':
            velocity_x -= delta;
            return 0;
        case 'D':
            velocity_x += delta;
            return 0;
        case 'R':
            AltColor = 0;
            return 0;
        case 'G':
            AltColor = 1;          
            return 0;
        case 'B':
            AltColor = 2;
            return 0;
        case 'M':
            if(AltMode == 3) {AltMode = 0;return 0;}
            AltMode++;
            return 0;
        case 'L':
            AltLight = !AltLight;
            return 0;
        case VK_SPACE:
            /*position_x = 0;
            position_y = 0;
            position_z = origin_position_z;*/
            velocity_x = 0;
            velocity_y = 0;
            velocity_z = 0;
            /*theta_x = 0;
            theta_y = 0;*/
            return 0;
        case VK_CONTROL:
            position = PositionCalc();
            velocity = VelocityCalc();
            velocity_x = -position_x / position * velocity;
            velocity_y = -position_y / position* velocity;
            velocity_z = -(position_z - origin_position_z) / position * velocity;
            return 0; 
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
