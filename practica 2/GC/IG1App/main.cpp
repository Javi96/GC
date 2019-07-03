//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming 

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"

#include <iostream>

using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort1(800, 600);
Viewport viewPort2(800, 600);

// Camera position, view volume and projection
Camera camera1(&viewPort1);
Camera camera2(&viewPort2);

// Graphics objects of the scene
Scene scene1, scene2;

bool need_update = true;		// Update automático
GLuint new_update_tick;			// Intervalo update

bool baldosas = false;			// Embaldosado
int num_baldosas = 2;			

bool twoPorts = false;			// Doble viewport

bool light0 = false;									// Luz direccional
bool light1 = false;									// Luz foco
bool light2 = true;										// Luz dron
GLfloat local_ambient[] = { 0.5, 0.5, 0.5, 1.0 };		// Luz ambiente encendida
GLfloat local_ambient2[] = { 0.0, 0.0, 0.0, 1.0 };		// Luz ambiente apagada

glm::dvec2 mCoord;
int mBot = 0;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void setTwoPorts();
void setOnePort();
void update();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void mouseWheel(int n, int d, int x, int y);
void embaldosar(int nCol);
void desbaldosar();

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	cout << "Starting console..." << '\n';

	camera1.orto = false;
	camera2.orto = false;

	// Initialization
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);   // GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(800, 600);   // window size	
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   

	int win = glutCreateWindow("IG1App");  // window's identifier

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMouseWheelFunc(mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';

	// after creating the context

	camera1.set3D();
	camera2.set3D();

	scene1.init1();
	scene2.init2();

	glutMainLoop();

	//cin.ignore(INT_MAX, '\n');  cin.get();  
	glutDestroyWindow(win);  // Destroy the context 

	return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffering
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!twoPorts) {
		if (baldosas)
			embaldosar(num_baldosas); // Se muestran 4 puertos de vista
		else
			scene1.render(camera1.getViewMat());
	}
	else {
		if (baldosas)
			embaldosar(num_baldosas);
		else {
			setTwoPorts();
		}
	}

	glutSwapBuffers();
}

//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
	if (!twoPorts) {
		viewPort1.uploadSize(newWidth, newHeight);
		camera1.uploadSize(viewPort1.getW(), viewPort1.getH());    // scale unchanged
		camera2 = camera1;			
	}
	else {
		viewPort1.uploadSize(newWidth, newHeight);
		camera1.uploadSize(viewPort1.getW(), viewPort1.getH());    // scale unchanged
		viewPort2.uploadSize(newWidth, newHeight);
		camera2.uploadSize(viewPort2.getW(), viewPort2.getH());    // scale unchanged
	}

	glutPostRedisplay();
}

//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
	Texture texture;
	bool need_redisplay = true;

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
		break;
	case '+':
		camera1.uploadScale(+0.01);   // zoom in  (increases the scale)
		if (twoPorts)
			camera2.uploadScale(+0.01);   // zoom in  (increases the scale)
		break;
	case '-':
		camera1.uploadScale(-0.01);   // zoom out (decreases the scale)
		if (twoPorts)
			camera2.uploadScale(-0.01);   // zoom in  (increases the scale)
		break;
	case 'h':
		if (baldosas) {
			baldosas = false;
			desbaldosar();
		}
		else {
			baldosas = true;
			embaldosar(num_baldosas);
		}
		break;
	case 'j':
		if (twoPorts) {
			twoPorts = false;
			setOnePort();
		}
		else {
			twoPorts = true;
			setTwoPorts();
		}
		break;
	case 'k':
		if (twoPorts)
			camera2.yaw(5);
		break;
	case 'l':
		camera1.set3D();
		if (twoPorts) {
			camera2.set3D();
		}
		break;
	case 'm':	// Luz ambiente ON
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, local_ambient);
		break;
	case 'n':	// Luz ambiente OFF
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, local_ambient2);
		break;
	case 'o':
		camera1.set2D();
		if (twoPorts) {
			camera2.set2D();
		}
		break;
	case 'p':
		camera1.orto = !camera1.orto;
		camera1.uploadPM();
		if (twoPorts) {
			camera2.orto = !camera2.orto;
			camera2.uploadPM();		
		}
		break;
	case 'u':
		scene1.update();
		if (twoPorts)
			scene2.update();	
		break;
	case 'U':
		if (need_update) need_update = false;
		else need_update = true;
		break;
	case '0':	// Luz direccional
		if (light0) {
			light0 = false;
			glDisable(GL_LIGHT0);
		}
		else {
			light0 = true;
			glEnable(GL_LIGHT0);
		}
		break;
	case '1':	// Luz foco
		if (light1) {
			light1 = false;
			glDisable(GL_LIGHT1);
		}
		else {
			light1 = true;
			glEnable(GL_LIGHT1);
		}
		break;
	case '2':	// Luz dron
		if (light2) {
			light2 = false;
			glDisable(GL_LIGHT2);
		}
		else {
			light2 = true;
			glEnable(GL_LIGHT2);
		}
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case GLUT_KEY_RIGHT:
		//camera.pitch(5);   // rotate 1 on the X axis
		scene1.move(0);
		break;
	case GLUT_KEY_LEFT:
		//camera.yaw(5);     // rotate 1 on the Y axis 
		scene1.move(1);
		break;
	case GLUT_KEY_UP:
		//camera.roll(5);    // rotate 1 on the Z axis
		scene1.move(2);
		break;
	case GLUT_KEY_DOWN:
		//camera.roll(-5);   // rotate -1 on the Z axis
		scene1.move(3);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}

//-------------------------------------------------------------------------

void update() {
	if (need_update) {
		scene1.update();
		if (twoPorts)
			scene2.update();
		glutPostRedisplay();
	}
}

//-------------------------------------------------------------------------

void mouse(int button, int state, int x, int y) {
	mBot = button;
	mCoord = glm::dvec2(x, y);
}

//-------------------------------------------------------------------------

void motion(int x, int y) {
	// Guardar los valores de mCoord cuando se pulsó el botón
	glm::dvec2 mp = mCoord;
	mCoord = glm::dvec2(x, y);
	// Calcular el desplazamiento habido
	mp = (mCoord - mp);
	if (mBot == GLUT_LEFT_BUTTON)
		// Recuerda que mp.x son radianes. Redúcelos a tu gusto
		if ((x < glutGet(GLUT_WINDOW_WIDTH) / 2 && twoPorts) || !twoPorts)
			camera1.orbit(mp.x*0.05, mp.y);
		else
			camera2.orbit(mp.x*0.05, mp.y);
	else if (mBot == GLUT_RIGHT_BUTTON) {
		if ((x < glutGet(GLUT_WINDOW_WIDTH) / 2 && twoPorts) || !twoPorts) {
			camera1.moveUD(mp.y);
			camera1.moveLR(-mp.x);
		}
		else {
			camera2.moveUD(mp.y);
			camera2.moveLR(-mp.x);
		}
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------------------

void mouseWheel(int n, int d, int x, int y) {
	// Se identifica cuántas de las teclas posibles
	// GLUT_ACTIVE_CTRL/_ALT/_SHIFT están pulsadas
	int m = glutGetModifiers();
	if (m == 0) { // Si ninguna tecla pulsada,
	// desplazar en la dirección de vista d
		if ((x < glutGet(GLUT_WINDOW_WIDTH) / 2 && twoPorts) || !twoPorts) {
			if (d == 1) camera1.moveFB(5);
			else camera1.moveFB(-5);
		}
		else {
			if (d == 1) camera2.moveFB(5);
			else camera2.moveFB(-5);
		}
	}
	else if (m == GLUT_ACTIVE_CTRL) {
		if ((x < glutGet(GLUT_WINDOW_WIDTH) / 2 && twoPorts) || !twoPorts) {
			if (d == 1) camera1.uploadScale(0.1);
			else camera1.uploadScale(-0.1);
		}
		else {
			if (d == 1) camera2.uploadScale(0.1);
			else camera2.uploadScale(-0.1);
		}
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------------------

void embaldosar(int nCol) {
	if (!twoPorts) {
		GLdouble SVAratio = (camera1.xRight - camera1.xLeft) / (camera1.yTop - camera1.yBot);
		GLdouble w = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / (GLdouble)nCol;
		GLdouble h = w / SVAratio;
		for (GLint c = 0; c < nCol; c++) {
			GLdouble currentH = 0;
			while ((currentH + h) <= glutGet(GLUT_WINDOW_HEIGHT)) {
				Viewport* vp = new Viewport((GLint)w, (GLint)h);
				glViewport(vp->getLeft(), vp->getBot(), vp->getW(), vp->getH());
				vp->uploadPos((GLint)(c*w), (GLint)currentH);
				vp->upload();
				camera1.setVP(vp);
				scene1.render(camera1.getViewMat());
				currentH += h;
			} // del while
		} // del for
	}
	else {
		GLdouble SVAratio = (camera1.xRight - camera1.xLeft) / (camera1.yTop - camera1.yBot);
		GLdouble limit = (GLdouble)glutGet(GLUT_WINDOW_WIDTH) / 2;
		GLdouble w = limit / (GLdouble)nCol;
		GLdouble h = w / SVAratio;
		for (GLint c = 0; c < nCol; c++) {
			GLdouble currentH = 0;
			while ((currentH + h) <= glutGet(GLUT_WINDOW_HEIGHT)) {
				Viewport* vp1 = new Viewport((GLint)w, (GLint)h);
				Viewport* vp2 = new Viewport((GLint)w, (GLint)h);
				vp1->uploadPos((GLint)(c*w), (GLint)currentH);
				vp2->uploadPos((GLint)(c*w+limit), (GLint)currentH);
				vp1->upload();
				vp2->upload();
				camera1.setVP(vp1);
				camera2.setVP(vp2);
				glViewport(vp1->getLeft(), vp1->getBot(), vp1->getW(), vp1->getH());
				scene1.render(camera1.getViewMat());
				glViewport(vp2->getLeft(), vp2->getBot(), vp2->getW(), vp2->getH());
				scene2.render(camera2.getViewMat());
				currentH += h;
			} // del while
		} // del for
	}
}

//-------------------------------------------------------------------------

void desbaldosar() {
	if (!twoPorts) {
		setOnePort();
	}
	else {
		setTwoPorts();
	}
}

//-------------------------------------------------------------------------

void setOnePort() {
	Viewport* vp = new Viewport(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	vp->uploadPos(0.0, 0.0);
	vp->upload();
	camera1.setVP(vp);
	scene1.render(camera1.getViewMat());
}

//-------------------------------------------------------------------------

void setTwoPorts() {
	int w = glutGet(GLUT_WINDOW_WIDTH) / 2;
	GLdouble SVAratio1 = (camera1.xRight - camera1.xLeft) / (camera1.yTop - camera1.yBot);
	GLdouble SVAratio2 = (camera2.xRight - camera2.xLeft) / (camera2.yTop - camera2.yBot);
	GLdouble h1 = (GLdouble)w / SVAratio1;
	GLdouble h2 = (GLdouble) w / SVAratio2;
	Viewport* vp1 = new Viewport(w, (GLint)h1);
	Viewport* vp2 = new Viewport(w, (GLint)h2);

	vp1->uploadPos(0.0, (glutGet(GLUT_WINDOW_HEIGHT) - h1 ) / 2);
	vp1->upload();
	camera1.setVP(vp1);
	camera1.uploadPM();
	scene1.render(camera1.getViewMat());
	
	vp2->uploadPos(w, (glutGet(GLUT_WINDOW_HEIGHT) - h2 ) / 2);
	vp2->upload();
	camera2.setVP(vp2);
	camera2.uploadPM();
	scene2.render(camera2.getViewMat());
}
