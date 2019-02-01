#include "Mesh.h"
#include "time.h"
using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }
	
    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh* Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------

glm::dvec3 Mesh::siguiente(GLint x, GLint y, GLdouble ang, GLint longSeg)
{
	return dvec3(x + longSeg * cos(radians(ang)), y + longSeg * sin(radians(ang)), 0);
}
//-------------------------------------------------------------------------

glm::dvec3 Mesh::t1(GLint x, GLint y) {
	return dvec3(0.824074 * x + 0.281482 * y - 0.882290, -0.212346 * x + 0.864198 * y - 0.110607, 0);
}
//-------------------------------------------------------------------------

glm::dvec3 Mesh::t2(GLint x, GLint y) {
	return dvec3(0.088272 * x + 0.520988 * y + 0.785360, -0.463889 * x -0.377778 * y - 8.095795, 0);
}
//-------------------------------------------------------------------------

Mesh* Mesh::generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert){
	
	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;
	m->colors = new dvec4[m->numVertices];
	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(verIni[0], verIni[1], 0);

	for (int i = 1; i < m->numVertices; i++) {

		dvec3 last = m->vertices[i - 1];

		//m->vertices[i] = siguiente(last[0], last[1], angIni, ladoIni);
		m->colors[i] = dvec4(0.0, 0.0, 1.0, 1.0);
		m->vertices[i] = dvec3(last[0] + ladoIni * cos(radians(angIni)), last[1] + ladoIni * sin(radians(angIni)), 0);
		angIni += incrAng;
		ladoIni += incrLado;
	}

	return m;
}
//-------------------------------------------------------------------------

Mesh* Mesh::generadragon(GLuint numVert) {

	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;
	m->colors = new dvec4[m->numVertices];
	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0, 0, 0);

	for (int i = 1; i < m->numVertices; i++) {
		m->colors[i] = dvec4(0.0, 0.0, 1.0, 1.0);
		dvec3 last = m->vertices[i - 1];

		double azar = rand() / double(RAND_MAX);

		if (azar < 0.787473) {
			//m->vertices[i] = dvec3(i, i, 0);

			m->vertices[i] = dvec3(0.824074 * last[0] + 0.281482 * last[1] - 0.882290, -0.212346 * last[0] + 0.864198 * last[1] - 0.110607, 0);
		}
		else { // azar >= 0.787473
			//m->vertices[i] = dvec3(-i, -i, 0);

			m->vertices[i] = dvec3(0.088272 * last[0] + 0.520988 * last[1] + 0.785360, -0.463889 * last[0] - 0.377778 * last[1] + 8.095795, 0);
		}
	}

	return m;
}
//-------------------------------------------------------------------------