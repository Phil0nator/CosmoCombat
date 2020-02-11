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
