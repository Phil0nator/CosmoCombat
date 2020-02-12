#include <iostream>
#include "CosmoCombat.h"
#include <SDL.h>
#include <ctime>
#undef main //prevents interfearence from SDL2_main.h

#define DEBUG true

//global variables:
int width;
int height;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screen;
bool running = true;


using namespace std;
//Global Variables


void setup() {
	//fullscreen, opengl window
	if (!DEBUG)
		window = SDL_CreateWindow("-- CosmoCombat --", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_OPENGL || SDL_WINDOW_FULLSCREEN);
	else
		window = SDL_CreateWindow("-- CosmoCombat --", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	
	SDL_GetWindowSize(window, &width, &height); //setup window size variables
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	screen = SDL_GetWindowSurface(window);

	//init things
	World_INIT(renderer, 0);
}




int main(int argc, char* argv[])
{
	srand(time(NULL));//setup random seed
	
	SDL_Init(SDL_INIT_EVERYTHING); //setup SDL
	quickInit(8,2); //setup SDL subsystems (SDL, Image, TTF), 8 = color depth, 2 = samples
	setup(); //create window, and setup renderer and screen
	setDefaultColor(color(255,255,255)); //sets default screen background color;
	loadSprites(renderer);
	configureParts();

	time_t frameStart = time(NULL);
	int frames = 0;

	SDL_Point offset = SDL_Point();

	//Game Loop:

	while (running) {

		//event loop:

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
			if (event.type == SDL_KEYDOWN) {

				SDL_Log("button");

				switch (event.key.keysym.sym)
				{
				case SDLK_UP: 
					offset.y -= 1000;
					break;

				case SDLK_DOWN: 
					offset.y += 1000;
					break;

				case SDLK_LEFT: 
					offset.x -= 1000;
					break;

				case SDLK_RIGHT: 
					offset.x += 1000;
					break;
				}

			}

		}

		SDL_RenderClear(renderer);
		//Draw Stuff:
		
		offset.x += 3;
		offset.y += 3;
		World_draw(renderer, offset);
	
		//resetRenderColor(renderer);
		SDL_RenderPresent(renderer);

		if (time(NULL) > frameStart)
		{
			cout << "second up!!" << endl;
			string buffer = "-- CosmoCombat -- fps: " + to_string(frames);
			SDL_SetWindowTitle(window, buffer.c_str());
			frames = 0;
			frameStart = time(NULL);
		}
		frames++;
	}

	smoothFinish(window, renderer);


    cout << "Hello World!\n";
	return 1;

}