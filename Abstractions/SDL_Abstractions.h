#pragma once
#ifdef __linux__

#endif


#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
//#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include <algorithm>

#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")



using namespace std;

//misc
int main(int argc, char* argv[]);
int randint(int min, int max);
void smoothFinish(SDL_Window* window, SDL_Renderer* renderer);
void quickInit();
void quickInit(int colorDepth, int samples);
//colors

struct Color {

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a = 255;


};
Color color(int r, int g, int b);
Color color(int r, int g, int b, int a);
void setDefaultColor(Color color);
Color getDefaultColor();
Color randomColor();
void resetRenderColor(SDL_Renderer* renderer);
SDL_Color color(Color color);
SDL_Color sdlColor(int r, int g, int b);
SDL_Color sdlColor(int r, int g, int b, int a);
void print(Color inp);

//Geometry
	//drawing
SDL_Rect getQuickRect(int x, int y, int w, int h);
void quickCircle(SDL_Renderer* renderer, int32_t centerx, int32_t centery, int32_t r, Color color);
void quickRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color);
void quickPoint(SDL_Renderer* renderer, SDL_Point p, Color color);
void quickPoint(SDL_Renderer* renderer, int x, int y, Color color);
void quickLine(SDL_Renderer* renderer, int sx, int sy, int fx, int fy, Color color);
void quickFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color);
//math

SDL_Point rotatePoint(SDL_Point p, SDL_Point center, float r);
SDL_Point Point(int x, int y);
float radians(Uint32 degrees);
Uint32 degrees(long float r);


//Images
void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest);
void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, float r, SDL_Point center, SDL_RendererFlip flags);
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, float r, SDL_Point center, SDL_RendererFlip flags);

SDL_Point getTextureSize(SDL_Texture* texture);
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* path);
SDL_Rect getTextureRect(SDL_Texture* texture);

//text
enum TextQuality {

	FAST = 0x001, MEDIUM = 0x010, SLOW = 0x100,

};
TTF_Font* loadFont(const char* path, Uint32 size);
SDL_Texture* renderText(SDL_Renderer* renderer, const char* text, TTF_Font* font, Color c, TextQuality flags);
//UI Elements:
enum UIElement_Type {

	UNKOWN, BUTTON, ENTRY, SLIDER, PROGRESS_BAR, PAGE

};
typedef void(__cdecl* Callback)(); //Function Pointer typdef
class UIElement {
private:
	UIElement* parent;


	Callback callback; //defines function pointer for callbacks
	
	

public:
	vector<UIElement*> elems;
	Color color;
	Color mouseOverColor;
	Color mouseDownColor;
	bool pressed;
	string text;
	string hintText;

	bool holdable;
	bool textured;
	bool expander;

	bool visible = true;
	int x, y, w, h;
	Color text_color;
	SDL_Texture* texture;
	SDL_Texture* text_texture;
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
	void click();
	void release();
	void renderOwnText(SDL_Renderer* renderer, string text, TTF_Font* f, TextQuality q);
	void setCallback(Callback inp);
	Callback getCallback();
	void show();
	void hide();
	void toggle();
	void add(UIElement* adder);
	//client
	void draw(SDL_Renderer* renderer,SDL_Event* event);
	void update(SDL_Renderer* renderer, SDL_Event* event);
	void tick(SDL_Event* event);
	void init();

	void destroy();


};
UIElement Button(int x, int y, int w, int h);
UIElement Page(int x, int y, int w, int h);
void SDL_GUI_DISPLAY(SDL_Renderer* renderer, SDL_Event* event);
