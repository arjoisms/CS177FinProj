#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#define OVALID      1
#define SPHEREID    2
#define BOXID       3
#define PLANEID     4
#define TEXTID      5
#define GAP  50
#define TRUE  1
#define FALSE 0
#define PI 3.141592653589793238462643

int window_x;
int window_y;

int window_width = 700;
int window_height = 700;

char *window_title = "Freaking Awesome Project";

int main_window, subwindow_1;

int leftButton = 0;
int middleButton = 0;
int rightButton = 0;

#define DRAFT  0
#define MEDIUM 1
#define BEST   2
int drawquality = DRAFT;

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
      int i;
   double radius = 1.0;
   static double theta = 0;
   GLfloat mshin1[] = {5.0};               /* For the sphere */
   GLfloat mspec1[] = {0.5,0.5,0.5,1.0};
   GLfloat mdiff1[] = {0.6,0.0,0.6,1.0};
   GLfloat mamb1[]  = {0.1,0.0,0.1,1.0};
   GLfloat mdiff2[] = {0.0,1.0,0.0,1.0};   /* Green plane */
   GLfloat mamb2[]  = {0.0,0.2,0.0,1.0};
   GLfloat mdiff3[] = {0.5,0.5,0.5,1.0};  /* Grey boxes */
   GLfloat mamb3[]  = {0.2,0.2,0.2,1.0};

   /* Create a green ground plane */
   glLoadName(PLANEID);
   if (drawquality > DRAFT)
      glBegin(GL_POLYGON);
   else
      glBegin(GL_LINE_LOOP);
   glColor3f(0.0,1.0,1.0);
   if (drawquality > DRAFT) {
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mdiff2);
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mamb2);
   }
   glNormal3f( 0.0, 1.0, 0.0);
   glVertex3f( 5.0, 0.0, 5.0);
   glVertex3f( 5.0, 0.0,-5.0);
   glVertex3f(-5.0, 0.0,-5.0);
   glVertex3f(-5.0, 0.0, 5.0); 
   glEnd();

   /* Place a few yellow boxes around the place */
   glLoadName(BOXID);
   glColor3f(1.0,1.0,0.0);
   if (drawquality > DRAFT) {
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mdiff3);
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mamb3);
   }
   glPushMatrix();
   glTranslatef(5,0.1,5.0);
   if (drawquality > DRAFT)
      glutWireCube(0.2);
   else
      glutSolidCube(0.2);
   glColor3f(1.0,0.0,0.0);
   glTranslatef(0.0,0.2,0.0);
   if (drawquality > DRAFT)
      glutWireCube(0.2);
   else
      glutSolidCube(0.2);
   glTranslatef(0.0,0.2,0.0);
   glColor3f(1.0,1.0,0.0);
   if (drawquality > DRAFT)
      glutWireCube(0.2);
   else
      glutSolidCube(0.2);
   glPopMatrix();

   /* Create a magenta bouncing ball */
   /*
   glLoadName(SPHEREID);
   glColor3f(0.0,0.0,0.0);
   if (drawquality > DRAFT) {
      glMaterialfv(GL_FRONT,GL_SHININESS,mshin1);
      glMaterialfv(GL_FRONT,GL_SPECULAR,mspec1);
   }
   glPushMatrix();
   glTranslatef(0.0,radius+0.5*(1+sin(PI*theta/180)),0.0);
   glScalef(radius,radius,radius);
   if (ballbounce)
      theta += ballspeed;
   if (drawquality > DRAFT)
      glutSolidSphere(1.0,16,16);
   else
      glutWireSphere(1.0,32,32);
   glPopMatrix();
   */
   /* Create a yellow half-oval loop at one end */
   glLoadName(OVALID);
   glBegin(GL_LINE_STRIP);
   glColor3f(1.0,1.0,0.0);
   glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
   for (i=0;i<=180;i++)
      glVertex3f(2*cos(i*PI/180),1.5*sin(i*PI/180),-2.0);
   glEnd();

   /* Write some text */
   //glLoadName(TEXTID);
   //DrawTextXY(-2.0,-0.25,2.0,0.002,"Arjo + Frank = Pogi");
}

void DrawTextXY(double x,double y,double z,double scale,char *s)
{
   int i;

   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(scale,scale,scale);
   for (i=0;i<strlen(s);i++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
   glPopMatrix();
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