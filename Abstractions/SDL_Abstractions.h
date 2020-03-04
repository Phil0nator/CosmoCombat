//combine all the headers in Abstractions/ to easily include in the correct order

#pragma once
#ifdef __linux__

#endif
#define SDL_MAIN_HANDLED //prevents interfearence from SDL_Main

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_thread.h"
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
#include "video.h"
extern const char* clearLine = "\r"; //some escape sequences used to clear a line in the console
