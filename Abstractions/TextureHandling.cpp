
namespace TH
{
  class Sprite{
  public:
    SDL_Texture *texture;
    SDL_Surface *surface;
    std::string path;

    Sprite();
    Sprite(string inpPath);
    loadFromPath();
    ~Sprite(){
      SDL_DestroyTexture(texture);
      SDL_FreeSurface(surface);
    }

  };

  vector<Sprite *> allSprites;
  vector<Sprite *> queueRender;

  SDL_Renderer* renderer;
  SDL_Window* window;
  SDL_Surface* screen;

  void init(SDL_Renderer* r, SDL_Window* w, SDL_Surface* s){
    vector<Sprite *> allSprites = vector<Sprite *>(0);
    vector<Sprite *> queueRender = vector<Sprite *>(0);

    renderer = r;
    window = w;
    screen = s;
  }

  void addToRenderQueue(Sprite *sp){
    queueRender.push_back(sp);
  }

  void popCreateQueue(){
    queueRender.at(0)->texture = SDL_CreateTextureFromSurface(renderer, queueRender.at(0)->surface);
    queueRender.erase(queueRender.begin());
  }

  void shutdown()
  {
    while (int(queueRender.size()) > 0)
    {
      if(queueRender.at(0)!= NULL)
        delete queueRender.at(0);
      
      queueRender.erase(queueRender.begin());
    } 
  }

  Sprite::Sprite()
  {
    texture = NULL;
    surface = NULL;
    path = "";
  }

  Sprite::Sprite(string inpPath)
  {
    texture = NULL;
    surface = NULL;
    path = inpPath;
  }

  Sprite::loadFromPath()
  {
    char[] buffer = path.c_str();
    surface = IMG_Load(path);
    cout << "Load From Path: " << path << " " << surface;
  }
}