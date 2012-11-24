#include "../shared/gltools.h"
#include <math.h>

// define a constant for the value of PI
#define GL_PI 3.1415f

// rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// called to draw scene
void RenderScene(void){
	GLfloat x,y,z,angle; // storage for coordinates and angles
	
	// clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	// save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// call only once for all remaining points
	glBegin(GL_POINTS);

	z = -50.0f;
	for(angle = 0.0f; angle <= (2.0*GL_PI)*3.0f; angle += 0.1f){
		x = 50.0f * sin(angle);
		y = 50.0f * cos(angle);

		// specify the point and move the Z value up a little
		glVertex3f(x, y, z);
		z += 0.5f;
	}
	
	// done drawing points
	glEnd();

	// restore transformation matrix
	glPopMatrix();

	// flush drawing commands
	glutSwapBuffers();
}

// this function does any needed initialization on the rendering context
void SetupRC(void){
	// black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);
}

void SpecialKeys(int key, int x, int y){
	if(key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if(key > 356.0f){
		xRot = 0.0f;
		yRot = 0.0f;
	}
		
	if(key < -1.0f){
		xRot = 355.0f;
		yRot = 355.0f;
	}					
	
	glutPostRedisplay();
}

void ChangeSize(int w, int h){
	GLfloat nRange = 100.0f;

	// prevent divide by zero
	if(h == 0)
		h = 1;

	// set view port to window dimensions
	glViewport(0,0,w,h);

	// reset projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// establish clipping volume (left, right, bottom, top, near, far)
	if(w <= h)
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	// reset model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Points example");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}