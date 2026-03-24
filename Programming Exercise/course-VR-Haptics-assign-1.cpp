// === Course VR and Haptics (K.Tzafestas) ===
// === Sample Source Code for assignment 1 ===

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// ===== Global Variables Definitions
int mouse_posx, mouse_posy, d_mouse_posx, d_mouse_posy;
int mousebutton_down = 0;
double distance_x, distance_y;

    
// ===== set Viewport (screen window) =====
void setViewport(int left, int right, int bottom, int top)
{
    glViewport(left, bottom, right - left, top - bottom);
}

// ===== Personalized Initialization Procedure =====
void myInit(GLint mywidth, GLint myheight)
{
    glClearColor(1.0,1.0,1.0,0.0);  //set (white) background color
    glColor3f(0.0f, 0.0f, 0.0f);    //set the drawing color

    //set 3D World-Coordinates Window: glOrtho(left,right, bottom,top, near,far)
    GLfloat aspect = (GLfloat)mywidth/(GLfloat)myheight;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0*aspect, 2.0*aspect, -2.0, 2.0, 0.1, 100.0);
    //--------------------------------------------------------------------------

    setViewport(0, mywidth, 0, myheight);   //set viewport window (screen coordinates)
}


// ===== Personalized Display Procedure =====
void myDisplay(void)
{
    //** Set properties of surface material: choose the collor and material properties you like
    //-----------------------------------------------------------------------------------------
    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};   //**==> you can choose the surface properties of your preference
    GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};   // ...
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // ...
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //set light sources
    //-----------------
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f}; //**==> you can choose the light properties of your preference
    GLfloat lightPosition[] = {2.0f, 6.0f, 3.0f, 0.0f};  // ...
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);


    //set the Camera model ==>  animate camera motion --> set 3D World-Coordinates Window
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
     //**==> use command: gluLookAt(eye.x,y,z, look.x,y,z, up.x,y,z);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen


    glPushMatrix();
    
        // animate object motion
        //**==> use functions: glTranslatef(...) or glRotatef(...)
        
        glPushMatrix();
            //**==> Draw Cube... you can use commands: glColor*(...); glBegin(...); ... glNormal*(...); glVertex*(...);  ... glEnd(); etc.
        glPopMatrix();

        glPushMatrix();
            //**==> glTranslated(...);
            //**==> Draw Conical Surface...
        glPopMatrix();

        // similarly draw other 3D geometric objects

    glPopMatrix();


    //glFlush();    //send all output to display (for GLUT_SINGLE)
    glutSwapBuffers(); //for double buffering (GLUT_DOUBLE)

}


void Update()
{
    glutPostRedisplay();
}


//--------------------------------------
//==== Mouse Interaction Procedures ====
//--------------------------------------

void myMouse(int button, int state, int x, int y)
{

   if (state == GLUT_DOWN)
    {
        switch (button)
        {
            case GLUT_LEFT_BUTTON:  
                mousebutton_down = 1;
                break;
            case GLUT_RIGHT_BUTTON:  
                break;
            case GLUT_MIDDLE_BUTTON:  
                break;
        }
        mouse_posx = x;
        mouse_posy = y;
   }
    else
    {
        mousebutton_down = 0;
        d_mouse_posx = 0;
        d_mouse_posy = 0;
    }

}

void myMovedMouse(int mouseX, int mouseY)
{

    d_mouse_posx = mouseX - mouse_posx ;
    d_mouse_posy = -mouseY + mouse_posy ;
    mouse_posx = mouseX;
    mouse_posy = mouseY;

    switch (mousebutton_down)
    {   
        //*===> choose the mouse interaction settings of your preference
        case 1: distance_x += 0.005*d_mouse_posx;
                distance_y += 0.005*d_mouse_posy;
                printf("dx = %f, dy = %f \n", distance_x, distance_y);
                break;
    }
}

//--------------------------------------
//==== Keyboard Interaction Procedures ====
//--------------------------------------
void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
}

//----------------------
//==== Main Program ====
//----------------------
void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH); // DOUBLE BUFFERING and Z-BUFFERING 
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Simple 3D Shaded Scene");
    glutDisplayFunc(myDisplay);
    glutIdleFunc(Update);        // User provided Update function
    glutMouseFunc(myMouse);      // mouse pressed/released
    glutMotionFunc(myMovedMouse);    // mouse moved
    glutKeyboardFunc(myKeyboard);    // key pressed

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    //hidden surface removal
    glEnable(GL_NORMALIZE);     //normalize vectors for proper shading

    myInit(640, 480);
    glutMainLoop();
}
