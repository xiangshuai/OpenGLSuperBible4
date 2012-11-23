#include "../shared/gltools.h"

// called to draw scene
void RenderScene(void){
	// clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);
	// flush drawing commands
	glFlush();
}

// set up rendering state
void SetupRC(void){
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Simple");
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}