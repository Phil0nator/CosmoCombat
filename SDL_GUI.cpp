#pragma once
#include "Abstractions\\SDL_Abstractions.h"


vector<UIElement*> master = vector<UIElement*>();


void UIElement::click() {
	
	pressed = true;
	callback();
}
void UIElement::release() {
	
	pressed = false;

}
void tickButton(UIElement* b, SDL_Event* event) {
	int x = b->x;
	int y = b->y;
	int w = b->w;
	int h = b->h;
	int mx;
	int my;
	SDL_GetMouseState(&mx, &my);

	b->currentColor = &b->getColor();
	if (mx > x&& my > y&& mx < x + w && my < y + h) { //if in bounds
		b->currentColor = &b->getMouseOverColor();
		if (event->button.state == SDL_PRESSED) {
			b->currentColor = &b->getMouseDownColor();
			b->click();
		}
		else {
			b->release();
		}
	}
	else {
		b->release();
	}

}

void UIElement::tick(SDL_Event* event) {
	
	if (type == BUTTON) {
		tickButton(this, event);
	}

}

void UIElement::update(SDL_Renderer* renderer, SDL_Event* event) {
	
	tick(event);
	draw(renderer);

}


Color UIElement::getColor() {
    return color;
}
Color UIElement::getMouseOverColor() {
    return mouseOverColor;
}
Color UIElement::getMouseDownColor() {
    return mouseDownColor;
}
void UIElement::setColor(Color c) {
    color = c;
}
void UIElement::setMouseOverColor(Color c) {
    mouseOverColor = c;
}
void UIElement::setMouseDownColor(Color c) {
    mouseDownColor = c;
}
void UIElement::setColors(Color normal, Color mouseOver, Color mouseDown) {
	setColor(normal);
	setMouseOverColor(mouseOver);
	setMouseDownColor(mouseDown);
}
void UIElement::init() {
	master.push_back(this);
}
void UIElement::renderOwnText(SDL_Renderer* renderer, string text, TTF_Font *f, TextQuality q) {
	
	text_texture = renderText(renderer,text.c_str(),f,text_color,q);

}

//data type Callback is just a function pointer
void UIElement::setCallback(Callback inp) {
	callback = inp;
} //sets the callback function
Callback UIElement::getCallback() {
	
	return callback;

} //gets it 

UIElement Button(int x, int y, int w, int h) {

	UIElement out;
	out.x = x;
	out.y = y;
	out.w = w;
	out.h = h;
	out.type = BUTTON;
	return out;

}

void drawButton(UIElement* b, SDL_Renderer* renderer) {
	
	quickFillRect(renderer, b->x, b->y, b->w, b->h,*b->currentColor);


	quickImage(renderer,b->text_texture, b->x+b->w/10,b->y+b->h/2);

}


void UIElement::draw(SDL_Renderer* renderer) {
	
	if (type == BUTTON) {
		drawButton(this, renderer);
	}


}


void SDL_GUI_DISPLAY(SDL_Renderer*renderer,SDL_Event*event) {

	for (int i = 0; i < master.size(); i++) {
		master.at(i)->update(renderer,event);
	}
	resetRenderColor(renderer);
}
