
//colors

struct Color {

	Uint8 r = 255;
	Uint8 g = 0;
	Uint8 b = 255;
	Uint8 a = 255;


};
/**
*\brief easy-access data structure for rgba data
*\warning uses unsigned 8 bit integers
**/

Color color(int r, int g, int b);
/**
*\brief constructor for a Color struct, with default (255) alpha value
**/


Color color(int r, int g, int b, int a);
/**
*\brief constructor for a Color struct
**/
Color color(int v);
/**
*\brief constructor for a Color struct, setting r,g, and b to the input
**/
void setDefaultColor(Color color);
Color getDefaultColor();
Color randomColor();
/**
*\brief get a color struct with random values (will always be valid)
**/
void resetRenderColor(SDL_Renderer* renderer);
SDL_Color color(Color color);
SDL_Color sdlColor(int r, int g, int b);/**
*\Brief easy constructor for the SDL_Color struct (uses default alpha 255)
**/
SDL_Color sdlColor(int r, int g, int b, int a);
/**
*\Brief easy constructor for the SDL_Color struct, using alpha
**/
void print(Color inp);
/**
*\brief pretty print for a color struct
**/



#include "Colors.cpp"
