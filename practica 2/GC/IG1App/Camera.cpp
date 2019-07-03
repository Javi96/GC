#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Camera::set2D() 
{
	eye= dvec3(0, 0, 500);
	look= dvec3(0, 0, 0);
	up= dvec3(0, 1, 0);
	viewMat = lookAt(eye, look, up);
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	ang = -45.0;
	GLdouble frente = radio * cos(radians(ang));

	eye = dvec3(frente, frente, frente);
	look = dvec3(0.0, 0.0, 0.0);
	up = dvec3(0.0, 1.0, 0.0);

	viewMat = lookAt(eye, look, up);

	//setCenital();
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::uploadSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadScale(GLdouble s)
{
	factScale -= s;
	if (factScale < 0) factScale = 0.01;
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadPM()
{
	if (orto) {
		nearVal = 1;
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}
	else {
		nearVal = 2 * yTop;
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------

void Camera::setAxes()
{
	u = row(viewMat, 0);
	v = row(viewMat, 1);
	front = -(row(viewMat, 2));
}

//-------------------------------------------------------------------------

void Camera::setVM()
{
	viewMat = lookAt(eye, look, up);
	setAxes();
}

//-------------------------------------------------------------------------

void Camera::setVP(Viewport *viewport)
{
	vp = viewport;
}

//-------------------------------------------------------------------------

void Camera::setCenital()
{
	ang = -90.0;

	eye = dvec3(0.0, radio, 0.0);
	look = dvec3(0.0, 0.0, 0.0);
	up = dvec3(0.0, 0.0, -1.0);

	setVM();
}

//-------------------------------------------------------------------------

void Camera::moveLR(GLdouble cs)
{
	eye += u * cs;
	look += u * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::moveFB(GLdouble cs)
{
	eye += -front * cs;
	look += -front * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::moveUD(GLdouble cs)
{
	eye += v * cs;
	look += v * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::lookLR(GLdouble cs)
{
	look += u * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::lookUD(GLdouble cs)
{
	look += v * cs;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::orbit(GLdouble ax)
{
	ang += ax;
	eye.x = look.x + cos(radians(ang)) * radio;
	eye.z = look.z - sin(radians(ang)) * radio;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::orbit(GLdouble ax, GLdouble ay)
{
	ang += ax;
	eye.x = look.x + cos(radians(ang)) * radio;
	eye.z = look.z - sin(radians(ang)) * radio;
	eye.y += ay;
	setVM();
}

