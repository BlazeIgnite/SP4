#ifndef INVENTORY_BUTTON
#define INVENTORY_BUTTON

#include "../../Objects/Items/ItemEntity.h"
#include "../../Miscellaneous/Button.h"
#include "../../Miscellaneous/Description.h"
#include "../../Objects/Characters/Player.h"

class InventoryButtons
{
private:
	Button* CraftRedPot;
	Button* CraftBluePot;
	Button* CraftAtkPot;
	Button* CraftDefPot;
	Button* CraftBandage;

	Description* CraftRedPotDes;
	Description* CraftBluePotDes;
	Description* CraftAtkPotDes;
	Description* CraftDefPotDes;
	Description* CraftBandageDes;



public:
	InventoryButtons();
	~InventoryButtons();

	void Init(double x, double y);
	void Update(float dt);
	void Render();

	std::vector<Button*> buttonVector;
	std::vector<Description*> DescriptionVector;
};

#endif