#define MAX_OTHER_SHIPS 1024
#define MAX_GAMEOBJECT_LIFETIME 10000
#define MAX_PARTICLES 100
#define MAX_OBJECTS 10000000

int numParticles =0;

GameShip otherShips[MAX_OTHER_SHIPS];
void preAllocateShips(){
  loadingMessage = "Allocating Ships";
  for(int i = 0 ; i < MAX_OTHER_SHIPS;i++){
    otherShips[i] = createNewShip(DEFAULT_SHIP_DIM,DEFAULT_SHIP_DIM,renderer, screen);
  }

}
enum Particle_Type{

  PARTICLE_SMOKE, PARTICLE_FLAME, PARTICLE_DEAD_ROOM, PARTICLE_DEAD_DERELECT_ROOM, PARTICLE_NONE

};

enum Projectile_Type{

  TORPEDO_BASIC, INJECTOR, PROJECTILE_NONE

};

int globalTranslationFactorX=0;
int globalTranslationFactorY=0;

void setTranslationFactor(){
  globalTranslationFactorX=current_Ship->gx;
  globalTranslationFactorY=current_Ship->gy;
}

void globalToLocal(int &x,int &y){

  x-=globalTranslationFactorX;
  y-=globalTranslationFactorY;

}

void localToGlobal(int &x,int &y){

  x+=globalTranslationFactorX;
  y+=globalTranslationFactorY;

}

class GameObject{
public:
  double x,y; // COORDINATES ARE IN TERMS OF A GLOBAL CONTEXT (see alden's renderer)
  unsigned int w,h;
  double velx, vely;
  Particle_Type particleType = PARTICLE_NONE;
  Projectile_Type projectileType = PROJECTILE_NONE;
  AnimationInstance anim;
  Sprite *primary;
  int timeCreated;
  int index = 0;


  GameObject(){
    timeCreated=now();
  }
  ~GameObject(){}
  virtual void draw(SDL_Renderer* renderer) =0;
  virtual void physics(){

    x+=velx;
    y+=vely;



  }
  virtual void remove();
  virtual void collision() = 0;
  virtual void update(SDL_Renderer* renderer){
    physics();
    draw(renderer);
    if(now()-timeCreated>MAX_GAMEOBJECT_LIFETIME){
      remove();
    }
  }
  virtual void init() = 0;

  

};


vector<std::unique_ptr<GameObject > > gameObjects = vector<std::unique_ptr<GameObject > >();


void GameObject::remove(){

  gameObjects.erase(gameObjects.begin()+index);

}

class Particle : public GameObject{
public:

  Particle(){}

  Particle(int ax, int ay){

    x=ax;
    y=ay;

  }

  void collision(){
    //pass
  }

  void draw(SDL_Renderer* renderer){

    image(renderer, primary->texture,(SDL_Rect){0,0,primary->w,primary->h}, (SDL_Rect){x,y,w,h});

  }

  void init(){

    gameObjects.push_back(std::unique_ptr<GameObject>(this));
    index = gameObjects.size()-1;
  }

  void remove(){

    gameObjects.erase(gameObjects.begin()+index);
    numParticles--;
  }

};
void CreateSmokeParticle(int x, int y, SDL_Point initialVector){


  numParticles++;
  if(numParticles>MAX_PARTICLES)return;
  Particle *p = new Particle(x,y);
  p->w = SPRITE_DIM;
  p->h = SPRITE_DIM;
  p->particleType = PARTICLE_SMOKE;
  p->primary = sprites.at(16);
  p->velx = initialVector.x+(double)(randint(-50,50)/10);
  p->vely = initialVector.y+(double)(randint(-50,50)/10);
  p->timeCreated=now();
  p->init();

}


void handleGameObjects(SDL_Renderer* renderer){

  setTranslationFactor();  
  for(int i = 0 ; i < gameObjects.size();i++){

    gameObjects.at(i)->update(renderer);

  }

}
