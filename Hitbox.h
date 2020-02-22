double dist(int x1, int y1, int x2, int y2){

  return abs(x2-x1)+abs(y2-y1);

}


class HitBox{

public:
  int x;
  int y;
  int w;
  int h;

  SDL_Rect rect;


  HitBox(int x, int y, int w, int h){
    this->x=x;
    this->y=y;
    this->w=w;
    this->h=h;
    rect={x,y,w,h};
  }

  HitBox copy(){

    HitBox out = HitBox(x,y,w,h);
    return out;
  }



  bool contains(SDL_Point q){
    return (q.x>x&&q.x<x+w&&q.y>y&&q.y<y+h);
  }

  bool contains(int x, int y){
    return contains(point(x,y));
  }

  bool simpleCollide(HitBox q){

    return (contains(q.x,q.y)||contains(q.x+q.w,q.y)||contains(q.x+q.w,q.y+q.h)||contains(q.x,q.y+q.h));

  }

  bool sdlCollide(HitBox q){

    return (SDL_HasIntersection(&rect,&q.rect)==SDL_TRUE);

  }

  bool CDCollition(HitBox q){

    int threshold = ((w+h)/2)+((q.w+q.h)/2);
    return (dist(x+w/2,y+h/2,q.x+q.w/2,q.y+q.h/2)<threshold);

  }

  void rotate(float r){

    //pass coordinates and dimentions into 4 points
    SDL_Point center = point(x+(w/2), y+(h/2));
    SDL_Point tleft = point(x,y);
    SDL_Point tright = point(x+w,y);
    SDL_Point bleft = point(x,y+h);
    SDL_Point bright = point(x+w,y+h);

    //rotate the four points around the center
    tleft = rotatePoint(tleft, center, r);
    tright = rotatePoint(tright, center, r);
    bleft = rotatePoint(bleft, center, r);
    bright = rotatePoint(bright, center, r);

    //place the values of the points back into the dimentions

  }

  void draw(SDL_Renderer* renderer){

    quickFillRect(renderer, x,y,w,h,color(255,0,255));

  }

};
