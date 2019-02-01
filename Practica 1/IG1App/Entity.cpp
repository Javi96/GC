#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat()); 
		glLineWidth(2);
		mesh->render();
		glLineWidth(15);
	}
}
//-------------------------------------------------------------------------

Poliespiral::Poliespiral(GLdouble l): Entity()
{
	//mesh = Mesh::generaPoliespiral(dvec2(0.0, 0.0), 0.0, 160.0, 1.0, 1.0, 50);
	//mesh = Mesh::generaPoliespiral(dvec2(0.0, 0.0), 0.0, 72.0, 30.0, 0.001, 5);
	//mesh = Mesh::generaPoliespiral(dvec2(0.0, 0.0), 0.0, 60.0, 0.5, 0.5, 100);
	mesh = Mesh::generaPoliespiral(dvec2(0.0, 0.0), 0.0, 89.5, 0.5, 0.5, 100);
	//mesh = Mesh::generaPoliespiral(dvec2(0.0, 0.0), 0.0, 45, 1.0, 1.0, 50);

}
//-------------------------------------------------------------------------

void Poliespiral::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(55.0, 55.0, 55.0);
		mesh->render();
	}
}
//-------------------------------------------------------------------------

Dragon::Dragon(GLint l)
{
	mesh = Mesh::generadragon(l);
}

void Dragon::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glPointSize(1);
		glColor3d(55.0, 55.0, 55.0);
		setModelMat(translate(modelMat, dvec3(-40, -170, 0)));
		setModelMat(scale(modelMat, dvec3(40, 40, 40)));
		mesh->render();
	}
}
