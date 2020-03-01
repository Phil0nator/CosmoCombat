#pragma once
#define PI 3.141592
#define TAO PI*2
//Geometry
	//drawing
SDL_Rect getQuickRect(int x, int y, int w, int h); //depricated

void quickRect(SDL_Rect* rect, int x, int y, int w, int h);
/**
* \param rect reference to the destination of the rect information 
**/


void quickCircle(SDL_Renderer* renderer, int32_t centerx, int32_t centery, int32_t r, Color color);
void quickRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color);
void quickPoint(SDL_Renderer* renderer, SDL_Point p, Color color);
void quickPoint(SDL_Renderer* renderer, int x, int y, Color color);
void quickLine(SDL_Renderer* renderer, int sx, int sy, int fx, int fy, Color color);
void quickFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color);
//math

SDL_Point rotatePoint(SDL_Point p, SDL_Point center, float r);
SDL_Point Point(int x, int y);
SDL_Point point(int x,int y);
float radians(Uint32 degrees);
Uint32 degrees(double r);




//drawing
SDL_Rect getQuickRect(int x, int y, int w, int h) {

	SDL_Rect *out = new SDL_Rect();
	out->x = x;
	out->y = y;
	out->w = w;
	out->h = h;
	return *out;

}
void quickRect(SDL_Rect* rect, int x, int y, int w, int h){
	rect->x=x;
	rect->y=y;
	rect->w=w;
	rect->h=h;
}


void quickFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color) {

	SDL_Rect r = (SDL_Rect){x,y,w,h};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &r);
	Color defaultColor = getDefaultColor();
	SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}
void quickRect(SDL_Renderer *renderer,int x, int y, int w, int h, Color color) {

	SDL_Rect r = (SDL_Rect){x,y,w,h};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,color.a);
	SDL_RenderDrawRect(renderer,&r);
	Color defaultColor = getDefaultColor();
	SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);

}
void quickPoint(SDL_Renderer*renderer, int x, int y, Color color) {

	SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
	SDL_RenderDrawPoint(renderer, x,y);
	Color defaultColor = getDefaultColor();
	SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);

}
void quickPoint(SDL_Renderer* renderer, SDL_Point p, Color color) {

	quickPoint(renderer, p.x, p.y, color);

}
void quickCircle(SDL_Renderer* renderer, int32_t centerx, int32_t centery, int32_t r, Color color)
{

	//https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl

	SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);

	const int32_t diameter = (r * 2);

	int32_t x = (r - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centerx + x, centery - y);
		SDL_RenderDrawPoint(renderer, centerx + x, centery + y);
		SDL_RenderDrawPoint(renderer, centerx - x, centery - y);
		SDL_RenderDrawPoint(renderer, centerx - x, centery + y);
		SDL_RenderDrawPoint(renderer, centerx + y, centery - x);
		SDL_RenderDrawPoint(renderer, centerx + y, centery + x);
		SDL_RenderDrawPoint(renderer, centerx - y, centery - x);
		SDL_RenderDrawPoint(renderer, centerx - y, centery + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
	Color defaultColor = getDefaultColor();
	SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}
void quickLine(SDL_Renderer* renderer, int sx, int sy, int fx, int fy, Color color) {

	SDL_SetRenderDrawColor(renderer, color.r,color.g,color.b,color.a);
	SDL_RenderDrawLine(renderer,sx,sy,fx,fy);
	Color defaultColor = getDefaultColor();
	SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}

//math
SDL_Point rotatePoint(SDL_Point p, SDL_Point center, float r) {

	float s = sin(r);
	float c = cos(r);

	p.x -= center.x;
	p.y -= center.y;


	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;


	p.x = xnew + center.x;
	p.y = ynew + center.y;

	return p;
}
SDL_Point Point(int x, int y) {
	SDL_Point *p = new SDL_Point();
	p->x=x;
	p->y=y;
	return *p;
}
SDL_Point point(int x,int y){

	SDL_Point *p = new SDL_Point();
	p->x=x;
	p->y=y;
	return *p;

}

float radians(Uint32 degrees) {

	return degrees * M_PI / 180;

}
Uint32 degrees(double r) {

	return r*180/M_PI;

}
