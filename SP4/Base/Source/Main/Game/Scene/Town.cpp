#include "Town.h"
#include "../Systems/ObjectManager.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Systems/EventSystem.h"
#include "GL\glew.h"
#include "../Mains/Application.h"
#include <string>
#include "../../Engine/Audio/Audio_Player.h"

Town::Town()
{
}

Town::~Town()
{
}

void Town::Init()
{
	this->EntityID = "Town_Scene";

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	EventSystem::Instance().Init();

	inventory = new InventoryButtons();
	inventory->Init(x, y);

	Button* temp;
	temp = new Button();
	temp->Init(Vector3(50, 10, 1), Vector3(15, 5, 5), "Inventory");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(75, 10, 1), Vector3(15, 5, 5), "Mission");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(100, 10, 1), Vector3(15, 5, 5), "Setting");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(125, 10, 1), Vector3(15, 5, 5), "Exit Game");
	buttonList.push_back(temp);

	OpenInventory = false;
	OpenCraftingTab = false;
	OpenSetting = false;
	OpenMission = false;
	isSelected = false;

	Volume = 5;
}

void Town::Update(float dt)
{
	UpdateInventory(dt);
}

void Town::UpdateInventory(float dt)
{
	//Crafting
	if (OpenCraftingTab)
	{
		inventory->Update(dt);
		inventory->UpdateDescriptions(dt);
		for (std::vector<Button*>::iterator itr = inventory->buttonVector.begin(); itr != inventory->buttonVector.end(); itr++)
		{
			if ((*itr)->type == "Red Potion" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					for (std::vector<Button*>::iterator itr2 = inventory->buttonVector.begin(); itr2 != inventory->buttonVector.end(); itr2++)
					{
						(*itr2)->SetisSelected(false);
					}
					(*itr)->SetisSelected(true);
				}
			}
			if ((*itr)->type == "Attack Potion" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					for (std::vector<Button*>::iterator itr2 = inventory->buttonVector.begin(); itr2 != inventory->buttonVector.end(); itr2++)
					{
						(*itr2)->SetisSelected(false);
					}
					(*itr)->SetisSelected(true);
				}
			}
			if ((*itr)->type == "Defence Potion" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					for (std::vector<Button*>::iterator itr2 = inventory->buttonVector.begin(); itr2 != inventory->buttonVector.end(); itr2++)
					{
						(*itr2)->SetisSelected(false);
					}
					(*itr)->SetisSelected(true);
				}
			}
			if ((*itr)->type == "Bandage" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					for (std::vector<Button*>::iterator itr2 = inventory->buttonVector.begin(); itr2 != inventory->buttonVector.end(); itr2++)
					{
						(*itr2)->SetisSelected(false);
					}
					(*itr)->SetisSelected(true);
				}
			}


			if ((*itr)->type == "Craft" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					for (std::vector<Button*>::iterator itr2 = inventory->buttonVector.begin(); itr2 != inventory->buttonVector.end(); itr2++)
					{
						if ((*itr2)->GetisSelected() && (*itr2)->type == "Red Potion")
						{
							if ((Player::Instance().GetMaterialList().find("Red Herb")->second > 1) && (Player::Instance().GetMaterialList().find("Empty Bottle")->second > 0))
							{
								Player::Instance().AddMaterialItem("Red Herb", -2);
								Player::Instance().AddMaterialItem("Empty Bottle", -1);
								Player::Instance().AddConsumableItem("Red Potion", 1);
								std::cout << "Red Potion Crafted" << std::endl;

							}
							else
							{
								std::cout << "Not Enough Materials" << std::endl;
							}
						}
						else if ((*itr2)->GetisSelected() && (*itr2)->type == "Attack Potion")
						{
							if ((Player::Instance().GetMaterialList().find("White Herb")->second > 0) && (Player::Instance().GetMaterialList().find("Red Herb")->second > 2) && (Player::Instance().GetMaterialList().find("Empty Bottle")->second > 0))
							{
								Player::Instance().AddMaterialItem("White Herb", -1);
								Player::Instance().AddMaterialItem("Red Herb", -3);
								Player::Instance().AddMaterialItem("Empty Bottle", -1);
								Player::Instance().AddConsumableItem("Attack Potion", 1);
								std::cout << "Attack Potion Crafted" << std::endl;
							}
							else
							{
								std::cout << "Not Enough Materials" << std::endl;
							}
						}
						else if ((*itr2)->GetisSelected() && (*itr2)->type == "Defence Potion")
						{
							if ((Player::Instance().GetMaterialList().find("White Herb")->second > 0) && (Player::Instance().GetMaterialList().find("Blue Herb")->second > 2) && (Player::Instance().GetMaterialList().find("Empty Bottle")->second > 0))
							{
								Player::Instance().AddMaterialItem("White Herb", -1);
								Player::Instance().AddMaterialItem("Blue Herb", -3);
								Player::Instance().AddMaterialItem("Empty Bottle", -1);
								Player::Instance().AddConsumableItem("Defence Potion", 1);
								std::cout << "Defence Potion Crafted" << std::endl;
							}
							else
							{
								std::cout << "Not Enough Materials" << std::endl;
							}
						}
						else if ((*itr2)->GetisSelected() && (*itr2)->type == "Bandage")
						{
							if (Player::Instance().GetMaterialList().find("Cloth")->second > 2)
							{
								Player::Instance().AddMaterialItem("Cloth", -3);
								Player::Instance().AddConsumableItem("Bandage", 1);
								std::cout << "Bandage Crafted" << std::endl;
							}
							else
							{
								std::cout << "Not Enough Materials" << std::endl;
							}
						}
					}
				}
			}
		}

	}

	//To Open Tab
	for (std::vector<Button*>::iterator itr = inventory->buttonVector.begin(); itr != inventory->buttonVector.end(); itr++)
	{
		if ((*itr)->type == "DecreaseVolume" && (*itr)->isitHover())
		{
			if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK && Volume > 0.f)
			{
				Volume -= 1.f;
				AudioPlayer::Instance().SetVolume(Volume * 0.1f);
			}
		}
		if ((*itr)->type == "IncreaseVolume" && (*itr)->isitHover())
		{
			if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK && Volume < 10.f)
			{
				Volume += 1.f;
				AudioPlayer::Instance().SetVolume(Volume * 0.1f);
			}
		}
		//Close Inventory Tab
		if (!inventory->GetisOpened())
		{
			if ((*itr)->type == "Close Button" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					if (!(*itr)->GetisPressed())
					{
						OpenCraftingTab = false;
						OpenSetting = false;
						inventory->SetisOpened(true);
						(*itr)->SetisPressed(true);
					}
				}
				else
				{
					if ((*itr)->GetisPressed())
					{
						(*itr)->SetisPressed(false);
					}
				}
			}
		}
	}
	//To Open Inventory
	for (std::vector<Button*>::iterator itr = buttonList.begin(); itr != buttonList.end(); itr++)
	{
		if (!OpenInventory)
		{
			inventory->SetisOpened(false);
			if ((*itr)->type == "Inventory" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					if (!(*itr)->GetisPressed())
					{
						OpenInventory = true;
						OpenCraftingTab = true;
						OpenSetting = false;
						std::cout << "Open" << std::endl;
						(*itr)->SetisPressed(true);
					}
				}
				else
				{
					if ((*itr)->GetisPressed())
					{
						(*itr)->SetisPressed(false);
					}
				}
			}
		}
		if (OpenInventory)
		{
			if (inventory->GetisOpened())
			{
				OpenInventory = false;
			}
		}

		if ((*itr)->type == "Exit Game" && (*itr)->isitHover())
		{
			if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
			{
				Application::GetInstance().QuitGame();
			}
		}

		//OpenSetting
		if (!OpenSetting)
		{
			inventory->SetisOpened(false);
			if ((*itr)->type == "Setting" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					if (!(*itr)->GetisPressed())
					{
						OpenSetting = true;
						OpenInventory = false;
						OpenCraftingTab = false;
						std::cout << "Open" << std::endl;
						(*itr)->SetisPressed(true);
					}
				}
				else
				{
					if ((*itr)->GetisPressed())
					{
						(*itr)->SetisPressed(false);
					}
				}
			}
		}
		if (OpenSetting)
		{
			if (inventory->GetisOpened())
			{
				OpenSetting = false;
			}
		}

		if (!OpenMission)
		{
			if ((*itr)->type == "Mission" && (*itr)->isitHover())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					SceneSystem::Instance().SwitchScene("CharacterSelection_Scene");
					OpenMission = true;
					break;
				}
			}
		}
	}
}

void Town::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	Mtx44 projection;
	projection.SetToOrtho(0, ObjectManager::Instance().WorldWidth, 0, ObjectManager::Instance().WorldHeight, -10, 10);
	projectionStack->LoadMatrix(projection);

	// Camera matrix
	viewStack->LoadIdentity();
	viewStack->LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack->LoadIdentity();

	//Background
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	//Renderer->SetHUD(true);
	Renderer->RenderMesh("MainMenu", false);
	//Renderer->SetHUD(false);
	modelStack->PopMatrix();

	std::string Name = Player::Instance().GetPlayerName();
	modelStack->PushMatrix();
	modelStack->Translate(10, ObjectManager::Instance().WorldHeight * 0.9f, -5.f);
	modelStack->Scale(5, 5, 1);
	Renderer->RenderText("text","Player Name: " + Name, Color(1,1,1));
	modelStack->PopMatrix();


	if (OpenInventory)
		RenderInventoryButtons();
	if (OpenCraftingTab && OpenInventory)
		RenderCraftingButtons();
	if (OpenSetting)
		RenderSetting();

	for (std::vector<Button*>::iterator itr = buttonList.begin(); itr != buttonList.end(); itr++)
	{
		Button *obj = (Button *)*itr;
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0.5);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);

		if (obj->type == "Inventory")
		{
			Renderer->RenderMesh("CraftStation", false);
			modelStack->PopMatrix();
		}

		if (obj->type == "Mission")
		{
			Renderer->RenderMesh("Mission", false);
			modelStack->PopMatrix();
		}

		if (obj->type == "Setting")
		{
			Renderer->RenderMesh("Setting", false);
			modelStack->PopMatrix();
		}

		if (obj->type == "Exit Game")
		{
			Renderer->RenderMesh("ExitGame", false);
			modelStack->PopMatrix();
		}
	}
}

void Town::RenderCraftingButtons()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	for (std::vector<Button*>::iterator itr = inventory->buttonVector.begin(); itr != inventory->buttonVector.end(); itr++)
	{
		Button *obj = (Button *)*itr;

		//Buttons
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "Red Potion")
			Renderer->RenderMesh("RedPotion", false);
		if (obj->type == "Attack Potion")
			Renderer->RenderMesh("AttackPotion", false);
		if (obj->type == "Defence Potion")
			Renderer->RenderMesh("DefencePotion", false);
		if (obj->type == "Bandage")
			Renderer->RenderMesh("Bandage", false);
		if (obj->type == "Craft")
			Renderer->RenderMesh("Craft", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		if (obj->type == "Red Potion" && obj->GetisSelected())
		{
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, 2.f);
			modelStack->Scale(20, 20, 1);
			Renderer->RenderMesh("RedPotion", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("RedHerb", false);
			modelStack->PopMatrix();

			std::string temp = std::to_string(Player::Instance().GetMaterialList().find("Red Herb")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/2", Color(1, 1, 1));
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 20.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("Empty Bottle", false);
			modelStack->PopMatrix();

			temp = std::to_string(Player::Instance().GetMaterialList().find("Empty Bottle")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 20.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/1", Color(1, 1, 1));

		}
		if (obj->type == "Attack Potion" && obj->GetisSelected())
		{
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, 2.f);
			modelStack->Scale(20, 20, 1);
			Renderer->RenderMesh("AttackPotion", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("RedHerb", false);
			modelStack->PopMatrix();

			std::string temp = std::to_string(Player::Instance().GetMaterialList().find("Red Herb")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/2", Color(1, 1, 1));
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 20.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("WhiteHerb", false);
			modelStack->PopMatrix();

			temp = std::to_string(Player::Instance().GetMaterialList().find("White Herb")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 20.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/2", Color(1, 1, 1));
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 25.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("Empty Bottle", false);
			modelStack->PopMatrix();

			temp = std::to_string(Player::Instance().GetMaterialList().find("Empty Bottle")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 25.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/1", Color(1, 1, 1));
		}
		if (obj->type == "Defence Potion" && obj->GetisSelected())
		{
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, 2.f);
			modelStack->Scale(20, 20, 1);
			Renderer->RenderMesh("DefencePotion", false);
			modelStack->PopMatrix();	

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("BlueHerb", false);
			modelStack->PopMatrix();

			std::string temp = std::to_string(Player::Instance().GetMaterialList().find("Blue Herb")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/2", Color(1, 1, 1));
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 20.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("WhiteHerb", false);
			modelStack->PopMatrix();

			temp = std::to_string(Player::Instance().GetMaterialList().find("White Herb")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 20.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/2", Color(1, 1, 1));
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 25.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("Empty Bottle", false);
			modelStack->PopMatrix();

			temp = std::to_string(Player::Instance().GetMaterialList().find("Empty Bottle")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 25.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/1", Color(1, 1, 1));
		}
		if (obj->type == "Bandage" && obj->GetisSelected())
		{
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, 2.f);
			modelStack->Scale(20, 20, 1);
			Renderer->RenderMesh("Bandage", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 5.f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(5, 5, 1);
			Renderer->RenderMesh("Cloth", false);
			modelStack->PopMatrix();

			std::string temp = std::to_string(Player::Instance().GetMaterialList().find("Cloth")->second);
			modelStack->PushMatrix();
			modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f - 15.f, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x" + temp + "/2", Color(1, 1, 1));
		}
		modelStack->PopMatrix();

		if (obj->type == "Attack Potion")
		{
			std::string temp = std::to_string(Player::Instance().GetConsumableList().find("Attack Potion")->second);
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x + 10.f, obj->GetPosition().y, 2.f);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x " + temp, Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		if (obj->type == "Red Potion")
		{
			std::string temp = std::to_string(Player::Instance().GetConsumableList().find("Red Potion")->second);
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x + 10, obj->GetPosition().y, 2);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x " + temp, Color(1, 1, 1));
			modelStack->PopMatrix();
		}

		if (obj->type == "Defence Potion")
		{
			std::string temp = std::to_string(Player::Instance().GetConsumableList().find("Defence Potion")->second);
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x + 10, obj->GetPosition().y, 2);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x " + temp, Color(1, 1, 1));
			modelStack->PopMatrix();
		}

		if (obj->type == "Bandage")
		{
			std::string temp = std::to_string(Player::Instance().GetConsumableList().find("Bandage")->second);
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x + 10, obj->GetPosition().y, 2);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", "x " + temp, Color(1, 1, 1));
			modelStack->PopMatrix();
		}




		//Description
		for (std::vector<Description*>::iterator itr2 = inventory->DescriptionVector.begin(); itr2 != inventory->DescriptionVector.end(); itr2++)
		{
			Description* obj2 = (Description*)*itr2;
			modelStack->PushMatrix();
			modelStack->Translate(obj2->GetPosition().x, obj2->GetPosition().y, /*obj2->GetPosition().z*/5);

			if (obj->isitHover() && obj->type == "Red Potion" && obj2->type == "Red Potion")
			{
				modelStack->PushMatrix();
				modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
				Renderer->RenderMesh("DescripRedPotion", false);
				modelStack->PopMatrix();
				if (obj2->text->GetType() == "Red Potion")
				{
					modelStack->PushMatrix();
					modelStack->Translate(obj2->text->GetPosition().x, obj2->text->GetPosition().y, /*obj2->GetPosition().z*/5);
					modelStack->Scale(obj2->text->GetScale().x, obj2->text->GetScale().y, obj2->text->GetScale().z);
					//Renderer->RenderText("text", "Test", Color(1, 1, 1));
					modelStack->PopMatrix();

				}
			}
			if (obj->isitHover() && obj->type == "Blue Potion" && obj2->type == "Blue Potion")
			{
				modelStack->PushMatrix();
				modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
				Renderer->RenderMesh("DescripBluePotion", false);
				modelStack->PopMatrix();
			}
			if (obj->isitHover() && obj->type == "Attack Potion" && obj2->type == "Attack Potion")
			{
				modelStack->PushMatrix();
				modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
				Renderer->RenderMesh("DescripAttackPotion", false);
				modelStack->PopMatrix();
			}
			if (obj->isitHover() && obj->type == "Defence Potion" && obj2->type == "Defence Potion")
			{
				modelStack->PushMatrix();
				modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
				Renderer->RenderMesh("DescripDefencePotion", false);
				modelStack->PopMatrix();
			}
			if (obj->isitHover() && obj->type == "Bandage" && obj2->type == "Bandage")
			{
				modelStack->PushMatrix();
				modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
				Renderer->RenderMesh("DescripBandage", false);
				modelStack->PopMatrix();
			}
			modelStack->PopMatrix();
		}
	}
}

void Town::RenderInventoryButtons()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	for (std::vector<Button*>::iterator itr = inventory->buttonVector.begin(); itr != inventory->buttonVector.end(); itr++)
	{
		Button *obj = (Button *)*itr;

		modelStack->PushMatrix();
		modelStack->Translate(ObjectManager::Instance().WorldWidth* 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -3);
		modelStack->Scale(130, 70, 1);
		Renderer->RenderMesh("Border", false);
		modelStack->PopMatrix();

		//Buttons
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		modelStack->Scale(obj->GetScale().x * 5, obj->GetScale().y * 2, obj->GetScale().z);
		if (obj->type == "Crafting Tab")
			Renderer->RenderMesh("CraftBorder", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "Close Button")
			Renderer->RenderMesh("Back", false);
		modelStack->PopMatrix(); 
	}
}

void Town::RenderSetting()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	for (std::vector<Button*>::iterator itr = inventory->buttonVector.begin(); itr != inventory->buttonVector.end(); itr++)
	{
		Button *obj = (Button *)*itr;

		modelStack->PushMatrix();
		modelStack->Translate(ObjectManager::Instance().WorldWidth* 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -3);
		modelStack->Scale(130, 70, 1);
		Renderer->RenderMesh("Border", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "Close Button")
			Renderer->RenderMesh("Back", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "DecreaseVolume")
			Renderer->RenderMesh("LeftVolume", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "IncreaseVolume")
			Renderer->RenderMesh("RightVolume", false);
		modelStack->PopMatrix();

		std::string tempVolume = std::to_string((int)Volume);
		modelStack->PushMatrix();
		modelStack->Translate(85, 40, 5);
		modelStack->Scale(7, 7, 1);
		Renderer->RenderText("text", tempVolume, Color(0,0,0));
		modelStack->PopMatrix();

		tempVolume = "Volume"; 
		modelStack->PushMatrix();
		modelStack->Translate(70, ObjectManager::Instance().WorldHeight* 0.5f + 20, 5);
		modelStack->Scale(10, 10, 1);
		Renderer->RenderText("text", tempVolume, Color(0, 0, 0));
		modelStack->PopMatrix();
	}
}

void Town::Exit()
{
	ObjectManager::Instance().Exit();

	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
	buttonList.clear();
}
