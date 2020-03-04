//defines UIElement class and functions

#pragma once

using namespace std;
//text predefined from text.h
TTF_Font* loadFont(const char* path, Uint32 size);
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, Color c, TextQuality flags);
//UI Elements:
enum UIElement_Type {

	UNKOWN, BUTTON, ENTRY, SLIDER, PROGRESS_BAR, PAGE, PERIF

};/**
*\brief Used to determine the type of element a given object will be
*\brief not needed by user, will be done automatically in secondary constructors
**/

void defaultCallback(){}

typedef void(*Callback)(void); /**
*\brief defines function pointer as type Callback.
**/

class UIElement {
/*
*\brief single class which can be used to represent each of the UIElement_Types:
*\breif			>UNKOWN, BUTTON, ENTRY, SLIDER, PROGRESS_BAR, PAGE (see enum UIElement_Type)
*\briefthe type variable will determine its functionality
*
*/
private:
	UIElement* parent; //used for pages


	Callback callback = defaultCallback; //defines function pointer for callbacks



public:
	vector<UIElement*> elems;/**
	*\brief used for pages to contain pointer to child objects
	**/
	Color color;
	Color mouseOverColor;
	Color mouseDownColor;
	bool pressed = false;
	string text;
	string hintText;

	bool holdable;
	bool textured;
	bool expander;

	bool perifDir;

	bool visible = true;
	int x, y, w, h;
	Color text_color;
	Sprite* texture = new Sprite();
	Sprite* mouseOverTexture = new Sprite();
	Sprite* mouseDownTexture = new Sprite();
	Sprite* currentTexture = nullptr; // works like currentColor

	Sprite* text_texture = new Sprite();
	UIElement_Type type = UNKOWN;
	Color* currentColor;
	//getters
	Color getColor();
	Color getMouseOverColor();
	Color getMouseDownColor();


	//setters
	void setColor(Color c);
	void setMouseOverColor(Color c);
	void setMouseDownColor(Color c);
	void setColors(Color a, Color b, Color c);
	void setTextures(Sprite * nat, Sprite * mover, Sprite * mdwn);
	void click();
	void release();
	void renderOwnText(SDL_Renderer* renderer, string text, TTF_Font* f, TextQuality q);/**
	*\brief render some words to the object's text sprite
	*\brief see text.h
	**/
	void setCallback(Callback inp);/**
	*\brief set the funtion to be called by the button when it is clicked (done with mouse up by default)
	*\param inp give a pointer to a function
	**/
	Callback getCallback();
	void show();
	void hide();
	void toggle();
	void add(UIElement* adder);/**
	*\breif used for pages, add a pointer to child element to list of children
	*\brief see UIElement::elems
	**/
	//client
	void draw(SDL_Renderer* renderer, SDL_Event* event);/**
	*\brief not needed by user. Used to call correct draw function for type of element
	**/
	void update(SDL_Renderer* renderer, SDL_Event* event);/**
	*\brief not needed by user. calls UIElement::tick and UIElement::draw
	**/
	void tick(SDL_Event* event);/**
	*\brief calls correct tick function for element type. (tick means do conditionals)
	**/
	void init();/**
	*\brief initialize a UIElement to the maser page
	**/

	void destroy();/**
	*\brief will remove element from its parent. Data will still exist, but it will not be drawn
	*\warning this not a destructor, data will remain persistent
	**/

};
UIElement Button(int x, int y, int w, int h);
UIElement Page(int x, int y, int w, int h);
void SDL_GUI_DISPLAY(SDL_Renderer* renderer, SDL_Event* event);



//masterlist of UIElements
//each instanciated UIElement object is added here so that it can be updated each frame by SDL_GUI_DISPLAY()
//															(see bottom of this document and CosmoCombat.cpp)
vector<UIElement*> master = vector<UIElement*>();
#include "SDL_GUI.cpp"
