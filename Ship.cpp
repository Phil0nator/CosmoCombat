vector<GameShip> bluePrints;


void setShipAttributes(GameShip *ship){//setup attributes of a ship that need to be calculated before flight, or during

	ship->angularAcceleration = ship->thrust/(ship->weight*25);
	ship->acceleration = ship->thrust/(ship->weight);

	//find center of mass:
	float xnumerator = 0;
	float ynumerator = 0;

	for(int i = 0 ; i < ship->contents.size();i++){
		for(int j = 0 ; j < ship->contents.at(i).size();j++){
			if(ship->contents.at(i).at(j).sprite != 0){
				int w =  ship->contents.at(i).at(j).origin.weight;
				xnumerator += w*i;
				ynumerator += w *j;
			}
		}

	}
	float x = xnumerator / (ship->weight+1);
	float y = ynumerator / (ship->weight+1);

	ship->centerOfMass = Point(round(x),round(y));

	//	</center of mass>

}
void placePart(GameShip* ship, int x, int y, GamePart p) { //correctly add a part to a ship / replace a part

	if(ship->contents.at(x).at(y).sprite !=0){
		//remove old properties

		if(ship->contents.at(x).at(y).sprite == p.sprite&&ship->contents.at(x).at(y).rot==p.rot){ //don't need to place a part if it is the same as the existing part
			return;
		}

		ship->thrust -= ship->contents.at(x).at(y).origin.thrust;
		ship->weight -= ship->contents.at(x).at(y).origin.weight;




	}
	p.x = x;
	p.y = y;
	ship->contents.at(x).at(y) = p;

	ship->thrust += ship->contents.at(x).at(y).origin.thrust;
	ship->weight += ship->contents.at(x).at(y).origin.weight;
	setShipAttributes(ship);

	//setup SDL_Point vectors to remember coords if this type
	switch (p.origin.type){
		case ENGINE:
			ship->engines.push_back(Point(x,y));
			break;
		case WEAPON:
			ship->weapons.push_back(Point(x,y));
			break;
	}


	ship->updated =false;
	bufferShip(renderer, screen,ship);

}


void placePart(GameShip* ship, int x, int y, int part, float r) { //place a part with rotation, calls above function
	GamePart p = gamePart(part);
	p.rot = r;
	placePart(ship,x,y,p);
	ship->updated =false;
}

void bufferShip_mapTexture(GameShip* ship){

	SDL_Texture* out;
	out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ship->w*FSDIM, ship->h*FSDIM); //setup new texture
	SDL_SetTextureBlendMode(out, SDL_BLENDMODE_BLEND); //for transparency
	SDL_SetRenderTarget(renderer, out);

	//loop though all the parts and draw them onto the buffer:
	for (int i = 0; i < ship->contents.size(); i++) {
		for (int j = 0; j < ship->contents.at(i).size(); j++) {

			if (ship->contents.at(i).at(j).sprite == 0)continue;

			SDL_Rect source = getTextureRect(sprite(ship->contents.at(i).at(j).sprite));
			SDL_Rect dest = getQuickRect(i * FSDIM, j * FSDIM, FSDIM, FSDIM);
			const float r = ship->contents.at(i).at(j).rot;
			image(renderer, sprite(ship->contents.at(i).at(j).sprite), source, dest, r, Point(FSDIM/2,FSDIM/2), SDL_FLIP_NONE);
		}


	}
	SDL_SetRenderTarget(renderer, NULL);

	ship->mapTexture = out;

}

SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface* screen, GameShip* ship) { //draws the parts of a ship onto a graphics buffer. Only called when parts change
	SDL_Texture* out;

		out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ship->w*SPRITE_DIM, ship->h*SPRITE_DIM); //setup new texture
		SDL_SetTextureBlendMode(out, SDL_BLENDMODE_BLEND); //for transparency

	SDL_SetRenderTarget(renderer, out);

	//loop though all the parts and draw them onto the buffer:
	for (int i = 0; i < ship->contents.size(); i++) {
		for (int j = 0; j < ship->contents.at(i).size(); j++) {

			if (ship->contents.at(i).at(j).sprite == 0)continue;

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
	//initialize contents vector correctly
	out.contents.resize(w);
	for (int i = 0; i < w; i++) {
		out.contents.at(i).resize(h);
		for (int j = 0; j < h; j++) {
			out.contents.at(i).push_back(gamePart(0));
		}

	}
	out.centerOfMass = Point((int)w/2,(int)h/2);
	out.w = w;
	out.h = h;
	setShipAttributes(&out);
	placePart(&out, w / 2, h / 2, 1,0); //starts with a bridge in the middle
	bufferShip(renderer, screen, &out);

	out.overlayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
	SDL_SetTextureBlendMode(out.overlayTexture, SDL_BLENDMODE_BLEND); //for transparency

	//animations
	out.exhaust = AnimationInstance(&Fire1);
	anims.push_back(&out.exhaust);

	return out;
}

void drawShip(SDL_Renderer* renderer, GameShip* ship) { //draw ship for a UI, not taking rotation into account
	SDL_Rect r = getTextureRect(ship->texture);
	quickFillRect(renderer, (width/4)-1,-1,r.w+1,r.h+1, color(255,255,255));
	quickRect(renderer, (width/4),0,r.w,r.h,color(0));
	quickImage(renderer, ship->texture,width/4,0);
}

void shipPhysics(GameShip* ship){ //update ship's geometric variables based on it's velocities

	ship->velx = fclamp(ship->velx, -2,2);
	ship->vely = fclamp(ship->vely, -2,2);

	ship->gx+=ship->velx;
	ship->gy+=ship->vely;
	ship->rot+=ship->rotvel;


}

void clearShipOverlay(GameShip* ship){
	SDL_SetRenderTarget(renderer,ship->overlayTexture);
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	//quickFillRect(renderer, 0,0,ship->w,ship->h,color(0,0,0,0));
	SDL_SetRenderTarget(renderer, NULL);
}


void renderShipOverlay(GameShip* ship){

	if(ship->enginesOn){
		ship->exhaust.tick();
		SDL_SetRenderTarget(renderer, ship->overlayTexture);
		for(int i = 0 ; i < ship->engines.size();i++){

			//draw engine light up copy
			SDL_Rect source = getTextureRect(sprite(Engine.altSprite));
			int x = ship->engines.at(i).x;
			int y = ship->engines.at(i).y;
			GamePart gp = ship->contents.at(x).at(y);
			SDL_Rect dest = getQuickRect(x* SPRITE_DIM, y * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM);
			float r = gp.rot;

			image(renderer, sprite(gp.origin.altSprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);

			//draw flame animation
			Direction d = dir(r);
			SDL_Point v = vDir(d);
			SDL_Rect dest2 = getQuickRect(dest.x+(v.x*SPRITE_DIM), dest.y+(v.y*SPRITE_DIM),dest.w,dest.h);
			image(renderer, ship->exhaust.get(), source, dest2, r,  Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);




		}
		SDL_SetRenderTarget(renderer, NULL);
	}

}

void drawGameShip(SDL_Renderer* renderer, GameShip* ship) { //draw ship for ingame, does rotate

	SDL_Rect textDim = getTextureRect(ship->texture);
	int sw = textDim.w;
	int sh = textDim.h;
	int rotCentx = (SPRITE_DIM*ship->centerOfMass.x)+SPRITE_DIM/2;
	int rotCenty = (SPRITE_DIM*ship->centerOfMass.y)+SPRITE_DIM/2;
	quickImage(renderer, ship->texture,(width/2)-(rotCentx),(height/2)-(rotCenty),ship->rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
	clearShipOverlay(ship);
	renderShipOverlay(ship);
	quickImage(renderer, ship->overlayTexture,(width/2)-(rotCentx),(height/2)-(rotCenty),ship->rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);

}

void drawShipMap(GameShip* ship){

	SDL_Rect source = {me.x,me.y,width,height};

	SDL_Rect dest = {0,0,width,height};
	image(renderer,ship->mapTexture,source,dest);
	//quickImage(renderer, ship->mapTexture, 0,0);
	//quickFillRect(renderer, 50,50,50,50,color(255,0,255));
}
