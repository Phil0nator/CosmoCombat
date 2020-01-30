#pragma once
#include "Abstractions\SDL_Abstractions.h"
 //will include "SDL_Abstractions.h", which includes the all the other libraries


const int SPRITE_DIM =100;
const int DEFAULT_SHIP_DIM =11;
extern int width;
extern int height;


//assetHandling:

struct Part {

	int sprite;
	int weight;
	int type;
	int price = 9;
	int capacity;
	int thrust;
	int consumtion;
	int defence;

};
struct GamePart {
	int x;
	int y;
	Part* origin;
	int sprite;



};


enum PartType {

	ARMOR, WEAPON, BRIDGE, HALL, ENGINE, STORAGE

};


void loadSprites(SDL_Renderer* renderer);
SDL_Texture* sprite(int index);

//item Data:
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


};
extern vector<GameShip> bluePrints;



GameShip createNewShip(int w, int h);



//UIConfig
void configure_UI_Elements(SDL_Renderer* renderer);
