#include "CosmoCombat.h"

vector<Part> ALLPARTS = vector<Part>();

Part Bridge;
Part Hallway;
Part FuelReserve;
Part TorpedoBay;
Part Engine;
Part QuadHall;
Part TriArmor;
Part ShellArmor;




void configureParts() {


	Bridge.sprite = 1;
	Bridge.price = 0;
	Bridge.weight = 10;
	Bridge.type = BRIDGE;
	ALLPARTS.push_back(Bridge);

}