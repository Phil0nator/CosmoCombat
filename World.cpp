
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///	TODO:
///		make asteroids have velocity
///		make asteroid chuks
///
///
///
///
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////



/// World Classes/Structs:

struct Asteroid
{
	int x;
	int y;
	int r;
};

struct Chunk
{
	SDL_Point pos;
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


SDL_Point dimensions;
Chunk fGroundChunks[CHUNK_AMT_FG][CHUNK_AMT_FG]; // 1/2 size of the world
Chunk bGroundChunks[CHUNK_AMT_BG][CHUNK_AMT_BG]; // 1/4 size of the world


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
	smallStarTexture = sprite(9);


	medStarSource.h = 50;
	medStarSource.w = 50;
	medStarSource.x = 0;
	medStarSource.y = 0;
	medStarTexture = sprite(8);

	asteroidSource.w = 474;
	asteroidSource.h = 512;
	asteroidSource.x = 0;
	asteroidSource.y = 0;
	asteroidTexture = sprite(7);


	for (size_t y = 0; y < CHUNK_AMT_FG; y++)
		for (size_t x = 0; x < CHUNK_AMT_FG; x++)
		{
			Chunk* chunk = &fGroundChunks[x][y];

			chunk->pos = Point(x * CHUNK_SIZE, y * CHUNK_SIZE);
			chunk->drawTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CHUNK_SIZE, CHUNK_SIZE);

			SDL_SetTextureBlendMode(chunk->drawTexture, SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(r, chunk->drawTexture);

			for (size_t i = 0; i < SMALL_STAR_AMT / 2; i++)
				SDL_RenderCopy(r, smallStarTexture, &smallStarSource, &getQuickRect(rand() % CHUNK_SIZE, rand() % CHUNK_SIZE, 3, 3));

			//SDL_LockTexture(chunk->drawTexture, NULL, NULL, NULL);
		}

	for (size_t y = 0; y < CHUNK_AMT_BG; y++)
		for (size_t x = 0; x < CHUNK_AMT_BG; x++)
		{
			Chunk* chunk = &bGroundChunks[x][y];

			chunk->pos = Point(x * CHUNK_SIZE, y * CHUNK_SIZE);
			chunk->drawTexture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, CHUNK_SIZE, CHUNK_SIZE);

			SDL_SetTextureBlendMode(chunk->drawTexture, SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(r, chunk->drawTexture);

			for (size_t i = 0; i < SMALL_STAR_AMT / 2; i++)
				SDL_RenderCopy(r, smallStarTexture, &smallStarSource, &getQuickRect(rand() % CHUNK_SIZE, rand() % CHUNK_SIZE, 3, 3));
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

	offset.x = clamp(offset.x, CHUNK_SIZE, CHUNK_AMT_FG * CHUNK_SIZE);
	offset.y = clamp(offset.y, CHUNK_SIZE, CHUNK_AMT_FG * CHUNK_SIZE);

	int rx = offset.x / CHUNK_SIZE;
	int ry = offset.y / CHUNK_SIZE;

	int rfx = offset.x / CHUNK_SIZE / 2;
	int rfy = offset.y / CHUNK_SIZE / 2;

	int rbx = offset.x / CHUNK_SIZE / 4;
	int rby = offset.y / CHUNK_SIZE / 4;

	int ix = clamp(rx, 0, CHUNK_AMT_BG);
	int iy = clamp(ry, 0, CHUNK_AMT_BG);

	//cout << ix << ":" << iy << ", " << (ix * CHUNK_SIZE) + offset.x << ":" << (iy * CHUNK_SIZE) + offset.y << endl;

	for (size_t y = 0; y < 4; y++)
		for (size_t x = 0; x < 5; x++)
		{
			ix = clamp(rbx + x, 0, CHUNK_AMT_BG);
			iy = clamp(rby + y, 0, CHUNK_AMT_BG);
			quickImage(r, bGroundChunks[ix][iy].drawTexture, ix * CHUNK_SIZE - offset.x/4, iy * CHUNK_SIZE - offset.y/4);
			ix = clamp(rfx + x, 0, CHUNK_AMT_FG);
			iy = clamp(rfy + y, 0, CHUNK_AMT_FG);
			quickImage(r, fGroundChunks[ix][iy].drawTexture, ix * CHUNK_SIZE - offset.x/2, iy * CHUNK_SIZE - offset.y/2);
		}


}
