#define PLAYER_DIM 150
class Player{

public:
  int x = 0;
  int y = 0;
  int velx = 0;
  int vely = 0;
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
    //shouldersAnimation = AnimationInstance(Shoulders1);
    //armsAnimation=AnimationInstance(Arms1);
    //textureRect = getTextureRect(armsAnimation.get());
  }

  Player(int x, int y){

    shouldersAnimation = AnimationInstance(Shoulders1);
    armsAnimation=AnimationInstance(Arms1);
    this->x=x;
    this->y=y;


  }
  void physics(){

    x+=velx;
    y+=vely;

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
    physics();
    //shoulders,arms,head
    //image(renderer, shouldersAnimation.get(), textureRect, getQuickRect(width/2-SPRITE_DIM/2,height/2-SPRITE_DIM/2,SPRITE_DIM,SPRITE_DIM));
    //image(renderer, armsAnimation.get(), textureRect,getQuickRect(width/2-SPRITE_DIM/2,height/2-SPRITE_DIM/2,SPRITE_DIM,SPRITE_DIM));
    image(renderer, sprite(12),getTextureRect(sprite(12)),getQuickRect(width/2-PLAYER_DIM/2,height/2-PLAYER_DIM/2,PLAYER_DIM,PLAYER_DIM));

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
