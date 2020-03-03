//configure all the uielements for all various pages
//also, defines their callback functions

#define MAX_PARTS 128




//buttons and pages:
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
	/*
	*fonts are loaded into arrays so that they can be accessed in different sizes and still look smooth
	*/
	for (int i = 0; i < 50; i++) {
		fontAstro[i] = loadFont(file_fix("assets\\Fonts\\arizone-unicase-font\\ArizoneUnicaseRegular-5dRZ.ttf"), i);
	}


}

//designated callbacks:
void MM_toShipView(){
	state = SHIP_VIEW;

}
void MM_toEditShip() {
	state = BUILD_SHIP;
	current_Part = part(0);
}
void BSP_toBack() {
	state = MAIN_MENU;
	setShipAttributes(&bluePrints.at(0));
	print(BSP_Back.text_color);
	current_Ship = &bluePrints.at(0);
	bufferShip_mapTexture(current_Ship);
	bufferShipOverlay(current_Ship);
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
	BSP_Back.text_color = color(0);
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

void configure_UI_Elements(SDL_Renderer* renderer) { //root function, called in main. Does overall initiation process for the UI and fonts, and creates the pages and buttons, etc..

	loadFontAstro();
	mainPage = Page(0,0,width,height);
	mainPage.setColors(color(0,0,0),color(0,0,0),color(0,0,0));

	buildShipsPage = Page(0, 0, 0, 0); //dims set to 0 because its just a container
	buildShipsPage.setColors(color(0,0,0,0), color(0, 0, 0), color(0, 0, 0));
	buildShipsPage.hide();

	const int MMSX = width/2-width/6;//Main menu start x
	const int MMSY = height/10;//Main menu start y
	const int MMBW = width/3; //Main menu button width
	const int MMBH = MMBW*(500.0/1131.0); //Main menu button height (Is function of MMBW to avoid stretching)

	MM_ToGame = Button(MMSX,MMSY,MMBW,MMBH);
	MM_ToGame.setColors(color(235, 235, 235,0),color(255,255,255,0),color(135,135,135,0));
	MM_ToGame.text_color = color(0, 0, 0, 255);
	MM_ToGame.renderOwnText(renderer,"Play Game", fontAstro[20],SLOW);
	MM_ToGame.setCallback(&MM_toShipView);
	MM_ToGame.setTextures(UI_B3,UI_B3_H,UI_B3_C);
	mainPage.add(&MM_ToGame);
	//MM_ToGame.createBgElements(UI_B_BG1);


	MM_ToSettings = Button(MMSX, MMSY+MMBH+10, MMBW, MMBH);
	MM_ToSettings.setColors(color(235, 235, 235,0),color(255,255,255,0),color(135,135,135,0));
	MM_ToSettings.text_color = color(0, 0, 0, 255);
	MM_ToSettings.renderOwnText(renderer, "Options", fontAstro[20], SLOW);
	MM_ToSettings.setTextures(UI_B3,UI_B3_H,UI_B3_C);
	mainPage.add(&MM_ToSettings);
	//MM_ToSettings.createBgElements(UI_B_BG1);


	MM_EditShip = Button(MMSX, MMSY + 2*(MMBH) + 20,MMBW, MMBH);
	MM_EditShip.setColors(color(235, 235, 235,0),color(255,255,255,0),color(135,135,135,0));
	MM_EditShip.text_color = color(0, 0, 0, 255);
	MM_EditShip.renderOwnText(renderer, "Edit Ship", fontAstro[20], SLOW);
	MM_EditShip.setCallback(&MM_toEditShip);
	MM_EditShip.setTextures(UI_B3,UI_B3_H,UI_B3_C);
	mainPage.add(&MM_EditShip);
	//MM_EditShip.createBgElements(UI_B_BG1);


	MM_Quit = Button(0, 0, width / 10, height / 10);
	MM_Quit.setColors(color(235, 235, 235,0),color(255,255,255,0),color(135,135,135,0));
	MM_Quit.text_color = color(0,0,0);
	MM_Quit.renderOwnText(renderer, "Quit", fontAstro[15], SLOW);
	MM_Quit.setCallback(&endGame);
	MM_Quit.setTextures(UI_B1,UI_B1_H,UI_B1_C);
	mainPage.add(&MM_Quit);



	mainPage.init();

	fill_Build_Ship_Page(renderer);
	BSP_Back = Button(0,0, width / 10, height / 15);
	BSP_Back.setColors(color(235, 235, 235,0),color(255,255,255,0),color(135,135,135,0));
	BSP_Back.renderOwnText(renderer, "Back", fontAstro[15], SLOW);
	BSP_Back.setCallback(&BSP_toBack);
	BSP_Back.setTextures(UI_B1,UI_B1_H,UI_B1_C);
	mainPage.add(&MM_Quit);
	buildShipsPage.add(&BSP_Back);

	buildShipsPage.init();
}


//ui functions for gamestates:
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



}
