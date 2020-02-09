
class Animation{

private:
    int count = 1;

public:
  vector<SDL_Texture* > frames;
  int delay =0 ;
  int currentFrame = 0;
  int lastTick = 0;

  bool active = true;
  gameState activeState = NONE_STATE;
  Animation();
  Animation(string path, int numFrames, int indelay);
  SDL_Texture* get();
  void tick();
  void destroy();

};
vector<Animation *> animations;
void removeFromVector(vector<Animation*> *e, Animation* t) {
	e->erase(remove(e->begin(), e->end(), t));
}
void Animation::destroy(){

  removeFromVector(&animations,this);


}
Animation::Animation(){
  active=false;
}

Animation::Animation(string path, int numFrames, int indelay){
  count = numFrames-1;
  cout << "COUNT INIT AT: " << count << endl;
  for(int i = 1 ; i <= numFrames;i++){
    //assets\Animations\player\Shoulders1\1.png
    string file = path + to_string(i);
    file+=".png";
    cout << "loading: " << file << endl;
    SDL_Texture *f = loadImage(renderer, file.c_str());
    frames.push_back(f);

  }
  delay = indelay;
  animations.push_back(this);

}

SDL_Texture* Animation::get(){
  return frames.at(currentFrame);

}

void Animation::tick(){
  if(state==activeState)active=true;
  if(!active)return;
  if(now()-lastTick > delay){
    cout << count << endl;
    currentFrame=(currentFrame+1)%count;
    lastTick=now();

  }
}
void handleAnimations(void* ptr){
  while(true){
    SDL_Delay(1);
    for(int i = 0 ; i < animations.size();i++){

      animations.at(i)->tick();

    }
  }

}
void startAnimations(){

  SDL_CreateThread(&handleAnimations,"AnimationsThread",nullptr);

}
