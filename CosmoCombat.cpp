#include <iostream>
#include "CosmoCombat.h"
#undef main //prevents interfearence from SDL2_main.h

//TODO:
//runtime pointer access violations making it very unstable
//see pointer issues in SDL_GUI & Modifiers








//global variables:
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screen;
bool running = true;
int width;
int height;

using namespace std;
//Global Variables


void setup() {
	//fullscreen, opengl window
	window = SDL_CreateWindow("--CosmoCombat--", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_OPENGL || SDL_WINDOW_FULLSCREEN);
	SDL_GetWindowSize(window, &width, &height); //setup window size variables
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	screen = SDL_GetWindowSurface(window);
}




int main(int argc, char* argv[])
{
	srand(time(NULL));//setup random seed
	setDefaultColor(color(0, 0, 0));
	SDL_Init(SDL_INIT_EVERYTHING); //setup SDL
	quickInit(8,2); //setup SDL subsystems (SDL, Image, TTF), 8 = color depth, 2 = samples
	setup(); //create window, and setup renderer and screen
	setDefaultColor(color(255,255,255)); //sets default screen background color;
	loadSprites(renderer);
	configureParts(); // sets up reference Part structures
	bluePrints.push_back(createNewShip(DEFAULT_SHIP_DIM,DEFAULT_SHIP_DIM)); //creates a placeholder for the first ship
	configure_UI_Elements(renderer); 
	

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

			}

		}

		SDL_RenderClear(renderer); //clear last frame
		//Draw Stuff:

	
		SDL_GUI_DISPLAY(renderer, &event); //display gui to renderer

		SDL_SetRenderDrawColor(renderer,0,0,0,255); //reset to black background
		SDL_RenderPresent(renderer); //update display
	}

	smoothFinish(window, renderer);


	return 1;

}