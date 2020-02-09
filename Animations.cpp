class Animation{

private:
  vector<SDL_Texture* > frames;
public:
  int delay =0 ;
  int currentFrame = 0;
  int lastTick = 0;
  bool active = true;
  Animation(string path, int numFrames, int indelay);
  SDL_Texture* get();
  void tick();
  void destroy();

};
vector<Animation *> animations;

Animation::destroy(){

  animations.remove(this);


}

Animation::Animation(string path, int numFrames, int indelay){

  for(int i = 0 ; i < numFrames;i++){

    string file = path + to_string(i);
    file+=".PNG";
    frames.push_back(loadImage(renderer, file.c_str()));


  }
  delay = indelay;
  animations.push_back(this);

}

SDL_Texture* Animation::get(){

  return frames.at(currentFrame);

}

void Animation::tick(){
  if(!active)return;
  if(now()-lastTick > delay){
    currentFrame=(currentFrame+1)%frames.size();
    lastTick=now();
  }

}
