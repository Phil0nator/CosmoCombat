
Part current_Part; //part being held in the ship build menu
GameShip *current_Ship;//ship that the player is currently flying (ship view)
bool BSP_Rotated = false;

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

		if (event->button.clicks == 1&&current_Part.num>0) {
			int sx = width / 4;
			if (mx > sx) {
				placePart(&bluePrints.at(0), (mx - sx) / SPRITE_DIM, my / SPRITE_DIM, current_Part.num,current_Part.rot);
				bufferShip(renderer, screen, &bluePrints.at(0));
			}


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


//TODO make the ship move

void root_Ship_View(SDL_Renderer* renderer, SDL_Event *event){
	UI_Ship_View(renderer);
//draw world

//draw/physiscs ships
	if(event->type == SDL_KEYDOWN){
		bool engineUsed = false;
		if (event->key.keysym.sym == SDLK_w) { //w
			//degrees(current_Ship->acceleration)*spriteDimention
			float dx = cos((current_Ship->rot)+90) * current_Ship->acceleration*SPRITE_DIM; // last = size
			float dy = sin((current_Ship->rot)+90) * current_Ship->acceleration*SPRITE_DIM;

			current_Ship->velx+=dx;
			current_Ship->vely+=dy;
			engineUsed=true;
		}
		if (event->key.keysym.sym == SDLK_a) {//a
			current_Ship->rotvel-=current_Ship->angularAcceleration;
			engineUsed=true;
 		}
		if (event->key.keysym.sym == SDLK_d) { //d
			current_Ship->rotvel+=current_Ship->angularAcceleration;
			engineUsed=true;
		}
		if (event->key.keysym.sym == SDLK_s) { //s
		}
		if(event->key.keysym.sym == SDLK_ESCAPE){
			state = MAIN_MENU;

		}

		if (engineUsed) {
			/*
			current_Ship->fuel-=current_Ship->fuelConsumption;
			for (int i = 0; i < current_Ship->engines.size(); i++) {
				Particle p = new Particle(current_Ship->engines.get(i).getAbsolute());
				p.setVelocity((int)current_Ship->velx+(int)random(-3, 3), (int) current_Ship->vely+(int)random(-3, 3));
				particles.add(p);
			}
			*/
		}
	}


	shipPhysics(current_Ship);
	drawGameShip(renderer, current_Ship);
//draw objs



}
void root_Player_View(){



}
