// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include "wx_labyrinth.h"

// ----------------------------------------------------------------------------
// helper functions
// ----------------------------------------------------------------------------

static void CheckGLError()
{
    GLenum errLast = GL_NO_ERROR;

    for ( ;; )
    {
        GLenum err = glGetError();
        if ( err == GL_NO_ERROR )
            return;

        // normally the error is reset by the call to glGetError() but if
        // glGetError() itself returns an error, we risk looping forever here
        // so check that we get a different error than the last time
        if ( err == errLast )
        {
            wxLogError(_T("OpenGL error state couldn't be reset."));
            return;
        }

        errLast = err;

        wxLogError(_T("OpenGL error %d"), err);
    }
}


// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// LabyrinthGLContext
// ----------------------------------------------------------------------------

LabyrinthGLContext::LabyrinthGLContext(wxGLCanvas *canvas)
             : wxGLContext(canvas)
{
    SetCurrent(*canvas);

    wxRect rect = canvas->GetRect();
    m_width = rect.GetWidth();
    m_height = rect.GetHeight();

    MyInit();

    DrawScene();

    CheckGLError();
}


// ----------------------------------------------------------------------------
// LabyrinthApp: the application object
// ----------------------------------------------------------------------------

IMPLEMENT_APP(LabyrinthApp)

bool LabyrinthApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    new MainFrame();

    return true;
}

int LabyrinthApp::OnExit()
{
    delete m_glContext;

    return wxApp::OnExit();
}

LabyrinthGLContext& LabyrinthApp::GetContext(wxGLCanvas *canvas)
{
    if ( !m_glContext )
    {
        // Create the OpenGL context for the first window which needs it:
        // subsequently created windows will all share the same context.
        m_glContext = new LabyrinthGLContext(canvas);
    }

    m_glContext->SetCurrent(*canvas);

    return *m_glContext;
}

// ----------------------------------------------------------------------------
// MainGLCanvas
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MainGLCanvas, wxGLCanvas)
    EVT_PAINT(MainGLCanvas::OnPaint)
    EVT_KEY_DOWN(MainGLCanvas::OnKeyDown)
//    EVT_SIZE(MainGLCanvas::OnSize)
END_EVENT_TABLE()

MainGLCanvas::MainGLCanvas(wxWindow *parent)
    // With perspective OpenGL graphics, the wxFULL_REPAINT_ON_RESIZE style
    // flag should always be set, because even making the canvas smaller should
    // be followed by a paint event that updates the entire canvas with new
    // viewport settings.
    : wxGLCanvas(parent, wxID_ANY, NULL /* attribs */,
                 wxDefaultPosition, wxDefaultSize,
                 wxFULL_REPAINT_ON_RESIZE)
{
}

void MainGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    // This is required even though dc is not used otherwise.
    wxPaintDC dc(this);

    // Set the OpenGL viewport according to the client size of this canvas.
    // This is done here rather than in a wxSizeEvent handler because our
    // OpenGL rendering context (and thus viewport setting) is used with
    // multiple canvases: If we updated the viewport in the wxSizeEvent
    // handler, changing the size of one canvas causes a viewport setting that
    // is wrong when next another canvas is repainted.
    const wxRect rect = GetRect();

    wxGetApp().GetContext(this).RedrawScene(rect.GetWidth(), rect.GetHeight());

    wxString viewport;
    viewport << _("(") << rect.GetWidth() << _(",") << rect.GetHeight() << _(")");
    wxLogStatus(viewport);
}

void MainGLCanvas::OnKeyDown( wxKeyEvent& event )
{

    switch ( event.GetKeyCode() )
    {
        case WXK_RIGHT:
            wxGetApp().GetContext(this).DrawScene();
            break;
        case WXK_LEFT:
            wxGetApp().GetContext(this).DynamicDraw();
            break;
        case WXK_SPACE:
            wxGetApp().GetContext(this).StepDraw();
            break;
        default:
            event.Skip();
            return;
    }
}

// ----------------------------------------------------------------------------
// MainFrame: main application window
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_NEW, MainFrame::OnNewWindow)
    EVT_MENU(wxID_CLOSE, MainFrame::OnClose)
END_EVENT_TABLE()

MainFrame::MainFrame()
       : wxFrame(NULL, wxID_ANY, _T("wxLabyrinth"))
{
    new MainGLCanvas(this);

    SetIcon(wxICON(sample));

    // Make a menubar
    wxMenu *menu = new wxMenu;
    menu->Append(wxID_NEW);
    menu->AppendSeparator();
    menu->Append(wxID_CLOSE);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, _T("&Labyrinth"));

    SetMenuBar(menuBar);

    CreateStatusBar();

    SetClientSize(400, 400);
    Show();

    // test IsDisplaySupported() function:
//    static const int attribs[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, 0 };
//    wxLogStatus("Double-buffered display %s supported",
//                wxGLCanvas::IsDisplaySupported(attribs) ? "is" : "not");
}

void MainFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MainFrame::OnNewWindow( wxCommandEvent& WXUNUSED(event) )
{
    new MainFrame();
}

