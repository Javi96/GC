//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh{
public:

	static Mesh * createRGBAxes(GLdouble l); // creates a new 3D RGB axes mesh
	static Mesh * generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	static Mesh * generadragon(GLuint numVert);

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

	glm::dvec3 siguiente(GLint x, GLint y, GLdouble ang, GLint longSeg);
	glm::dvec3 t1(GLint x, GLint y);
	glm::dvec3 t2(GLint x, GLint y);
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_