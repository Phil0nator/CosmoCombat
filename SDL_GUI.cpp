#pragma once
#include "Abstractions\\SDL_Abstractions.h"


vector<UIElement*> master = vector<UIElement*>();


void UIElement::click() {
	
	pressed = true;

}
void UIElement::release() {
	if (pressed) {
		pressed = false;
		if (callback != nullptr) {
			callback();
		}
	}
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
		b->currentColor = &b->mouseOverColor;
		if (event->button.state == SDL_PRESSED) {
			b->currentColor = &b->mouseDownColor;
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
	draw(renderer,event);

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
void UIElement::show() {
	visible = true;
}
void UIElement::hide() {
	visible = false;
}
void UIElement::toggle() {
	visible = !visible;
}
void UIElement::add(UIElement* adder) {

	if (type != PAGE) {
		cout << "Error: Attempting to add UIElements to something other than a page" << endl;
		return;
	}
	elems.push_back(adder);
	adder->parent = this;
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
	out.currentColor = &color(255, 0, 255);
	return out;

}
UIElement Page(int x, int y, int w, int h) {
	
	UIElement out;
	out.x = x;
	out.y = y;
	out.w = w;
	out.h = h;
	out.type = PAGE;
	out.currentColor =&color(0,0,0);
	return out;
}



void drawButton(UIElement* b, SDL_Renderer* renderer) {
	
	if (b->texture == nullptr) {
		quickFillRect(renderer, b->x, b->y, b->w, b->h, *b->currentColor);
	}
	else {
		quickFillRect(renderer, b->x - 1, b->y - 1, b->w + 2, b->h + 2, *b->currentColor);
		image(renderer,b->texture,getTextureRect(b->texture),getQuickRect(b->x,b->y,b->w,b->h));
		
	}

	quickImage(renderer,b->text_texture, b->x+b->w/10,b->y+b->h/2);

}
void drawPage(UIElement* p, SDL_Renderer* renderer, SDL_Event* event) {

	quickFillRect(renderer, p->x, p->y, p->w, p->h, p->getColor());
	for (int i = 0; i < p->elems.size(); i++) {
		p->elems.at(i)->update(renderer,event); //draw each sub element

	}
	
}

void UIElement::draw(SDL_Renderer* renderer,SDL_Event* event) {
	if (!visible)return;
	if (type == BUTTON) {
		drawButton(this, renderer);
	}
	else if (type == PAGE) {
		drawPage(this, renderer, event);
	}



}


void SDL_GUI_DISPLAY(SDL_Renderer*renderer,SDL_Event*event) {

	for (int i = 0; i < master.size(); i++) {
		master.at(i)->update(renderer,event);
	}
	resetRenderColor(renderer);
}
void removeFromVector(vector<UIElement*> *e, UIElement* t) {
	e->erase(remove(e->begin(), e->end(), t));
} //remove from vector by value
void UIElement::destroy() {

	if (parent != nullptr) {
		removeFromVector(&parent->elems, this);
	}
	else {
		removeFromVector(&master, this); //removes element from master
	}

}