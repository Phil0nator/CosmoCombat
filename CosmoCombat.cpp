//L:3167
#include "unitDefines.h"
#include "SDL_timer.h"
#include "CosmoCombat.h"
#undef main




//global variables:
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* screen;
bool running = true;
int width;
int height;
gameState state = MAIN_MENU;
using namespace std;


bool loaded = false;

//Global Variables
void endGame() {

	running = false;

}






//configure necessary SDL stuffs
void setup() {
	//fullscreen, opengl window
	SDL_DisplayMode dispmode;
	SDL_GetDesktopDisplayMode(0,&dispmode);
	cout << "WINDOW: "<< dispmode.w << " : " << dispmode.h << endl;
	window = SDL_CreateWindow("--CosmoCombat--", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_OPENGL || SDL_WINDOW_FULLSCREEN );
	SDL_GetWindowSize(window, &width, &height); //setup window size variables
	renderer = SDL_CreateRenderer(window, -1, getRendererFlags());
	screen = SDL_GetWindowSurface(window);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //allows for transparency
	textureHandler.setup(renderer,window,screen);
}

int startup(void* ptr){

	loadSprites(renderer);
	textureHandler.doQueue();
	cout << "Loaded Sprites" << endl;
	loadingMessage = "Configuring Parts...";
	configureParts(); // sets up reference Part structures
	cout << " Configured Parts " << endl;
	configure_UI_Elements(renderer); //setup all the various ui pages, and fonts
	cout << " Configured UI Elements" << endl;
	GameShip firstShip = createShip(DEFAULT_SHIP_DIM,DEFAULT_SHIP_DIM,renderer,screen);
	bluePrints.push_back(firstShip); //creates a placeholder for the first ship
	World_INIT(renderer, time(NULL));
	me = Player();
	//preAllocateShips();
	state = MAIN_MENU;
	//SDL_DestroyTexture(startup_message_texture);
	loaded = true;

	return 0;
}




int main(int argc, char* argv[])
{
	srand(time(NULL));//setup random seed
	setDefaultColor(color(0, 0, 0)); //the background color of the window by default
	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");
	SDL_Init(SDL_INIT_EVERYTHING); //setup SDL
	quickInit(8,2); //setup SDL subsystems (SDL, Image, TTF), 8 = color depth, 2 = samples
	setup(); //create window, and setup renderer and screen
	setDefaultColor(color(255,255,255)); //sets default screen background color;
	startup(nullptr);
	initializeNetworkClient();
	EntityServerEvent e;
	e.ID = 200;
	PackEventType(&e);
	//test:

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





		//handleAnimations(); //update the current frame for AnimationInstance objects. see assetHandling.cpp
		//gamestates:
		if (state == MAIN_MENU) {
			root_Main_Menu();
			SDL_GUI_DISPLAY(renderer, &event); //display gui to renderer
		}
		else if (state == BUILD_SHIP) {
			SDL_GUI_DISPLAY(renderer, &event); //display gui to renderer
			root_Build_Ship(renderer,screen,&event);
		} else if (state == SHIP_VIEW){
			World_draw(renderer, Point(-current_Ship->x,-current_Ship->y));
			SDL_GUI_DISPLAY(renderer, &event);
			root_Ship_View(renderer, &event);
			handleGameObjects(renderer);

			cout << clearLine << current_Ship->x << " : "<<current_Ship->y << "                             ";

		} else if (state == PLAYER_VIEW){
			SDL_GUI_DISPLAY(renderer, &event);

			root_Player_View();
		}


		SDL_SetRenderDrawColor(renderer,0,0,0,255); //reset to black background


		SDL_RenderPresent(renderer); //update display
		//SDL_Delay(0);

		//Sleep the remaining frame time
		//SDL_Delay((1000 / FRAME_CAP ));


	}
	smoothFinish(window, renderer); //clear memory buffers, and smoothly shutdown program correctly
	cout << " GOODBYE " << endl;

	return 1;

}
