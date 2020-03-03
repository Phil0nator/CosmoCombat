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


void quickCircle(SDL_Renderer* renderer, int32_t centerx, int32_t centery, int32_t r, Color color);/**
*\brief draw an unfilled circle
**/
void quickRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color);
void quickPoint(SDL_Renderer* renderer, SDL_Point p, Color color);
void quickPoint(SDL_Renderer* renderer, int x, int y, Color color);
void quickLine(SDL_Renderer* renderer, int sx, int sy, int fx, int fy, Color color);
void quickFillRect(SDL_Renderer* renderer, int x, int y, int w, int h, Color color);
//math

SDL_Point rotatePoint(SDL_Point p, SDL_Point center, float r);/**
*\brief Using abstract coordinates, rotate any given point around any given center with r radians
**/
SDL_Point Point(int x, int y);
SDL_Point point(int x,int y);
float radians(Uint32 degrees);
Uint32 degrees(double r);
#include "Geometry.cpp"
