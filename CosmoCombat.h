
#include <cstddef>
#include "Abstractions/SDL_Abstractions.h" //some simple functions to make SDL a little easier to work with shorthand
#include <iostream>
#pragma once


#define ICON_DIM 75 //dimention of icons
#define SPRITE_DIM 100 // dimention of Sprites (the size of rooms in a ship for example)
#define FSDIM 1000 //full-size-dimention: the original size of the images, used for playerView


//definitions of different gamestates, each of which has a different set of functions to be called each frame
enum gameState {

	MAIN_MENU, BUILD_SHIP, SHIP_VIEW, PLAYER_VIEW, CUSTOMIZE_PLAYER, NONE_STATE

};


enum Direction{

	UP ,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT

};
Direction dir(int rot){
	rot=rot % 360; //bring back to earth

	if(rot%45!=0)return NULL; //if not a snapping-rotation

	switch (rot) {
		case 0:
			return UP;
			break;
		case 90:
			return LEFT;
			break;
		case 180:
			return DOWN;
			break;
	  case 270:
		 	return RIGHT;
			break;
		default:
			return NULL;
			break;
	}
	return NULL;
} //turn a float into the Direction enum

float rotFromDir(Direction dir){

	switch(dir){
		case UP:
			return 0;
			break;
		case DOWN:
			return 180;
			break;
		case LEFT:
			return 270;
			break;
		case RIGHT:
			return 90;
			break;
		case UPRIGHT:
			return 45;
			break;
		case DOWNRIGHT:
			return 135;
			break;
		case DOWNLEFT:
			return 215;
			break;
		case UPLEFT:
			return 315;
			break;
		default:
			return 0;
	}
	return 0;

}

SDL_Point vDir(Direction d){

	switch (d){
		case UP:
			return Point(0,-1);
			break;
		case DOWN:
			return Point(0,1);
			break;
		case LEFT:
			return Point(-1,0);
			break;
		case RIGHT:
			return Point(1,0);
			break;

	}
	return Point(0,0);

} //turn a Direction enum into a translation vector


//big global variables:
extern int numberOfParts; //total number of existing rooms that can be added to a ship
const int DEFAULT_SHIP_DIM =11; //default dimention of a ship
extern int width; //screen width
extern int height; // screen height
extern gameState state; //current gamestate
extern SDL_Renderer *renderer;
extern SDL_Surface *screen;
extern SDL_Window *window;

//zoom
extern float playerView_ZoomFactor = 1.0;


void endGame();

//assetHandling:
#include "Animations.cpp"
struct Part { //Part Structs store the game-mechanic information about parts, such as their weight and thrust, etc...
	//This structure is NOT what goes in ships, as it stores more information than is necessary
	int num = 0;
	int sprite = 0;
	int altSprite = 0;
	int weight = 0;
	int type = 0;
	int price = 9;
	int capacity = 0;
	int thrust = 0;
	int consumtion = 0;
	int defence = 0;
	float rot = 0;
};
struct GamePart { //this is the type of part that goes on ships, it stores coordinates in terms of thier index
	int x = 0;
	int y = 0;
	float rot = 0;
	Part origin; //reference to the extra info from the above struct ^
	int sprite = 0;
};

//classifications of parts for functionality
enum PartType {

	ARMOR, WEAPON, BRIDGE, HALL, ENGINE, STORAGE

};


void setupSprites(SDL_Renderer* renderer);
SDL_Texture* sprite(int index);

//item Data:
UIElement buttonFromPart(int index);
void configureParts();
Part part(int index);
GamePart gamePart(int index);

//Ships:
struct GameShip {
	//parts/contents:
	vector<vector<GamePart>> contents = vector<vector<GamePart>>();
	vector<SDL_Point> engines = vector<SDL_Point>();
	vector<SDL_Point> weapons = vector<SDL_Point>();



	//physical data
	int w = DEFAULT_SHIP_DIM;
	int h = DEFAULT_SHIP_DIM;
	int gx = 0;
	int gy = 0;
	int weight = 0;
	int fuel = 0;
	float velx = 0;
	float vely = 0;
	float rot = 0;
	float rotvel = 0;
	bool updated = true;
	float acceleration =0;
	float angularAcceleration = 1.0;
	int fuelConsumption = 0;
	float thrust = 0;
	SDL_Point centerOfMass;


	//visuals
	SDL_Texture* texture;
	SDL_Texture* overlayTexture;
	SDL_Texture* mapTexture;

	bool needsOverlay;
	AnimationInstance exhaust;



	//state-booleans
	bool enginesOn = false;

};

Part current_Part; //part being held in the ship build menu
GameShip *current_Ship;//ship that the player is currently flying (ship view)


extern vector<GameShip> bluePrints;
SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface* screen, GameShip* ship);
void drawShip(SDL_Renderer* renderer, GameShip* ship);
void placePart(GameShip* ship, int x, int y, GamePart p);
GameShip createNewShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen);
void placePart(GameShip* ship, int x, int y, int part, float r);
void shipPhysics(GameShip* ship);
void drawGameShip(SDL_Renderer* renderer, GameShip* ship);
void setShipAttributes(GameShip *ship);


//Coordinates:
SDL_Point globalToLocalPlayer(int x, int y);
SDL_Point localToGlobalPlayer(int x, int y);

SDL_Point globalToLocalShip(int x, int y){

	return point(x-current_Ship->gx,y-current_Ship->gy);

}
SDL_Point localToGlobalShip(int x, int y){

	return point(x+current_Ship->gx,y+current_Ship->gy);

}



///UIConfig
void configure_UI_Elements(SDL_Renderer* renderer);


//used to act on game events depending on gamestate
void eventHandler(SDL_Event* event);
//Game State Functions:
//	each starting with "root_" will handle all necessary functions for that gamestate.
//														and is called directly from main()
//indented functions are the global sub-functions that each root will call
void setCurrentPart(Part p);
void root_Main_Menu();
/*     */void UI_Main_Menu();


void root_Build_Ship(SDL_Renderer* renderer,SDL_Surface* screen,SDL_Event* event);
/*     */void UI_Build_Ship(SDL_Renderer* renderer);

void root_Ship_View(SDL_Renderer* renderer, SDL_Event *event);
/*     */void UI_Ship_View(SDL_Renderer*renderer);


//animations

void handleAnimations();

bool keyPressed(SDL_Keycode keyCode);

#include "assetHandling.cpp" //load images, and store them
#include "loadingScreen.cpp" // loading screen handling by ALEX HARLAN

#include "ItemData.cpp" //store and initialize data about items, rooms, etc...
#include "Hitbox.h" //collition utilities
#include "GameObjects.cpp" //handles solid objects that exist in the world

#include "Player.h" //player class
#include "Ship.cpp" //functions for the GameShip data structure

#include "GameStates.cpp" //handling for each of the root gamestate functions
#include "UIConfig.cpp" //configure the UI, and callbacks, etc...
#include "World.cpp" // handling of the world (Alex Harlan)
#include "EventHandling.cpp" // smooth keyboard input, mouse scrolling, general event stuff etc...
