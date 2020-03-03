#pragma once

//Images

void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest);/**
*\breif passees values through to SDl_RenderCopy()
*\param source used to crop source image. If you just want the whole image, use (SDL_Rect){0,0,image.nativeWidth, image.nativeHeight}
*\param dest used to place the image onto the screen. The rect's x and y will be x and y on the screen, and w and h will be the dimentions of the drawing
**/
void image(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect source, SDL_Rect dest, float r, SDL_Point center, SDL_RendererFlip flags);
/**
*\breif passees values through to SDl_RenderCopy(), using rotation
*\param source used to crop source image. If you just want the whole image, use (SDL_Rect){0,0,image.nativeWidth, image.nativeHeight}
*\param dest used to place the image onto the screen. The rect's x and y will be x and y on the screen, and w and h will be the dimentions of the drawing
*\param center point relative to image itself to rotate around. Example: Image w and h = 100, center would be 50,50
*\param flags SDL_RenderFlip flags. flip horizontal,vertical, or none
**/

void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y);/**
*\brief draw image at x and y using native dimentions, and without cropping
*
**/
void quickImage(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, float r, SDL_Point center, SDL_RendererFlip flags);/**
*\brief draw an image with native size, but using rotation.
*\param center point relative to image itself to rotate around. Example: Image w and h = 100, center would be 50,50
*\param flags SDL_RenderFlip flags. flip horizontal,vertical, or none
**/
void clearTexture(SDL_Renderer* renderer, SDL_Texture* texture); /**
*\brief clear contents of existing texture to transparent
**/

SDL_Point getTextureSize(SDL_Texture* texture); /**
*\brief gets the native dimentions of a texture and returns them through an SDL_Point contianer
**/
Sprite * loadImage(SDL_Renderer* renderer, const char* path);/**
*\brief load image from disk into Sprite pointer
*\param path The relative path to image file
**/
SDL_Rect getTextureRect(SDL_Texture* texture);/**
*\brief get native dimentions of texture in the form of a SDL_Rect struct (x and y will always = 0)
**/
#include "Images.cpp"
