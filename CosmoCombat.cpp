#include "linuxComp.h"
#include "SDL_timer.h"
#include "CosmoCombat.h"
#undef main

#define CAP_FRAMERATE true
#define FRAME_CAP 120






//global variables:
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screen;
bool running = true;
int width;
int height;
gameState state = MAIN_MENU;
using namespace std;
//Global Variables
void endGame() {

	running = false;

}

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
	bluePrints.push_back(createNewShip(DEFAULT_SHIP_DIM,DEFAULT_SHIP_DIM,renderer,screen)); //creates a placeholder for the first ship
	configure_UI_Elements(renderer);
	time_t lastFrame = now();
	//Game Loop:
	SDL_Event event;
	cout << "Starting Game Loop" << endl;
	while (running) {
		lastFrame = now();
		//event loop:

		while(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}

		}
		SDL_RenderClear(renderer); //clear last frame
		//Draw Stuff:
		//note: SDL_GUI_DISPLAY is called seperately in different gamestates because in some of them it
		//should be behind other graphics, while in others it should go in the front





		handleAnimations();
		if (state == MAIN_MENU) {
			root_Main_Menu();
			SDL_GUI_DISPLAY(renderer, &event); //display gui to renderer
		}
		else if (state == BUILD_SHIP) {
			SDL_GUI_DISPLAY(renderer, &event); //display gui to renderer
			root_Build_Ship(renderer,screen,&event);
		} else if (state == SHIP_VIEW){

			SDL_GUI_DISPLAY(renderer, &event);
			root_Ship_View(renderer, &event);
		}


		SDL_SetRenderDrawColor(renderer,0,0,0,255); //reset to black background
		image(renderer, s1.get(), getTextureRect(s1.get()),getQuickRect(50,50,100,100));

		SDL_RenderPresent(renderer); //update display
		SDL_Delay(0);

		//Sleep the remaining frame time
		SDL_Delay((1000 / FRAME_CAP ));


	}

	smoothFinish(window, renderer);
	cout << " GOODBYE " << endl;

	return 1;

}
