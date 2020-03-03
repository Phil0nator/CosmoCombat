enum TextQuality{

	SLOW, MEDIUM, FAST

};/**
*
*\brief enumerated value for the quality of text. SLOW looks best but is expensive, FAST looks worse but is much cheaper
**/
TTF_Font *loadFont(const char* path, Uint32 size);/**
*\brief load a .ttf file into a font pointer
*\param path relative path to .tff file
*\param size the text size to render to (See SDL_TTF online)
**/
SDL_Texture* renderText(SDL_Renderer *renderer,const char *text, TTF_Font* font, Color c, TextQuality flags);/**
*\breif render words to new texture using font, color, and textQuality flags
*\warning will allocate a new SDL_Texture
**/
SDL_Texture* renderText(SDL_Renderer* renderer, SDL_Texture* dest, const char *text, TTF_Font* font, Color c, TextQuality flags);
/**
*\breif render words to an existing texture using font, color, and textQuality flags
*\param dest the destination texture for the rendering
**/
#include "Text.cpp"
