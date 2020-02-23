//handling for all of the game states
//lots of general purpose stuff


bool BSP_Rotated = false;
time_t lastShipUpdate = 1;
bool bsp_pickupClick = false;

//event handlers
void BSP_Events(SDL_Event* event){

	int mx, my;
	SDL_GetMouseState(&mx, &my);
	if (&current_Part != nullptr) {


		if (current_Part.sprite > 0) {
			SDL_Rect textRect = getTextureRect(sprite(current_Part.sprite));
			image(renderer, sprite(current_Part.sprite), textRect, getQuickRect(mx-ICON_DIM/2, my- ICON_DIM / 2, ICON_DIM, ICON_DIM),current_Part.rot,Point(ICON_DIM/2,ICON_DIM/2),SDL_FLIP_NONE);
		}
		int sx = width / 4;
		int ex = (width/4)+(bluePrints.at(0).w*SPRITE_DIM);
		if (/*event->button.clicks == 1&&*/current_Part.num>0&&event->type==SDL_MOUSEBUTTONUP) {
			if (mx > sx&&mx<ex) {
				placePart(&bluePrints.at(0), (mx - sx) / SPRITE_DIM, my / SPRITE_DIM, current_Part.num,current_Part.rot);

			}


		}else if(/*event->button.clicks == 1&&*/current_Part.num==0&&event->type==SDL_MOUSEBUTTONUP){//pick up existing parts
			if(mx>sx&&!bsp_pickupClick){
				current_Part = part(bluePrints.at(0).contents.at((mx - sx) / SPRITE_DIM).at(my / SPRITE_DIM).origin.num);
				placePart(&bluePrints.at(0), (mx - sx) / SPRITE_DIM, my / SPRITE_DIM, 0,0);
				bsp_pickupClick=true;
			}
		}else if(event->type!=SDL_MOUSEBUTTONUP){
			bsp_pickupClick=false;
		}


	}
	if (event->key.state == SDLK_r && !BSP_Rotated) {
		current_Part.rot += 90;
		BSP_Rotated = true; //used to slow down the rotation speed
	}
	else if (event->key.state != SDLK_r){
		BSP_Rotated = false;
	}

}
void Ship_View_Events(SDL_Event* event){
	//handle key events:

	bool engineUsed = false;
	if (keyPressed(SDLK_w)) { //w
		//degrees(current_Ship->acceleration)*spriteDimention
		float dx = cos(radians((current_Ship->rot)+90)) * .05; // last = size
		float dy = sin(radians((current_Ship->rot)+90)) * .05;

		current_Ship->velx+=dx;
		current_Ship->vely+=dy;
		engineUsed=true;
	}
	if (keyPressed(SDLK_a)) {//a
		current_Ship->rotvel-=current_Ship->angularAcceleration;
		engineUsed=true;
	}
	if (keyPressed( SDLK_d)) { //d
		current_Ship->rotvel+=current_Ship->angularAcceleration;
		engineUsed=true;
	}
	if (keyPressed(SDLK_s)) { //s
	}
	if(keyPressed(SDLK_ESCAPE)){
		state = MAIN_MENU;

	}
	if(keyPressed(SDLK_SPACE)){

		state=PLAYER_VIEW;

	}

	if (engineUsed) {
		current_Ship->enginesOn =true;
		/*   subtract fuel, create particles, etc...
		*old java code:

		current_Ship->fuel-=current_Ship->fuelConsumption;
		for (int i = 0; i < current_Ship->engines.size(); i++) {
			Particle p = new Particle(current_Ship->engines.get(i).getAbsolute());
			p.setVelocity((int)current_Ship->velx+(int)random(-3, 3), (int) current_Ship->vely+(int)random(-3, 3));
			particles.add(p);
		}

		*/

	}else{

		current_Ship->enginesOn=false;

	}

}
void Player_View_Events(SDL_Event* event){
	if(keyPressed(SDLK_SPACE)){

		//state=SHIP_VIEW;

	}
	if (keyPressed(SDLK_w)) { //w
		me.vely-=5;
		me.rot = UP;
	}
	if (keyPressed(SDLK_a)) {//a
		me.velx-=5;
		me.rot = LEFT;
	}
	if (keyPressed(SDLK_d)) { //d
		me.velx+=5;
		me.rot = RIGHT;
	}
	if (keyPressed(SDLK_s)) { //s
		me.vely+=5;
		me.rot = DOWN;
	}

	if(keyPressed(SDLK_s)&&keyPressed(SDLK_d)){
		me.rot = DOWNRIGHT;
	}else if (keyPressed(SDLK_s)&&keyPressed(SDLK_a)){
		me.rot = DOWNLEFT;
	}else if (keyPressed(SDLK_w)&&keyPressed(SDLK_d)){
		me.rot = UPRIGHT;
	}else if (keyPressed(SDLK_w)&&keyPressed(SDLK_a)){
		me.rot = UPLEFT;
	}

	if(keyPressed(SDLK_ESCAPE)){
		state = SHIP_VIEW;

	}
}

void GameStateEventHandler(SDL_Event* event){

	if (state == BUILD_SHIP) {
		BSP_Events(event);
	}else if (state == SHIP_VIEW){
		Ship_View_Events(event);
	}else if (state == PLAYER_VIEW){
		Player_View_Events(event);
	}

}

//root functions
void root_Main_Menu() {

	UI_Main_Menu();


}
void setCurrentPart(Part p) {
	current_Part = p;
}
void root_Build_Ship(SDL_Renderer* renderer, SDL_Surface* screen, SDL_Event* event) {

	UI_Build_Ship(renderer);

	drawShip(renderer,&bluePrints.at(0));
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	if (&current_Part != nullptr) {


		if (current_Part.sprite > 0) {
			SDL_Rect textRect = getTextureRect(sprite(current_Part.sprite));
			image(renderer, sprite(current_Part.sprite), textRect, getQuickRect(mx-ICON_DIM/2, my- ICON_DIM / 2, ICON_DIM, ICON_DIM),current_Part.rot,Point(ICON_DIM/2,ICON_DIM/2),SDL_FLIP_NONE);
		}
	}




}



void root_Ship_View(SDL_Renderer* renderer, SDL_Event *event){
	UI_Ship_View(renderer);
//draw world

//draw/physiscs ships





	shipPhysics(current_Ship);
	lastShipUpdate=now();
	drawGameShip(renderer, current_Ship);
//draw objs



}


//TODO
void root_Player_View(){

	drawShipMap(current_Ship);
	me.drawLocal();

}
