#define MAX_OTHER_SHIPS 1024
GameShip otherShips[MAX_OTHER_SHIPS];
void preAllocateShips(){
  loadingMessage = "Allocating Ships";
  for(int i = 0 ; i < MAX_OTHER_SHIPS;i++){
    otherShips[i] = createNewShip(DEFAULT_SHIP_DIM,DEFAULT_SHIP_DIM,renderer, screen);
  }

}
enum Particle_Type{

  SMOKE, FLAME, DEAD_ROOM, DEAD_DERELECT_ROOM, PARTICLE_NONE

};

enum Projectile_Type{

  TORPEDO_BASIC, INJECTOR, PROJECTILE_NONE

};
class GameObject{
public:
  double x,y;
  unsigned int w,h;
  double velx, vely;
  Particle_Type particleType = PARTICLE_NONE;
  Projectile_Type projectileType = PROJECTILE_NONE;
  AnimationInstance anim;
  Sprite *primary;

  virtual void draw(SDL_Renderer* renderer);
  virtual void physics();


};
class Particle : public GameObject{



};
