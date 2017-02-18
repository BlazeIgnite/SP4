#ifndef INVENTORY_SYSTEM
#define INVENTORY_SYSTEM

#include "../Objects/Items/ItemEntity.h"
#include "../Miscellaneous/Button.h"
#include "../Miscellaneous/Description.h"
#include "../Objects/Characters/Player.h"

class InventorySystem
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
	InventorySystem();
	~InventorySystem();

	void Init();
	void Init(Player* player, double x, double y);
	void Update(float dt);
	void Render();
	void Exit();

	std::vector<Button*> buttonVector;
	std::vector<Description*> DescriptionVector;
};

#endif