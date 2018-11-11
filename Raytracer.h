#pragma once
#ifndef	_RAYTRACER_H_
#define _RAYTRACER_H_
#include <vector>
#include "MCG_GFX_Lib.h"
//#include "Sphere.h"
//#include "Camera.h"
#include <cmath>
#include <iostream>


struct Object
{	
	
	Object(float _radius, glm::vec3 _position, glm::vec3 _colour, bool _mirror);
	Object(float _radius, glm::vec3 _position, glm::vec3 _colour);
	Object(float _xLength, float _yLength, glm::vec3 _position, glm::vec3 _colour);
	Object();
	~Object() {};
	float m_radius;
	glm::vec3 m_centre;
	glm::vec3 m_colour;
	bool m_static = false;
	int m_type;
	float m_xLength, m_yLength;
	bool m_shadow = false;
	bool m_mirror;
};



struct Ray
{
	Ray(glm::vec3 _origin, glm::vec3 _end, glm::vec3 _direction);
	~Ray() {};
	//Ray(bool _shadowRay, glm::vec3 _origin, glm::vec3 _end, glm::vec3 _direction);
	glm::vec3 m_direction = glm::vec3(0, 0, 0);
	glm::vec3 m_origin = glm::vec3(0, 0, 0);
	glm::vec3 m_end = glm::vec3(0, 0, 0);
	bool m_hit = false;
	glm::vec3 m_firstIntersectionPoint;
	glm::vec4 m_origin4;
	glm::vec4 m_end4;
	glm::vec3 m_normal;
	glm::vec3 m_colour;
	bool m_shadowCast = false;
	float m_depth = INFINITY;

	glm::vec3 normalise(glm::vec3 _point, Object *_object);


};

class RayTracer
{
public:
	glm::vec3 shade(Ray &_ray, Object &_light);
	glm::vec3 traceRay(Ray &_ray, std::vector<Object*>_object, Object &_light);
	void intersection(Ray &_ray, std::vector<Object*>_object, Object &_light);

};




#endif