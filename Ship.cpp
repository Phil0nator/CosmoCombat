#include "CosmoCombat.h"


void placePart(GameShip* ship, int x, int y, int part) {

	

}



SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface *screen,GameShip* ship) {


	SDL_Texture* out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
	for (int i = 0; i < ship->contents.size(); i++) {
		for (int j = 0; j < ship->contents.at(i).size(); j++) {

			SDL_SetRenderTarget(renderer, out);
			quickImage(renderer, sprite(ship->contents.at(i).at(j).sprite), i * 100 , j * 100,ship->rot,Point(i*50,j*50),SDL_FLIP_NONE);


		}


	}
}



