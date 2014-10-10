// Name: Aranya Meas
// Quarter, Year: Spring 2014
// Assignment 2
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <GL/glut.h>

#include "const.h"
#include "color.h"
#include "vector3.h"
#include "particlesystem.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const double VIEW_LEFT = 0.0;
const double VIEW_RIGHT = WINDOW_WIDTH;
const double VIEW_BOTTOM = 0.0;
const double VIEW_TOP = WINDOW_HEIGHT;
const double VIEW_FRONT = -800;
const double VIEW_BACK = 800;

int currentTime = 0;
int previousTime = 0;

std::vector<ParticleSystem*> psystems;

void GLrender();
void GLupdate();
void GLprocessMouse(int button, int state, int x, int y);

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lab 3 - Aranya Meas");
	glutDisplayFunc(GLrender);
	glutIdleFunc(GLupdate);
	glutMouseFunc(GLprocessMouse);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glOrtho(VIEW_LEFT, VIEW_RIGHT, VIEW_BOTTOM, VIEW_TOP, VIEW_FRONT, VIEW_BACK);
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	GLInit(&argc, argv);
	glutMainLoop();
	return 0;
}

void GLupdate()
{
	const int FRAME_RATE = 25;
	
	double dt = FRAME_RATE / 1000.0;
	updateParticleSystems(psystems, dt);
	cleanupParticleSystems(psystems);

	glutPostRedisplay();

	//sleep is not effective in capturing constant time between frames because sleep
	//doesn't consider the time it takes for context-switching. However, this reduces
	//the cpu-usage. If accurate time frames are desire, use a time accumulator
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int diffTime = currentTime - previousTime;
	previousTime = currentTime;
	usleep(1000 * std::max(FRAME_RATE - diffTime, 0));
}

void GLrender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < psystems.size(); ++i)
		psystems[i]->render();

	glFlush();	
	glutSwapBuffers();
}

void GLprocessMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		psystems.push_back(new ParticleSystemSpringMass(Vector3(x, WINDOW_HEIGHT - y, 0)));
	}
}
