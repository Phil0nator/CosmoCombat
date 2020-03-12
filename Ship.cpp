
void GameShip::setAttributes(){//setup attributes of a ship that need to be calculated before flight, or during

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
	setAttributes();

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
	buffer(renderer, screen);

}
void GameShip::placePart(int x, int y, int part, float r) { //place a part with rotation, calls above function
	GamePart p = gamePart(part);
	p.rot = r;
	if(this == nullptr){
		cout << "IS NULL" << endl;
		return;
	}
	placePart(x,y,p);
	updated =false;
}
void GameShip::bufferMapTexture(){

	SDL_Texture* out;
	out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*FSDIM, h*FSDIM); //setup new texture
	SDL_SetTextureBlendMode(out, SDL_BLENDMODE_BLEND); //for transparency
	SDL_SetRenderTarget(renderer, out);
	//loop though all the parts and draw them onto the buffer:
	for (int i = 0; i < contents.size(); i++) {
		for (int j = 0; j < contents.at(i).size(); j++) {

			if (contents.at(i).at(j).sprite == 0)continue;

			SDL_Rect source = getTextureRect(sprite( contents.at(i).at(j).sprite));
			SDL_Rect dest = getQuickRect(i * FSDIM, j * FSDIM, FSDIM, FSDIM);
			const float r = contents.at(i).at(j).rot;
			image(renderer, sprite(contents.at(i).at(j).sprite), source, dest, r, Point(FSDIM/2,FSDIM/2), SDL_FLIP_NONE);
		}


	}
	SDL_SetRenderTarget(renderer, NULL);

	mapTexture = out;

}
void GameShip::bufferOverlay(){
	SDL_SetRenderTarget(renderer, overlayTexture);
	for(int i = 0 ; i < engines.size();i++){

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
SDL_Texture* GameShip::buffer(SDL_Renderer* renderer, SDL_Surface* screen) { //draws the parts of a ship onto a graphics buffer. Only called when parts change
	  SDL_Texture* out;

		out = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
		SDL_SetTextureBlendMode(out, SDL_BLENDMODE_BLEND); //for transparency

	  SDL_SetRenderTarget(renderer, out);

	//loop though all the parts and draw them onto the buffer:
	for (int i = 0; i < contents.size(); i++) {
		for (int j = 0; j < contents.at(i).size(); j++) {

			if (contents.at(i).at(j).sprite == 0)continue;

			SDL_Rect source = getTextureRect(sprite( contents.at(i).at(j).sprite));
			SDL_Rect dest = getQuickRect(i * SPRITE_DIM, j * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM);
			 float r = contents.at(i).at(j).rot;
			image(renderer, sprite(contents.at(i).at(j).sprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);

			 source = (SDL_Rect){0,0,SPRITE_ASSET_DIMENTION,SPRITE_ASSET_DIMENTION};
			 dest = (SDL_Rect){i * SPRITE_DIM, j * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM};
			 r = contents.at(i).at(j).rot;
			image(renderer, sprite(contents.at(i).at(j).sprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
		}


	}
	SDL_SetRenderTarget(renderer, NULL);

	texture = out;
	updated = true;
	return out;
}
GameShip::GameShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen) {
	//initialize contents vector correctly
	contents.resize(w);
	for (int i = 0; i < w; i++) {
		contents.at(i).resize(h);
		for (int j = 0; j < h; j++) {
			contents.at(i).push_back(gamePart(0));
		}

	}
	centerOfMass = Point((int)w/2,(int)h/2);
	w = w;
	h = h;
	setAttributes();
	placePart(w / 2, h / 2, 1,0); //starts with a bridge in the middle
	buffer(renderer, screen);

	overlayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
	SDL_SetTextureBlendMode(overlayTexture, SDL_BLENDMODE_BLEND); //for transparency
	clearTexture(renderer, overlayTexture); //fill in trasparent
	animationsTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w*SPRITE_DIM, h*SPRITE_DIM); //setup new texture
	SDL_SetTextureBlendMode(animationsTexture, SDL_BLENDMODE_BLEND); //for transparency
	clearTexture(renderer, animationsTexture);
	//animations
	exhaust = AnimationInstance(&Fire1);
	//anims.push_back(exhaust);

}
void GameShip::drawBSP(SDL_Renderer* renderer) { //draw ship for a UI, not taking rotation into account
	SDL_Rect r = getTextureRect(texture);
	quickFillRect(renderer, (width/4)-1,-1,r.w+1,r.h+1, color(255,255,255));
	quickRect(renderer, (width/4),0,r.w,r.h,color(0));
	quickImage(renderer, texture,width/4,0);
}

void GameShip::physics(){ //update ship's geometric variables based on it's velocities

	velx = fclamp(velx, -2,2);
	vely = fclamp(vely, -2,2);

	x+=velx;
	y+=vely;
	rot+=rotvel;


}
void GameShip::clearOverlay(){
	SDL_SetRenderTarget(renderer,animationsTexture);
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	//quickFillRect(renderer, 0,0,w,h,color(0,0,0,0));
	SDL_SetRenderTarget(renderer, NULL);
}

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
			SDL_Rect dest = getQuickRect(x* SPRITE_DIM, y * SPRITE_DIM, SPRITE_DIM, SPRITE_DIM);
			float r = gp.rot;

			image(renderer, sprite(gp.origin.altSprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);


			/*
			 --  moved to bufferShipOverlay --
			image(renderer, Sprite( renderer, gp.origin.altSprite), source, dest, r, Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);
			*/
			//draw flame animation
			Direction d = dir(r);
			SDL_Point v = vDir(d);
			SDL_Rect dest2 = getQuickRect(dest.x+(v.x*SPRITE_DIM), dest.y+(v.y*SPRITE_DIM),dest.w,dest.h);
			image(renderer, exhaust.get(), source, dest2, r,  Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);

			image(renderer, exhaust.get(), source, dest2, r,  Point(SPRITE_DIM/2,SPRITE_DIM/2), SDL_FLIP_NONE);




		}
		SDL_SetRenderTarget(renderer, NULL);
	}

}

void GameShip::drawShipView(SDL_Renderer* renderer) { //draw ship for ingame, does rotate

	SDL_Rect textDim = getTextureRect(texture);
	int sw = textDim.w;
	int sh = textDim.h;
	int rotCentx = (SPRITE_DIM*centerOfMass.x)+SPRITE_DIM/2;
	int rotCenty = (SPRITE_DIM*centerOfMass.y)+SPRITE_DIM/2;
	quickImage(renderer, texture,(width/2)-(rotCentx),(height/2)-(rotCenty),rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
	clearOverlay();
	renderOverlay();
	quickImage(renderer, overlayTexture,(width/2)-(rotCentx),(height/2)-(rotCenty),rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
	if(enginesOn){

		quickImage(renderer, overlayTexture,(width/2)-(rotCentx),(height/2)-(rotCenty),rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
		quickImage(renderer, animationsTexture,(width/2)-(rotCentx),(height/2)-(rotCenty),rot,Point(rotCentx,rotCenty),SDL_FLIP_NONE);
  }
}


void GameShip::drawPlayerView(SDL_Renderer* renderer){

	SDL_Rect source = {me.x,me.y,width,height};

	SDL_Rect dest = {0,0,width,height};
	image(renderer,mapTexture,source,dest);
	//quickImage(renderer, mapTexture, 0,0);
	//quickFillRect(renderer, 50,50,50,50,color(255,0,255));
}

void GameShip::init(){
  //gameObjects.push_back(std::unique_ptr<GameObject>(this));
  //index = gameObjects.size()-1;
}
void GameShip::collision(){

}
void GameShip::draw(SDL_Renderer* renderer){

}

GameShip createShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen){

  GameShip out = GameShip(w,h,renderer,screen);
  out.init();
  return out;

}
