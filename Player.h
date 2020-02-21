class Player{

public:
  int x = 0;
  int y = 0;
  int shoulders = 0;
  int arms = 0;
  int head = 0;

  AnimationInstance shouldersAnimation;
  AnimationInstance armsAnimation;
  AnimationInstance headAnimation;

  SDL_Rect textureRect;

  Player(){

    //shouldersAnimation = AnimationInstance(Shoulders1);
    //armsAnimation=AnimationInstance(Arms1);
    //textureRect = getTextureRect(armsAnimation.get());
  }

  Player(int x, int y){

    shouldersAnimation = AnimationInstance(Shoulders1);
    armsAnimation=AnimationInstance(Arms1);
    this->x=x;
    this->y=y;
    textureRect = getTextureRect(armsAnimation.get());

  }

  drawLocal(){

    //shoulders,arms,head
    image(renderer, shouldersAnimation.get(), textureRect, getQuickRect(width/2-SPRITE_DIM/2,height/2-SPRITE_DIM/2,SPRITE_DIM,SPRITE_DIM));
    image(renderer, armsAnimation.get(), textureRect,getQuickRect(width/2-SPRITE_DIM/2,height/2-SPRITE_DIM/2,SPRITE_DIM,SPRITE_DIM));
    image(renderer, sprite(12),textureRect,getQuickRect(width/2-SPRITE_DIM/2,height/2-SPRITE_DIM/2,SPRITE_DIM,SPRITE_DIM));

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
