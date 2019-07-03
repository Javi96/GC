#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

GLuint last_update_tick = 0;

//-------------------------------------------------------------------------

/*void Scene::init()
{ // OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // enable textures

	// lights
	// textures  
	// meshes

	// Graphics objects (entities) of the scene
	grObjects.push_back(new EjesRGB(dvec2(0.0, 0.0), 200));
	grObjects.push_back(new Diamante(75.0, 200.0, 8));

	int x, z;

	x = 0.0 + 300 * cos(radians(90.0));
	z = 0.0 + 300 * sin(radians(90.0));
	Entity * tri1 = new Piramide(75.0, 100.0, 4);
	tri1->setModelMat(translate(tri1->getModelMat(), dvec3(x, 0.0, z)));
	grObjects.push_back(tri1);

	x = 0.0 + 300 * cos(radians(210.0));
	z = 0.0 + 300 * sin(radians(210.0));
	Entity * tri2 = new Piramide(75.0, 100.0, 4);
	tri2->setModelMat(translate(tri2->getModelMat(), dvec3(x, 0.0, z)));
	grObjects.push_back(tri2);

	x = 0.0 + 300 * cos(radians(330.0));
	z = 0.0 + 300 * sin(radians(330.0));
	Entity * tri3 = new Piramide(75.0, 100.0, 4);
	tri3->setModelMat(translate(tri3->getModelMat(), dvec3(x, 0.0, z)));
	grObjects.push_back(tri3);
	
	Entity * ent = new Cubo(50.0, 50.0);
	ent->setModelMat(scale(ent->getModelMat(), dvec3(2.0, 2.0, 2.0)));
	grObjects.push_back(ent);

	ent = new Cubo(50.0, 50.0);
	ent->setModelMat(scale(ent->getModelMat(), dvec3(3.0, 3.0, 3.0)));
	grObjects.push_back(ent);

	ent = new Cubo(50.0, 50.0);
	ent->setModelMat(scale(ent->getModelMat(), dvec3(4.0, 4.0, 4.0)));
	grObjects.push_back(ent);

	ent = new Cubo(50.0, 50.0);
	ent->setModelMat(scale(ent->getModelMat(), dvec3(5.0, 5.0, 5.0)));
	grObjects.push_back(ent);
}*/
//-------------------------------------------------------------------------

void Scene::init(int scene)
{ // OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // enable textures

	switch (scene) {
	case 0:
		grObjects.push_back(new EjesRGB(dvec2(0.0, 0.0), 200));
		grObjects.push_back(new Poliespiral(dvec2(-200.0, -150.0), 0.0, 160.0, 1.0, 1.0, 50));
		grObjects.push_back(new Poliespiral(dvec2(-100.0, -150.0), 0.0, 72.0, 30.0, 0.001, 6));
		grObjects.push_back(new Poliespiral(dvec2(0.0, -150.0), 0.0, 60.0, 0.5, 0.5, 100));
		grObjects.push_back(new Poliespiral(dvec2(100.0, -150.0), 0.0, 89.5, 0.5, 0.5, 100));
		grObjects.push_back(new Poliespiral(dvec2(200.0, -150.0), 0.0, 45, 1.0, 1.0, 50));
		grObjects.push_back(new Dragon(6000));
		grObjects.push_back(new TrianguloRGB(50));
		grObjects.push_back(new Rectangulo(200.0, 100.0));
		grObjects.push_back(new TrianguloAnimado(50, 90.0, 100.0));
		break;
	case 1:
		grObjects.push_back(new EjesRGB(dvec2(0.0, 0.0), 200));
		Entity * caja = new CajaTex(100.0);
		caja->setModelMat(translate(caja->getModelMat(), dvec3(-50.0, 52.0, -50.0)));
		Entity * estrella = new Estrella3DTex(50, 4.0, 100.0);
		estrella->setModelMat(translate(estrella->getModelMat(), dvec3(-50.0, 300.0, -50.0)));
		Entity * suelo = new Suelo(800.0, 600.0);
		Entity * foto = new Foto(600.0, 400.0);
		foto->setModelMat(translate(foto->getModelMat(), dvec3(300.0, 300.0, -250.0)));
		grObjects.push_back(caja);
		grObjects.push_back(estrella);
		grObjects.push_back(suelo);
		grObjects.push_back(foto);
		break;
	}
}
Scene::~Scene()
{ // free memory and resources   

	for (Entity* el : grObjects)
	{
		delete el;
	}
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* entity : grObjects)
	{
		entity->render(cam);
	}
}
//-------------------------------------------------------------------------

void Scene::update() {
	for (Entity* entity : grObjects) {
		entity->update();
	}
}
//-------------------------------------------------------------------------

void Scene::update(GLuint timeElapsed) {
	if (timeElapsed - last_update_tick > 25) {
		for (Entity* entity : grObjects) {
			entity->update();
		}
		last_update_tick = timeElapsed;
	}
}
