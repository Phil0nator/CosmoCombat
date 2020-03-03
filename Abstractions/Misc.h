//misc

int randint(int min, int max); /**
*\brief gets a random integer within the specified range (Uses semi random time)
**/
float fclamp (float val, float min, float max); /**
*\brief standard constrain function using floats
**/
void smoothFinish(SDL_Window* window, SDL_Renderer* renderer);/**
*\brief uses standard SDL Cleanup methods to properly deallocate memory and close program
*\warning after this call, the pointers given as perameters will become unsafe. Do not use them after calling this.
**/
void quickInit(); /**
*\brief initialize SDL with some common default values
**/
void quickInit(int colorDepth, int samples); /**
*\breif initialize SDL with common defaults, and your own color depth and samples
**/
int now(); /**
*\brief get current time since epoch
**/
int clamp(int val, int min, int max); /**
*\brief standard constrain function
**/

#include "Misc.cpp"
