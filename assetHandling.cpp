#define FPS24 1000/24
#define FPS60 1000/60



vector<SDL_Texture* > sprites;
Animation Shoulders1;


void loadSprites(SDL_Renderer *renderer) {

	for (int i = 0; i < 15; i++) {
		SDL_Texture* sp = loadImage(renderer,string("assets\\sprites\\").append(to_string(i).append(".PNG")).c_str());
		sprites.push_back(sp);
	}
	Shoulders1 = Animation(file_fix("assets\\Animations\\player\\Shoulders1\\"),24,FPS24);
	Shoulders1.activeState = MAIN_MENU;

}


SDL_Texture* sprite(int index) {

	return sprites.at(index);

}
