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
    Sprite(bool thread);
    //Sprite& operator=(Sprite other);
    SDL_Texture* get(){

      return texture;
    }
    Sprite(const Sprite& sp);
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
      vector<Sprite *> allSprites = vector<Sprite *>(0);
      vector<Sprite *> queueCreate=vector<Sprite *>(0);
      vector<Sprite *> queueRender=vector<Sprite *>(0);

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
      cout << "\t<POP>" << endl;
      queueCreate.at(0)->texture = SDL_CreateTextureFromSurface(renderer, queueCreate.at(0)->source);
      //queueRender.push_back(queueCreate.at(0));

      //SDL_FreeSurface(queueCreate.at(0)->source);
      queueCreate.erase(queueCreate.begin());

      cout << "\t </POP>" << endl;
    }

    void doQueue(){
      cout << "DOING QUEUE: " << endl;
      int count = 0;
      while(queueCreate.size()>0){
        popCreateQueue();
        count++;
      }
      cout << "POPED " << count << " Images" << endl;
    }

  };

  TextureHandler textureHandler = TextureHandler();

  //Sprite class definitions
  /*
  Sprite& operator=(Sprite other){

    swap(texture, other.texture);
    swap(surface, other.surface);
    return *this;

  }
  */
  Sprite::Sprite(const Sprite& sp){

    texture=sp.texture;
    source =sp.source;
    w=sp.w;
    h=sp.h;

  }

  Sprite::Sprite(){

    new Sprite(this);

    //textureHandler.allSprites.push_back(this);
  }
  Sprite::Sprite(bool thread){
    if(thread){
    }else{
    }
  }

  Sprite::Sprite(SDL_Surface* src, bool thread){
    //textureHandler.allSprites.push_back(this);
    cout << "\t\t" << "a" << endl;
    if(thread){
      cout << "\t\t" << "b" << endl;
      textureHandler.addCreateQueue(this);
      source=src;
      w=src->w;
      h=src->h;
      cout << "\t\t" << "c" << endl;
    }else{

      texture = SDL_CreateTextureFromSurface(textureHandler.renderer,src);
      w=src->w;
      h=src->h;

    }

  }


  Sprite * TH_CreateSpriteForLoad(SDL_Surface* src){
    return new Sprite(src,true);
  }






}
