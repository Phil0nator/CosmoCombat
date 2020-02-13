
#define SIZE_X 20000
#define SIZE_Y 20000

#define SMALL_STAR_AMT 1000
#define MED_STAR_AMT 5
#define BIG_STAR_AMT 1
#define ASTEROID_AMT 10

/// World Classes/Structs:
struct Asteroid
{
	int x;
	int y;
	int r;
};
struct Chunk
{
	SDL_Texture* drawTexture;
	vector<Asteroid> asteroids;
};



Asteroid Asteroid_new(int x, int y, int r)
{
	Asteroid asteroid;
	asteroid.x = x;
	asteroid.y = y;
	asteroid.r = r;
	return asteroid;
}
void Asteroid_draw(SDL_Renderer* r, Asteroid a, SDL_Point offset);

bool equal(SDL_Point a, SDL_Point b)
{
	if (a.x == b.x)
	{
		if (a.y == b.y)
		{
			return true;
		}
	}

	return false;
}
bool onScreen(int x, int y)
{
	if (x >= 0 && x <= width)
	{
		if (y >= 0 && y <= height)
		{
			return true;
		}
	}
	return false;
}


SDL_Point global;
SDL_Point dimensions;
Chunk chunks[SIZE_X / 2000][SIZE_Y / 2000];

SDL_Rect smallStarSource;
SDL_Texture *smallStarTexture;

SDL_Rect medStarSource;
SDL_Texture* medStarTexture;

vector<Asteroid> asteroids;
SDL_Rect asteroidSource;
SDL_Texture* asteroidTexture;

//private static final int SMALL_STAR_AMT = 1000;
//private static final int MED_STAR_AMT = 1000;
//private static final int BIG_STAR_AMT = 10;

void World_INIT(SDL_Renderer *r, int seed)
{
	global.x = 0;
	global.y = 0;
	dimensions.x = 20000;
	dimensions.y = 20000;

	srand(seed);
	smallStarSource.h = 50;
	smallStarSource.w = 50;
	smallStarSource.x = 0;
	smallStarSource.y = 0;
	smallStarTexture = loadImage(r, "assets\\sprites\\9.PNG");


	medStarSource.h = 50;
	medStarSource.w = 50;
	medStarSource.x = 0;
	medStarSource.y = 0;
	medStarTexture = loadImage(r, "assets\\sprites\\8.PNG");

	asteroidSource.w = 474;
	asteroidSource.h = 512;
	asteroidSource.x = 0;
	asteroidSource.y = 0;
	asteroidTexture = loadImage(r, "assets\\sprites\\7.PNG");


	for (size_t y = 0; y < SIZE_Y / 2000; y++)
		for (size_t x = 0; x < SIZE_X / 2000; x++)
		{
			Chunk* chunk = &chunks[x][y];
			Asteroid bufferAsteroid;

			chunk->drawTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2000, 2000);

			SDL_SetTextureBlendMode(chunk->drawTexture, SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(r, chunk->drawTexture);

			for (size_t i = 0; i < SMALL_STAR_AMT; i++)
				SDL_RenderCopy(r, smallStarTexture, &smallStarSource, &getQuickRect(rand() % 2000, rand() % 2000, 5, 5));


			for (size_t i = 0; i < ASTEROID_AMT; i++)
			{
				bufferAsteroid = Asteroid_new(rand() % 2000, rand() % 2000, (rand() % 25) + 25);
				chunk->asteroids.push_back(bufferAsteroid);
				Asteroid_draw(r, bufferAsteroid, Point(0, 0));
			}
		}

	SDL_SetRenderTarget(r, NULL);
}

void Asteroid_draw(SDL_Renderer* r, Asteroid a, SDL_Point offset)
{
	SDL_Rect buffer;
	buffer.w = a.r * 2;
	buffer.h = a.r * 2;
	buffer.x = a.x + offset.x;
	buffer.y = a.y + offset.y;
	image(r, asteroidTexture, asteroidSource, buffer);
}

void World_draw(SDL_Renderer *r, SDL_Point offset){
	/**
		Draws Chunks and their corrisponding arteroids
		@param renderer pointer
		@param offset point
	*/


	if (!equal(offset, global))
	{
		global = offset;

	}

	/// finds the index of current chunk and draws neiboring chunks
	//r = render - the index of the chunk we are rendering
	//i = index - index buffer for neiboring chunks

	int rx = offset.x / 2000;
	int ry = offset.y / 2000;

	int ix = clamp(rx, 0, SIZE_X / 2000);
	int iy = clamp(ry, 0, SIZE_Y / 2000);


	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx - 1, 0, SIZE_X / 2000);
	iy = clamp(ry, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx + 1, 0, SIZE_X / 2000);
	iy = clamp(ry, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx, 0, SIZE_X / 2000);
	iy = clamp(ry - 1, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx - 1, 0, SIZE_X / 2000);
	iy = clamp(ry - 1, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx + 1, 0, SIZE_X / 2000);
	iy = clamp(ry - 1, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx, 0, SIZE_X / 2000);
	iy = clamp(ry + 1, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx - 1, 0, SIZE_X / 2000);
	iy = clamp(ry + 1, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);

	ix = clamp(rx + 1, 0, SIZE_X / 2000);
	iy = clamp(ry + 1, 0, SIZE_Y / 2000);
	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);
}
