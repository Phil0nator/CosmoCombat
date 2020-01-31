#include "CosmoCombat.h"

vector<Part> ALLPARTS = vector<Part>();
int numberOfParts;

Part Empty;

Part Bridge;
Part Hallway;
Part FuelReserve;
Part TorpedoBay;
Part Engine;
Part QuadHall;
Part TriArmor;
Part ShellArmor;


UIElement buttonFromPart(int index) {

	UIElement out = Button(0, 0, ICON_DIM, ICON_DIM);
	Part p = part(index);
	out.texture = sprite(p.sprite);
	out.setColors(color(255,255,255), color(230,10,15),color(150,10,15));
	return out;

}

Part part(int index) {

	return ALLPARTS.at(index);

}
GamePart gamePart(int index) {
	
	Part p = part(index);
	GamePart out;
	out.origin = &p;
	out.sprite = p.sprite;
	return out;

}


void configureParts() {

	Empty.sprite = 0;
	ALLPARTS.push_back(Empty);


	Bridge.sprite = 1;
	Bridge.price = 0;
	Bridge.weight = 10;
	Bridge.type = BRIDGE;
	ALLPARTS.push_back(Bridge);


	Hallway.sprite = 10;
	Hallway.price = 50;
	Hallway.weight = 20;
	Hallway.type = HALL;
	ALLPARTS.push_back(Hallway);

	FuelReserve.price = 200;
	FuelReserve.weight = 25;
	FuelReserve.sprite = 5;
	FuelReserve.capacity = 30;
	FuelReserve.consumtion = 0;
	FuelReserve.type = STORAGE;
	ALLPARTS.push_back(FuelReserve);

	QuadHall.price = 50;
	QuadHall.weight = 20;
	QuadHall.sprite = 11;
	QuadHall.type = HALL;
	ALLPARTS.push_back(QuadHall);


	TorpedoBay.price = 200;
	TorpedoBay.weight = 50;
	TorpedoBay.sprite = 4;
	TorpedoBay.type = WEAPON;
	ALLPARTS.push_back(TorpedoBay);

	ShellArmor.price = 10;
	ShellArmor.weight = 20;
	ShellArmor.sprite = 14;
	ShellArmor.type = ARMOR;
	ShellArmor.defence = 20;
	ALLPARTS.push_back(ShellArmor);


	TriArmor.price = 50;
	TriArmor.weight = 35;
	TriArmor.sprite = 3;
	TriArmor.defence = 20;
	TriArmor.type = ARMOR;
	ALLPARTS.push_back(TriArmor);


	numberOfParts = ALLPARTS.size();
}