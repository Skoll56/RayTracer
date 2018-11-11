#include "Camera.h"
#include "Raytracer.h"
#include <cmath>
#include <iostream>
//#include "Sphere.h"
#include "MCG_GFX_Lib.h"

Ray Camera::generateRay(glm::vec2 _coords, glm::ivec2 _windowSize)
{
	glm::vec4 origin4, end4;
	glm::vec3 origin, end, direction;
	_coords.y = -1.0f + (1.0f - -1.0f) * ((_coords.y) / (_windowSize.y));  //Making the co-ordinates NDC (Between -1 to 1)
	_coords.x = -1.0f + (1.0f - -1.0f) * ((_coords.x) / (_windowSize.x));

	origin4 = (glm::vec4(_coords.x, _coords.y, -1, 1));
	end4 = (glm::vec4(_coords.x, _coords.y, 1, 1));
	origin4 = (inverseProjection * origin4);
	end4 = (inverseProjection * end4);

	origin4 = (origin4 / origin4.w);
	end4 = (end4 / end4.w);

	origin = (glm::vec3(origin4.x, origin4.y, origin4.z));
	end = (glm::vec3(end4.x, end4.y, end4.z));
	direction = (glm::normalize(end - origin));

	Ray ray(origin, end, direction);

	return ray;
}

Camera::Camera() /// The code in this function has been adapted from the OpenGL tutorial on Matrices.
{
	float aspectRatio = 640.0f / 480.0f;
	projection = glm::mat4(glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f));  
	inverseProjection = glm::inverse(projection);
	//view = glm::mat4(1.0f);
	//inverseView = glm::inverse(view);
} 