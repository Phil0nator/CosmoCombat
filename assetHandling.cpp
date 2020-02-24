
//quick FPS numbers
#define FPS24 1000/24
#define FPS60 1000/60
#define FPS12 1000/12
#define FPS6  1000/6

<<<<<<< Updated upstream

=======
vector<Sprite> sprites;
vector<AnimationInstance *> anims;
>>>>>>> Stashed changes

//animations:
	//world
Animation Fire1;

	//player
Animation Shoulders1;
Animation Arms1;


// </animations>

void loadSprites(SDL_Renderer *renderer)
//load all sprites in the "assets\sprites\" folder into a single vector, to be referenced later
{
<<<<<<< Updated upstream
	anims = vector<AnimationInstance* >(0);
	sprites = vector<SDL_Texture* >(0);
	for (int i = 0; i < 16; i++) {
		SDL_Texture* sp = loadImage(renderer,string(file_fix("assets\\sprites\\")).append(to_string(i).append(".PNG")).c_str());
		sprites.push_back(sp);
	}
	//load animations
	Fire1 = Animation(file_fix("assets\\Animations\\world\\fire1\\"),24,FPS24);
	Shoulders1 = Animation(file_fix("assets\\Animations\\player\\Shoulders1\\"), 24,FPS24);
	Arms1 = Animation(file_fix("assets\\Animations\\player\\Arms1\\"),24,FPS24);
=======
	cout << "bruh a" << endl;
	//load animations
	loadingMessage= "Loading Animations: ";
	Shoulders1 = Animation(renderer,file_fix("assets\\Animations\\player\\Shoulders1\\"), 24,FPS24);
	Fire1 = Animation(renderer,file_fix("assets\\Animations\\world\\fire1\\"),24,FPS24);
	Arms1 = Animation(renderer,file_fix("assets\\Animations\\player\\Arms1\\"),24,FPS24);

	cout << "bruh b" << endl;
	loadingMessage = "Loading Assets...";
	anims = vector<AnimationInstance *>(0);
	for (int i = 0; i < ASSET_NUMBER; i++) {
		Sprite sp = Sprite(renderer,file_fix(string("assets\\sprites\\").append(to_string(i).append(".PNG")).c_str()    ));
		cout << "bruh: " << i << endl;
		loadingMessage =  to_string(i) + "/" + to_string(ASSET_NUMBER);
		sprites.push_back(sp);
	}

>>>>>>> Stashed changes


}

//used each frame to tick all active animations
void handleAnimations(){
	for(int i = 0 ; i < anims.size();i++){

		anims.at(i)->tick();

	}

}

SDL_Texture* sprite(int index) {//quick access to a sprite by its index number

	return sprites.at(index).get();

}
