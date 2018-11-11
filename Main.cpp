#include "Camera.h"
#include "Raytracer.h"
#include <cmath>
#include <iostream>
#include "MCG_GFX_Lib.h"
#include <vector>
#include <SDL\SDL.h>
#include <stdlib.h>
#include <time.h>

glm::vec3 randCol();
std::vector<Object*> smile();
void drawCircle(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre);
void drawTriangle(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre);
void drawSquare(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre);
void drawLine(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre);
//Drawing function prototypes



int main(int argc, char *argv[])
{
	bool quit = false;
	while (quit == false)
	{
		glm::ivec2 windowSize(640, 480);
		if (!MCG::Init(windowSize))
		{
			// We must check if something went wrong
			// (this is very unlikely)
			return -1;
		}

		// Sets every pixel to the same colour
		// parameters are RGBA, numbers are from 0 to 255
		MCG::SetBackground(glm::ivec3(0, 0, 0));


		glm::ivec2 pixelPosition;
		glm::ivec3 pixelColour;
		Camera camera1;
		RayTracer tracer;
		Object light(1.0f, glm::vec3(-27.5, -27.5, -0), glm::vec3(255, 255, 255), false);
		std::vector<Object*> sphere;
		char option = 'a';
		char option2 = '¬';
		bool invalid;
		srand(time(NULL));

		do // Menu loop, so you can always re-enter the menu.
		{	
			invalid = false;
			system("cls");
			std::cout << "Pick a function for me to show off: " << std::endl;
			std::cout << "1- Boring Circle made of TV static\n2- Boring Square made of TV static\n3- Boring line\n4- Boring Triangle made of TV static" << std::endl;
			std::cout << "\nI mean, if it helps, the boring shapes move.\n" << std::endl;
			std::cout << "5- Big shiny balls with shadows! (Raytracer)\n6- 'Give me a smile' (40s load time max, worth the wait) (Raytracer)" << std::endl;
			std::cout << "7- Quit" << std::endl;
			std::cin >> option;
			std::cin.ignore(9000, '\n');
			switch (option)
			{
				case '1': {break; }
				case '2': {break; }
				case '3': {break; }
				case '4': {break; }
				case '5': 
				{
					sphere.push_back(new Object(5.0f, glm::vec3(0, -3, -50), glm::vec3(255, 0, 0), false));
					sphere.push_back(new Object(7.0f, glm::vec3(-18, -5, -70), glm::vec3(255, 0, 0), false));
					sphere.push_back(new Object(30.0f, glm::vec3(0, 0, -100), glm::vec3(255, 255, 255), false));
					sphere.push_back(new Object(2.0f, glm::vec3(10, -10, -30), glm::vec3(0, 255, 0), false));
					sphere.push_back(new Object(2.0f, glm::vec3(-7, -15, -50), glm::vec3(0, 255, 0), false));

					sphere[0]->m_shadow = true;
					std::cout << "Would you like it to look like it's made of trippy TV static ? Y= Yes, N= No" << std::endl;
					while (option2 != 'Y' && option2 != 'N')
					{
						std::cin >> option2;
						if (option2 != '¬' && option2 != 'Y' && option2 != 'N')	{ std::cout << "Invalid Input" << std::endl; }
					}

					if (option2 == 'Y') { sphere[0]->m_static = true; }
					break; 
				} // Draw three spheres with shadows

				case '6': 
				{
					sphere = smile(); // Make a smile
					//sphere[0]->m_shadow = true;  // Uncomment this to turn shadows on (Doubles Load time).
					break; 
				} 


				case '7': {quit = true; break; }
				default: 
				{
					std::cout << "Invalid Input" << std::endl;
					invalid = true; 
					SDL_Delay(5000);
					break; 
				}
			}
		} while (invalid == true);


		if (option == '6' || option == '5')
		{
			uint32_t time = SDL_GetTicks();
			for (float horizontal = 0.0f; horizontal < windowSize.x; horizontal++)
			{
				for (int vertical = 0; vertical < windowSize.y; vertical++)
				{
					glm::vec2 coords = glm::vec2(horizontal, vertical);
					pixelColour = tracer.traceRay(camera1.generateRay(coords, windowSize), sphere, light);
					pixelPosition = coords;
					MCG::DrawPixel(pixelPosition, pixelColour);
				}
				float percent = (horizontal / windowSize.x) * 100;
				std::cout << percent << "% complete" << std::endl;
			}
			std::cout << "Done. " << SDL_GetTicks() - time << " ms has passed" << std::endl;
			
		
			// Displays drawing to screen and holds until user presses escape
			while (MCG::ProcessFrame())
			{

			}

		}

		for (int i = 0; i < sphere.size(); i++)
		{
			delete sphere[i];
		}

		
		




		// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:


		// Variable to keep track of time
		float timer = 0.0f;

		// This is our game loop
		// It will run until the user presses 'escape' or closes the window

		if (option != '5' && option != '6' && option != '7')
		{
			while (MCG::ProcessFrame())
			{
				if (option != '3') { MCG::SetBackground(glm::ivec3(0, 0, 0)); }
				glm::ivec2 centre = (windowSize / 2) + (int)(sin(timer) * 100.0f);
				pixelPosition = centre;
				timer += 1.0f / 30.0f;

				if (option == '1') { drawCircle(windowSize, pixelColour, pixelPosition, centre); }
				else if (option == '2') { drawSquare(windowSize, pixelColour, pixelPosition, centre); }
				else if (option == '3') { drawLine(windowSize, pixelColour, pixelPosition, centre); }
				else if (option == '4') { drawTriangle(windowSize, pixelColour, pixelPosition, centre); }
			}
		}
		MCG::Cleanup();

	}
	return 0; 
}


void drawLine(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre)
{
	_pixelColour = glm::vec3(255, 0, 0);
	_pixelPosition = _centre;
	MCG::DrawPixel(_pixelPosition, _pixelColour);

}

std::vector<Object*> smile()
{
	std::vector<Object*> sphere;

	//Eyes
	sphere.push_back(new Object(5.0f, glm::vec3(-15, -12, -50), glm::vec3(255, 255, 255)));
	sphere.push_back(new Object(5.0f, glm::vec3(15, -12, -50), glm::vec3(255, 255, 255)));

	sphere.push_back(new Object(3.0f, glm::vec3(-14, -11.5, -47), glm::vec3(255, 0, 0)));
	sphere.push_back(new Object(3.0f, glm::vec3(14, -11.5, -47), glm::vec3(255, 0, 0)));

	sphere.push_back(new Object(1.5f, glm::vec3(-13.5, -11, -45), glm::vec3(0, 0, 0)));
	sphere.push_back(new Object(1.5f, glm::vec3(13.5, -11, -45), glm::vec3(0, 0, 0)));

	//Head
	sphere.push_back(new Object(50.0f, glm::vec3(0, 0, -100), glm::vec3(255, 255, 255)));
	
	//Eyebrows
	for (int i = 0; i < 4; i++)
	{
		sphere.push_back(new Object(2.4f, glm::vec3(-13 + (i*2), -21 + (i*1.5), -50), glm::vec3(0, 0, 0)));

	}

	for (int i = 0; i < 4; i++)
	{
		sphere.push_back(new Object(2.4f, glm::vec3(13 - (i * 2), -21 + (i*1.5), -50), glm::vec3(0, 0, 0)));

	}

	//Nose
	sphere.push_back(new Object(7.0f, glm::vec3(0, 0, -50), glm::vec3(255, 0, 0)));


	//Lip left
	for (float l = 0.0f; l < 7.5f; l += 2.5f)
	{
		glm::vec3 c;
		for (int i = 0; i < 10; i += 2)
		{
			if (i == 0) { c = glm::vec3(155, 0, 0); }
			else if (l == 2.5f) { c = glm::vec3(255, 255, 255); }
			else { c = glm::vec3(155, 0, 0); }
			sphere.push_back(new Object(3.0f, glm::vec3(-24 + i, 3 + l + i, -50), c));
		}

		// Lip middle
		for (int i = 0; i < 28; i += 4)
		{
			if (l == 2.5f) { c = glm::vec3(255, 255, 255); }
			else { c = glm::vec3(155, 0, 0); }
			sphere.push_back(new Object(3.0f, glm::vec3(-12 + i, 13 + l, -50), c));
		}

		//Lip right
		for (int i = 0; i < 10; i += 2)
		{
			if (i == 8) { c = glm::vec3(155, 0, 0); }
			else if (l == 2.5f) { c = glm::vec3(255, 255, 255); }
			else { c = glm::vec3(155, 0, 0); }
			sphere.push_back(new Object(3.0f, glm::vec3(16 + i, 11 - i + l, -50), c));
		}

	}

	return sphere;
}

void drawSquare(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre)
{
	int length = 50;
	for (int horizontal = 0; horizontal < _windowSize.x; horizontal++)
	{
		for (int vertical = 0; vertical < _windowSize.y; vertical++)
		{
			if (vertical <= _centre.y + (length / 2) && horizontal <= _centre.x + (length / 2) && vertical >= _centre.y - (length / 2) && horizontal >= _centre.x - (length / 2))
			{
				_pixelColour = randCol();
				_pixelPosition.x = horizontal;
				_pixelPosition.y = vertical;
				MCG::DrawPixel(_pixelPosition, _pixelColour);
			}
		}
	}

}


void drawTriangle(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre)
{
	int height = -100;
	int width = 100;
	for (int i = 0; i > height; i--)
	{
		for (int w = width; w > 0; w--)
		{
			_pixelColour = randCol();
			MCG::DrawPixel(_pixelPosition, _pixelColour);
			_pixelPosition.x += 1;
		}
		width--;
		_pixelPosition.x = _centre.x;
		_pixelPosition.y += 1;
	}

	//Mirror the triangle:
	width = 100;
	height = -100;
	_pixelPosition.y = _centre.y;
	_pixelPosition.x = _centre.x + 1;
	for (int i = 0; i > height; i--)
	{
	for (int w = width; w > 0; w--)
	{
		_pixelColour = randCol();
	MCG::DrawPixel(_pixelPosition, _pixelColour);
	_pixelPosition.x -= 1;
	}
	width--;
	_pixelPosition.x = _centre.x+1;
	_pixelPosition.y += 1;
	} 


}

void drawCircle(glm::ivec2 _windowSize, glm::ivec3 _pixelColour, glm::ivec2 _pixelPosition, glm::ivec2 _centre)
{
	int radius = 30;
	for (int horizontal = 0; horizontal < _windowSize.x; horizontal++)
	{
		for (int vertical = 0; vertical < _windowSize.y; vertical++)
		{
			float yDifference = pow(vertical - _centre.y, 2);
			float xDifference = pow(horizontal - _centre.x, 2);
			if (pow(radius, 2) > yDifference + xDifference)
			{
				_pixelColour = randCol();
				_pixelPosition.x = horizontal;
				_pixelPosition.y = vertical;
				MCG::DrawPixel(_pixelPosition, _pixelColour);
			}

		}
	}
}

glm::vec3 randCol()
{
	return glm::vec3(rand() % 255, rand() % 255, rand() %255);
}