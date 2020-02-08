#define MAX_PARTS 128



TTF_Font *fontAstro[50];
UIElement MM_ToGame;
UIElement MM_ToSettings;
UIElement MM_Quit;
UIElement MM_EditShip;

UIElement BSP_Back;
UIElement BSP_allParts[MAX_PARTS];


UIElement mainPage;
UIElement buildShipsPage;
UIElement buildShipsPage_SideMenu;

void loadFontAstro() {

	for (int i = 0; i < 50; i++) {

		fontAstro[i] = loadFont(file_fix("assets\\Fonts\\arizone-unicase-font\\ArizoneUnicaseRegular-5dRZ.ttf"), i);
	}


}

//designated callbacks:
void MM_toShipView(){
	state = SHIP_VIEW;
	//current_Ship = &bluePrints.at(0);

}
void MM_toEditShip() {
	state = BUILD_SHIP;
}
void BSP_toBack() {
	state = MAIN_MENU;
	setShipAttributes(&bluePrints.at(0));
	cout << bluePrints.at(0).angularAcceleration << endl;
	current_Ship = &bluePrints.at(0);

}
void BSP_setCurrentPart() {
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	int ix = (mx-10) / (ICON_DIM+10);
	int iy = (my-10) / (ICON_DIM+10);
	int i = ix + (4 * (iy-1));
	setCurrentPart(part(i));

}


//</designated callbacks>


void fill_Build_Ship_Page(SDL_Renderer* renderer) {


	BSP_Back = Button(0, 0, width / 10, height / 15);
	BSP_Back.setColors(color(235, 235, 235), color(255, 235, 235), color(255, 0, 0));
	BSP_Back.renderOwnText(renderer, "Back", fontAstro[20],SLOW);
	buildShipsPage.add(&BSP_Back);


	buildShipsPage_SideMenu = Page(0, 0, width / 4, height);
	buildShipsPage_SideMenu.setColors(color(255, 255, 255), color(255, 255, 255), color(255, 255, 255));


	for (int i = 0; i < numberOfParts; i++) {

		BSP_allParts[i] = buttonFromPart(i);
		BSP_allParts[i].x = ((ICON_DIM+10)*(i%4))+10;
		BSP_allParts[i].y = (ICON_DIM+10)*((i/4)+1)+10;
		BSP_allParts[i].setCallback(&BSP_setCurrentPart);
		buildShipsPage_SideMenu.add(&BSP_allParts[i]);

	}



	buildShipsPage.add(&buildShipsPage_SideMenu);
	cout << "Build Ships Page Side Menu has " << buildShipsPage_SideMenu.elems.size() << " elements." << endl;
	cout << "Build Ships Page has " << buildShipsPage.elems.size() << " elements." << endl;
}

void configure_UI_Elements(SDL_Renderer* renderer) {

	loadFontAstro();

	mainPage = Page(0,0,width,height);
	mainPage.setColors(color(0,0,0),color(0,0,0),color(0,0,0));

	buildShipsPage = Page(0, 0, 0, 0); //dims set to 0 because its just a container
	buildShipsPage.setColors(color(0,0,0,0), color(0, 0, 0), color(0, 0, 0));
	buildShipsPage.hide();


	MM_ToGame = Button(width/2-width/6,height/2,width/3,height/15);
	MM_ToGame.setColors(color(235, 235, 235),color(255,255,255),color(135,135,135));
	MM_ToGame.text_color = color(0, 0, 0, 255);

	MM_ToGame.renderOwnText(renderer,"Play Game", fontAstro[20],SLOW);

	MM_ToGame.setCallback(&MM_toShipView);
	mainPage.add(&MM_ToGame);

	MM_ToSettings = Button(width / 2 - width / 6, height / 2+height/15+10, width / 3, height / 15);
	MM_ToSettings.setColors(color(235, 235, 235), color(255, 255, 255), color(135, 135, 135));
	MM_ToSettings.text_color = color(0, 0, 0, 255);
	MM_ToSettings.renderOwnText(renderer, "Options", fontAstro[20], SLOW);
	mainPage.add(&MM_ToSettings);

	MM_EditShip = Button(width / 2 - width / 6, height / 2 + 2*(height / 15) + 20, width / 3, height / 15);
	MM_EditShip.setColors(color(235, 235, 235), color(255, 255, 255), color(135, 135, 135));
	MM_EditShip.text_color = color(0, 0, 0, 255);
	MM_EditShip.renderOwnText(renderer, "Edit Ship", fontAstro[20], SLOW);
	MM_EditShip.setCallback(&MM_toEditShip);
	mainPage.add(&MM_EditShip);


	MM_Quit = Button(0, 0, width / 10, height / 15);
	MM_Quit.setColors(color(235,235,235),color(255,235,235),color(255,0,0));
	MM_Quit.text_color = color(0,0,0);
	MM_Quit.renderOwnText(renderer, "Quit", fontAstro[15], SLOW);
	MM_Quit.setCallback(&endGame);
	mainPage.add(&MM_Quit);



	mainPage.init();


	fill_Build_Ship_Page(renderer);
	BSP_Back = Button(0,0, width / 10, height / 15);
	BSP_Back.setColors(color(235, 235, 235), color(255, 235, 235), color(255, 0, 0));
	BSP_Back.renderOwnText(renderer, "Back", fontAstro[15], SLOW);
	BSP_Back.setCallback(&BSP_toBack);
	buildShipsPage.add(&BSP_Back);

	buildShipsPage.init();

}



void UI_Build_Ship(SDL_Renderer* renderer) {

	mainPage.hide();
	buildShipsPage.show();


}


void UI_Main_Menu() {

	mainPage.show();
	buildShipsPage.hide();

}
void UI_Ship_View(SDL_Renderer*renderer){

	mainPage.hide();
	buildShipsPage.hide();
	quickImage(renderer, renderText(renderer,to_string(current_Ship->centerOfMass.x).c_str(),fontAstro[15],color(255,255,255),SLOW), 0,0);
	quickImage(renderer, renderText(renderer,to_string(current_Ship->centerOfMass.y).c_str(),fontAstro[15],color(255,255,255),SLOW), 0,150);
	//quickImage(renderer, renderText(renderer,to_string(bluePrints.at(0).angularAcceleration).c_str(),fontAstro[15],color(255,255,255),SLOW), 0,300);


}
