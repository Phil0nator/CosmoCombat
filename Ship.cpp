vector<GameShip> bluePrints;

void placePart(GameShip* ship, int x, int y, int part) {

	ship->contents.at(x).at(y) = gamePart(part);

}
void placePart(GameShip* ship, int x, int y, int part, float r) {
	GamePart p = gamePart(part);
	p.rot = r;
	ship->contents.at(x).at(y) = p;
}


SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface* screen, GameShip* ship) {


	SDL_Texture* out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DEFAULT_SHIP_DIM*SPRITE_DIM, DEFAULT_SHIP_DIM*SPRITE_DIM);
	for (int i = 0; i < ship->contents.size(); i++) {
		for (int j = 0; j < ship->contents.at(i).size(); j++) {
			if (ship->contents.at(i).at(j).sprite == 0)continue;
			SDL_SetRenderTarget(renderer, out);
			SDL_Rect source = getTextureRect(sprite(ship->contents.at(i).at(j).sprite));
			SDL_Rect dest = getQuickRect(i * SPRITE_DIM, j * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM);
			const float r = ship->contents.at(i).at(j).rot;
			image(renderer, sprite(ship->contents.at(i).at(j).sprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
		}


	}
	SDL_SetRenderTarget(renderer, NULL);
	ship->texture = out;
	return out;
}

GameShip createNewShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen) {

	GameShip out;
	out.contents.resize(w);
	for (int i = 0; i < w; i++) {
		out.contents.at(i).resize(h);
		for (int j = 0; j < h; j++) {
			out.contents.at(i).push_back(gamePart(0));
		}

	}
	placePart(&out, w / 2, h / 2, 1);
	bufferShip(renderer, screen, &out);
	return out;
}

void drawShip(SDL_Renderer* renderer, GameShip* ship) {

	quickImage(renderer, ship->texture,width/4,0);

}

void drawGameShip(SDL_Renderer* renderer, GameShip* ship) {


}
