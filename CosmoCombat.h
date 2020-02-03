#include <iostream>
#include <cstddef>
#include "Abstractions\\SDL_Abstractions.h"

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
	int num;
	int sprite;
	int weight;
	int type;
	int price = 9;
	int capacity;
	int thrust;
	int consumtion;
	int defence;
	float rot = 0;
};
struct GamePart {
	int x;
	int y;
	float rot = 0;
	Part* origin;
	int sprite;



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
	int gx;
	int gy;
	int weight;
	int fuel;
	float velx;
	float vely;
	float rot;
	float rotvel;
	SDL_Texture* texture;


};
extern vector<GameShip> bluePrints;
SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface* screen, GameShip* ship);
void drawShip(SDL_Renderer* renderer, GameShip* ship);
void placePart(GameShip* ship, int x, int y, int part);
GameShip createNewShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen);
void placePart(GameShip* ship, int x, int y, int part, float r);


//UIConfig
void configure_UI_Elements(SDL_Renderer* renderer);


//Game State Functions:
void setCurrentPart(Part p);
void root_Main_Menu();
/*     */void UI_Main_Menu();


void root_Build_Ship(SDL_Renderer* renderer,SDL_Surface* screen,SDL_Event* event);
/*     */void UI_Build_Ship(SDL_Renderer* renderer);

void root_Ship_View();
/*     */void UI_Ship_View();

#include "assetHandling.cpp"
#include "ItemData.cpp"
#include "Ship.cpp"


#include "GameStates.cpp"
#include "UIConfig.cpp"
