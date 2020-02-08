#include <iostream>
#include <cstddef>
#ifdef __linux__
#include "Abstractions/SDL_Abstractions.h"
#else
#include "Abstractions\\SDL_Abstractions.h"
#endif

#pragma once
#define ICON_DIM 75
#define SPRITE_DIM 100
#define FSDIM 1000
 //will include "SDL_Abstractions.h", which includes the all the other libraries

enum gameState {

	MAIN_MENU, BUILD_SHIP, SHIP_VIEW, PLAYER_VIEW, CUSTOMIZE_PLAYER

};

extern int numberOfParts;
const int DEFAULT_SHIP_DIM =11;
extern int width;
extern int height;
extern gameState state;
void endGame();

//assetHandling:

struct Part {
	int num = 0;
	int sprite = 0;
	int weight = 0;
	int type = 0;
	int price = 9;
	int capacity = 0;
	int thrust = 0;
	int consumtion = 0;
	int defence = 0;
	float rot = 0;
};
struct GamePart {
	int x = 0;
	int y = 0;
	float rot = 0;
	Part origin;
	int sprite = 0;



};


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
struct GameShip {

	vector<vector<GamePart>> contents = vector<vector<GamePart>>();
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
	SDL_Texture* texture;
	SDL_Point centerOfMass;


};



extern vector<GameShip> bluePrints;
SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface* screen, GameShip* ship);
void drawShip(SDL_Renderer* renderer, GameShip* ship);
void placePart(GameShip* ship, int x, int y, GamePart p);
GameShip createNewShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen);
void placePart(GameShip* ship, int x, int y, int part, float r);
void shipPhysics(GameShip* ship);
void drawGameShip(SDL_Renderer* renderer, GameShip* ship);
void setShipAttributes(GameShip *ship);


//UIConfig
void configure_UI_Elements(SDL_Renderer* renderer);


//Game State Functions:
void setCurrentPart(Part p);
void root_Main_Menu();
/*     */void UI_Main_Menu();


void root_Build_Ship(SDL_Renderer* renderer,SDL_Surface* screen,SDL_Event* event);
/*     */void UI_Build_Ship(SDL_Renderer* renderer);

void root_Ship_View(SDL_Renderer* renderer, SDL_Event *event);
/*     */void UI_Ship_View(SDL_Renderer*renderer);

#include "assetHandling.cpp"
#include "ItemData.cpp"
#include "Ship.cpp"


#include "GameStates.cpp"
#include "UIConfig.cpp"
