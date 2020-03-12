class GameShip : public GameObject{
public:
  vector<vector<GamePart>> contents = vector<vector<GamePart>>(); //Game Part objects that constitute the ship
	vector<SDL_Point> engines = vector<SDL_Point>(); //Index x, y for all engines of ship (prevent unecissary for loops)
	vector<SDL_Point> weapons = vector<SDL_Point>(); //Index x, y, for all weapons of the ship ^
	//physical data
	int w = DEFAULT_SHIP_DIM; //index width
	int h = DEFAULT_SHIP_DIM; //index height
	int weight = 0; //mass
	int fuel = 0;

  int index; //index in the gameObjects vector. See GameObjects.cpp


  int x; //global x coordinate
  int y; //global y coordinate
  float velx;
  float vely;
  float rot; //degrees
  float rotvel;

	bool updated = true;
	float acceleration = 0;
	float angularAcceleration = 1.0;
	int fuelConsumption = 0;
	float thrust = 0;
	SDL_Point centerOfMass; //index in contents at which the center of mass lies
	//visuals
	SDL_Texture* texture; //normal drawing texture
	SDL_Texture* overlayTexture; //texture with alternate sprites
	SDL_Texture* mapTexture; //texture for Player view (see player.h, or cosmoCombat.h)
	SDL_Texture* animationsTexture; //texture to use as placeholder for animations on a given frame. Not Persistent
	bool needsOverlay;
	AnimationInstance exhaust; //See animations.cpp
	//state-booleans
	bool enginesOn = false;

  GameShip(){}
  GameShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen);/**
  *\breif creates a new GameShip object
  *\param w the width in indexes of the GameShip
  *\param h the height in indexes of the GameShip
  *\param screen (used to initialize textures)
  **/

	void setAttributes();/**
  *\warning can be expensive
  *\breif uses for loop to force-set all the ship's attributes based on it's contents
  **/
	void placePart(int x, int y, GamePart p);/**
  *\breif x and y are index. Ship's properties will be updated
  **/
	void placePart(int x, int y, int part, float r);/**
  *\brief x and y are index. Ship's properties will be updated
  *\param part the part id number (see itemData.cpp)
  *\param r the rotation at which the part should be placed (must be multiple of 90)
  **/
	void bufferMapTexture();/**
  *\brief updates the mapTexture buffer
  *\warning uses rendering -> expensive
  **/
	void bufferOverlay();/**
  *\breif updates the overlay texture
  *\warning uses rendering -> expensive
  **/
	SDL_Texture* buffer(SDL_Renderer* renderer, SDL_Surface* screen);/**
  *\breif updates the general purpose texture
  *\warning uses rendering -> expensive
  **/

	void drawBSP(SDL_Renderer* renderer);/**
  *\breif draws the ship for the Ship Building page (see gameStates, or UIConfig)
  **/
	void physics();/**
  *\brief updates coordinates (not collision)
  **/
	void clearOverlay();/**
  *\breif clears the overlayTexture
  **/
	void renderOverlay();/**
  *\breif rerenders the contents of the overlay texture
  **/
	void drawShipView(SDL_Renderer* renderer);/**
  *\brief draw the ship for ship view (see gameStates)
  **/
	void drawPlayerView(SDL_Renderer* renderer);/**
  *\breif draws the ship for Player View, using the shipmap texture
  **/

  void draw(SDL_Renderer* renderer);/**
  *\breif inherited from GameObject (not used)
  **/
  void init();/**
  *\
  **/
  void collision();/**
  *\
  **/


};


vector<GameShip> bluePrints;
GameShip *current_Ship;//ship that the player is currently flying (ship view)

int globalTranslationFactorX=0;
int globalTranslationFactorY=0;

void setTranslationFactor(){
  globalTranslationFactorX=current_Ship->x;
  globalTranslationFactorY=current_Ship->y;
}

void globalToLocal(int &x,int &y){

  x-=globalTranslationFactorX;
  y-=globalTranslationFactorY;

}

void localToGlobal(int &x,int &y){

  x+=globalTranslationFactorX;
  y+=globalTranslationFactorY;

}






//Coordinates:
SDL_Point globalToLocalPlayer(int x, int y);
SDL_Point localToGlobalPlayer(int x, int y);

SDL_Point globalToLocalShip(int x, int y){

	return point(x-current_Ship->x,y-current_Ship->y);

}
SDL_Point localToGlobalShip(int x, int y){

	return point(x+current_Ship->x,y+current_Ship->y);

}


#include "Ship.cpp"
