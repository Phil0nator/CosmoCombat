#include "CosmoCombat.h"

TTF_Font *fontAstro[50];
UIElement PlayButton;
UIElement SettingsButton;


void loadFontAstro() {

	for (int i = 0; i < 50; i++) {
		fontAstro[i] = loadFont("assets\\Fonts\\arizone-unicase-font\\ArizoneUnicaseRegular-5dRZ.ttf", i);
	}


}
void buttonFunctionA() {
	
	PlayButton.setColor(randomColor());
	SettingsButton.setColor(randomColor());
}

void configure_UI_Elements(SDL_Renderer* renderer) {

	loadFontAstro();

	PlayButton = Button(width/2-width/6,height/2,width/3,height/15);
	PlayButton.setColors(color(235,235,235),color(255,255,255),color(135,135,135));
	PlayButton.text_color = color(0, 0, 0, 255);
	PlayButton.renderOwnText(renderer,"Play Game", fontAstro[20],SLOW);
	PlayButton.setCallback(buttonFunctionA);
	PlayButton.init();

	SettingsButton = Button(width / 2 - width / 6, height / 2+height/15+10, width / 3, height / 15);
	SettingsButton.setColors(color(235, 235, 235), color(255, 255, 255), color(135, 135, 135));
	SettingsButton.text_color = color(0, 0, 0, 255);
	SettingsButton.renderOwnText(renderer, "Options", fontAstro[20], SLOW);
	SettingsButton.setCallback(buttonFunctionA);
	SettingsButton.init();
}