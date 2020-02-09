


vector<SDL_Texture* > sprites;
Animation Shoulders1;


void loadSprites(SDL_Renderer *renderer) {

	for (int i = 0; i < 15; i++) {
		SDL_Texture* sp = loadImage(renderer,string("assets\\sprites\\").append(to_string(i).append(".PNG")).c_str());
		sprites.push_back(sp);
	}

	


}


SDL_Texture* sprite(int index) {

	return sprites.at(index);

}
