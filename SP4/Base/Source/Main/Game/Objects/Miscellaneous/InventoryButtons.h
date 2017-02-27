#ifndef INVENTORY_BUTTON
#define INVENTORY_BUTTON

#include "../../Objects/Items/ItemEntity.h"
#include "../../Miscellaneous/Button.h"
#include "../../Miscellaneous/Description.h"
#include "../../Objects/Characters/Player.h"

class InventoryButtons
{
private:

	bool isOpened;

public:
	InventoryButtons();
	~InventoryButtons();

	void Init(double x, double y);
	void Update(float dt);
	void UpdateDescriptions(float dt);
	void Render();
	void Exit();

	Button* button;

	std::vector<Button*> buttonVector;
	std::vector<Description*> DescriptionVector;

	void SetisOpened(bool);
	bool GetisOpened();
};

#endif