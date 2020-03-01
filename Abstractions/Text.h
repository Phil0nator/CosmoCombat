enum TextQuality{

	SLOW, MEDIUM, FAST

};

TTF_Font *loadFont(const char* path, Uint32 size) {

	return TTF_OpenFont(path,size);

}

SDL_Texture* renderText(SDL_Renderer *renderer,const char *text, TTF_Font* font, Color c, TextQuality flags) {

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
	//SDL_FreeSurface(primary);
	return out;
}
SDL_Texture* renderText(SDL_Renderer* renderer, SDL_Texture* dest, const char *text, TTF_Font* font, Color c, TextQuality flags){

	SDL_Surface* primary;
	SDL_Texture* intermediary;
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
	intermediary = SDL_CreateTextureFromSurface(renderer, primary);
	//SDL_FreeSurface(primary);
	
	
	SDL_RenderCopy(renderer,intermediary, NULL, &getTextureRect(intermediary));
	SDL_DestroyTexture(intermediary);
	return dest;
}
