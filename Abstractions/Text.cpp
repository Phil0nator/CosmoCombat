//load, render, and handle fonts

#pragma once


TTF_Font *loadFont(const char* path, Uint32 size) {

	return TTF_OpenFont(path,size);

}

SDL_Texture* renderText(SDL_Renderer *renderer,const char *text, TTF_Font* font, Color c, TextQuality flags) { //will render a string through a font onto a SDL_Surface
	//flags will determine the quality of the render:
					//>SLOW - smooth edges, looks nice but renders very slowly
					//>MEDIUM - less smooth edges, looks decent but renders a little faster
					//>FAST - accelerated rendering, blocky looking, often blurry if large
	SDL_Texture* out;
	SDL_Surface* primary;
	if (flags == FAST) {
		primary = TTF_RenderText_Solid(font,text, color(c));
	}
	else if (flags == MEDIUM) {
		primary = TTF_RenderText_Shaded(font, text,color(c), sdlColor(0,0,0,0));
	}
	else if (flags == SLOW) {
		primary = TTF_RenderText_Blended(font, text, color(c));
	}
	else {
		primary = TTF_RenderText_Solid(font, text, color(c));
	}

	out = SDL_CreateTextureFromSurface(renderer, primary);
	SDL_FreeSurface(primary);
	return out;
}
