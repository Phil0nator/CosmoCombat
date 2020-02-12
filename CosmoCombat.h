#pragma once
#include "Abstractions\SDL_Abstractions.h"

#define SPRITE_DIM 100;
extern int width;
extern int height;

//assetHandling:

struct Part {

	int sprite;
	int weight;
	int type;
	int price = 9;

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

// World:
void World_INIT(SDL_Renderer* r, int seed);
void World_draw(SDL_Renderer* r, SDL_Point offset);
struct Asteroid;
Asteroid Asteroid_new(int x, int y, int r);