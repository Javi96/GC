//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
  
protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB() { delete mesh; };
	virtual void render(Camera const& cam); 
};

//-------------------------------------------------------------------------


class Poliespiral : public Entity
{
public:
	Poliespiral(GLdouble l);
	~Poliespiral() { delete mesh; };
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------


class Dragon : public Entity
{
public:
	Dragon(GLint l);
	~Dragon() { delete mesh; };
	virtual void render(Camera const& cam);
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_