class Animation{ //storage class, only one made of each possuble animation

public:
  vector<TH::Sprite* > frames;
  int numberOfFrames = 1;
  int delay = 0;

  Animation::Animation();
  Animation::Animation(string path, int numFrames, int indelay);
  Animation::Animation( const Animation& a );
  ~Animation();
};

Animation::~Animation(){
}

Animation::Animation(){
}

Animation::Animation( const Animation& a ){
  delay = a.delay;
  numberOfFrames = a.numberOfFrames;
  frames = a.frames;
} //copy contstructor

Animation::Animation(string path, int numFrames, int indelay){
  numberOfFrames = numFrames-1;
  frames = vector<TH::Sprite *>();
  
  cout << "NUMFRAMES: " << numFrames << endl;

  for (int i = 0 ; i < numFrames; i++)
  {
    cout << clearLine <<"Load_Animation: " << i << "/" << numFrames << "                ";
    string file = path + to_string(i + 1);
    file += ".png";
    
    TH::Sprite buffer(path);

    frames.push_back(&buffer);
    TH::addToRenderQueue(&buffer);
  }

  delay = indelay;
}


//instance class-> used to create seperate instances of a single animation
/*
EX: multiple flames:
  multiple AnimationInstance objects, all referencing one single flame animation
  each one would tick independantly, and could be turned on and off independantly
  but would all have the same set of images, stored in class Animtion -> AnimationObject.origin
*/
class AnimationInstance{


public:
  Animation *origin;

  int frame = 0;
  int lastTick = now();
  bool active = true;

  AnimationInstance(){}

  AnimationInstance(Animation *o){
    origin = o;
  }

  void tick(){
    if(!active) {return;}
    if(now() - lastTick > origin->delay){
      frame++;

      if(frame>=origin->frames.size()){
        frame=0;
      }

      lastTick = now();
    }
  }

  SDL_Texture* get(){
    return origin->frames.at(frame)->texture;
  }

};
