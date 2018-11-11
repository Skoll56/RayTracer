#pragma once
#pragma once
#ifndef	_SPHERE_H_
#define _SPHERE_H_

#include "MCG_GFX_Lib.h"
//#include "Camera.h"
#include <cmath>
#include <iostream>
//#include "Raytracer.h"

class Sphere 
{
public:

	float m_radius = 5.0f;
	glm::vec3 m_centre = glm::vec3(0, 0, -80);


};

#endif