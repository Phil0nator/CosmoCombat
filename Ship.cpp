
vector<GameShip> bluePrints;
class GameShip : public GameObject{
  vector<vector<GamePart>> contents = vector<vector<GamePart>>();
	vector<SDL_Point> engines = vector<SDL_Point>();
	vector<SDL_Point> weapons = vector<SDL_Point>();
	//physical data
	int w = DEFAULT_SHIP_DIM;
	int h = DEFAULT_SHIP_DIM;
	int weight = 0;
	int fuel = 0;

	bool updated = true;
	float acceleration =0;
	float angularAcceleration = 1.0;
	int fuelConsumption = 0;
	float thrust = 0;
	SDL_Point centerOfMass;
	//visuals
	SDL_Texture* texture;
	SDL_Texture* overlayTexture;
	SDL_Texture* mapTexture;
	SDL_Texture* animationsTexture;
	bool needsOverlay;
	AnimationInstance exhaust;
	//state-booleans
	bool enginesOn = false;

  Ship();
  Ship(SDL_Renderer* renderer, SDL_Surface *screen, int w, int h);

	void setAttriutes();
	void placePart(int x, int y, GamePart p);
	void placePart(int x, int y, int part, float r);
	void bufferMapTexture();
	void bufferOverlay();
	SDL_Texture* buffer(SDL_Renderer* renderer, SDL_Surface* screen);

	void drawBSP();
	void physics();
	void clearOverlay();
	void renderOverlay();
	void drawShipView();
	void drawPlayerView();
};

void GameShip::setAtributes(){//setup attributes of a ship that need to be calculated before flight, or during

	angularAcceleration = thrust/(weight*25);
	acceleration = thrust/(weight);

	//find center of mass:
	float xnumerator = 0;
	float ynumerator = 0;

	for(int i = 0 ; i < contents.size();i++){
		for(int j = 0 ; j < contents.at(i).size();j++){
			if(contents.at(i).at(j).sprite != 0){
				int w =  contents.at(i).at(j).origin.weight;
				xnumerator += w*i;
				ynumerator += w *j;
			}
		}

	}
	float x = xnumerator / (weight+1);
	float y = ynumerator / (weight+1);

	centerOfMass = Point(round(x),round(y));

	//	</center of mass>

}

void GameShip::placePart(int x, int y, GamePart p) { //correctly add a part to a ship / replace a part

	if(contents.at(x).at(y).sprite !=0){
		//remove old properties

		if(contents.at(x).at(y).sprite == p.sprite&&contents.at(x).at(y).rot==p.rot){ //don't need to place a part if it is the same as the existing part
			return;
		}

		thrust -= contents.at(x).at(y).origin.thrust;
		weight -= contents.at(x).at(y).origin.weight;




	}
	p.x = x;
	p.y = y;
	contents.at(x).at(y) = p;

	thrust += contents.at(x).at(y).origin.thrust;
	weight += contents.at(x).at(y).origin.weight;
	setShipAttributes(ship);

	//setup SDL_Point vectors to remember coords if this type
	switch (p.origin.type){
		case ENGINE:
			engines.push_back(Point(x,y));
			break;
		case WEAPON:
			weapons.push_back(Point(x,y));
			break;
	}


	updated =false;
	bufferShip(renderer, screen,ship);

}


void GameShip::placePart(int x, int y, int part, float r) { //place a part with rotation, calls above function
	GamePart p = gamePart(part);
	p.rot = r;
	placePart(x,y,p);
	updated =false;
}

<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
void bufferShip_mapTexture(GameShip* ship){

	Sprite out;
	out = Sprite( renderer, ship->w*FSDIM, ship->h*FSDIM); //setup new texture
	SDL_SetRenderTarget(renderer, out.get());
=======
void GameShip::bufferMapTexture(){

	SDL_Texture* out;
	out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*FSDIM, h*FSDIM); //setup new texture
	SDL_SetTextureBlendMode(out, SDL_BLENDMODE_BLEND); //for transparency
	SDL_SetRenderTarget(renderer, out);
>>>>>>> Stashed changes

	//loop though all the parts and draw them onto the buffer:
	for (int i = 0; i < contents.size(); i++) {
		for (int j = 0; j < contents.at(i).size(); j++) {

			if (contents.at(i).at(j).sprite == 0)continue;

<<<<<<< Updated upstream
			SDL_Rect source = getTextureRect(sprite( ship->contents.at(i).at(j).sprite));
=======
			SDL_Rect source = getTextureRect(sprite(contents.at(i).at(j).sprite));
>>>>>>> Stashed changes
			SDL_Rect dest = getQuickRect(i * FSDIM, j * FSDIM, FSDIM, FSDIM);
			const float r = contents.at(i).at(j).rot;
			image(renderer, sprite(contents.at(i).at(j).sprite), source, dest, r, Point(FSDIM/2,FSDIM/2), SDL_FLIP_NONE);
		}


	}
	SDL_SetRenderTarget(renderer, NULL);

	mapTexture = out;

}
<<<<<<< Updated upstream
void bufferShipOverlay(GameShip *ship){
	SDL_SetRenderTarget(renderer, ship->overlayTexture.get());
	for(int i = 0 ; i < ship->engines.size();i++){
=======

void GameShip::bufferOverlay(){
	SDL_SetRenderTarget(renderer, overlayTexture);
	for(int i = 0 ; i < engines.size();i++){
>>>>>>> Stashed changes

		//draw engine light up copy
		SDL_Rect source = getTextureRect(sprite(Engine.altSprite));
		int x = engines.at(i).x;
		int y = engines.at(i).y;
		GamePart gp = contents.at(x).at(y);
		SDL_Rect dest = getQuickRect(x* SPRITE_DIM, y * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM);
		float r = gp.rot;

		image(renderer, sprite(gp.origin.altSprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
	}
	SDL_SetRenderTarget(renderer, NULL);

}
>>>>>>> Stashed changes

<<<<<<< Updated upstream
SDL_Texture* bufferShip(SDL_Renderer* renderer, SDL_Surface* screen, GameShip* ship) { //draws the parts of a ship onto a graphics buffer. Only called when parts change
	Sprite out;

<<<<<<< Updated upstream
		out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DEFAULT_SHIP_DIM*SPRITE_DIM, DEFAULT_SHIP_DIM*SPRITE_DIM); //setup new texture
=======
SDL_Texture* GameShip::buffer(SDL_Renderer* renderer, SDL_Surface* screen) { //draws the parts of a ship onto a graphics buffer. Only called when parts change
	SDL_Texture* out;

		out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
>>>>>>> Stashed changes
		SDL_SetTextureBlendMode(out, SDL_BLENDMODE_BLEND); //for transparency
=======
	out = Sprite( renderer, ship->w*SPRITE_DIM, ship->h*SPRITE_DIM);
>>>>>>> Stashed changes

	SDL_SetRenderTarget(renderer, out.get());

	//loop though all the parts and draw them onto the buffer:
	for (int i = 0; i < contents.size(); i++) {
		for (int j = 0; j < contents.at(i).size(); j++) {

			if (contents.at(i).at(j).sprite == 0)continue;

<<<<<<< Updated upstream
			SDL_Rect source = getTextureRect(sprite( ship->contents.at(i).at(j).sprite));
			SDL_Rect dest = getQuickRect(i * SPRITE_DIM, j * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM);
			const float r = ship->contents.at(i).at(j).rot;
			image(renderer, sprite(ship->contents.at(i).at(j).sprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
=======
			SDL_Rect source = (SDL_Rect){0,0,SPRITE_ASSET_DIMENTION,SPRITE_ASSET_DIMENTION};
			SDL_Rect dest = (SDL_Rect){i * SPRITE_DIM, j * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM};
			const float r = contents.at(i).at(j).rot;
			image(renderer, sprite(contents.at(i).at(j).sprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
>>>>>>> Stashed changes
		}


	}
	SDL_SetRenderTarget(renderer, NULL);

<<<<<<< Updated upstream
	ship->texture = out;
	ship->updated = true;
	return out.get();
}

GameShip createNewShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen) {
=======
	texture = out;
	updated = true;
	return out;
}


GameShip::GameShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen) {

>>>>>>> Stashed changes

	//initialize contents vector correctly
	contents.resize(w);
	for (int i = 0; i < w; i++) {
		contents.at(i).resize(h);
		for (int j = 0; j < h; j++) {
			contents.at(i).push_back(gamePart(0));
		}

	}
<<<<<<< Updated upstream
	out.centerOfMass = Point((int)w/2,(int)h/2);
	out.w = w;
	out.h = h;
	setShipAttributes(&out);
	placePart(&out, w / 2, h / 2, 1,0); //starts with a bridge in the middle
	bufferShip(renderer, screen, &out);

<<<<<<< Updated upstream
	out.overlayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
	SDL_SetTextureBlendMode(out.overlayTexture, SDL_BLENDMODE_BLEND); //for transparency

=======
	out.overlayTexture = Sprite( renderer, w*SPRITE_DIM, h*SPRITE_DIM);
	clearTexture(renderer, out.overlayTexture.get()); //fill in trasparent
	out.animationsTexture = Sprite( renderer, w*SPRITE_DIM, h*SPRITE_DIM);
	clearTexture(renderer, out.animationsTexture.get());
>>>>>>> Stashed changes
	//animations
	out.exhaust = new AnimationInstance(Fire1);
	anims.push_back(out.exhaust);
=======
	centerOfMass = Point((int)w/2,(int)h/2);
	w = w;
	h = h;
	setAttributes();
	placePart(w / 2, h / 2, 1,0); //starts with a bridge in the middle
	bufferShip(renderer, screen);

	overlayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
	SDL_SetTextureBlendMode(overlayTexture, SDL_BLENDMODE_BLEND); //for transparency
	clearTexture(renderer, overlayTexture); //fill in trasparent
	animationsTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
	SDL_SetTextureBlendMode(animationsTexture, SDL_BLENDMODE_BLEND); //for transparency
	clearTexture(renderer, animationsTexture);
	//animations
	exhaust = AnimationInstance(&Fire1);
	anims.push_back(exhaust);
>>>>>>> Stashed changes

}

<<<<<<< Updated upstream
void drawShip(SDL_Renderer* renderer, GameShip* ship) { //draw ship for a UI, not taking rotation into account
	SDL_Rect r = getTextureRect(ship->texture.get());
	quickFillRect(renderer, (width/4)-1,-1,r.w+1,r.h+1, color(255,255,255));
	quickRect(renderer, (width/4),0,r.w,r.h,color(0));
<<<<<<< Updated upstream
	quickImage(renderer, ship->texture,width/4,0);

=======
	quickImage(renderer, ship->texture.get(),width/4,0);
>>>>>>> Stashed changes
=======
void GameShip::drawBSP(SDL_Renderer* renderer) { //draw ship for a UI, not taking rotation into account
	SDL_Rect r = getTextureRect(texture);
	quickFillRect(renderer, (width/4)-1,-1,r.w+1,r.h+1, color(255,255,255));
	quickRect(renderer, (width/4),0,r.w,r.h,color(0));
	quickImage(renderer, texture,width/4,0);
>>>>>>> Stashed changes
}

void GameShip::physics(){ //update ship's geometric variables based on it's velocities

<<<<<<< Updated upstream
	ship->gx+=ship->velx;
	ship->gy+=ship->vely;
	ship->rot+=ship->rotvel;
=======
	velx = fclamp(velx, -2,2);
	vely = fclamp(vely, -2,2);

	x+=velx;
	y+=vely;
	rot+=rotvel;
>>>>>>> Stashed changes


}

<<<<<<< Updated upstream
void clearShipOverlay(GameShip* ship){
<<<<<<< Updated upstream
	SDL_SetRenderTarget(renderer,ship->overlayTexture);
=======
	SDL_SetRenderTarget(renderer,ship->animationsTexture.get());
>>>>>>> Stashed changes
=======
void GameShip::clearOverlay(){
	SDL_SetRenderTarget(renderer,animationsTexture);
>>>>>>> Stashed changes
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	//quickFillRect(renderer, 0,0,w,h,color(0,0,0,0));
	SDL_SetRenderTarget(renderer, NULL);
}

<<<<<<< Updated upstream
Direction dir(int rot){
	rot=rot % 360; //bring back to earth

	if(rot%45!=0)return NULL; //if not a snapping-rotation

	switch (rot) {
		case 0:
			return UP;
			break;
		case 90:
			return LEFT;
			break;
		case 180:
			return DOWN;
			break;
	  case 270:
		 	return RIGHT;
			break;
		default:
			return NULL;
			break;
	}
} //turn a float into the Direction enum

SDL_Point vDir(Direction d){

	switch (d){
		case UP:
			return Point(0,-1);
			break;
		case DOWN:
			return Point(0,1);
			break;
		case LEFT:
			return Point(-1,0);
			break;
		case RIGHT:
			return Point(1,0);
			break;

	}
	return Point(0,0);

} //turn a Direction enum into a translation vector

void renderShipOverlay(GameShip* ship){

	if(ship->enginesOn){
<<<<<<< Updated upstream
		SDL_SetRenderTarget(renderer, ship->overlayTexture);
=======
		ship->exhaust.tick();
		SDL_SetRenderTarget(renderer, ship->animationsTexture.get());
>>>>>>> Stashed changes
		for(int i = 0 ; i < ship->engines.size();i++){

			//draw engine light up copy
			SDL_Rect source = getTextureRect(sprite( Engine.altSprite));
			int x = ship->engines.at(i).x;
			int y = ship->engines.at(i).y;
			GamePart gp = ship->contents.at(x).at(y);
=======
void GameShip::renderOverlay(){
	//TODO make updated bool for animations, make engines an array
	if(enginesOn){
		exhaust.tick();
		SDL_SetRenderTarget(renderer, animationsTexture);
		for(int i = 0 ; i < engines.size();i++){

			//draw engine light up copy
			SDL_Rect source = getTextureRect(sprite(Engine.altSprite));
			int x = engines.at(i).x;
			int y = engines.at(i).y;
			GamePart gp = contents.at(x).at(y);
>>>>>>> Stashed changes
			SDL_Rect dest = getQuickRect(x* SPRITE_DIM, y * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM);
			float r = gp.rot;
<<<<<<< Updated upstream

			image(renderer, sprite(gp.origin.altSprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);

=======
			/*
			 --  moved to bufferShipOverlay --
			image(renderer, Sprite( renderer, gp.origin.altSprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
			*/
>>>>>>> Stashed changes
			//draw flame animation
			Direction d = dir(r);
			SDL_Point v = vDir(d);
			SDL_Rect dest2 = getQuickRect(dest.x+(v.x*SPRITE_DIM), dest.y+(v.y*SPRITE_DIM),dest.w,dest.h);
<<<<<<< Updated upstream
			image(renderer, ship->exhaust->get(), source, dest2, r,  Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
=======
			image(renderer, exhaust.get(), source, dest2, r,  Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
>>>>>>> Stashed changes




		}
		SDL_SetRenderTarget(renderer, NULL);
	}

}

void GameShip::drawShipView(SDL_Renderer* renderer) { //draw ship for ingame, does rotate

<<<<<<< Updated upstream
	SDL_Rect textDim = getTextureRect(ship->texture.get());
	int sw = textDim.w;
	int sh = textDim.h;
	int rotCentx = (SPRITE_DIM*ship->centerOfMass.x)+SPRITE_DIM/2;
	int rotCenty = (SPRITE_DIM*ship->centerOfMass.y)+SPRITE_DIM/2;
	quickImage(renderer, ship->texture.get(),(width/2)-(rotCentx),(height/2)-(rotCenty),ship->rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
	clearShipOverlay(ship);
	renderShipOverlay(ship);
	quickImage(renderer, ship->overlayTexture,(width/2)-(rotCentx),(height/2)-(rotCenty),ship->rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);

<<<<<<< Updated upstream
=======
	if(ship->enginesOn){

		quickImage(renderer, ship->overlayTexture.get(),(width/2)-(rotCentx),(height/2)-(rotCenty),ship->rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
		quickImage(renderer, ship->animationsTexture.get(),(width/2)-(rotCentx),(height/2)-(rotCenty),ship->rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
=======
	SDL_Rect textDim = getTextureRect(texture);
	int sw = textDim.w;
	int sh = textDim.h;
	int rotCentx = (SPRITE_DIM*centerOfMass.x)+SPRITE_DIM/2;
	int rotCenty = (SPRITE_DIM*centerOfMass.y)+SPRITE_DIM/2;
	quickImage(renderer, texture,(width/2)-(rotCentx),(height/2)-(rotCenty),rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
	clearOverlay();
	renderOverlay();

	if(enginesOn){

		quickImage(renderer, overlayTexture,(width/2)-(rotCentx),(height/2)-(rotCenty),rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
		quickImage(renderer, animationsTexture,(width/2)-(rotCentx),(height/2)-(rotCenty),rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
		//cout << "the bruh spot" << endl;
>>>>>>> Stashed changes

	}

}

void GameShip::drawPlayerView(){

	SDL_Rect source = {me.x,me.y,width,height};

	SDL_Rect dest = {0,0,width,height};
<<<<<<< Updated upstream
	image(renderer,ship->mapTexture.get(),source,dest);
	//quickImage(renderer, ship->mapTexture, 0,0);
=======
	image(renderer,mapTexture,source,dest);
	//quickImage(renderer, mapTexture, 0,0);
>>>>>>> Stashed changes
	//quickFillRect(renderer, 50,50,50,50,color(255,0,255));
>>>>>>> Stashed changes
}
