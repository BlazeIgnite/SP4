#include "InventoryButtons.h"
#include "../../Mains/Application.h"

InventoryButtons::InventoryButtons()
{
}


InventoryButtons::~InventoryButtons()
{
}

void InventoryButtons::Init(double x, double y)
{
	//Buttons
	Button* temp;

	temp = new Button();
	temp->Init(Vector3(40, 75, 0), Vector3(15, 5, 1), "Consumable Tab");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(60, 75, 0), Vector3(15, 5, 1), "Material Tab");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(80, 75, 0), Vector3(15, 5, 1), "Crafting Tab");
	buttonVector.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(50, 60, 0), Vector3(10, 10, 1), "Red Potion");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(50, 50, 0), Vector3(10, 10, 1), "Attack Potion");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(50, 40, 0), Vector3(10, 10, 1), "Defence Potion");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(50, 30, 0), Vector3(10, 10, 1), "Bandage");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(130, 30, 0), Vector3(30, 10, 1), "Craft");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(140, 75, 0), Vector3(15, 5, 1), "Close Button");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(70, 40, 0), Vector3(10, 10, 1), "DecreaseVolume");
	buttonVector.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(100, 40, 0), Vector3(10, 10, 1), "IncreaseVolume");
	buttonVector.push_back(temp);

	//Descriptions
	Description* temp2;
	temp2 = new Description();
	temp2->Init(Vector3((float)x, (float)y, 0), Vector3(14, 10, 1), "Red Potion");
	DescriptionVector.push_back(temp2);
	temp2 = new Description();
	temp2->Init(Vector3((float)x, (float)y, 0), Vector3(14, 10, 1), "Attack Potion");
	DescriptionVector.push_back(temp2);
	temp2 = new Description();
	temp2->Init(Vector3((float)x, (float)y, 0), Vector3(14, 10, 1), "Defence Potion");
	DescriptionVector.push_back(temp2);
	temp2 = new Description();
	temp2->Init(Vector3((float)x, (float)y, 0), Vector3(14, 10, 1), "Bandage");
	DescriptionVector.push_back(temp2);



	isOpened = false;
}

void InventoryButtons::Update(float dt)
{
	for (std::vector<Button*>::iterator itr = buttonVector.begin(); itr != buttonVector.end(); itr++)
	{
		(*itr)->UpdateCrafting(dt);
	}
}

void InventoryButtons::UpdateDescriptions(float dt)
{
	for (std::vector<Description*>::iterator itr2 = DescriptionVector.begin(); itr2 != DescriptionVector.end(); itr2++)
	{
		(*itr2)->Update(dt);
	}
}

bool InventoryButtons::GetisOpened()
{
	return isOpened;
}

void InventoryButtons::SetisOpened(bool open)
{
	this->isOpened = open;
}

void InventoryButtons::Exit()
{
	for (std::vector<Button*>::iterator itr = buttonVector.begin(); itr != buttonVector.end(); itr++)
	{
		if ((*itr) != nullptr)
		{
			delete (*itr);
			(*itr) = nullptr;
		}
	}
}