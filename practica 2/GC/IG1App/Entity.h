//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

#include <vector>

//-------------------------------------------------------------------------

class Entity
{
public:
	Entity() : modelMat(1.0) { };
	virtual ~Entity() { };

	virtual void render(glm::dmat4 const& modelViewMat) = 0;
	virtual void update() = 0;
	//virtual void update(GLuint timeElapsed) = 0;

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }

protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix
	Texture textura;
	glm::fvec3 color = glm::fvec3(-1.0, -1.0, -1.0);

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity
{
public:
	EjesRGB(glm::dvec2 center, GLdouble l);
	~EjesRGB() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

class Dragon : public Entity
{
public:
	Dragon(GLint l);
	~Dragon() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLint l);
	~TrianguloRGB() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

class Rectangulo : public Entity
{
public:
	Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

class RectanguloRGB : public Entity
{
public:
	RectanguloRGB(GLdouble w, GLdouble h, glm::dvec4 c);
	~RectanguloRGB() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	glm::dvec4 c;
};

//-------------------------------------------------------------------------

class RectanguloTex : public Entity
{
public:
	RectanguloTex(GLdouble w, GLdouble h);
	~RectanguloTex() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();

};

//-------------------------------------------------------------------------

class TrianguloAnimado : public Entity {
public:
	
	TrianguloAnimado(GLint l, GLdouble angle, GLdouble radio);
	~TrianguloAnimado() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
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
	virtual void render(glm::dmat4 const& modelViewMat);
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
	virtual void render(glm::dmat4 const& modelViewMat);
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
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

class CuboRGB : public Entity {
public:
	CuboRGB(GLdouble w, GLdouble h, glm::dvec4 c);
	~CuboRGB() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	glm::dvec4 c;
};

//-------------------------------------------------------------------------

class Caja : public Entity {
public:
	Caja(GLdouble w, GLdouble h);
	~Caja() { delete mesh; delete meshP0; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble w;
	Texture textura;
	Mesh* meshP0 = nullptr;
};

//-------------------------------------------------------------------------

class CajaTex : public Entity {
public:
	CajaTex(GLdouble l);
	~CajaTex() { delete mesh; delete meshP0; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble width;
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
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------

class Foto : public Entity {
public:
	Foto(GLdouble w, GLdouble h);
	~Foto() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class Tablero : public Entity {
public:
	Tablero(GLdouble w, GLdouble h, GLdouble angle, GLdouble margin);
	~Tablero() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble length;
	GLdouble margin;
	GLdouble angle;
};

//-------------------------------------------------------------------------

class Cangilon : public CajaTex {
public:
	Cangilon(GLdouble l, GLdouble angle);
	~Cangilon() { delete mesh; delete meshP0; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble angle;
};

//-------------------------------------------------------------------------

class QuadricEntity : public Entity {
public:
	QuadricEntity() { q = gluNewQuadric(); };
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
};

//-------------------------------------------------------------------------

class Sphere : public QuadricEntity {
public:
	Sphere(GLdouble r, Material* mat); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r;
	Material* mat;
};

//-------------------------------------------------------------------------

class Cylinder : public QuadricEntity {
public:
	Cylinder(GLdouble r1, GLdouble r2, GLdouble h, glm::fvec3 color); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r1, r2, h;
	glm::fvec3 c;
};

//-------------------------------------------------------------------------

class Disk : public QuadricEntity {
public:
	Disk(GLdouble r1, GLdouble r2); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r1, r2;
};

//-------------------------------------------------------------------------

class PartialDisk : public QuadricEntity {
public:
	PartialDisk(GLdouble r1, GLdouble r2, GLdouble ini, GLdouble fin); // r is the radius of the sphere
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r1, r2, ini, fin;
};

//-------------------------------------------------------------------------

class Rotor : public QuadricEntity {
public:
	Rotor(GLdouble r, GLdouble w, bool spin, glm::dvec4 c); // r is the radius of the sphere
	~Rotor() { delete mesh; };
	void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble r, w, h, angle;
	bool spin;
	glm::dvec4 c;
};

//-------------------------------------------------------------------------

class Chasis : public CuboRGB {
public:
	Chasis(GLdouble w, GLdouble h, glm::dvec4 color);
	~Chasis() { delete mesh; delete meshP0; delete meshP1; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	glm::dvec4 c;
	GLdouble w, h;
	Mesh* meshP0 = nullptr;
	Mesh* meshP1 = nullptr;
};

//-------------------------------------------------------------------------

class Dron : public Chasis {
public:
	Dron(GLdouble w, GLdouble h, glm::dvec4 color);
	~Dron() {
		delete mesh; delete meshP0; delete meshP1; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	Rotor *r1;
	Rotor *r2;
	Rotor *r3;
	Rotor *r4;
};

//-------------------------------------------------------------------------

class Cone : public Entity {
public:
	Cone(GLdouble w, GLdouble h);
	~Cone() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
};

//-------------------------------------------------------------------------

class SphereRV : public Entity {
public:
	SphereRV(int paralelos, int meridianos, GLdouble r, Material* mat);
	~SphereRV() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	Material* mat;
};

//-------------------------------------------------------------------------

class Satelite : public SphereRV {
public:
	Satelite(int paralelos, int meridianos, GLdouble r);
	~Satelite() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void orbitate(int move);
protected:
	Dron *dron;
	GLdouble angleX, angleY, r;
};

//-------------------------------------------------------------------------

class Enjambre : public Dron {	// Multidron
public:
	Enjambre(GLdouble w, GLdouble h, glm::dvec4 color);
	~Enjambre() {
		delete mesh; delete meshP0; delete meshP1;
	};
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	Dron *d1;
	Dron *d2;
	Dron *d3;
	Dron *d4;
};

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

class CompoundEntity : public Entity {
public:
	CompoundEntity() { };
	~CompoundEntity() { for (Entity* it : grObjects) delete it; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();

	virtual Entity*	getEntity(int i) { return grObjects[i]; };

protected:
	std::vector<Entity*> grObjects;
};

//-------------------------------------------------------------------------

class Aspa : public RectanguloRGB {
public:
	Aspa(GLdouble w, GLdouble h, bool spin, glm::dvec4 c);
	~Aspa() { delete mesh; };
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	GLdouble angle;
	bool spin;
	glm::dvec4 c;
};

//-------------------------------------------------------------------------

class RotorCompound : public CompoundEntity {
public:
	RotorCompound(GLdouble r, GLdouble w, bool spin, glm::dvec4 c);
protected:
	GLdouble r, w, h, angle;
	bool spin;
	glm::dvec4 c;
};

//-------------------------------------------------------------------------

class DronCompound : public CompoundEntity {
public:
	DronCompound(GLdouble w, GLdouble h, glm::dvec4 color);
protected:
	GLdouble w, h;
};

//-------------------------------------------------------------------------

class DronCompoundLight : public CompoundEntity {
public:
	DronCompoundLight(GLdouble w, GLdouble h, glm::dvec4 color);
	virtual void render(glm::dmat4 const& modelViewMat);
protected:
	GLdouble w, h;
	Entity* r1;
	Entity* r2;
	Entity* r3;
	Entity* r4;
	Chasis* ch;
	SpotLight* light;
};

//-------------------------------------------------------------------------

class SateliteMat : public CompoundEntity {
public:
	SateliteMat(int paralelos, int meridianos, GLdouble r, Material* matt);
	~SateliteMat() { delete mesh; };
	void orbitate(int move);
protected:
	DronCompoundLight* dron;
	SphereRV* esfera;
	GLdouble angleX, angleY, r;
};

#endif //_H_Entities_H_