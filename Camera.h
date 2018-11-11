#pragma once
#ifndef	_CAMERA_H_
#define _CAMERA_H_
#include "MCG_GFX_Lib.h"
#include "Raytracer.h"
#include <cmath>
#include <iostream>
//#include "Sphere.h"

class Camera
{

private:
	//Position in Worldspace, facing the origin, rotated in the 'up' direction (not upside down)
	glm::mat4 view;
	glm::mat4 projection; //(Field of view, aspect ratio, near and far ranges)
	glm::mat4 inverseProjection;
	//glm::mat4 inverseView;

public:	
	Camera();
	~Camera() {};
	//Reference OpenGL tutorial for the matrix code

	Ray generateRay(glm::vec2 _coords, glm::ivec2 _windowSize);

};

#endif