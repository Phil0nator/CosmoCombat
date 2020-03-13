//standard location for all project #define

//* WORLD *//

    #define SIZE_X 20000
    #define SIZE_Y 20000
    #define CHUNK_SIZE 500
    #define CHUNK_AMT_FG 20
    #define CHUNK_AMT_BG 10

    #define SMALL_STAR_AMT 100
    #define MED_STAR_AMT 5
    #define BIG_STAR_AMT 1
    #define ASTEROID_AMT 10


// * \World *//

//* PARTS *//

    #define MAX_PARTS 128

//* \PARTS *//

//* PLAYER *//

    #define PLAYER_DIM 150

//* \PLAYER *//

//* GAME-OBJECTS *//

    #define MAX_OTHER_SHIPS 1024
    #define MAX_GAMEOBJECT_LIFETIME 10000
    #define MAX_PARTICLES 100
    #define MAX_OBJECTS 10000000


//* \GAME-OBJECTS *//

//* ASSETS *//

    #define ICON_DIM 75 //dimention of icons

    #define SPRITE_DIM 100 // dimention of Sprites (the size of rooms in a ship for example)
    #define FSDIM 1000 //full-size-dimention: the original size of the images, used for playerView
    //will include "SDL_Abstractions.h", which includes the all the other libraries
    #define SPRITE_ASSET_DIMENTION 1920

    //quick FPS numbers
    #define FPS24 1000/24
    #define FPS60 1000/60
    #define FPS12 1000/12
    #define FPS6  1000/6
    #define ASSET_NUMBER 17



//* \ASSETS *//

//* MISC *//

    #define CAP_FRAMERATE true
    #define FRAME_CAP 120
    #define FRAME_COUNTER true
    #define WORLD_DIV_FACTOR 10000

