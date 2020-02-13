class Animation{ //storage class, only one made of each possuble animation



public:
  vector<SDL_Texture* > frames;

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
  frames = vector<SDL_Texture* >(numFrames);
  cout << "numberOfFrames INIT AT: " << numberOfFrames << "            " << &numberOfFrames << endl;
  for(int i = 1 ; i <= numFrames;i++){
    //assets\Animations\player\Shoulders1\1.png
    string file = path + to_string(i);
    file+=".png";
    cout << "loading: " << file << endl;
    SDL_Texture *f = loadImage(renderer, file.c_str());
    frames.at(i-1)=f;
  }

  delay = indelay;
  cout << "Delay starts @" << delay << endl;
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
  Animation origin;
  int frame = 0;
  int lastTick = now();
  bool active = true;

  AnimationInstance(){}

  AnimationInstance(Animation o){

    origin = o;
  }
  void tick(){

    if(!active)return;

    if(now()-lastTick>origin.delay){
      frame++;
      if(frame>=origin.numberOfFrames){
        frame=0;

      }
      lastTick = now();

    }

  }

  SDL_Texture* get(){
    return origin.frames.at(frame);

  }


};
