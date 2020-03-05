enum Particle_Type{

  SMOKE, FLAME, DEAD_ROOM, DEAD_DERELECT_ROOM

};
enum Projectile_Type{

  TORPEDO_BASIC, INJECTOR

};

class Particle{

  int x, y;
  float velx,vely,rotel,rot;

<<<<<<< Updated upstream
=======
class GameObject{
public:
  double x,y; // COORDINATES ARE IN TERMS OF A GLOBAL CONTEXT (see alden's renderer)
  unsigned int w,h;
  double velx, vely;
  double rot = 0;
  double rotvel = 0;
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
    rot+=rotvel;


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


>>>>>>> Stashed changes

};


class Projectile{



};
<<<<<<< Updated upstream
=======
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
>>>>>>> Stashed changes


vector<Particle> particles = vector<Particle>();
vector<Projectile> projectiles = vector<Projectile>();
