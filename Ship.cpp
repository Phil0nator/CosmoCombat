vector<GameShip> bluePrints;


void setShipAttributes(GameShip* ship){
	ship -> weight = 0;
	ship->thrust=0;
	ship->fuelConsumption = 0;
	ship->fuel = 0;
	for (int i = 0; i < ship->contents.size(); i++) {
		for (int j = 0; j < ship->contents.at(i).size(); j++) {
			if(ship->contents.at(i).at(j).sprite != 0){
				Part *temp = ship->contents.at(i).at(j).origin;
				ship->weight+=temp->weight;
				if(temp->type == ENGINE){
					ship->thrust+=temp->thrust;
					ship->fuelConsumption+=temp->consumtion;
				}
				if(temp->type == STORAGE){
					ship->fuel+=temp->capacity;
				}
			}
		}
	}
	ship->angularAcceleration = ship->thrust/(ship->weight);
	ship->acceleration = ship->thrust/(ship->weight);
}
void placePart(GameShip* ship, int x, int y, int part) {

	ship->contents.at(x).at(y) = gamePart(part);
	setShipAttributes(ship);
	ship->updated =false;

}
void placePart(GameShip* ship, int x, int y, int part, float r) {
	GamePart p = gamePart(part);
	p.rot = r;
	ship->contents.at(x).at(y) = p;
	setShipAttributes(ship);
	ship->updated =false;
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
	ship->updated = true;
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

void shipPhysics(GameShip* ship){

	ship->gx+=ship->velx;
	ship->gy+=ship->vely;
	ship->rot+=ship->rotvel;


}



void drawGameShip(SDL_Renderer* renderer, GameShip* ship) {

	SDL_Rect textDim = getTextureRect(ship->texture);
	int sw = textDim.w;
	int sh = textDim.h;


	quickImage(renderer, ship->texture,(width/2)-(sw/2),(height/2)-(sh/2),degrees(ship->rot),Point(sw/2,sh/2),SDL_FLIP_NONE);


}
