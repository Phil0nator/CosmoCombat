#include <iostream>
#include <SDL_Abstractions.h>
#undef main //prevents interfearence from SDL2_main.h



using namespace std;
//Global Variables

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface *screen;
bool running = true;
int width;
int height;


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
	
	SDL_Init(SDL_INIT_EVERYTHING); //setup SDL
	quickInit(8,2); //setup SDL subsystems (SDL, Image, TTF), 8 = color depth, 2 = samples
	setup(); //create window, and setup renderer and screen
	setDefaultColor(color(255,255,255)); //sets default screen background color;


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

		SDL_RenderClear(renderer);
		//Draw Stuff:


		
	
	
	
		resetRenderColor(renderer);
		SDL_RenderPresent(renderer);
	}




    cout << "Hello World!\n";
	return 1;

}