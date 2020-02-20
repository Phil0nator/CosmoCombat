
#include "Abstractions/SDL_Abstractions.h"
#include "CosmoCombat.h"

#define SIZE_X 20000
#define SIZE_Y 20000

#define SMALL_STAR_AMT 1000
#define MED_STAR_AMT 5
#define BIG_STAR_AMT 1
#define ASTEROID_AMT 10

////////////////////////////////////////////////////////////////////////////////////////////////////////////
///	TODO:
///		make textures smaller
///		make stuff move slower
///		make the star chunks static
///		make asteroid chuk
///		make smaller framerate
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////








/// World Classes/Structs:

struct Chunk
{
	SDL_Point pos;
	SDL_Texture* drawTexture;
	vector<Asteroid> asteroids;
};

struct Asteroid
{
	int x;
	int y;
	int r;
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


SDL_Point dimensions;
Chunk chunks[SIZE_X / 2000 + 1][SIZE_Y / 2000 + 1];
Chunk chunksBack[SIZE_X / 2000 + 1][SIZE_Y / 2000 + 1];

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


	for (size_t y = 0; y < SIZE_Y / 2000 + 1; y++)
		for (size_t x = 0; x < SIZE_X / 2000 + 1; x++)
		{
			Chunk* chunk = &chunks[x][y];
			Asteroid bufferAsteroid;

			chunk->pos = Point(x * 2000, y * 2000);
			chunk->drawTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2000, 2000);

			SDL_SetTextureBlendMode(chunk->drawTexture, SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(r, chunk->drawTexture);

			for (size_t i = 0; i < SMALL_STAR_AMT/2; i++)
				SDL_RenderCopy(r, smallStarTexture, &smallStarSource, &getQuickRect(rand() % 2000, rand() % 2000, 5, 5));
			

			for (size_t i = 0; i < ASTEROID_AMT; i++)
			{
				bufferAsteroid = Asteroid_new(rand() % 2000, rand() % 2000, (rand() % 25) + 25);
				chunk->asteroids.push_back(bufferAsteroid);
				Asteroid_draw(r, bufferAsteroid, Point(0, 0));
			}
		}

	

	for (size_t y = 0; y < SIZE_Y / 2000 + 1; y++)
		for (size_t x = 0; x < SIZE_X / 2000 + 1; x++)
		{
			Chunk* chunk = &chunksBack[x][y];
			
			chunk->pos = Point(x * 1000, y * 1000);
			chunk->drawTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000);

			SDL_SetTextureBlendMode(chunk->drawTexture, SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(r, chunk->drawTexture);
			
			for (size_t i = 0; i < SMALL_STAR_AMT/2; i++)
				SDL_RenderCopy(r, smallStarTexture, &smallStarSource, &getQuickRect(rand() % 1000, rand() % 1000, 2, 3));

			/*
			Debug stuff:
			quickRect(r, 0, 0, 100, 100, color(255, 0, 0));
			quickFillRect(r, 0, 0, 100 * (x / (SIZE_X / 2000.f)), 100, color(255, 0, 0));
			quickFillRect(r, 0, 0, 100, 100 * (y / (SIZE_X / 2000.f)), color(255, 0, 0));
			quickFillRect(r, 900, 900, 100, 100, color(255, 0, 0));
			*/
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

void World_draw(SDL_Renderer *r, SDL_Point offset)
{
	/**
		Draws Chunks and their corrisponding arteroids

		@param renderer pointer
		@param offset point
	*/

	/// finds the index of current chunk and draws neiboring chunks
	//r = render - the index of the chunk we are rendering
	//i = index - index buffer for neiboring chunks

	int rx = offset.x / 2000;
	int ry = offset.y / 2000;

	int ix = clamp(rx, 0, SIZE_X / 2000 - 1);
	int iy = clamp(ry, 0, SIZE_X / 2000 - 1);

	//cout << ix << ":" << iy << ", " << (ix * 2000) + offset.x << ":" << (iy * 2000) + offset.y << endl;

	quickImage(r, chunks[ix][iy].drawTexture, ix * 2000 - offset.x, iy * 2000 - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, ix * 1000 - offset.x / 2, iy * 1000 - offset.y / 2);

	ix = clamp(rx - 1, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 1, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 2, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry - 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx - 1, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry - 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 1, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry - 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 2, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry - 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry + 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx - 1, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry + 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 1, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry + 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunks[ix][iy].drawTexture, chunks[ix][iy].pos.x - offset.x, chunks[ix][iy].pos.y - offset.y);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 2, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry + 1, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry + 2, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 1, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry + 2, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);

	ix = clamp(rx + 2, 0, SIZE_X / 2000 - 1);
	iy = clamp(ry + 2, 0, SIZE_X / 2000 - 1);
	quickImage(r, chunksBack[ix][iy].drawTexture, chunksBack[ix][iy].pos.x - offset.x / 2, chunksBack[ix][iy].pos.y - offset.y / 2);
}
