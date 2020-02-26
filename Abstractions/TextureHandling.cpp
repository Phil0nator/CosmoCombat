namespace TextureHandling{


  class Sprite{
  public:
    SDL_Texture *texture;
    SDL_Surface *source;
    int w = 0;
    int h = 0;

    Sprite(SDL_Surface* src, bool thread);
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

    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* screen;

    TextureHandler(){

    }

    void setup(SDL_Renderer*r, SDL_Window*w, SDL_Surface*s){
      renderer=r;
      window=w;
      screen=s;
    }

    void addCreateQueue(Sprite* sp){
      queueCreate.push_back(sp);
    }

    void popCreateQueue(){
      queueCreate.at(0)->texture = SDL_CreateTextureFromSurface(renderer, queueCreate.at(0)->source);
      //queueRender.push_back(queueCreate.at(0));
      SDL_FreeSurface(queueCreate.at(0)->source);
      queueCreate.erase(queueCreate.begin());
    }

    void doQueue(){
      while(queueCreate.size()>0){
        popCreateQueue();
      }

    }

  };

  TextureHandler textureHandler = TextureHandler();

  //Sprite class definitions
  Sprite::Sprite(){
    textureHandler.allSprites.push_back(this);
  }
  Sprite::Sprite(SDL_Surface* src, bool thread){
    textureHandler.allSprites.push_back(this);

    if(thread){

      textureHandler.addCreateQueue(this);
      this->source=src;
      this->w=src->w;
      this->h=src->h;
    }else{

      this->texture = SDL_CreateTextureFromSurface(textureHandler.renderer,src);
      this->w=src->w;
      this->h=src->h;

    }

  }









}
