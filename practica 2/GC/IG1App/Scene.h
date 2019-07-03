//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Light.h"
#include <vector>

//-------------------------------------------------------------------------

class Scene : public CompoundEntity
{ 
public:
    Scene() { };
	~Scene();
    void init1(); 
	void init2();
	void move(int dir);
	void render(glm::dmat4 const& modelViewMat);
	  
protected:
	SateliteMat* movable;
	DirLight* dirL;
	SpotLight* spot;
	std::vector<Light*> luces;
	// 2 Spotlight y 1 DirLight

};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

