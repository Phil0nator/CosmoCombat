#pragma once
#ifdef __linux__

#endif
#define SDL_MAIN_HANDLED

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
//#include "SDL.h"
//#include "SDL_main.h"
#ifdef __linux__
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#else
#include "SDL_ttf.h"
#include "SDL_image.h"
#endif
#include <time.h>
#include <algorithm>
#include <cmath>
using namespace std;
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#include "Misc.h"
#include "Colors.h"
#include "Geometry.h"
#include "Images.h"
#include "Text.h"
#include "SDL_GUI.h"
