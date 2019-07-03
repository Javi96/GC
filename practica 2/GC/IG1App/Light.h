#pragma once
#ifndef _H_Light_H_
#define _H_Light_H_

#include <GL/freeglut.h>
#include <glm.hpp>


class Light
{
public:
	Light();
	virtual ~Light() { disable(); }
	void uploadL();
	virtual void upload(glm::dmat4 const& modelViewMat) = 0;

	void disable();
	void enable();
	void setAmb(glm::fvec4 amb);
	void setDiff(glm::fvec4 diff);
	void setSpec(glm::fvec4 spce);
	GLuint getId() { return id; };

protected:
	static  GLuint cont; // Para generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };
};

//-------------------------------------------------------------------------

class DirLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat);
	void setPosDir(glm::fvec3 dir);
};

//-------------------------------------------------------------------------

class PosLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat);
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kc, GLfloat kl, GLfloat kq);
protected:
	// Factores de atenuación
	GLfloat kc = 1, kl = 0, kq = 0;
};

//-------------------------------------------------------------------------

class SpotLight : public PosLight {
public:
	SpotLight(glm::fvec3 pos = { 0, 0, 0 })
		: PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat);
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
protected:
	// Atributos del foco
	glm::fvec4 direction = { 0, 0, -1, 0 };
	GLfloat cutoff = 10;
	GLfloat exp = 0;
};

#endif //_H_Light_H_