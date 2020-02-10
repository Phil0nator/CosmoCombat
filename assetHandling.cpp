//quick FPS numbers
#define FPS24 1000/24
#define FPS60 1000/60
#define FPS12 1000/12
#define FPS6  1000/6


vector<SDL_Texture* > sprites;
vector<AnimationInstance* > anims;
Animation Shoulders1;
AnimationInstance s1;


void loadSprites(SDL_Renderer *renderer)
//load all sprites in the "assets\sprites\" folder into a single vector, to be referenced later
{
	anims = vector<AnimationInstance* >(0);
	for (int i = 0; i < 15; i++) {
		SDL_Texture* sp = loadImage(renderer,string("assets\\sprites\\").append(to_string(i).append(".PNG")).c_str());
		sprites.push_back(sp);
	}
	Shoulders1 = Animation(file_fix("assets\\Animations\\world\\fire1\\"),24,FPS24);
	s1 = AnimationInstance(Shoulders1);
	anims.push_back(&s1);

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
