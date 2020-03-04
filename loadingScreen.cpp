
//loading screen window variables
SDL_Window* lwindow;
SDL_Renderer* lrenderer;
SDL_Surface* lscreen;
int lwidth;
int lheight; 
bool lrunning = true;

//loading screen drawing variables

void setupLoadingScreen()
{
    lwindow = SDL_CreateWindow("Loading...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_GetWindowSize(lwindow, &lwidth, &lheight);
	lrenderer = SDL_CreateRenderer(lwindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderTarget(lrenderer, NULL);
	lscreen = SDL_GetWindowSurface(lwindow);
}

bool launchLoadingScreen()
{
	bool success = true;
    setupLoadingScreen();
    SDL_Log("Loading Screen: START");

	//load background first

	SDL_Texture* loadingBackground = loadImage(lrenderer, "assets\\loading\\background.jpg");
	if (loadingBackground == NULL)
	{
		smoothFinish(lwindow, lrenderer);
		SDL_Log("Background not Loaded...");
		return false;
	}

	

	//load sprites
	//loadSprites(lrenderer);

	//Game Loop:
	SDL_Event event;
	while (lrunning) {
		//event loop:
		
		while(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) {
				lrunning = false;
				success = false;
				break;
			}
		}
		
		SDL_RenderClear(lrenderer);
		quickImage(lrenderer, loadingBackground, 0, 0);
		//SDL_FillRect(lscreen, NULL, SDL_MapRGB(lscreen->format, 255, 0, 0));
		SDL_RenderPresent(lrenderer);
	}

	smoothFinish(lwindow, lrenderer);
	SDL_Log("Loading Screen: END");
	std::cout << "Success: " << success << std::endl;
	return success;
}