//#include "Camera.h"
//#include "Sphere.h"
#include "Raytracer.h"
#include <cmath>
#include <iostream>
#include "MCG_GFX_Lib.h"
//#include <vector>

glm::vec3 RayTracer::traceRay(Ray &_ray, std::vector<Object*>_object, Object &_light)
{
	RayTracer::intersection(_ray, _object, _light);
	if (_ray.m_hit == true)
	{
		return RayTracer::shade(_ray, _light);
	}

	else
	{
		return glm::vec3(0, 0, 40);
	}

}

glm::vec3 Ray::normalise(glm::vec3 _point, Object *_object) // Small function to find the normal Vector of the intersection point (Unit Vector)
{
	return (glm::normalize((_point - _object->m_centre) / _object->m_radius ));
}



void RayTracer::intersection(Ray &_ray, std::vector<Object*>_object, Object &_light)
{
	for (int i = 0; i < _object.size(); i++)
	{
		{
			glm::vec3 queryPoint = _object[i]->m_centre;
			if (glm::distance(_ray.m_origin, queryPoint) > _object[i]->m_radius) // As long as Ray Origin is outside the sphere
			{
				glm::vec3 closestPoint = _ray.m_origin + (glm::dot((queryPoint - _ray.m_origin), _ray.m_direction) * _ray.m_direction); // Finds the closest point on the Ray's line
				float distance = glm::distance(closestPoint, queryPoint); //Distance between the closest point on the line to the query point (d)
				if (distance <= _object[i]->m_radius && _ray.m_origin.z > _object[i]->m_centre.z) //If we're contacting and not behind the camera
				{
					glm::vec3 closestPointToQuery = queryPoint - closestPoint;
					float closestIntersection = sqrt((_object[i]->m_radius * _object[i]->m_radius) - (distance * distance)); //Finding the distance of the first intersection point from the centre of the sphere
					glm::vec3 firstIntersect = _ray.m_origin + ((glm::dot((queryPoint - _ray.m_origin), _ray.m_direction) - closestIntersection)* _ray.m_direction);
					float depth = glm::distance(_ray.m_origin, firstIntersect);
					if (depth < _ray.m_depth) // Only count a hit for the closest object to the camera.
					{
						_ray.m_firstIntersectionPoint = firstIntersect;
						_ray.m_hit = true; // Intersection true
						_ray.m_depth = depth;
						_ray.m_normal = (_ray.normalise(_ray.m_firstIntersectionPoint, _object[i]));
						if (_object[0]->m_static == true)	{_ray.m_colour = glm::vec3(rand() % 255, rand() % 255, rand() % 255); }
						else { _ray.m_colour = _object[i]->m_colour; }


						//Shadow or Reflection checker
						if (_object[0]->m_shadow == true) //If contacted, check if we need to draw a shadow.
						{
							
							for (int i2 = 0; i2 < _object.size(); i2++)
							{
								if (i2 != i)
								{
									glm::vec3 shadowDir = glm::normalize(firstIntersect - _light.m_centre);
									queryPoint = _object[i2]->m_centre;
									closestPoint = firstIntersect + (glm::dot((queryPoint - firstIntersect), shadowDir) * shadowDir); // Finds the closest point on the Ray's line
									
									
									float distance2 = glm::distance(closestPoint, queryPoint);
									if ( distance2 <= _object[i2]->m_radius) //If we're contacting another shape between the light source and the initial contact point
									{
										closestPointToQuery = queryPoint - closestPoint;
										closestIntersection = sqrt((_object[i2]->m_radius * _object[i2]->m_radius) - (distance2 * distance2)); //Finding the distance of the first intersection point from the centre of the sphere
										glm::vec3 firstIntersect2 = firstIntersect + ((glm::dot((queryPoint - firstIntersect), shadowDir) - closestIntersection)* shadowDir);
										float test1 = glm::distance(firstIntersect, _light.m_centre);
										float test2 = glm::distance(firstIntersect2, _light.m_centre);
										if (test1 > test2 && _ray.m_shadowCast == false) // If the object is between the light source and the contact point, and a shadow isn't already there.
										{
											glm::vec3 shadowColour;
											if (_object[i]->m_mirror == true)
											{
												shadowColour = _object[i2]->m_colour;
											}
											else
											{
												shadowColour = glm::vec3(_ray.m_colour.x / 5, _ray.m_colour.y / 5, _ray.m_colour.z / 5);
											}
											_ray.m_colour = shadowColour;
											_ray.m_shadowCast = true; //Stop the program drawing another shadow on the same pixel
										}
									}
								}
							}

						}
					}
				}
			}
		}
	}
}


glm::vec3 RayTracer::shade(Ray &_ray, Object &_light) /// The code in this function has been adapted from code by Marcus Mathiassen in his video "Raytracer in 30 minutes"
{
	glm::vec3 lightDir = glm::normalize(_light.m_centre - _ray.m_firstIntersectionPoint);
	float wIn = glm::dot(lightDir, _ray.m_normal);
	glm::vec3 newColour = (_ray.m_colour * wIn);
	if (newColour.x > 255) { newColour.x = 255; }
	if (newColour.y > 255) { newColour.y = 255; }
	if (newColour.z > 255) { newColour.z = 255; }
	if (newColour.x < 0) { newColour.x = 0; }
	if (newColour.y < 0) { newColour.y = 0; }
	if (newColour.z < 0) { newColour.z = 0; } 
	return newColour;
}

Ray::Ray(glm::vec3 _origin, glm::vec3 _end, glm::vec3 _direction)
{
	m_origin = _origin;
	m_end = _end;
	m_direction = _direction;
}


Object::Object(float _radius, glm::vec3 _position, glm::vec3 _colour, bool _mirror)
{
	m_type = 0; // A sphere
	m_radius = _radius;
	m_centre = _position;
	m_colour = _colour;
	m_mirror = _mirror;
}

Object::Object(float _radius, glm::vec3 _position, glm::vec3 _colour)
{
	m_type = 0; // A sphere
	m_radius = _radius;
	m_centre = _position;
	m_colour = _colour;
}

Object::Object(float _xLength, float _yLength, glm::vec3 _position, glm::vec3 _colour)
{
	m_type = 1; //A plane
	m_radius = 1000;
	m_centre = _position;
	m_colour = _colour;
	m_xLength = _xLength;
	m_yLength = _yLength;
}

Object::Object()
{
	m_radius = 1;
	m_colour = glm::vec3(255, 255, 255);
	m_centre = glm::vec3(0,0,-10);
}

