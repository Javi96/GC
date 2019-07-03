//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh{
public:

	static Mesh * createRGBAxes(glm::dvec2 center, GLdouble l); 
	static Mesh * generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	static Mesh * generadragon(GLuint numVert);
	static Mesh* generaTrianguloRGB(GLdouble r);
	static Mesh* generaRectangulo(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloTex(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);
	static Mesh* generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h);
	static Mesh* generaCubo(GLdouble w, GLdouble h);
	static Mesh* generaCajaTexCor(GLdouble l);
	//static Mesh* generaPrisma(GLdouble r, GLdouble h, int n = 3);
	//static Mesh* generaPiramide(GLdouble r, GLdouble h, int n = 3);

	Mesh(void) { };
	~Mesh(void);
	virtual void render();

	glm::dvec3* getVertices() { return vertices; };  // vertex array
	glm::dvec4* getColors() { return colors; };      // color array
   
protected:

	GLuint numVertices = 0;   // arrays size (number of elements)
	GLuint primitive = GL_TRIANGLES;  // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...

	glm::dvec3* vertices = nullptr;  // vertex array
	glm::dvec4* colors = nullptr;    // color array
	glm::dvec2* texCoords = nullptr; // texture array
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_