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

EjesRGB::EjesRGB(glm::dvec2 center, GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(center, l);
}
//-------------------------------------------------------------------------

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat()); 
		glLineWidth(1);
		mesh->render();
		glLineWidth(1);
	}
}
void EjesRGB::update()
{
}


//-------------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert): Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
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
void Poliespiral::update()
{
}
//-------------------------------------------------------------------------

Dragon::Dragon(GLint l) : Entity()
{
	mesh = Mesh::generadragon(l);
}
//-------------------------------------------------------------------------

void Dragon::render(Camera const & cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = cam.getViewMat();
		setModelMat(translate(auxMat, dvec3(-40, -170, 0)));
		setModelMat(scale(auxMat, dvec3(40, 40, 40)));

		uploadMvM(cam.getViewMat());
		glPointSize(2);
		glColor3d(55.0, 55.0, 55.0);
		mesh->render();
		glPointSize(1);
		glColor3d(1.0, 1.0, 1.0);
	}
}
void Dragon::update()
{
}
//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLint l) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(l);
}
//-------------------------------------------------------------------------

void TrianguloRGB::render(Camera const & cam) 
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
		//glPolygonMode(GL_BACK, GL_LINE);
		mesh->render();
	}
}
void TrianguloRGB::update()
{
}
//-------------------------------------------------------------------------

Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaRectangulo(w, h);
}
//-------------------------------------------------------------------------

void Rectangulo::render(Camera const & cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = cam.getViewMat();
		//auxMat = translate(auxMat, dvec3(center.x, center.y, 0.0));
		auxMat = rotate(auxMat, radians(25.0), dvec3(0.0, 0.0, 1.0));
		//auxMat = translate(auxMat, dvec3(-center.x, -center.y, 0.0));
		uploadMvM(auxMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//rotate(modelMat, radians(25), dvec3(0.0, 0.0, 1.0));
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
}
void Rectangulo::update()
{
}
//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaRectanguloRGB(w, h);
}

void RectanguloRGB::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		mesh->render();

	}
}

void RectanguloRGB::update()
{
}

RectanguloTex::RectanguloTex(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloTex(w, h);
	textura.load("..\\Bmps\\Zelda.bmp");
}

void RectanguloTex::render(Camera const & cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = cam.getViewMat();
		auxMat = rotate(auxMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
		uploadMvM(auxMat);
		mesh->render();
		
	}
}

void RectanguloTex::update()
{
}

TrianguloAnimado::TrianguloAnimado(GLint r, GLdouble angle, GLdouble radio)
{
	this->angleOut = 0;
	this->angleIn = 0;
	this->radio = radio;
	mesh = Mesh::generaTrianguloRGB(r);
}

void TrianguloAnimado::render(Camera const & cam)
{
	dmat4 auxMat = cam.getViewMat();

	if (mesh != nullptr) {

		
		GLint x = 0 + radio * cos(radians(this->angleOut));
		GLint y = 0 + radio * sin(radians(this->angleOut));

		
		auxMat = translate(auxMat, dvec3(x, y, 0.0));
		auxMat = rotate(auxMat, radians(this->angleIn), dvec3(0.0, 0.0, 1.0));
		//auxMat = translate(auxMat, dvec3(-this->center.x, -this->center.y, 0.0));


		uploadMvM(auxMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void TrianguloAnimado::update()
{
	this->angleOut += 1;
	this->angleIn += 3;
}

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	this->angleZ = 90;
	this->angleY = 90;
	mesh = Mesh::generaEstrella3D(re, np, h);
}

void Estrella3D::render(Camera const & cam)
{
	if (mesh != nullptr) {

		dmat4 auxMat = modelMat;
		modelMat = auxMat;

		modelMat = rotate(modelMat, radians(this->angleY), dvec3(0.0, 1.0, 0.0));; // rota sobre eje Y
		modelMat = rotate(modelMat, radians(this->angleZ), dvec3(0.0, 0.0, 1.0));; // rota sobre eje Y

		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat
		mesh->render();

		modelMat = rotate(modelMat, radians(180.0), dvec3(0.0, 1.0, 0.0));; // matP1 posiciona a P1 con respecto a P0
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat * matP1
		mesh->render();

		

		modelMat = auxMat;
	}
}

void Estrella3D::update()
{
	this->angleY += 1;
	this->angleZ += 3;
}

Cubo::Cubo(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaCubo(w, h);
}

void Cubo::render(Camera const & cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = cam.getViewMat();
		uploadMvM(auxMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

void Cubo::update()
{
}

Caja::Caja(GLdouble w, GLdouble h)
{
	this->w = w;
	mesh = Mesh::generaCubo(w, h);
	meshP0 = Mesh::generaRectangulo(w, w);
}

void Caja::render(Camera const & cam)
{
	if (mesh != nullptr && meshP0 != nullptr) {
		
		dmat4 auxMat = modelMat;
		modelMat = auxMat;
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat
		mesh->render();
		modelMat = rotate(modelMat, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		modelMat = translate(modelMat,dvec3(0, 0, w/2)); //USAR WIDTH/2
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat * matP1
		meshP0->render();
		//modelMat = rotate(modelMat, radians(-90.0), dvec3(1.0, 0.0, 0.0));

		modelMat = auxMat;
	}
}

void Caja::update()
{
}

Suelo::Suelo(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	textura.load("..\\Bmps\\Zelda.bmp");
}

void Suelo::render(Camera const & cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = cam.getViewMat();
		auxMat = rotate(auxMat, radians(-90.0), dvec3(1.0, 0.0, 0.0));
		uploadMvM(auxMat);
		textura.bind();
		mesh->render();
		textura.unbind();
	}
}

void Suelo::update()
{
}

Foto::Foto(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	textura.loadColorBuffer();
}

void Foto::render(Camera const & cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		textura.bind();
		mesh->render();
		textura.unbind();
	}
}

void Foto::update()
{
	textura.loadColorBuffer();
}

Estrella3DTex::Estrella3DTex(GLdouble r, GLdouble nL, GLdouble h)
{
	mesh = Mesh::generaEstrellaTexCor(r, nL, h);
	textura.load("..\\Bmps\\picos.bmp");
}

void Estrella3DTex::render(Camera const & cam)
{
	if (mesh != nullptr) {

		dmat4 auxMat = modelMat;
		modelMat = auxMat;

		modelMat = rotate(modelMat, radians(this->angleY), dvec3(0.0, 1.0, 0.0));; // rota sobre eje Y
		modelMat = rotate(modelMat, radians(this->angleZ), dvec3(0.0, 0.0, 1.0));; // rota sobre eje Y

		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat
		textura.bind();
		mesh->render();
		textura.unbind();

		modelMat = rotate(modelMat, radians(180.0), dvec3(0.0, 1.0, 0.0));; // matP1 posiciona a P1 con respecto a P0
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat * matP1
		textura.bind();
		mesh->render();
		textura.unbind();

		modelMat = auxMat;
	}
}

void Estrella3DTex::update()
{
	this->angleY += 1;
	this->angleZ += 3;
}

CajaTex::CajaTex(GLdouble l)
{
	this->w = l;
	meshP0 = Mesh::generaCajaTexCor(l);
	mesh = Mesh::generaRectanguloTex(l, l);
	texturaOut.load("..\\Bmps\\container2.bmp");
	texturaIn.load("..\\Bmps\\container.bmp");
	texturaDown.load("..\\Bmps\\baldosa1.bmp");
	
}

void CajaTex::render(Camera const & cam)
{
	if (meshP0 != nullptr && mesh != nullptr) {

		glEnable(GL_CULL_FACE);

		dmat4 auxMat = modelMat;
		modelMat = auxMat;
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat

		texturaOut.bind();
		meshP0->render();
		texturaOut.unbind();
		glCullFace(GL_FRONT);
		texturaIn.bind();
		meshP0->render();
		texturaIn.unbind();
		glCullFace(GL_BACK);

		modelMat = rotate(modelMat, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		modelMat = translate(modelMat, dvec3(0, 0, w / 2)); //USAR WIDTH/2
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat * matP1

		texturaDown.bind();
		mesh->render();
		texturaDown.unbind();
		glCullFace(GL_FRONT);
		texturaDown.bind();
		mesh->render();
		texturaDown.unbind();
		glCullFace(GL_BACK);

		//modelMat = rotate(modelMat, radians(-90.0), dvec3(1.0, 0.0, 0.0));

		modelMat = auxMat;

		glDisable(GL_CULL_FACE);
	}
}

void CajaTex::update()
{
}

/*Prisma::Prisma(GLdouble r, GLdouble h, int n)
{
	mesh = Mesh::generaPrisma(r, h, n);
}

void Prisma::render(Camera const & cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = cam.getViewMat();
		uploadMvM(auxMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

void Prisma::update()
{
}

Piramide::Piramide(GLdouble r, GLdouble h, int n)
{
	mesh = Mesh::generaPiramide(r, h, n);
}

void Piramide::render(Camera const & cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = cam.getViewMat();
		uploadMvM(auxMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
	}
}

void Piramide::update()
{
}

Diamante::Diamante(GLdouble r, GLdouble h, int n)
{
	mesh = Mesh::generaPiramide(r, h, n);
}

void Diamante::render(Camera const & cam)
{
	if (mesh != nullptr) {

		dmat4 auxMat = modelMat;
		modelMat = auxMat;

		modelMat = rotate(modelMat, radians(this->angleY), dvec3(0.0, 1.0, 0.0));; // rota sobre eje Y
		//modelMat = rotate(modelMat, radians(this->angleZ), dvec3(0.0, 0.0, 1.0));; // rota sobre eje Y

		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat
		mesh->render();

		modelMat = rotate(modelMat, radians(180.0), dvec3(0.0, 0.0, 1.0));; // matP1 posiciona a P1 con respecto a P0
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat * matP1
		mesh->render();

		modelMat = auxMat;
	}
}

void Diamante::update()
{
	this->angleY += 1;
	//this->angleZ += 3;
}*/
