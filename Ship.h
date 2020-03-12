class GameShip : public GameObject{
public:
  vector<vector<GamePart>> contents = vector<vector<GamePart>>();
	vector<SDL_Point> engines = vector<SDL_Point>();
	vector<SDL_Point> weapons = vector<SDL_Point>();
	//physical data
	int w = DEFAULT_SHIP_DIM;
	int h = DEFAULT_SHIP_DIM;
	int weight = 0;
	int fuel = 0;

  int index;


  int x;
  int y;
  float velx;
  float vely;
  float rot;
  float rotvel;

	bool updated = true;
	float acceleration =0;
	float angularAcceleration = 1.0;
	int fuelConsumption = 0;
	float thrust = 0;
	SDL_Point centerOfMass;
	//visuals
	SDL_Texture* texture;
	SDL_Texture* overlayTexture;
	SDL_Texture* mapTexture;
	SDL_Texture* animationsTexture;
	bool needsOverlay;
	AnimationInstance exhaust;
	//state-booleans
	bool enginesOn = false;

  GameShip(){}
  GameShip(int w, int h, SDL_Renderer* renderer, SDL_Surface* screen);

	void setAttributes();
	void placePart(int x, int y, GamePart p);
	void placePart(int x, int y, int part, float r);
	void bufferMapTexture();
	void bufferOverlay();
	SDL_Texture* buffer(SDL_Renderer* renderer, SDL_Surface* screen);

	void drawBSP(SDL_Renderer* renderer);
	void physics();
	void clearOverlay();
	void renderOverlay();
	void drawShipView(SDL_Renderer* renderer);
	void drawPlayerView(SDL_Renderer* renderer);

  void draw(SDL_Renderer* renderer);
  void init();
  void collision();


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
