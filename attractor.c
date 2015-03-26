#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th = 120;
int ph = -30;
double w = 1;

double a = 10.0;
double b = 28.0;
double c = 2.6666;

int N = 50000;
double pa[50000][3];
double color[50000][3];

#define LEN 8192

void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}


void lorenz(void) 
	{
	int i;
	double x = 1;
	double y = 1;
	double z = 1;
	double w = 1;

pa[0][0] = x;
pa[0][1] = y;
pa[0][2] = z;
pa[0][3] = w;

	double dt = 0.001;
	
	for (i=0;i<N;i++)
		{
			double dx = a*(y-x);
			double dy = x*(b-z)-y;
			double dz = x*y-c*z;
		
			x += dt*dx;
			y += dt*dy;
			z += dt*dz;



			pa[i+1][0] = x;
			pa[i+1][1] = y;
			pa[i+1][2] = z;
			pa[i+1][3] = w;

			/*color[i+1][0] = x;
			color[i+1][1] = y;
			color[i+1][2] = z;
			*/

		}
	}



void display()
	{	lorenz();
		int i;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glRotated(ph,1,0,0);
		glRotated(th,0,1,0);

		glBegin(GL_LINE_STRIP);
		for (i=0;i<N;i++)
		{
			glColor3dv(pa[i]);
			glVertex3dv(pa[i++]);
		}
		glEnd();
		
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex3d(0,0,0);
		glVertex3d(1,0,0);
		glVertex3d(0,0,0);
		glVertex3d(0,1,0);
		glVertex3d(0,0,0);
		glVertex3d(0,0,1);
		glEnd();

		glRasterPos3d(1,0,0);
   		Print("X");
   		glRasterPos3d(0,1,0);
   		Print("Y");
   		glRasterPos3d(0,0,1);
   		Print("Z");
		
		glWindowPos2i(5,5);

		
			
	glFlush();
	glutSwapBuffers();
	}



void key(unsigned char ch,int x,int y)
	{
		if (ch == 27)
		exit(0);
		else if (ch == '0')
		th = ph = 0;
		else if (ch == 'q')
		 {
			a += 1.0;
			lorenz();
		}
		else if (ch == 'a')
		 {
			a -= 1.0;
			lorenz();
		}
		else if (ch == 'w')
		{
			b += 1.0;
			lorenz();
		}
		else if (ch == 's')
		{
			b -= 1.0;
			lorenz();
		}
		else if (ch == 'e')
		{
			c += 1.0;
			lorenz();
		}
		else if (ch == 'd')
		{
			c -= 1.0;
			lorenz();
		}
		else if (ch == 'r')
		{
			w += 0.1;
			lorenz();
		}
		else if (ch == 'f')
		{ 
			w -= 0.1;
			lorenz();
		}
	glutPostRedisplay();
	}


static void special(int key, int x, int y)
	{
		if (key == GLUT_KEY_RIGHT)
		th += 5;
		else if (key == GLUT_KEY_LEFT)
		th -= 5;
		else if (key == GLUT_KEY_UP)
		ph += 5;
		else if (key == GLUT_KEY_DOWN)
		ph -= 5;

		th %= 360;
		ph %= 360;
		
		glutPostRedisplay();
	}


static void reshape(int width, int height)
	{
		GLfloat htw = (GLfloat) height / (GLfloat) width;
		glViewport(0,0, width,height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-5.0, 5.0, -htw*2, htw*2, 1.0, 300.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0, 0.0, -60.0);
	}


int main(int argc, char* argv[]) 
	{
	//lorenz();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D Lorenz Attractor");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
	}
