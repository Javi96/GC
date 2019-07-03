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

void EjesRGB::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat); 
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

void Poliespiral::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
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

void Dragon::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		setModelMat(translate(auxMat, dvec3(-40, -170, 0)));
		setModelMat(scale(auxMat, dvec3(40, 40, 40)));

		uploadMvM(modelViewMat);
		glPointSize(2);
		glColor3d(55.0, 55.0, 55.0);
		mesh->render();
		glPointSize(1);
		glColor3d(1.0, 1.0, 1.0);

		modelMat = auxMat;
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

void TrianguloRGB::render(dmat4 const& modelViewMat) 
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
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

void Rectangulo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		//auxMat = translate(auxMat, dvec3(center.x, center.y, 0.0));
		auxMat = rotate(auxMat, radians(25.0), dvec3(0.0, 0.0, 1.0));
		//auxMat = translate(auxMat, dvec3(-center.x, -center.y, 0.0));
		uploadMvM(modelViewMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//rotate(modelMat, radians(25), dvec3(0.0, 0.0, 1.0));
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		modelMat = auxMat;
	}
}
void Rectangulo::update()
{
}

//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h, dvec4 cc) : Entity()
{
	mesh = Mesh::generaRectanguloRGB(w, h, cc);
	c = cc;
}

void RectanguloRGB::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		mesh->render();
	}
}

void RectanguloRGB::update()
{
}

//-------------------------------------------------------------------------


RectanguloTex::RectanguloTex(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloTex(w, h);
	textura.load("..\\Bmps\\Zelda.bmp");
}

void RectanguloTex::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		auxMat = rotate(auxMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
		uploadMvM(modelViewMat);
		mesh->render();

		modelMat = auxMat;		
	}
}

void RectanguloTex::update()
{
}

//-------------------------------------------------------------------------

TrianguloAnimado::TrianguloAnimado(GLint r, GLdouble angle, GLdouble radio)
{
	this->angleOut = 0;
	this->angleIn = 0;
	this->radio = radio;
	mesh = Mesh::generaTrianguloRGB(r);
}

void TrianguloAnimado::render(dmat4 const& modelViewMat)
{
	dmat4 auxMat = modelMat;

	if (mesh != nullptr) {

		
		GLdouble x = 0 + radio * cos(radians(this->angleOut));
		GLdouble y = 0 + radio * sin(radians(this->angleOut));

		
		auxMat = translate(auxMat, dvec3(x, y, 0.0));
		auxMat = rotate(auxMat, radians(this->angleIn), dvec3(0.0, 0.0, 1.0));
		//auxMat = translate(auxMat, dvec3(-this->center.x, -this->center.y, 0.0));

		uploadMvM(modelViewMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		modelMat = auxMat;
	}
}

void TrianguloAnimado::update()
{
	this->angleOut += 1;
	this->angleIn += 3;
}

//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	this->angleZ = 90;
	this->angleY = 90;
	mesh = Mesh::generaEstrella3D(re, np, h);
}

void Estrella3D::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxMat = modelMat;
		modelMat = auxMat;

		modelMat = rotate(modelMat, radians(this->angleY), dvec3(0.0, 1.0, 0.0));; // rota sobre eje Y
		modelMat = rotate(modelMat, radians(this->angleZ), dvec3(0.0, 0.0, 1.0));; // rota sobre eje Y

		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat
		mesh->render();

		modelMat = rotate(modelMat, radians(180.0), dvec3(0.0, 1.0, 0.0));; // matP1 posiciona a P1 con respecto a P0
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat * matP1
		mesh->render();

		modelMat = auxMat;
	}
}

void Estrella3D::update()
{
	this->angleY += 1;
	this->angleZ += 3;
}

//-------------------------------------------------------------------------

Cubo::Cubo(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaCubo(w, h);
}

void Cubo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(1.0, 1.0, 1.0);
		mesh->render();
		glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);

		modelMat = auxMat;
	}
}

void Cubo::update()
{
}

//-------------------------------------------------------------------------

CuboRGB::CuboRGB(GLdouble w, GLdouble h, dvec4 cc)
{
	mesh = Mesh::generaCuboRGB(w, h, cc);
	c = cc;
}

void CuboRGB::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);
		mesh->render();

		modelMat = auxMat;
	}
}

void CuboRGB::update()
{
}

//-------------------------------------------------------------------------

Caja::Caja(GLdouble w, GLdouble h)
{
	this->w = w;
	mesh = Mesh::generaCubo(w, h);
	meshP0 = Mesh::generaRectangulo(w, w);
}

void Caja::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr && meshP0 != nullptr) {
		
		dmat4 auxMat = modelMat;
		modelMat = auxMat;
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat
		mesh->render();
		modelMat = rotate(modelMat, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		modelMat = translate(modelMat,dvec3(0, 0, w/2)); //USAR WIDTH/2
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat * matP1
		meshP0->render();
		//modelMat = rotate(modelMat, radians(-90.0), dvec3(1.0, 0.0, 0.0));

		modelMat = auxMat;
	}
}

void Caja::update()
{
}

//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	textura.load("..\\Bmps\\Zelda.bmp");
}

void Suelo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		auxMat = rotate(auxMat, radians(-90.0), dvec3(1.0, 0.0, 0.0));
		uploadMvM(modelViewMat);
		textura.bind();
		mesh->render();
		textura.unbind();

		modelMat = auxMat;
	}
}

void Suelo::update()
{
}

//-------------------------------------------------------------------------

Foto::Foto(GLdouble w, GLdouble h)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
	textura.loadColorBuffer();
}

void Foto::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		textura.bind();
		mesh->render();
		textura.unbind();
	}
}

void Foto::update()
{
	textura.loadColorBuffer();
}

//-------------------------------------------------------------------------

Estrella3DTex::Estrella3DTex(GLdouble r, GLdouble nL, GLdouble h)
{
	mesh = Mesh::generaEstrellaTexCor(r, nL, h);
	textura.load("..\\Bmps\\picos.bmp");
}

void Estrella3DTex::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {

		dmat4 auxMat = modelMat;
		modelMat = auxMat;

		modelMat = rotate(modelMat, radians(this->angleY), dvec3(0.0, 1.0, 0.0));; // rota sobre eje Y
		modelMat = rotate(modelMat, radians(this->angleZ), dvec3(0.0, 0.0, 1.0));; // rota sobre eje Y

		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat
		textura.bind();
		mesh->render();
		textura.unbind();

		modelMat = rotate(modelMat, radians(180.0), dvec3(0.0, 1.0, 0.0));; // matP1 posiciona a P1 con respecto a P0
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat * matP1
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

//-------------------------------------------------------------------------

CajaTex::CajaTex(GLdouble l)
{
	this->width = l;
	meshP0 = Mesh::generaCajaTexCor(l);
	mesh = Mesh::generaRectanguloTex(l, l);
	texturaOut.load("..\\Bmps\\container2.bmp");
	texturaIn.load("..\\Bmps\\container.bmp");
	texturaDown.load("..\\Bmps\\baldosa1.bmp");
	
}

void CajaTex::render(dmat4 const& modelViewMat)
{
	if (meshP0 != nullptr && mesh != nullptr) {

		glEnable(GL_CULL_FACE);

		dmat4 auxMat = modelMat;
		modelMat = auxMat;
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat

		texturaOut.bind();
		meshP0->render();
		texturaOut.unbind();
		glCullFace(GL_FRONT);
		texturaIn.bind();
		meshP0->render();
		texturaIn.unbind();
		glCullFace(GL_BACK);

		modelMat = rotate(modelMat, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		modelMat = translate(modelMat, dvec3(0, 0, width / 2)); //USAR WIDTH/2
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat * matP1

		texturaDown.bind();
		mesh->render();
		texturaDown.unbind();
		glCullFace(GL_FRONT);
		texturaDown.bind();
		mesh->render();
		texturaDown.unbind();
		glCullFace(GL_BACK);

		modelMat = auxMat;

		glDisable(GL_CULL_FACE);
	}
}

void CajaTex::update()
{
}

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
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Tablero::Tablero(GLdouble w, GLdouble h, GLdouble angle, GLdouble margin)
{
	mesh = Mesh::generaCuboRGB(w, h, dvec4(0.0, 0.0, 0.0, 1.0));
	this->length = w;
	this->angle = angle;
	this->margin = margin;
}

void Tablero::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		modelMat = rotate(modelMat, radians(this->angle), dvec3(0.0, 0.0, 1.0));
		modelMat = translate(modelMat, dvec3(this->length, 0.0, margin));
		modelMat = scale(modelMat, dvec3(2.0, 0.2, 0.02));
		uploadMvM(modelViewMat);


		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		mesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glLineWidth(1);

		modelMat = auxMat;
	}
}

void Tablero::update()
{
	this->angle += 1.0;
}

//-------------------------------------------------------------------------

Cangilon::Cangilon(GLdouble l, GLdouble angle):CajaTex(l)
{	
	this->angle = angle;
}

void Cangilon::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr && meshP0!= nullptr) {
		dmat4 auxMat = modelMat;
		GLdouble x = 2 * this->width * cos(radians(this->angle));
		GLdouble y = 2 * this->width * sin(radians(this->angle));
		modelMat = translate(modelMat, dvec3(x, y, 0.0));
		uploadMvM(modelViewMat);

		CajaTex::render(modelViewMat);

		modelMat = auxMat;
	}
}

void Cangilon::update()
{
	this->angle += 1.0;
}

//-------------------------------------------------------------------------

Sphere::Sphere(GLdouble rr, Material* matt) {
	r = rr;
	mat = matt;
}

void Sphere::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	glDisable(GL_COLOR_MATERIAL);
	// Fijar el color con glColor3f(...);

	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);
	
	this->mat->upload();

	gluSphere(q, r, 50, 50);

	gluQuadricDrawStyle(q, GLU_FILL);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1.0, 1.0, 1.0);
}

void Sphere::update()
{
}

//-------------------------------------------------------------------------

Cylinder::Cylinder(GLdouble rr1, GLdouble rr2, GLdouble hh, fvec3 cc) {
	r1 = rr1;
	r2 = rr2;
	h = hh;
	c = cc;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	// Fijar el color con glColor3f(...);
	glColor3f(c[0], c[1], c[2]);
	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	//gluQuadricDrawStyle(q, GLU_LINE);

	gluCylinder(q, r1, r2, h, 50, 50);

	gluQuadricDrawStyle(q, GLU_FILL);
	glColor3f(1.0, 1.0, 1.0);
}

void Cylinder::update()
{
}

//-------------------------------------------------------------------------

Disk::Disk(GLdouble rr1, GLdouble rr2) {
	r1 = rr1;
	r2 = rr2;
}

void Disk::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	// Fijar el color con glColor3f(...);
	glColor3f(0.0, 0.0, 0.0);
	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	gluQuadricDrawStyle(q, GLU_LINE);

	gluDisk(q, r1, r2, 50, 50);

	gluQuadricDrawStyle(q, GLU_FILL);
	glColor3f(1.0, 1.0, 1.0);
}

void Disk::update()
{
}

//-------------------------------------------------------------------------

PartialDisk::PartialDisk(GLdouble rr1, GLdouble rr2, GLdouble inii, GLdouble finn)
{
	r1 = rr1;
	r2 = rr2;
	ini = inii;
	fin = finn;
}

void PartialDisk::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat);
	// Fijar el color con glColor3f(...);
	glColor3f(0.0, 0.0, 0.0);
	// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
	gluQuadricDrawStyle(q, GLU_LINE);

	gluPartialDisk(q, r1, r2, 50, 50, ini, fin);

	gluQuadricDrawStyle(q, GLU_FILL);
	glColor3f(1.0, 1.0, 1.0);
}

void PartialDisk::update()
{
}

//-------------------------------------------------------------------------

Rotor::Rotor(GLdouble rr, GLdouble ww, bool spinn, dvec4 cc)
{
	mesh = Mesh::generaRectanguloRGB(2*rr, ww, dvec4(0.0, 0.0, 0.0, 1.0));
	r = rr;
	w = ww;
	angle = 0.0;
	spin = spinn;
	c = cc;
}

void Rotor::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;

		modelMat = translate(modelMat, dvec3(0.0, 0.0, -w/2));

		uploadMvM(modelViewMat);
		glColor3f(c[0], c[1], c[2]);
		gluQuadricDrawStyle(q, GLU_LINE);
		gluCylinder(q, r, r, w, 50, 50);
		glColor3f(1.0, 1.0, 1.0);

		modelMat = translate(modelMat, dvec3(0.0, 0.0, w/2));
		modelMat = rotate(modelMat, radians(this->angle), dvec3(0.0, 0.0, 1.0));
		modelMat = rotate(modelMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
		uploadMvM(modelViewMat);

		glLineWidth(2);
		mesh->render();
		glLineWidth(1);

		modelMat = auxMat;
	}
}

void Rotor::update()
{
	if (!spin)
		angle += 80;
	else
		angle -= 80;
}

//-------------------------------------------------------------------------

Chasis::Chasis(GLdouble ww, GLdouble hh, glm::dvec4 cc) :CuboRGB(ww, hh, cc)
{
	meshP0 = Mesh::generaRectanguloRGB(ww, ww, cc);
	meshP1 = Mesh::generaRectanguloRGB(ww, ww, cc);
	w = ww;
	h = hh;
	c = cc;
}

void Chasis::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr && meshP0 != nullptr) {

		dmat4 auxMat = modelMat;
		modelMat = auxMat;
		uploadMvM(modelViewMat);

		mesh->render();
		
		modelMat = translate(modelMat, dvec3(0.0, h/2, 0.0)); //USAR WIDTH/2
		modelMat = rotate(modelMat, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat * matP1
		meshP0->render();

		modelMat = translate(modelMat, dvec3(0.0, 0.0, h)); //USAR WIDTH/2
		uploadMvM(modelViewMat); // envía a la GPU modelViewMat * modelMat * matP1
		meshP1->render();

		modelMat = auxMat;
	}
}

void Chasis::update()
{
}

//-------------------------------------------------------------------------

Dron::Dron(GLdouble ww, GLdouble hh, dvec4 color) :Chasis(ww, hh, color)
{
	r1 = new Rotor(ww / 4, hh / 2, true, dvec4(0.0, 1.0, 0.0, 1.0));
	r2 = new Rotor(ww / 4, hh / 2, false, dvec4(0.0, 1.0, 0.0, 1.0));
	r3 = new Rotor(ww / 4, hh / 2, true, dvec4(1.0, 0.0, 0.0, 1.0));
	r4 = new Rotor(ww / 4, hh / 2, false, dvec4(1.0, 0.0, 0.0, 1.0));
}

void Dron::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr && meshP0 != nullptr && meshP1 != nullptr) {
		dmat4 auxMat = modelMat;
		modelMat = auxMat;
		uploadMvM(modelViewMat);

		Chasis::render(modelViewMat);

		dmat4 m = dmat4(1.0);
		m = translate(m, dvec3(-w/2, 0.75*h, -w/2)); //USAR WIDTH/2
		m = rotate(m, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		r1->render(modelViewMat*m);

		m = dmat4(1.0);
		m = translate(m, dvec3(-w / 2, 0.75*h, w / 2)); //USAR WIDTH/2
		m = rotate(m, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		r2->render(modelViewMat*m);

		m = dmat4(1.0);
		m = translate(m, dvec3(w / 2, 0.75*h, w / 2)); //USAR WIDTH/2
		m = rotate(m, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		r3->render(modelViewMat*m);

		m = dmat4(1.0);
		m = translate(m, dvec3(w / 2, 0.75*h, -w / 2)); //USAR WIDTH/2
		m = rotate(m, radians(90.0), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		r4->render(modelViewMat*m);

		modelMat = auxMat;
	}
}

void Dron::update()
{
	r1->update();
	r2->update();
	r3->update();
	r4->update();
}

//-------------------------------------------------------------------------

Cone::Cone(GLdouble h, GLdouble r) {
	int m = 3; // m=número de puntos del perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.0, h, 0.0);
	this->mesh = new MBR(m, 50, perfil);
}

void Cone::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(0.0, 0.0, 1.0);
		mesh->render();
		glColor3d(1.0, 1.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);

		modelMat = auxMat;
	}
}

void Cone::update()
{
}

//-------------------------------------------------------------------------

SphereRV::SphereRV(int paralelos, int meridianos, GLdouble r, Material* matt)
{
	dvec3* perfil = new dvec3[paralelos];

	GLdouble incrAng = 180.0 / (paralelos-1);
	GLdouble angIni = 270.0;
	GLdouble x = 0.0;
	GLdouble y = 0.0;

	mat = matt;

	for (int i = 0; i < paralelos; i++) {
		x = 0.0 + r * cos(radians(angIni + incrAng * i));
		y = 0.0 + r * sin(radians(angIni + incrAng * i));
		perfil[i] = dvec3(x, y, 0.0);
	}

	this->mesh = new MBR(paralelos, meridianos, perfil);
}

void SphereRV::render(glm::dmat4 const & modelViewMat) 
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);

		glDisable(GL_COLOR_MATERIAL);
		// Fijar el color con glColor3f(...);

		// Fijar el modo en que se dibuja la entidad con gluQuadricDrawStyle(q, ...);
		//gluQuadricDrawStyle(q, GLU_LINE);

		this->mat->upload();

		//if (color != fvec3(-1.0, -1.0, -1.0)) glColor3f(color[0], color[1], color[2]);
		//else glColor3f(0.2, 0.4, 0.6);

		mesh->render();

		glEnable(GL_COLOR_MATERIAL);
		//glColor3f(1.0, 1.0, 1.0);

		modelMat = auxMat;
	}
}

void SphereRV::update()
{
}

//-------------------------------------------------------------------------

Satelite::Satelite(int paralelos, int meridianos, GLdouble rr) : SphereRV(paralelos, meridianos, rr, new Material())
{
	dron = new Dron(200.0, 25.0, dvec4(0.0, 0.0, 1.0, 1.0));
	r = rr + 3;
	angleY = 0.0;
	angleX = 45.0;
}

void Satelite::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);

		SphereRV::render(modelViewMat);

		dmat4 m = dmat4(1.0);
		m = rotate(m, radians(angleX), dvec3(0.0, 1.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		m = rotate(m, radians(angleY), dvec3(1.0, 0.0, 0.0)); // matP1 posiciona a P1 con respecto a P0
		m = translate(m, dvec3(0.0, r+10, 0));
		m = scale(m, dvec3(0.2, 0.2, 0.2));
		dron->render(modelViewMat*m);

		modelMat = auxMat;
	}
}

void Satelite::update()
{
	//angle += 1.0;
	//dron->update();
}

void Satelite::orbitate(int move)
{
	switch (move) {
	case(0):				// DERECHA
		angleX += 2.0;
		break;
	case(1):				// IZQUIERDA
		angleX -= 2.0;
		break;
	case(2):				// ARRIBA
		angleY -= 2.0;
		break;
	case(3):				// ABAJO
		angleY += 2.0;
		break;
	default:	
		break;
	}

	dron->update();
}

//-------------------------------------------------------------------------

Enjambre::Enjambre(GLdouble w, GLdouble h, dvec4 color) : Dron(w, h, color)	//Multidron
{
	d1 = new Dron(w / 4, h / 2, color);
	d2 = new Dron(w / 4, h / 2, color);
	d3 = new Dron(w / 4, h / 2, color);
	d4 = new Dron(w / 4, h / 2, color);
}

void Enjambre::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);

		Dron::render(modelViewMat);

		dmat4 m = dmat4(1.0);
		m = translate(m, dvec3(-w / 2, 2*h, -w / 2)); //USAR WIDTH/2
		d1->render(modelViewMat*m);

		m = dmat4(1.0);
		m = translate(m, dvec3(-w / 2, 2*h, w / 2)); //USAR WIDTH/2
		d2->render(modelViewMat*m);

		m = dmat4(1.0);
		m = translate(m, dvec3(w / 2, 2*h, w / 2)); //USAR WIDTH/2
		d3->render(modelViewMat*m);

		m = dmat4(1.0);
		m = translate(m, dvec3(w / 2, 2*h, -w / 2)); //USAR WIDTH/2
		d4->render(modelViewMat*m);

		modelMat = auxMat;
	}
}

void Enjambre::update()
{
	d1->update();
	d2->update();
	d3->update();
	d4->update();
	Dron::update();
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

void CompoundEntity::render(glm::dmat4 const & modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
	for (Entity* it : grObjects) {
		it->render(aMat);
	}
}

void CompoundEntity::update() {
	for (Entity* it : grObjects) {
		it->update();
	}
}

//-------------------------------------------------------------------------

Aspa::Aspa(GLdouble ww, GLdouble hh, bool spinn, glm::dvec4 cc) : RectanguloRGB(ww, hh, cc)
{
	mesh = Mesh::generaRectanguloRGB(ww, hh, cc);
	spin = spinn;
	angle = 0.0;

}

void Aspa::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);

		modelMat = rotate(modelMat, radians(this->angle), dvec3(0.0, 0.0, 1.0));
		modelMat = rotate(modelMat, radians(90.0), dvec3(1.0, 0.0, 0.0));
		uploadMvM(modelViewMat);
		mesh->render();

		modelMat = auxMat;
	}
}

void Aspa::update()
{
	if (!spin)
		angle += 20;
	else
		angle -= 20;
}

//-------------------------------------------------------------------------

RotorCompound::RotorCompound(GLdouble rr, GLdouble ww, bool spinn, glm::dvec4 cc)
{
	Entity *aspa = new Aspa(2 * rr, ww, spinn, dvec4(0.0, 0.0, 0.0, 1.0));
	Entity *cilindro = new Cylinder(rr, rr, ww, cc);
	w = ww;
	c = cc;

	cilindro->setModelMat(translate(cilindro->getModelMat(), dvec3(0, 0, -w / 2)));

	grObjects.push_back(aspa);
	grObjects.push_back(cilindro);
}

//-------------------------------------------------------------------------

DronCompound::DronCompound(GLdouble ww, GLdouble hh, dvec4 color)
{
	Entity *r1 = new RotorCompound(ww / 4, hh / 2, true, dvec4(0.0, 1.0, 0.0, 1.0));
	Entity *r2 = new RotorCompound(ww / 4, hh / 2, false, dvec4(0.0, 1.0, 0.0, 1.0));
	Entity *r3 = new RotorCompound(ww / 4, hh / 2, true, dvec4(1.0, 0.0, 0.0, 1.0));
	Entity *r4 = new RotorCompound(ww / 4, hh / 2, false, dvec4(1.0, 0.0, 0.0, 1.0));
	Entity *c = new Chasis(ww, hh, color);
	w = ww;
	h = hh;

	r1->setModelMat(translate(r1->getModelMat(), dvec3(-w / 2, 0.75*h, -w / 2)));
	r1->setModelMat(rotate(r1->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	r2->setModelMat(translate(r2->getModelMat(), dvec3(-w / 2, 0.75*h, w / 2)));
	r2->setModelMat(rotate(r2->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	r3->setModelMat(translate(r3->getModelMat(), dvec3(w / 2, 0.75*h, w / 2)));
	r3->setModelMat(rotate(r3->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	r4->setModelMat(translate(r4->getModelMat(), dvec3(w / 2, 0.75*h, -w / 2)));
	r4->setModelMat(rotate(r4->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	grObjects.push_back(r1);
	grObjects.push_back(r2);
	grObjects.push_back(r3);
	grObjects.push_back(r4);
	grObjects.push_back(c);
}

//-------------------------------------------------------------------------

SateliteMat::SateliteMat(int paralelos, int meridianos, GLdouble rr, Material * matt)
{
	esfera = new SphereRV(paralelos, meridianos, rr, matt);
	dron = new DronCompoundLight(200.0, 25.0, dvec4(0.0, 0.0, 1.0, 1.0));

	r = rr + 50;
	angleX = 0.0;
	angleY = 45.0;
	//light = lightt;

	dron->setModelMat(rotate(dron->getModelMat(), radians(angleY), dvec3(0.0, 1.0, 0.0)));
	dron->setModelMat(rotate(dron->getModelMat(), radians(angleX), dvec3(1.0, 0.0, 0.0)));
	dron->setModelMat(translate(dron->getModelMat(), dvec3(0.0, r, 0)));
	dron->setModelMat(scale(dron->getModelMat(), dvec3(0.2, 0.2, 0.2)));

	grObjects.push_back(esfera);
	grObjects.push_back(dron);
}

void SateliteMat::orbitate(int move)
{
	GLdouble radio = 0.0;
	switch (move) {
	case(0):				// DERECHA
		angleY += 2.0;
		break;
	case(1):				// IZQUIERDA
		angleY -= 2.0;
		break;
	case(2):				// ARRIBA
		angleX -= 2.0;
		break;
	case(3):				// ABAJO
		angleX += 2.0;
		break;
	default:
		break;
	}

	dmat4 i = dmat4(1.0);
	i = rotate(i, radians(angleY), dvec3(0.0, 1.0, 0.0));
	i = rotate(i, radians(angleX), dvec3(1.0, 0.0, 0.0));
	i = translate(i, dvec3(0.0, r , 0));
	i = scale(i, dvec3(0.2, 0.2, 0.2));
	dron->setModelMat(i);
}

//-------------------------------------------------------------------------

DronCompoundLight::DronCompoundLight(GLdouble ww, GLdouble hh, glm::dvec4 color)
{
	r1 = new RotorCompound(ww / 4, hh / 2, true, dvec4(0.0, 1.0, 0.0, 1.0));
	r2 = new RotorCompound(ww / 4, hh / 2, false, dvec4(0.0, 1.0, 0.0, 1.0));
	r3 = new RotorCompound(ww / 4, hh / 2, true, dvec4(1.0, 0.0, 0.0, 1.0));
	r4 = new RotorCompound(ww / 4, hh / 2, false, dvec4(1.0, 0.0, 0.0, 1.0));
	ch = new Chasis(ww, hh, color);
	w = ww;
	h = hh;
	
	light = new SpotLight();
	light->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	light->setDiff(glm::fvec4(1.0, 1.0, 1.0, 1.0));
	light->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	light->setSpot(fvec3(0.0, 0.0, -1.0), 120, 0.0);
	glEnable(light->getId());

	r1->setModelMat(translate(r1->getModelMat(), dvec3(-w / 2, 0.75*h, -w / 2)));
	r1->setModelMat(rotate(r1->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	r2->setModelMat(translate(r2->getModelMat(), dvec3(-w / 2, 0.75*h, w / 2)));
	r2->setModelMat(rotate(r2->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	r3->setModelMat(translate(r3->getModelMat(), dvec3(w / 2, 0.75*h, w / 2)));
	r3->setModelMat(rotate(r3->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	r4->setModelMat(translate(r4->getModelMat(), dvec3(w / 2, 0.75*h, -w / 2)));
	r4->setModelMat(rotate(r4->getModelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));

	grObjects.push_back(r1);
	grObjects.push_back(r2);
	grObjects.push_back(r3);
	grObjects.push_back(r4);
	grObjects.push_back(ch);
}

void DronCompoundLight::render(glm::dmat4 const & modelViewMat)
{
	dmat4 aMat = modelViewMat * modelMat;
	light->upload(aMat);
	CompoundEntity::render(modelViewMat);
}
