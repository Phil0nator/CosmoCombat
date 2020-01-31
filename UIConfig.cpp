#include "CosmoCombat.h"

TTF_Font *fontAstro[50];
UIElement MM_ToGame;
UIElement MM_ToSettings;
UIElement MM_Quit;
UIElement mainPage;
UIElement buildShipsPage;

void loadFontAstro() {

	for (int i = 0; i < 50; i++) {
		fontAstro[i] = loadFont("assets\\Fonts\\arizone-unicase-font\\ArizoneUnicaseRegular-5dRZ.ttf", i);
	}


}



void configure_UI_Elements(SDL_Renderer* renderer) {

	loadFontAstro();

	mainPage = Page(0,0,width,height);
	mainPage.setColors(color(0,0,0),color(0,0,0),color(0,0,0));

	buildShipsPage = Page(0, 0, width, height);
	buildShipsPage.setColors(color(100,100,100,100), color(0, 0, 0), color(0, 0, 0));
	buildShipsPage.hide();


	MM_ToGame = Button(width/2-width/6,height/2,width/3,height/15);
	MM_ToGame.setColors(color(235,235,235),color(255,255,255),color(135,135,135));
	MM_ToGame.text_color = color(0, 0, 0, 255);
	MM_ToGame.renderOwnText(renderer,"Play Game", fontAstro[20],SLOW);
	mainPage.add(&MM_ToGame);

	MM_ToSettings = Button(width / 2 - width / 6, height / 2+height/15+10, width / 3, height / 15);
	MM_ToSettings.setColors(color(235, 235, 235), color(255, 255, 255), color(135, 135, 135));
	MM_ToSettings.text_color = color(0, 0, 0, 255);
	MM_ToSettings.renderOwnText(renderer, "Options", fontAstro[20], SLOW);
	mainPage.add(&MM_ToSettings);

	MM_Quit = Button(0, 0, width / 10, height / 15);
	MM_Quit.setColors(color(235,235,235),color(255,235,235),color(255,0,0));
	MM_Quit.text_color = color(0,0,0);
	MM_Quit.renderOwnText(renderer, "Quit", fontAstro[15], SLOW);
	MM_Quit.setCallback(endGame);
	mainPage.add(&MM_Quit);

	mainPage.init();

}