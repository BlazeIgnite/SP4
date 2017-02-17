#include "Scene_Assignment1.h"
#include "GL\glew.h"
#include "../Mains/Application.h"
#include <sstream>
//#include "../Systems/ObjectManager.h"
#include "../Systems/EventSystem.h"
#include "../../Engine/State/StateList.h"
#include "../Objects/Characters/CharacterDatabase.h"
#include "../Systems/BattleSystem.h"
#include "../Audio/Audio_Player.h"

static bool MessageBoardActive = false;

Scene_Assignment1::Scene_Assignment1()
{
}

Scene_Assignment1::~Scene_Assignment1()
{
}

void Scene_Assignment1::Init()
{
	// Init Scene
	SceneBase::Init();
	
	//buttonVector.push_back(button);
	
	EventSystem::Instance().Init();
	x, y = 0;
	//HP = 10;

	GameStage = true;

	//Physics Related
	TimeMultiplier = 1.f;
	Math::InitRNG();

	Warrior* warrior = new Warrior();
	Warrior* warrior1 = new Warrior();

	Mage* mage = new Mage();

	warrior->Init(20);
	warrior->Init(Vector3(150, 50, 0), Vector3(5, 5, 1));
	warrior1->Init(20);
	warrior1->Init(Vector3(125, 50, 0), Vector3(10, 10, 1));

	mage->Init(1);
	//warrior->Init(2);
	//warrior->Init(Vector3(150, 50, 0), Vector3(5, 5, 1));
	//warrior1->Init(1);
	//warrior1->Init(Vector3(125, 50, 0), Vector3(10, 10, 1));
	//mage->Init(1);

	player = new Player();
	player->Init(1);
	Player::Instance().Init(1);
	AI = new AIDefault();
	AI->Init();
	//bs = new BattleSystem();
	//bs->Init();
	Player::Instance().AddCharacter("Warrior", warrior);
	player->AddCharacter("Warrior", warrior);
	player->AddCharacter("Mage", mage);
	AI->AddTroop("Warrior", warrior1);
	BattleSystem::Instance().Init();
	BattleSystem::Instance().SetPlayerTroops(0, *(player->GetClassUnitList("Warrior").begin()));
	BattleSystem::Instance().SetPlayerTroops(1, *(player->GetClassUnitList("Mage").begin()));
	BattleSystem::Instance().SetAITroops(0, *(AI->GetClassAIList("Warrior").begin()));

	//BattleSystem::Instance().SetPlayerTroops(1, *(player->GetClassUnitList("Warrior").begin()));
	//BattleSystem::Instance().SetAITroops(1, *(AI->GetClassAIList("Warrior").begin()));

	//Buttons
	CraftRedPot = new Button();
	CraftRedPot->Init(Vector3(75, 50, 0), Vector3(10, 10, 1), "Red Potion", player);
	buttonVector.push_back(CraftRedPot);
	CraftBluePot = new Button();
	CraftBluePot->Init(Vector3(90, 50, 0), Vector3(10, 10, 1), "Blue Potion", player);
	buttonVector.push_back(CraftBluePot);
	CraftAtkPot = new Button();
	CraftAtkPot->Init(Vector3(75, 35, 0), Vector3(10, 10, 1), "Attack Potion", player);
	buttonVector.push_back(CraftAtkPot);
	CraftDefPot = new Button();
	CraftDefPot->Init(Vector3(90, 35, 0), Vector3(10, 10, 1), "Defense Potion", player);
	buttonVector.push_back(CraftDefPot);
	CraftBandage = new Button();
	CraftBandage->Init(Vector3(82.5f, 20, 0), Vector3(12, 10, 1), "Bandage", player);
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

	//warrior1 = new Warrior();

	//player = new Player();
	//player->Init(1);
	//warrior1->Init(112);

	//warrior = new Warrior();
	//warrior->Init(1);
	//warrior->skill_1->SetTarget(warrior1);
	
	AudioPlayer::Instance().PlayMusic("BGM");
}

void Scene_Assignment1::UpdateCharacterLogic(double dt)
{
}

void Scene_Assignment1::UpdateInternals(double dt)
{
}

bool Scene_Assignment1::CheckCollision(BaseObject* o1, BaseObject* o2, std::string type)
{
	if (type == "Circle")
	{
		// Simple BC.
		float CombinedRadiusSquared = (o1->GetDimensions().x + o2->GetDimensions().x) * (o1->GetDimensions().x + o2->GetDimensions().x);
		float DistSquared = (o1->GetPosition() - o2->GetPosition()).LengthSquared();
		if (DistSquared < CombinedRadiusSquared)
		{
			return true;
		}
		return false;
	}
	else if (type == "AABB")
	{
		return false;
	}
	else if (type == "OBB")
	{
		return false;
	}
	else return false;
}

void Scene_Assignment1::Update(double dt)
{
	SceneBase::Update(dt);
	EventSystem::Instance().Update((float)dt);

	// Update Calls
	UpdateCharacterLogic(dt);
	UpdateInternals(dt);
	HandleUserInput();
	player->Update(dt);
	Player::Instance().Update(dt);
	AI->Update(dt);

	for (std::vector<Button*>::iterator itr = buttonVector.begin(); itr != buttonVector.end(); itr++)
	{
		(*itr)->Update(dt);
		(*itr)->UpdateCrafting(dt);
	}
	for (std::vector<Description*>::iterator itr2 = DescriptionVector.begin(); itr2 != DescriptionVector.end(); itr2++)
	{
		(*itr2)->Update(dt);
	}

	/*if (Application::IsKeyPressed('A'))
	{
		warrior->skill_1->SkillBehavior(warrior1->GetDamageMitigation());
		warrior1->Update(dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		warrior1->Levelup();
		warrior1->Update(dt);
	}*/

	
}

void Scene_Assignment1::RenderObjects(BaseObject *obj)
{
	/*if (obj->Active && obj->Visible && obj->GetEntityID() != "")
	{
		std::string Name = obj->GetEntityID();
		if (Name == "Scavenger")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_SCAVENGER], false);
			modelStack.PopMatrix();
		}
		else if (Name == "Drone")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_DRONE], false);
			modelStack.PopMatrix();
		}
		else if (Name == "Zombie")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_ZOMBIE], false);
			modelStack.PopMatrix();
		}
		else if (Name == "WildLife")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_WILDLIFE], false);
			modelStack.PopMatrix();
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_BULLET], false);
			modelStack.PopMatrix();
		}
	}*/
}

void Scene_Assignment1::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	
	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, ObjectManager::Instance().WorldWidth, 0, ObjectManager::Instance().WorldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
	
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5);
	modelStack.Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	RenderMesh(meshList[GEO_BACKGROUND], false);
	modelStack.PopMatrix();

	RenderCraftingButtons();

	//renders troop list
	/*std::string temp = "Warrior";
	for (std::vector<CharacterEntity*>::iterator it = Player::Instance().GetClassUnitList(temp).begin(); it != Player::Instance().GetClassUnitList(temp).end(); ++it)
	{
		Warrior *object = (Warrior *)*it;
		modelStack.PushMatrix();
		modelStack.Translate(object->Position.x, object->Position.y, object->Position.z);
		modelStack.Scale(object->Scale.x, object->Scale.y, object->Scale.z);
		RenderMesh(meshList[GEO_WARRIOR], false);
		modelStack.PopMatrix();
	}*/

	//For AI rendering
	/*for (std::vector<CharacterEntity*>::iterator it2 = )
	{

	}*/
	//On screen text


	//On screen text
	std::stringstream ss;
	ss.str("");
}

void Scene_Assignment1::RenderCraftingButtons()
{
	for (std::vector<Button*>::iterator itr = buttonVector.begin(); itr != buttonVector.end(); itr++)
	{
		Button *obj = (Button *)*itr;

		modelStack.PushMatrix();
		modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
		modelStack.Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "Red Potion")
		{
			RenderMesh(meshList[GEO_CRAFT_REDPOT], false);
		}
		if (obj->type == "Blue Potion")
		{
			RenderMesh(meshList[GEO_CRAFT_BLUEPOT], false);
		}
		if (obj->type == "Attack Potion")
		{
			RenderMesh(meshList[GEO_CRAFT_ATKPOT], false);
		}
		if (obj->type == "Defense Potion")
		{
			RenderMesh(meshList[GEO_CRAFT_DEFPOT], false);
		}
		if (obj->type == "Bandage")
		{
			RenderMesh(meshList[GEO_CRAFT_BANDAGE], false);
		}
		modelStack.PopMatrix();
		for (std::vector<Description*>::iterator itr2 = DescriptionVector.begin(); itr2 != DescriptionVector.end(); itr2++)
		{
			Description* obj2 = (Description*)*itr2;
			modelStack.PushMatrix();
			modelStack.Translate(obj2->GetPosition().x, obj2->GetPosition().y, /*obj2->GetPosition().z*/10);
			modelStack.Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
			if (obj->isitHover() && obj->type == "Red Potion" && obj2->type == "Red Potion")
			{
				RenderMesh(meshList[GEO_DES_CRAFT_REDPOT], false);
			}
			if (obj->isitHover() && obj->type == "Blue Potion" && obj2->type == "Blue Potion")
			{
				RenderMesh(meshList[GEO_DES_CRAFT_BLUEPOT], false);
			}
			if (obj->isitHover() && obj->type == "Attack Potion" && obj2->type == "Attack Potion")
			{
				RenderMesh(meshList[GEO_DES_CRAFT_ATKPOT], false);
			}
			if (obj->isitHover() && obj->type == "Defense Potion" && obj2->type == "Defense Potion")
			{
				RenderMesh(meshList[GEO_DES_CRAFT_DEFPOT], false);
			}
			if (obj->isitHover() && obj->type == "Bandage" && obj2->type == "Bandage")
			{
				RenderMesh(meshList[GEO_DES_CRAFT_BANDAGE], false);
			}
			modelStack.PopMatrix();
		}
 	}
	//renders troop list
	std::string temp = "Warrior";
	for (std::vector<CharacterEntity*>::iterator it = Player::Instance().GetClassUnitList(temp).begin(); it != Player::Instance().GetClassUnitList(temp).end(); ++it)
	{
		Warrior *object = (Warrior *)*it;
		modelStack.PushMatrix();
		modelStack.Translate(object->Position.x, object->Position.y, object->Position.z);
		modelStack.Scale(object->Scale.x, object->Scale.y, object->Scale.z);
		RenderMesh(meshList[GEO_WARRIOR_FRONT], false);
		modelStack.PopMatrix();
	}
	//For AI rendering
	int tempnum = 0;
	/*for (map<size_t, CharacterEntity*>::iterator it2 = BattleSystem::Instance().GetAITroops().begin(); it2 != BattleSystem::Instance().GetAITroops().end(); it2++,tempnum++)
	{
		
	}*/
	//On screen text
	std::stringstream ss;
	ss.str("");
	
}

void Scene_Assignment1::HandleUserInput()
{
	//Keys Section
	//Mouse Section
	
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float worldX = (float)x * ObjectManager::Instance().WorldWidth / (float)w;
	float worldY = ((float)h - (float)y) * ObjectManager::Instance().WorldHeight / (float)h;

	// Characters
	static bool SButtonState = false;
	float Radius = 1;
	if (!SButtonState && Application::IsKeyPressed('S'))
	{
		SButtonState = true;
	}
	else if (SButtonState && !Application::IsKeyPressed('S'))
	{
		SButtonState = false;
	}

	static bool DButtonState = false;
	if (!DButtonState && Application::IsKeyPressed('D'))
	{
		BattleSystem::Instance().SwitchSpots(BattleSystem::Instance().GetPlayerTroops(), 0, 1);
		//BattleSystem::Instance().SwitchSpots((&BattleSystem::Instance().GetPlayerTroops()), 0, 1);
		DButtonState = true;
	}
	else if (DButtonState && !Application::IsKeyPressed('D'))
	{
		DButtonState = false;
	}

	static bool WButtonState = false;
	if (!WButtonState && Application::IsKeyPressed('W'))
	{
		WButtonState = true;
	}
	else if (WButtonState && !Application::IsKeyPressed('W'))
	{
		WButtonState = false;
	}

	static bool AButtonState = false;
	if (!AButtonState && Application::IsKeyPressed('A'))
	{
		AButtonState = true;
	}
	else if (AButtonState && !Application::IsKeyPressed('A'))
	{
		AButtonState = false;
	}

	// Items
	static bool QButtonState = false;
	if (!QButtonState && Application::IsKeyPressed('Q'))
	{
		 if (BattleSystem::Instance().GetPlayerTurn())
		 	BattleSystem::Instance().DamageCalculation(BattleSystem::Instance().GetPlayerTroopAttacking(0), 0, BattleSystem::Instance().GetPlayerTroopAttacking(0)->Getskill());

		QButtonState = true;
	}
	else if (QButtonState && !Application::IsKeyPressed('Q'))
	{
		QButtonState = false;
	}

	static bool EButtonState = false;
	if (!EButtonState && Application::IsKeyPressed('E'))
	{
		if (BattleSystem::Instance().GetPlayerTurn())
		{

			BattleSystem::Instance().DamageCalculation(BattleSystem::Instance().GetPlayerTroopAttacking(0), 0);

		}
		EButtonState = true;
	}
	else if (EButtonState && !Application::IsKeyPressed('E'))
	{
		EButtonState = false;
	}

	static bool LMouse = false;
	if (!LMouse && Application::IsKeyPressed(VK_LBUTTON))
	{
		LMouse = true;
	}
	else if (LMouse && Application::IsKeyPressed(VK_LBUTTON))
	{
		LMouse = false;
	}
	//if (Application::IsKeyPressed(VK_RBUTTON))
	//{
	//}
}

void Scene_Assignment1::Exit()
{
	SceneBase::Exit();
	//Cleanup Objects
	ObjectManager::Instance().Exit();
	
	StateList::Instance().Exit();
}