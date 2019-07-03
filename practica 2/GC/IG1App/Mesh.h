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
	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h, glm::dvec4 c);
	static Mesh* generaRectanguloTex(GLdouble w, GLdouble h);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);
	static Mesh* generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h);
	static Mesh* generaCubo(GLdouble w, GLdouble h);
	static Mesh* generaCuboRGB(GLdouble w, GLdouble h, glm::dvec4 c);
	static Mesh* generaCajaTexCor(GLdouble l);

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

class MBR : public Mesh {
public:
	MBR(int mm, int nn, glm::dvec3* p) { 
		n = nn;
		m = mm;
		perfil = p;
		vertexBuilding();
		normalize();
	};

	void vertexBuilding() {
		vertices = new glm::dvec3[n*m]; // Definir el array vertices de tamaño numVertices(=n*m)
		for (int i = 0; i < n; i++) {
			// Cada vuelta genera la muestra i-ésima de vértices
			double theta = i * 2 * 3.14 / n;
			double c = cos(theta);
			double s = sin(theta);
			// R_y de más abajo es la matriz de rotación sobre el eje Y
			for (int j = 0; j < m; j++) {
				int indice = i * m + j;
				// Aplicar la matriz al punto j-ésimodel perfil
				double x = c * perfil[j][0] + s * perfil[j][2];
				double z = -s * perfil[j][0] + c * perfil[j][2];
				glm::dvec3 p = glm::dvec3(x, perfil[j][1], z);
				vertices[indice] = p;
			}
		}
	};

	void normalize() {
		normals = new glm::dvec3[n*m]; // Definir el arraynormalsde tamaño numVertices
		for (int i = 0; i < n*m; i++)// e inicializar sus componentes al vector cero(=dvec3(0,0,0))
			normals[i] = glm::dvec3(0.0, 0.0, 0.0);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m - 1; j++) {
				// Recorrido de todos los vértices
				// Ojo, i<n (obliga a usar %(n*m))
				// y j<m-1 (para excluir los vértices del borde superior)
				int indice = i * m + j;
				int i0 = indice;
				int i1 = (indice + m) % (n*m);
				int i2 = (indice + m + 1) % (n*m);
				int i3 = indice + 1;
				// Por cada cara en la que el vértice ocupa la esquina
				// inferior izquierda, se determinan 3 índices i0, i1, i2
				// de 3 vértices consecutivos de esa cara
				glm::dvec3 aux0 = vertices[i0];
				glm::dvec3 aux1 = vertices[i1];
				glm::dvec3 aux2 = vertices[i2];
				glm::dvec3 norm = glm::cross(aux2-aux1, aux0-aux1);
				normals[i0] += norm; normals[i1] += norm;
				normals[i2] += norm; normals[i3] += norm;
			} // Fin del forj
		}

		for (int i = 0; i < n*m; i++) // Se normalizan todos los vectores normales
			normals[i] = glm::normalize(normals[i]);
	};

	void render() {
		if (vertices != nullptr) {
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_DOUBLE, 0, vertices);
			// Activación de vertexarraysde colores y // coordenadas de textura, si hace el caso.
			// No olvidar desactivarlos
			if (normals != nullptr) {
				glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_DOUBLE, 0, normals);

				primitive = GL_POLYGON; // o GL_LINE_LOOP
				// Se dan índices de vértices de caras cuadrangulares
				for (int i = 0; i < n; i++) {
					// Unir muestra i-ésimacon (i+1)%n-ésima
					for (int j = 0; j < m - 1; j++) {
						// Empezar en esquina inferior izquierda de la cara
						int indice = i * m + j;
						unsigned int index[] =
						{ indice, (indice + m) % (n*m),
						(indice + m + 1) % (n*m), indice + 1 };
						glDrawElements(primitive, 4, GL_UNSIGNED_INT, index);
					}
				}
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glDisableClientState(GL_VERTEX_ARRAY);
		}
	};
				

protected:
	int m; // número de puntos del perfil
	int n; // número de rotaciones
	glm::dvec3* perfil; // perfil en el plano XY
	glm::dvec3* normals;
};

#endif //_H_Scene_H_