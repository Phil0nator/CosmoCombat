#include <iostream>
#include <cstddef>
#include "Abstractions/SDL_Abstractions.h" //some simple functions to make SDL a little easier to work with shorthand

#include "linuxComp.h"
string loadingMessage = "Loading";
#pragma once



//definitions of different gamestates, each of which has a different set of functions to be called each frame
enum gameState {

	MAIN_MENU, BUILD_SHIP, SHIP_VIEW, PLAYER_VIEW, CUSTOMIZE_PLAYER, NONE_STATE, LOADING

};


enum Direction{

	UP ,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT

};
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

//big global variables:
extern int numberOfParts; //total number of existing rooms that can be added to a ship
const int DEFAULT_SHIP_DIM =11; //default dimention of a ship
extern int width; //screen width
extern int height; // screen height
extern gameState state; //current gamestate
extern SDL_Renderer *renderer;
extern SDL_Surface *screen;
extern SDL_Window *window;

void endGame();

//assetHandling:
#include "Animations.cpp"

vector<Sprite* > sprites;
vector<AnimationInstance* > anims;


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


void loadSprites(SDL_Renderer* renderer);
SDL_Texture* sprite(int index);

//item Data:
UIElement buttonFromPart(int index);
void configureParts();
Part part(int index);
GamePart gamePart(int index);

//Ships:
/*
struct GameShip { //DEPRICATING FOR AN EXTENTION OF GAMEOBJECT CLASS
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
	Sprite texture;
	Sprite overlayTexture;
	Sprite mapTexture;
	Sprite animationsTexture;

	bool needsOverlay;
	AnimationInstance *exhaust;




	//state-booleans
	bool enginesOn = false;

};

extern GameShip* current_Ship;
*/
Part current_Part; //part being held in the ship build menu


//UIConfig
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


//coordinates:
void setTranslationFactor();
void globalToLocal(int &x,int &y);
void localToGlobal(int &x,int &y);


#include "Hitbox.h" //collition utilities
#include "assetHandling.cpp" //load images, and store them
#include "ItemData.cpp" //store and initialize data about items, rooms, etc...
#include "GameObjects.cpp" //handles solid objects that exist in the world
#include "Player.h" //player class

#include "Ship.h" //functions for the GameShip data structure

//#include "Player.cpp" //player class

#include "GameStates.cpp" //handling for each of the root gamestate functions
#include "UIConfig.cpp" //configure the UI, and callbacks, etc...
#include "World.cpp" // handling of the world (Alex Harlan)
