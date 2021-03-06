//Shorthand functions for SDL:
#define PI 3.141592
#define TAO PI*2
//Geometry
	//drawing

SDL_Rect getQuickRect(int x, int y, int w, int h); //create SDL_Rect object in one line
void quickCircle(SDL_Renderer* renderer, int32_t centerx, int32_t centery, int32_t r, Color color); //draw an unfilled circle quickly
void quickRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color); //quckly draw an unfilled rectangle
void quickPoint(SDL_Renderer* renderer, SDL_Point p, Color color); //draw a point
void quickPoint(SDL_Renderer* renderer, int x, int y, Color color);//draw a point with x and y instead of a SDL_Point instance
void quickLine(SDL_Renderer* renderer, int sx, int sy, int fx, int fy, Color color); //draw a line
void quickFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color); //draw a filled rectangle
//math

SDL_Point rotatePoint(SDL_Point p, SDL_Point center, float r);
SDL_Point Point(int x, int y);
float radians(Uint32 degrees);
Uint32 degrees(double r);


//Images
void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest);
void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, float r, SDL_Point center, SDL_RendererFlip flags); //same as image, but takes rotation
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y); //draws an image at original size without crop for quick use
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, float r, SDL_Point center, SDL_RendererFlip flags); //same as quickImage above, but can rotate

SDL_Point getTextureSize(SDL_Texture* texture); //get the dimentions of a texture in a SDL_Point instance
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* path);
SDL_Rect getTextureRect(SDL_Texture* texture);

//drawing
SDL_Rect getQuickRect(int x, int y, int w, int h) {

	SDL_Rect out;
	out.x = x;
	out.y = y;
	out.w = w;
	out.h = h;
	return out;

}
void quickFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color) {

	SDL_Rect r = getQuickRect(x, y, w, h);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &r);
	Color defaultColor = getDefaultColor();
	SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}
void quickRect(SDL_Renderer *renderer,int x, int y, int w, int h, Color color) {

	SDL_Rect r = getQuickRect(x,y,w,h);
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
	SDL_Point p;
	p.x = x;
	p.y = y;
	return p;
}
float radians(Uint32 degrees) {

	return degrees * M_PI / 180;

}
Uint32 degrees(double r) {

	return r*180/M_PI;

}
