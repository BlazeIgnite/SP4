#include "Scene_Assignment1.h"
#include "GL\glew.h"
#include "../Mains/Application.h"
#include <sstream>
//#include "../Systems/ObjectManager.h"
#include "../Systems/EventSystem.h"
#include "../../Engine/State/StateList.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Systems/BattleSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/LuaSystem.h"



Scene_Assignment1::Scene_Assignment1()
{
}

Scene_Assignment1::~Scene_Assignment1()
{
}

void Scene_Assignment1::Init()
{
	// Init Scene
	//SceneBase::Init();
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	EventSystem::Instance().Init();
	x, y = 0;

	this->EntityID = "Test_Scene";

	GameStage = true;

	//Physics Related
	TimeMultiplier = 1.f;
	Math::InitRNG();

	//Warrior* warrior = new Warrior();
	//Warrior* warrior1 = new Warrior();
	//warrior->Init(2);
	//warrior->Init(Vector3(150, 50, 0), Vector3(5, 5, 1));
	//warrior1->Init(1);
	//warrior1->Init(Vector3(125, 50, 0), Vector3(10, 10, 1));
	//mage->Init(1);

	//player = new Player();
	//player->Init(1);
	Player::Instance().Init(2);
	Player::Instance().AddGold(100);
	LuaSystem::Instance().GameSave();
	
	AI = new AIDefault();
	AI->Init();
	
	//bs = new BattleSystem();
	//bs->Init();
	//Player::Instance().AddCharacter("Warrior", warrior);
	//player->AddCharacter("Warrior", warrior);
	//player->AddCharacter("Mage", mage);
	/*BattleSystem::Instance().Init();
	BattleSystem::Instance().SetPlayerTroops(0, player->GetCharacterEntityInClassUnit("Warrior", 0));
	BattleSystem::Instance().SetPlayerTroops(1, player->GetCharacterEntityInClassUnit("Mage", 0));*/

	//BattleSystem::Instance().SetPlayerTroops(1, *(player->GetClassUnitList("Warrior").begin()));
	//BattleSystem::Instance().SetAITroops(1, *(AI->GetClassAIList("Warrior").begin()));

	//warrior1 = new Warrior();

	//player = new Player();
	//player->Init(1);
	//warrior1->Init(112);

	//warrior = new Warrior();
	//warrior->Init(1);
	//warrior->skill_1->SetTarget(warrior1);
	
	inventory = new InventoryButtons();
	inventory->Init(x, y);

	//AudioPlayer::Instance().PlayMusic("BGM");
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

void Scene_Assignment1::Update(float dt)
{
	//SceneBase::Update(dt);
	EventSystem::Instance().Update((float)dt);

	// Update Calls
	UpdateCharacterLogic(dt);
	UpdateInternals(dt);
	HandleUserInput();
	Player::Instance().Update(dt);
	AI->Update(dt);
	inventory->Update(dt);

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
	if (Application::IsKeyPressed('Q'))
	{
		//SceneSystem::Instance().SwitchScene("MainMenu_Scene");
		Application::ChangeWindowSize(800, 600);
	}
	if (Application::IsKeyPressed('E'))
	{
		//SceneSystem::Instance().SwitchScene("MainMenu_Scene");
		Application::FullScreenWindowSize();
	}
	
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
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	// Projection matrix : Orthographic Projection
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
	
	//RenderMesh(meshList[GEO_AXES], false);
	//Renderer->RenderTextOnScreen("TESTING", Color(0, 0, 0), 25, 0, 50);

	RenderCraftingButtons();

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -1.f);
	modelStack->Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	//RenderMesh(meshList[GEO_BACKGROUND], false);
	//Renderer->SetHUD(true);
	Renderer->RenderMesh("BackGround", false);
	//Renderer->SetHUD(false);
	modelStack->PopMatrix();

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
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	for (std::vector<Button*>::iterator itr = inventory->buttonVector.begin(); itr != inventory->buttonVector.end(); itr++)
	{
		Button *obj = (Button *)*itr;

		//Buttons
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "Red Potion")
		{
			Renderer->RenderMesh("CraftRedPotion", false);
		}
		if (obj->type == "Blue Potion")
		{
			Renderer->RenderMesh("CraftBluePotion", false);
		}
		if (obj->type == "Attack Potion")
		{
			Renderer->RenderMesh("CraftAttackPotion", false);
		}
		if (obj->type == "Defense Potion")
		{
			Renderer->RenderMesh("CraftDefencePotion", false);
		}
		if (obj->type == "Bandage")
		{
			Renderer->RenderMesh("CraftBandagePotion", false);
		}
		modelStack->PopMatrix();

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
				//if (obj2->text->GetType() == "Red Potion")
				//{
				//	modelStack->PushMatrix();
				//	std::cout << "out" << std::endl;
				//	modelStack->Translate(obj2->text->GetPosition().x, obj2->text->GetPosition().y, /*obj2->GetPosition().z*/5);
				//	modelStack->Scale(obj2->text->GetScale().x, obj2->text->GetScale().y, obj2->text->GetScale().z);
				//	Renderer->RenderText("text", "x2", Color(1, 1, 1));
				//	modelStack->PopMatrix();
				//	
				//}
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
			if (obj->isitHover() && obj->type == "Defense Potion" && obj2->type == "Defense Potion")
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
				Renderer->RenderMesh("DescripBandagePotion", false);
				modelStack->PopMatrix();
			}
			modelStack->PopMatrix();
		}
	}
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

		QButtonState = true;
	}
	else if (QButtonState && !Application::IsKeyPressed('Q'))
	{
		QButtonState = false;
	}

	static bool EButtonState = false;
	if (!EButtonState && Application::IsKeyPressed('E'))
	{
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
	//SceneBase::Exit();
	//Cleanup Objects
	if (AI)
	{
		AI->Exit();
		delete AI;
		AI = nullptr;
	}
	for (std::vector<Description*>::iterator itr2 = inventory->DescriptionVector.begin(); itr2 != inventory->DescriptionVector.end();)
	{
		(*itr2)->Exit();
		delete (*itr2);
		itr2 = inventory->DescriptionVector.erase(itr2);
	}
	if (inventory)
	{
		inventory->Exit();
		delete inventory;
		inventory = nullptr;
	}

	ObjectManager::Instance().Exit();
	
	StateList::Instance().Exit();
}