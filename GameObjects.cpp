#define MAX_OTHER_SHIPS 1024

GameShip otherShips[MAX_OTHER_SHIPS];



void preAllocateShips(){
  loadingMessage = "Allocating Ships";
  for(int i = 0 ; i < MAX_OTHER_SHIPS;i++){
    otherShips[i] = createNewShip(DEFAULT_SHIP_DIM,DEFAULT_SHIP_DIM,renderer, screen);
  }

}





enum Particle_Type{

  SMOKE, FLAME, DEAD_ROOM, DEAD_DERELECT_ROOM

};
enum Projectile_Type{

  TORPEDO_BASIC, INJECTOR

};

class Particle{

  int x, y;
  float velx,vely,rotel,rot;


};


class Projectile{



};


vector<Particle> particles = vector<Particle>();
vector<Projectile> projectiles = vector<Projectile>();
