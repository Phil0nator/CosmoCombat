#pragma once

//Images

void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest);
void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, float r, SDL_Point center, SDL_RendererFlip flags);
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, float r, SDL_Point center, SDL_RendererFlip flags);

SDL_Point getTextureSize(SDL_Texture* texture);
Sprite * loadImage(SDL_Renderer* renderer, const char* path);
SDL_Rect getTextureRect(SDL_Texture* texture);

void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest) {

	SDL_RenderCopy(renderer, texture, &source, &dest);

}
void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, float r, SDL_Point center, SDL_RendererFlip flags) {

	SDL_RenderCopyEx(renderer, texture, &source, &dest, r,&center, flags);

}
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y) {

	int w, h;
	SDL_QueryTexture(texture, NULL,NULL,&w,&h);
	SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){x,y,w,h});

}
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, float r, SDL_Point center, SDL_RendererFlip flags) {

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_RenderCopyEx(renderer, texture, NULL, &(SDL_Rect){x,y,w,h}, r, &center, flags);

}
void clearTexture(SDL_Renderer* renderer, SDL_Texture* texture){

	SDL_SetRenderTarget(renderer,texture);
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	//quickFillRect(renderer, 0,0,ship->w,ship->h,color(0,0,0,0));
	SDL_SetRenderTarget(renderer, NULL);

}

SDL_Point getTextureSize(SDL_Texture* texture) {

	int w, h;
	if(texture==nullptr){
		return Point(0,0);
	} //prevent seg fault for null pointers
	//cout << texture << endl;
	SDL_QueryTexture(texture, NULL, NULL, &w,&h);
	return Point(w,h);
}
Sprite * loadImage(SDL_Renderer*renderer,const char* path) {

	SDL_Surface* s = IMG_Load(path);
	//SDL_Texture* out = SDL_CreateTextureFromSurface(renderer, s);

	Sprite * out = new Sprite();
	//out->source= s;
	out->texture = SDL_CreateTextureFromSurface(renderer, s);
	SDL_FreeSurface(s);
	SDL_UnlockTexture(out->texture);
	return out;

}
SDL_Rect getTextureRect(SDL_Texture* texture) {
	SDL_Point dims = getTextureSize(texture);
	return (SDL_Rect){0,0,dims.x,dims.y};
}
