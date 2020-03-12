#define PLAYER_DIM 150

class Player{

public:
  int x = 0;
  int y = 0;
  int velx = 0;
  int vely = 0;
  Direction rot = UP;
  int shoulders = 0;
  int arms = 0;
  int head = 0;

  AnimationInstance shouldersAnimation;
  AnimationInstance armsAnimation;
  AnimationInstance headAnimation;

  SDL_Rect textureRect = {0,0,FSDIM,FSDIM};

  Player(){
    //place in center by default
    x=width/2 + (DEFAULT_SHIP_DIM*FSDIM)/2;
    y=width/2 + (DEFAULT_SHIP_DIM*FSDIM)/2;
    shouldersAnimation = AnimationInstance(&Shoulders1);
    armsAnimation=AnimationInstance(&Arms1);
    cout << "ShouldersAnimation size:" << shouldersAnimation.origin->frames.size() << endl;
    anims.push_back(&shouldersAnimation);
    anims.push_back(&armsAnimation);
  }

  Player(int x, int y){

    shouldersAnimation = AnimationInstance(&Shoulders1);
    armsAnimation=AnimationInstance(&Arms1);
    cout << "ShouldersAnimation size:" << shouldersAnimation.origin->frames.size() << endl;
    anims.push_back(&shouldersAnimation);
    anims.push_back(&armsAnimation);
    this->x=x;
    this->y=y;


  }
  void physics(){

    x+=velx;
    y+=vely;

    velx=clamp(velx,-2,2);
    vely=clamp(vely,-2,2);

    if(velx>0){
      velx--;
    }else if (velx<0){
      velx++;
    }

    if(vely>0){
      vely--;
    }else if (vely<0){
      vely++;
    }

  }



  void drawLocal(){

    //if moving, tick animations
    if(velx!=0||vely!=0){
      armsAnimation.tick();
      shouldersAnimation.tick();
    }else{
      armsAnimation.frame=0;
      armsAnimation.frame=0;
    }

    physics();
    //shoulders,arms,head
    image(renderer,armsAnimation.get(), getTextureRect(armsAnimation.get()),getQuickRect(width/2-PLAYER_DIM/2,height/2-PLAYER_DIM/2,PLAYER_DIM,PLAYER_DIM),rotFromDir(rot),point(PLAYER_DIM/2,PLAYER_DIM/2),SDL_FLIP_NONE);
    image(renderer, shouldersAnimation.get(), getTextureRect(shouldersAnimation.get()), getQuickRect(width/2-PLAYER_DIM/2,height/2-PLAYER_DIM/2,PLAYER_DIM,PLAYER_DIM),rotFromDir(rot),point(PLAYER_DIM/2,PLAYER_DIM/2),SDL_FLIP_NONE);
    image(renderer, sprite(12),getTextureRect(sprite(12)),getQuickRect(width/2-PLAYER_DIM/2,height/2-PLAYER_DIM/2,PLAYER_DIM,PLAYER_DIM),rotFromDir(rot),point(PLAYER_DIM/2,PLAYER_DIM/2),SDL_FLIP_NONE);

  }



};
Player me;

//player context coordinate conversions
SDL_Point globalToLocalPlayer(int x, int y){

  return point(x-me.x,y-me.y);

}
SDL_Point localToGlobalPlayer(int x, int y){

  return point(x+me.x,y+me.y);

}
