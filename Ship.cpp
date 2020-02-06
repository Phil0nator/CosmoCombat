vector<GameShip> bluePrints;


void setShipAttributes(GameShip *ship){

	ship->angularAcceleration = ship->thrust/(ship->weight*25);
	ship->acceleration = ship->thrust/(ship->weight);

	//find center of mass:
	int xnumerator = 0;
	int ynumerator = 0;

	for(int i = 0 ; i < ship->contents.size();i++){
		for(int j = 0 ; j < ship->contents.at(i).size();j++){
			int w =  ship->contents.at(i).at(j).origin.weight;
			xnumerator += w*i;
			ynumerator += w *j;
		}

	}
	int x = xnumerator / (ship->weight+1);
	int y = ynumerator / (ship->weight+1);
	ship->centerOfMass = Point(x,y);
	cout << ship->centerOfMass.x << " , " << ship->centerOfMass.y << endl;

	//	</center of mass>

}
void placePart(GameShip* ship, int x, int y, GamePart p) {

	ship->contents.at(x).at(y) = p;
	ship->thrust += ship->contents.at(x).at(y).origin.thrust;
	ship->weight += ship->contents.at(x).at(y).origin.weight;
	setShipAttributes(ship);
	ship->updated =false;

}
void placePart(GameShip* ship, int x, int y, int part, float r) {
	GamePart p = gamePart(part);
	p.rot = r;
	placePart(ship,x,y,p);
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
	out.centerOfMass = Point((int)w/2,(int)h/2);
	setShipAttributes(&out);
	placePart(&out, w / 2, h / 2, 1,0);
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
	int rotCentx = (SPRITE_DIM*ship->centerOfMass.x)+SPRITE_DIM/2;
	int rotCenty = (SPRITE_DIM*ship->centerOfMass.y)+SPRITE_DIM/2;
	quickImage(renderer, ship->texture,(width/2)-(rotCentx/2),(height/2)-(rotCenty/2),ship->rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);


}
