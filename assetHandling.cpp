//quick FPS numbers
#define FPS24 1000/24
#define FPS60 1000/60
#define FPS12 1000/12
#define FPS6  1000/6

bool allSpritesLoaded = false;
int spritesLoaded = 0;

vector<Sprite*> sprites;
vector<AnimationInstance *> anims;

//animations:
	//world
Animation Fire1;

	//player
Animation Shoulders1;
Animation Arms1;

//vector<TH::Sprite> sprites;


// </animations>


void checkAllSprites()
{
	cout << "Sprites" << time(NULL) << ":" << endl;
	for (int i = 0; i < 16; i++)
	{
		cout << "\t" << i << ": ";
		if (sprites.at(i) == NULL)
			cout << "NULL";
		else
			cout << "SUCCESS";
		cout << "\n";	
	}
}

void loadSprites(SDL_Renderer *renderer)
//load all sprites in the "assets\sprites\" folder into a single vector, to be referenced later
{
	cout << "Loading Assets: " << endl;
	anims = vector<AnimationInstance *>(0);
	for (int i = 0; i < 17; i++) {
		Sprite bufferSprite(string("assets\\sprites\\").append(to_string(i).append(".PNG"));		
		sprites.push_back(&bufferSprite);
		cout << i << " / 17" << endl;
	}

	for (size_t i = 0; i < sprites.size(); i++)
	{
		sprites.at(i).loadFromPath();
	}
	

	//load animations
	cout << endl << "Loading Animations: " << endl;
	Fire1 = Animation(file_fix("assets\\Animations\\world\\fire1\\"),24,FPS24);
	spritesLoaded += 24;
	Shoulders1 = Animation(file_fix("assets\\Animations\\player\\Shoulders1\\"), 24,FPS24);
	spritesLoaded += 24;
	Arms1 = Animation(file_fix("assets\\Animations\\player\\Arms1\\"),24,FPS24);
	spritesLoaded += 24;

	cout << "Loaded Sprites: " << spritesLoaded << endl;
	checkAllSprites();
	allSpritesLoaded = true;
}

//used each frame to tick all active animations
void handleAnimations(){
	for(int i = 0 ; i < anims.size();i++){

		anims.at(i)->tick();

	}

}

SDL_Texture* sprite(int index) {//quick access to a sprite by its index number

	return sprites.at(index);

}
