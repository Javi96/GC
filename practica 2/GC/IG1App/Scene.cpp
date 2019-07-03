#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

GLuint last_update_tick = 0;

//-------------------------------------------------------------------------

void Scene::init1()
{ // OpenGL basic setting
	glClearColor(0.7, 0.8, 0.9, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // enable textures

	// lights
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL); // Se activa el registro de color
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE);

	GLfloat amb0[] = { 0.0, 0.0, 0.0, 1.0 };				// Luz de ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb0);
	
	/*GLfloat local_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, local_ambient);*/

	dirL = new DirLight();									// Luz direccional
	dirL->setAmb(fvec4(0.2, 0.2, 0.2, 1.0));
	dirL->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	dirL->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	dirL->setPosDir(fvec3(1.0, 1.0, 0.0));
	luces.push_back(dirL);
	//glEnable(dirL->getId());

	spot = new SpotLight();									// Luz foco
	spot->setAmb(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	spot->setDiff(glm::fvec4(0.4, 0.8, 0.0, 1.0));
	spot->setSpec(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	spot->setSpot(fvec3(0.0, 0.0, -1.0), 7.5, 0.0);
	luces.push_back(spot);
	//glEnable(spot->getId());

	// lights
	// textures  
	// meshes

	// Graphics objects (entities) of the scene
	grObjects.push_back(new EjesRGB(dvec2(0.0, 0.0), 400));
	Material* mat = new Material();
	mat->setGold();
	
	//grObjects.push_back(new SphereRV(64, 64, 200, mat));
	movable = new SateliteMat(64, 64, 275, mat);
	grObjects.push_back(movable);
}

void Scene::init2()
{ // OpenGL basic setting
	glClearColor(0.7, 0.8, 0.9, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);  // enable textures

	// lights
	// textures  
	// meshes

	grObjects.push_back(new EjesRGB(dvec2(0.0, 0.0), 200));
}

Scene::~Scene()
{ // free memory and resources   

	for (Entity* el : grObjects)
	{
		delete el;
	}

	for (Light* luz : luces) {
		delete luz;
	}
}

void Scene::move(int dir)
{
	movable->orbitate(dir);
}


void Scene::render(glm::dmat4 const & modelViewMat)
{
	dirL->upload(modelViewMat);
	spot->upload(dmat4(1.0));

	CompoundEntity::render(modelViewMat);
}
