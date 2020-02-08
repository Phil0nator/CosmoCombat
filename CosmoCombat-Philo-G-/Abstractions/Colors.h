
//colors

struct Color {

	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
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


Color defaultColor;
void setDefaultColor(Color color){
	defaultColor = color;
}
Color getDefaultColor() {

	return defaultColor;

}
void resetRenderColor(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, defaultColor.r, defaultColor.g, defaultColor.b, defaultColor.a);
}
Color randomColor() {


	Color out;
	out.r = randint(0, 255);
	out.g = randint(0, 255);
	out.b = randint(0, 255);
	out.a = 255;
	return out;


}
Color color(int r, int g, int b) {

	Color out;

	out.r = r;
	out.g = g;
	out.b = b;

	return out;

}
Color color(int r, int g, int b, int a) {

	Color out;

	out.r = r;
	out.g = g;
	out.b = b;
	out.a = a;

	return out;



}
SDL_Color color(Color color){

	SDL_Color c;
	c.r = color.r;
	c.g = color.g;
	c.b = color.b;
	c.a = color.a;
	return c;

}
SDL_Color sdlColor(int r, int g, int b) {
	return color(color(r, g, b));
}
SDL_Color sdlColor(int r, int g, int b, int a) {
	return color(color(r, g, b,a));
}

void print(Color inp) {

	cout << "Color @(" << inp.r << ", " << inp.g << ", " << inp.b;
	if (inp.a != 0) {
		cout << ", " << inp.a;
	}
	cout << ")" << endl;

}
