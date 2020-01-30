#include "CosmoCombat.h"
vector<GameShip> bluePrints;

void placePart(GameShip* ship, int x, int y, int part) {

	ship->contents.at(x).at(y) = gamePart(part);

}

GameShip createNewShip(int w, int h) {

	GameShip out;
	out.contents.resize(w);
	for (int i = 0; i < w; i++) {
		out.contents.at(i).resize(h);
		for (int j = 0; j < h; j++) {
			out.contents.at(i).push_back(gamePart(0));
		}
	
	}
	placePart(&out, w / 2, h / 2, 1);
	return out;
}



SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface *screen,GameShip* ship) {

	
	SDL_Texture* out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
	for (int i = 0; i < ship->contents.size(); i++) {
		for (int j = 0; j < ship->contents.at(i).size(); j++) {

			SDL_SetRenderTarget(renderer, out);
			quickImage(renderer, sprite(ship->contents.at(i).at(j).sprite), i * 100 , j * 100,ship->rot,Point(i*50,j*50),SDL_FLIP_NONE);


		}


	}
	return out;
}



