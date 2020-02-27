#include "SDL_timer.h"
#include "CosmoCombat.h"
#undef main

#define CAP_FRAMERATE true
#define FRAME_CAP 120

#define WORLD_DIV_FACTOR 10000




//global variables:
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screen;
bool running = true;
int width;
int height;
gameState state = LOADING;
using namespace std;




//Global Variables
void endGame() {

	running = false;

}

//configure necessary SDL stuffs
void setup() {
	//fullscreen, opengl window
	window = SDL_CreateWindow("--CosmoCombat--", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_OPENGL || SDL_WINDOW_FULLSCREEN);
	SDL_GetWindowSize(window, &width, &height); //setup window size variables
	renderer = SDL_CreateRenderer(window, -1, getRendererFlags());
	screen = SDL_GetWindowSurface(window);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //allows for transparency
	textureHandler.setup(renderer,window,screen);
}

int startup(void* ptr){

	loadSprites(renderer);
	cout << "Loaded Sprites" << endl;
	loadingMessage = "Configuring Parts...";
	configureParts(); // sets up reference Part structures
	configure_UI_Elements(renderer); //setup all the various ui pages, and fonts
	bluePrints.push_back(createNewShip(DEFAULT_SHIP_DIM,DEFAULT_SHIP_DIM,renderer,screen)); //creates a placeholder for the first ship

	loadingMessage = "Initializing World...";
	//World_INIT(renderer, time(NULL));
	loadingMessage = "Creating Player....";
	me = Player();
	//preAllocateShips();
	state = MAIN_MENU;
	//SDL_DestroyTexture(startup_message_texture);

	return 0;
}


int main(int argc, char* argv[])
{
	srand(time(NULL));//setup random seed
	setDefaultColor(color(0, 0, 0)); //the background color of the window by default
	SDL_Init(SDL_INIT_EVERYTHING); //setup SDL
	quickInit(8,2); //setup SDL subsystems (SDL, Image, TTF), 8 = color depth, 2 = samples
	setup(); //create window, and setup renderer and screen
	setDefaultColor(color(255,255,255)); //sets default screen background color;

	//texture used to display loading messages on startup:
	startup_message_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,width,height);
	SDL_SetTextureBlendMode(startup_message_texture,SDL_BLENDMODE_BLEND);

	startup(nullptr);
	textureHandler.doQueue();

	//TODO: To make the startup thread work, images must first be loaded to surfaces in the seperate thread
	//      , then converted to textures in the main thread, as accelerated rendering must be done in the main thread.
	//			Load all images to a vector, then after everthing is loaded, go through the vector in the main thread and
	//			properly create the textures.
	//			Note: reading images from the disk is much slower than converting between surface and texture.
	/*

	Threading For later...

	SDL_Thread *startupThread = SDL_CreateThread(startup, "startupThread", (void *)NULL);
	if(startupThread == NULL){
		cout << "isNull" << endl;
	}
	*/




	//Game Loop:
	SDL_Event event;
	while (running) {
		//event loop:

		while(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
			eventHandler(&event);


		}
		SDL_RenderClear(renderer); //clear last frame
		//Draw Stuff:
		//note: SDL_GUI_DISPLAY is called seperately in different gamestates because in some of them it
		//should be behind other graphics, while in others it should go in the front





		handleAnimations(); //update the current frame for AnimationInstance objects. see assetHandling.cpp
		//gamestates:
		if (state == MAIN_MENU) {
			root_Main_Menu();
			SDL_GUI_DISPLAY(renderer, &event); //display gui to renderer
		}
		else if (state == BUILD_SHIP) {
			SDL_GUI_DISPLAY(renderer, &event); //display gui to renderer
			root_Build_Ship(renderer,screen,&event);
		} else if (state == SHIP_VIEW){
			World_draw(renderer, Point(-current_Ship->gx,-current_Ship->gy));
			SDL_GUI_DISPLAY(renderer, &event);
			root_Ship_View(renderer, &event);
			cout << clearLine << current_Ship->gx << " : "<<current_Ship->gy << "                             ";

		} else if (state == PLAYER_VIEW){
			SDL_GUI_DISPLAY(renderer, &event);

			root_Player_View();
		} else if (state == LOADING){

			root_loading_startup();
		}


		SDL_SetRenderDrawColor(renderer,0,0,0,255); //reset to black background


		SDL_RenderPresent(renderer); //update display
		SDL_Delay(0);

		//Sleep the remaining frame time
		SDL_Delay((1000 / FRAME_CAP ));


	}
	smoothFinish(window, renderer); //clear memory buffers, and smoothly shutdown program correctly
	cout << " GOODBYE " << endl;

	return 1;

}
