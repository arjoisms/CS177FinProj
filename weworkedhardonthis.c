#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <gl/glut.h>

#define GAP  50
 
int window_x;
int window_y;

int window_width = 700;
int window_height = 700;

char *window_title = "Freaking Awesome Project";

int main_window, subwindow_1;

int leftButton = 0;
int middleButton = 0;
int rightButton = 0;

float translate_x = 0.0f, translate_y = 0.0f, translate_z = 0.0f;
float rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
float scale_x = 1.0f, scale_y = 1.0f, scale_z = 1.0f;
float previousX = 0.0f, previousY = 0.0f, previousZ = 0.0f;

double eyeX = 0, eyeY = 0, eyeZ = 0;
double centerX = 0, centerY = 0, centerZ = 0;
double upX = 0, upY = 1, upZ = 0;

float subwindow1_x;
float subwindow1_y;
float subwindow1_w = 800;
float subwindow1_h = 800;

void main_display (void);
void main_reshape (int w, int h);
void keyboard (unsigned char key, int x, int y);

void display_1 (void);
void display (int id);
void redisplayAll ();
void mouse (int, int, int, int);
void motion (int, int);

void init ();

void centerOnScreen ();
void drawObject ();

void reset()
{
    translate_x = translate_y = translate_z = 0.0f;
    rot_x = rot_y = rot_z = 0.0f;
    scale_x = scale_y = scale_z = 1.0f;
    previousX = previousY = previousZ = 0;
    redisplayAll();
}

void main_display (void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void main_reshape (int w, int h)
{
    //  Disallow window re-sizing
    glutReshapeWindow (window_width, window_height);
}

void keyboard (unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'r':
        reset();
        break;
    }
}

void redisplayAll ()
{
    glutSetWindow (subwindow_1);
    glutPostRedisplay ();
}

void display (int id)
{
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear (GL_COLOR_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glOrtho(-1, 1, -1, 1, -2, 2);

    glMatrixMode (GL_MODELVIEW);
    gluLookAt (eyeX, eyeY, eyeZ,
        centerX, centerY, centerZ,
        upX, upY, upZ);

    glTranslatef (translate_x, translate_y, translate_z);

    glRotatef (rot_x, 1.0f, 0.0f, 0.0f);
    glRotatef (rot_y, 0.0f, 1.0f, 0.0f);
    glRotatef (rot_z, 0.0f, 0.0f, 1.0f);

    glScalef (scale_x, scale_y, scale_z);

    drawObject ();

    glLoadIdentity ();

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glutSwapBuffers ();
}

void display1 (void)
{
    glColor3f (1, 1, 0);
    eyeX = 0;
    eyeY = 0;
    eyeZ = 1;
    upX = 0;
    upY = 1;
    upZ = 0;
    display (1);
}


void drawObject ()
{
    glutWireTeapot (0.5);
}

void mouse (int button, int state, int x, int y) 
{	
    if (button == GLUT_LEFT_BUTTON) 
    {
        leftButton = state == GLUT_DOWN;
    } 
    else if (button == GLUT_MIDDLE_BUTTON) 
    {
        middleButton = state == GLUT_DOWN;
    } 
    else if (button == GLUT_RIGHT_BUTTON) 
    {
        rightButton = state == GLUT_DOWN;
    }

    previousX = x;
    previousY = y;
    previousZ = y;
}

void motion (int x, int y) 
{
    if (rightButton) 
    {
        translate_x += (x - previousX) * 0.005;
        translate_y -= (y - previousY) * 0.005;
    }

    if (middleButton) 
    {
        scale_x -= (y - previousZ) * 0.005;
        scale_y -= (y - previousZ) * 0.005;
        scale_z -= (y - previousZ) * 0.005;
    }

    if (leftButton) 
    {
        if ((y - previousY) >= 0)
            rot_x += (y - previousY);
        else 
            rot_x += (y - previousY);
        if ((x - previousX) >= 0)
            rot_y += (x - previousX);
        else
            rot_y += (x - previousX);
    }	

    previousX = (float)x;
    previousY = (float)y;
    previousZ = (float)y;

    redisplayAll ();
}

void centerOnScreen ()
{
    window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
    window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;
}

void main (int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize (window_width, window_height);

	centerOnScreen ();

    glutInitWindowPosition (window_x, window_y);

    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);

    main_window = glutCreateWindow (window_title);

    glutDisplayFunc (main_display);
    glutReshapeFunc  (main_reshape);
    glutKeyboardFunc (keyboard);

    subwindow_1 = glutCreateSubWindow (main_window, GAP, GAP, 600, 600);
    glutDisplayFunc (display1);
    glutMouseFunc (mouse);
    glutMotionFunc (motion);
    glutKeyboardFunc (keyboard);

    glutMainLoop();
}