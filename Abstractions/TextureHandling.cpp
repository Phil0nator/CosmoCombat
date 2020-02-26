namespace TextureHandling{


  class Sprite{
  public:
    SDL_Texture *texture;
    SDL_Surface *source;

    Sprite(SDL_Texture *dest, SDL_Surface* src);
    Sprite(SDL_Texture* inp);
    Sprite();
    SDL_Texture* get(){
      return texture;
    }

    ~Sprite(){
      SDL_DestroyTexture(texture);
      SDL_FreeSurface(source);
    }

  };


  class TextureHandler{
  public:
    vector<Sprite *> allSprites;
    vector<Sprite *> queueCreate;
    vector<Sprite *> queueRender;

    TextureHandler(){

    }

  };

  TextureHandler textureHandler = TextureHandler();

  //Sprite class definitions
  Sprite::Sprite(){}










}
