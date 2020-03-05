//quick FPS numbers
#define FPS24 1000/24
#define FPS60 1000/60
#define FPS12 1000/12
#define FPS6  1000/6
#define ASSET_NUMBER 17

vector<Sprite *> sprites;
vector<AnimationInstance *> anims;

//animations:
	//world
Animation Fire1;

	//player
Animation Shoulders1;
Animation Arms1;


// </animations>

// UI Element Standards
Sprite *UI_B1;
/*	*/Sprite *UI_B1_C;
/*	*/Sprite *UI_B1_H;
Sprite *UI_B2;
/*	*/Sprite *UI_B2_C;
/*	*/Sprite *UI_B2_H;
Sprite *UI_B3;
/*	*/Sprite *UI_B3_C;
/*	*/Sprite *UI_B3_H;

Sprite *UI_B_BG1;

// </UI>
void loadSprites(SDL_Renderer *renderer)
//load all sprites in the "assets\sprites\" folder into a single vector, to be referenced later
{
	loadingMessage = "Loading Assets...";
	anims = vector<AnimationInstance *>(0);
	sprites = vector<Sprite *>(0);
	for (int i = 0; i < ASSET_NUMBER; i++) {
		Sprite * sp = loadImage(renderer,string("assets\\sprites\\").append(to_string(i).append(".PNG")).c_str());
		loadingMessage =  to_string(i) + "/" + to_string(ASSET_NUMBER);
		sprites.push_back(sp);
	}
	//load animations
	cout << "loadingAnimations " << endl;
	loadingMessage= "Loading Animations: ";
	Fire1 = Animation(file_fix("assets\\Animations\\world\\fire1\\"),24,FPS24);
	Shoulders1 = Animation(file_fix("assets\\Animations\\player\\Shoulders1\\"), 24,FPS12);
	Arms1 = Animation(file_fix("assets\\Animations\\player\\Arms1\\"),24,FPS12);

	//Load UI specifics
	UI_B1 = loadImage(renderer,"assets\\UI\\B1\\b1.png");
	/*	*/UI_B1_C = loadImage(renderer, "assets\\UI\\B1\\b1c.png");
	/*	*/UI_B1_H = loadImage(renderer, "assets\\UI\\B1\\b1h.png");
	UI_B2 = loadImage(renderer,"assets\\UI\\B2\\b2.png");
	/*	*/UI_B2_C = loadImage(renderer, "assets\\UI\\B2\\b2c.png");
	/*	*/UI_B2_H = loadImage(renderer, "assets\\UI\\B2\\b2h.png");
	UI_B3 = loadImage(renderer,"assets\\UI\\B3\\b3.png");
	/*	*/UI_B3_C = loadImage(renderer, "assets\\UI\\B3\\b3c.png");
	/*	*/UI_B3_H = loadImage(renderer, "assets\\UI\\B3\\b3h.png");
	UI_B_BG1 = loadImage(renderer, "assets,\\UI\\bg.png");
}

//used each frame to tick all active animations
void handleAnimations(){
	for(int i = 0 ; i < anims.size();i++){

		//anims.at(i)->tick();

	}

}

SDL_Texture* sprite(int index) {//quick access to a sprite by its index number

	return sprites.at(index)->texture;

}
