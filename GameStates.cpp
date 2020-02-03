
Part current_Part; //part being held in the ship build menu
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
