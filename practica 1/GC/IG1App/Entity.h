//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity
{
public:
	Entity() : modelMat(1.0) { };
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;
	virtual void update() = 0;
	//virtual void update(GLuint timeElapsed) = 0;

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }

protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix
	Texture textura;

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity
{
public:
	EjesRGB(glm::dvec2 center, GLdouble l);
	~EjesRGB() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------


class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();

};

//-------------------------------------------------------------------------


class Dragon : public Entity
{
public:
	Dragon(GLint l);
	~Dragon() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();

};

//-------------------------------------------------------------------------


class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLint l);
	~TrianguloRGB() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();

};

//-------------------------------------------------------------------------

class Rectangulo : public Entity
{
public:
	Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();

};

//-------------------------------------------------------------------------

class RectanguloRGB : public Entity
{
public:
	RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();

};

//-------------------------------------------------------------------------

class RectanguloTex : public Entity
{
public:
	RectanguloTex(GLdouble w, GLdouble h);
	~RectanguloTex() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();

};

//-------------------------------------------------------------------------

class TrianguloAnimado : public Entity {
public:
	
	TrianguloAnimado(GLint l, GLdouble angle, GLdouble radio);
	~TrianguloAnimado() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();

protected:

	GLdouble angleOut;
	GLdouble angleIn;
	GLdouble radio;
};

//-------------------------------------------------------------------------

class Estrella3D : public Entity {
public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
protected:
	GLdouble angleY;
	GLdouble angleZ;
	Texture textura;
};

//-------------------------------------------------------------------------

class Estrella3DTex : public Entity {
public:
	Estrella3DTex(GLdouble r, GLdouble nL, GLdouble h);
	~Estrella3DTex() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
protected:
	GLdouble angleY;
	GLdouble angleZ;
	Texture textura;
};

//-------------------------------------------------------------------------

class Cubo : public Entity {
public:
	Cubo(GLdouble w, GLdouble h);
	~Cubo() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

class Caja : public Entity {
public:
	GLdouble w;
	Caja(GLdouble w, GLdouble h);
	~Caja() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
protected:
	Texture textura;
	Mesh* meshP0 = nullptr;
};

//-------------------------------------------------------------------------

class CajaTex : public Entity {
public:
	GLdouble w;
	CajaTex(GLdouble l);
	~CajaTex() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
protected:
	Texture texturaIn;
	Texture texturaOut;
	Texture texturaDown;
	Mesh* meshP0 = nullptr;
};

//-------------------------------------------------------------------------

class Suelo : public Entity {
public:
	Suelo(GLdouble w, GLdouble h);
	~Suelo() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

class Foto : public Entity {
public:
	Foto(GLdouble w, GLdouble h);
	~Foto() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

/*class Prisma : public Entity {
public:
	Prisma(GLdouble r, GLdouble h, int n);
	~Prisma() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

class Piramide : public Entity {
public:
	Piramide(GLdouble r, GLdouble h, int n);
	~Piramide() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

class Diamante : public Entity {
public:
	Diamante(GLdouble r, GLdouble h, int n);
	~Diamante() { delete mesh; };
	virtual void render(Camera const& cam);
	virtual void update();
protected:
	GLdouble angleY;
	GLdouble angleZ;
	Texture textura;
};*/

#endif //_H_Entities_H_