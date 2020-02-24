#define DEFAULT_EMPTIES 24

namespace TextureHandling{


  class Sprite{
  public:
    SDL_Texture* texture;
    SDL_Surface* source;
    int w = 1000;
    int h = 1000;

    Sprite(SDL_Renderer* renderer, int w, int h){

      texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h); //setup new texture
    	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //for transparency
      this->w = w;
      this->h=h;
    }
    Sprite(){

      

    }

    Sprite(SDL_Renderer* renderer, const char* path){

      source = IMG_Load(path);
      cout << "Loaded File: " <<  path<<endl;
    	texture= SDL_CreateTextureFromSurface(renderer, source);
      w = source->w;
      h = source->h;

    }

    SDL_Texture*get(){
      return texture;
    }

    ~Sprite(){

      SDL_DestroyTexture(texture);
      SDL_FreeSurface(source);

    }


  };




  class TextureHandler{
  public:

    SDL_Renderer* renderer;
    SDL_Surface* screen;
    SDL_Window* window;






    TextureHandler(){
    }

    TextureHandler(SDL_Renderer* renderer, SDL_Surface* screen, SDL_Window* window){
      this->renderer=renderer;
      this->screen = screen;
      this->window=window;
    }


  };












}
