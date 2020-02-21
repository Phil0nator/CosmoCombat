bool keys[4096];

void keyboardInput(SDL_Event* event){

  if(event->type==SDL_KEYDOWN){

    keys[event->key.keysym.sym] = true;

  }else if (event->type==SDL_KEYUP){

    keys[event->key.keysym.sym] = false;

  }


}

bool keyPressed(SDL_Keycode keyCode){

  return keys[keyCode];

}

void eventHandler(SDL_Event* event){


  keyboardInput(event);

  GameStateEventHandler(event);
}
