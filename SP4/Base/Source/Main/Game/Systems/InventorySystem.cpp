#include "InventorySystem.h"

InventorySystem::InventorySystem()
{
}


InventorySystem::~InventorySystem()
{
}

void InventorySystem::Init(double x, double y)
{
	//Buttons
	CraftRedPot = new Button();
	CraftRedPot->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Red Potion");
	buttonVector.push_back(CraftRedPot);
	CraftBluePot = new Button();
	CraftBluePot->Init(Vector3(90, 50, 0), Vector3(10, 10, 1), "Blue Potion");
	buttonVector.push_back(CraftBluePot);
	CraftAtkPot = new Button();
	CraftAtkPot->Init(Vector3(75, 35, 0), Vector3(10, 10, 1), "Attack Potion");
	buttonVector.push_back(CraftAtkPot);
	CraftDefPot = new Button();
	CraftDefPot->Init(Vector3(90, 35, 0), Vector3(10, 10, 1), "Defense Potion");
	buttonVector.push_back(CraftDefPot);
	CraftBandage = new Button();
	CraftBandage->Init(Vector3(82.5f, 20, 0), Vector3(12, 10, 1), "Bandage");
	buttonVector.push_back(CraftBandage);

	//Descriptions
	CraftRedPotDes = new Description();
	CraftRedPotDes->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Red Potion");
	DescriptionVector.push_back(CraftRedPotDes);
	CraftBluePotDes = new Description();
	CraftBluePotDes->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Blue Potion");
	DescriptionVector.push_back(CraftBluePotDes);
	CraftAtkPotDes = new Description();
	CraftAtkPotDes->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Attack Potion");
	DescriptionVector.push_back(CraftAtkPotDes);
	CraftDefPotDes = new Description();
	CraftDefPotDes->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Defense Potion");
	DescriptionVector.push_back(CraftDefPotDes);
	CraftBandageDes = new Description();
	CraftBandageDes->Init(Vector3(x, y, 0), Vector3(14, 10, 1), "Bandage");
	DescriptionVector.push_back(CraftBandageDes);
}

void InventorySystem::Update(float dt)
{
	for (std::vector<Button*>::iterator itr = buttonVector.begin(); itr != buttonVector.end(); itr++)
	{
		(*itr)->Update(dt);
		(*itr)->UpdateCrafting(dt);
	}
	for (std::vector<Description*>::iterator itr2 = DescriptionVector.begin(); itr2 != DescriptionVector.end(); itr2++)
	{
		(*itr2)->Update(dt);
	}
}