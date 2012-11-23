#include "../shared/gltools.h"

// called to draw scene
void RenderScene(void){
	// clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	// set current drawing color to red
	//		  R		G	  B		ALPHA defaults to 1.0f
	glColor3f(1.0f, 0.0f, 0.0f);

	// draw a filled rectangle with current color
	glRectf(-25.0f, 25.0f, 25.0f, -25.0f);

	// flush drawing commands
	glFlush();
}

// set up the rendering state
void SetupRC(void){
	// set clear color to blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// called by GLUT library when the window has changed size
void ChangeSize(GLsizei w, GLsizei h){
	GLfloat aspectRatio;

	// prevent a divide by zero
	if(h == 0)
		h = 1;

	// set View port to window dimensions
	glViewport(0,0,w,h);

	// reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat) w / (GLfloat) h;
	if(w <= h)
		glOrtho(-100.0, 100.0, -100 / aspectRatio, 100 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0 * aspectRatio, 100.0* aspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("GLRect");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();

	glutMainLoop();

	return 0;
}