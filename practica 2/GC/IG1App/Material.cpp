#include "Material.h"
#include <gtc/type_ptr.hpp>

using namespace glm;


void Material::upload()
{
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE); // Defecto
}

void Material::setCooper()
{
	ambient = { 0.19125, 0.0735, 0.0225, 1 };
	diffuse = { 0.7038, 0.27048, 0.0828, 1 };
	specular = { 0.256777, 0.137622, 0.086014, 1 };
	expF = (GLfloat) 12.8;
}

void Material::setGold() {
	ambient = { 0.24725, 0.1995, 0.0745, 1 };
	diffuse = { 0.75164, 0.60648, 0.22648, 1 };
	specular = { 0.628281, 0.555802, 0.366065, 1 };
	expF = (GLfloat) 51.2;
}

void Material::setSilver() {
	ambient = { 0.19225, 0.19225, 0.19225, 1 };
	diffuse = { 0.550754, 0.550754, 0.550754, 1 };
	specular = { 0.508273, 0.508273, 0.508273, 1 };
	expF = (GLfloat) 51.2;
}
