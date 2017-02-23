#include "SceneBattles.h"

#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Miscellaneous/Button.h"
#include "../Objects/Characters/Warrior.h"
#include "../Objects/Characters/Mage.h"

SceneBattles::SceneBattles()
{
}


SceneBattles::~SceneBattles()
{
	if (AI != nullptr)
	{
		AI->Exit();
		delete AI;
	}
	AI = nullptr;
}

void SceneBattles::Init()
{
	// Init Scene
	this->SetEntityID("Battle_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	button = new BattleButton();
	button->Init();

	Warrior* warrior = new Warrior();
	warrior->Init(20);
	Mage* mage = new Mage();
	mage->Init(2);
	Priest* priest = new Priest();
	priest->Init(2);

	Warrior* warrior2 = new Warrior();
	warrior2->Init(10);
	Mage* mage2 = new Mage();
	mage2->Init(10);
	Priest* priest2 = new Priest();
	priest2->Init(10);

	Player::Instance().AddCharacter("Warrior", warrior);
	Player::Instance().AddCharacter("Mage", mage);
	Player::Instance().AddCharacter("Priest", priest);
	BattleSystem::Instance().Init();
	BattleSystem::Instance().SetPlayerTroops(0, Player::Instance().GetCharacterEntityInClassUnit("Warrior", 0));
	BattleSystem::Instance().SetPlayerTroops(1, Player::Instance().GetCharacterEntityInClassUnit("Mage", 0));
	BattleSystem::Instance().SetPlayerTroops(2, Player::Instance().GetCharacterEntityInClassUnit("Priest", 0));

	AudioPlayer::Instance().PlayMusic("Battle Music");
	BattleSystem::Instance().SetAITroops(0, warrior2);
	BattleSystem::Instance().SetAITroops(1, mage2);
	BattleSystem::Instance().SetAITroops(2, priest2);

	AI = new AIStatusEffect();
	BattleSystem::Instance().Debugging();
}

void SceneBattles::UpdateCharacterLogic(double dt)
{
}

void SceneBattles::UpdateInternals(double dt)
{
}

bool SceneBattles::CheckCollision(BaseObject* o1, BaseObject* o2, std::string type)
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

void SceneBattles::Update(float dt)
{
	HandleUserInput();
	button->Update(dt);
	AI->Update(dt);
	std::cout << BattleSystem::Instance().GetPlayerTroops().at(1)->GetBleedTimer() << std::endl;
}

void SceneBattles::RenderObjects(BaseObject *obj)
{
	
}

void SceneBattles::Render()
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
	for (std::vector<Button*>::iterator itr = (*button->GetList()).begin(); itr != (*button->GetList()).end(); itr++)
	{
		Button* obj = (Button *)*itr;
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 10);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, 1);

		if (obj->type == "Character 1")
		{
			if (!obj->GetisSelected())
				Renderer->RenderMesh("RedPotion", false);
			else
				Renderer->RenderMesh("BluePotion", false);
		}
		if (obj->type == "Character 2")
		{
			if (!obj->GetisSelected())
				Renderer->RenderMesh("RedPotion", false);
			else
				Renderer->RenderMesh("BluePotion", false);
		}
		if (obj->type == "Character 3")
		{
			if (!obj->GetisSelected())
				Renderer->RenderMesh("RedPotion", false);
			else
				Renderer->RenderMesh("BluePotion", false);
		}
		if (obj->type == "Red Potion")
			Renderer->RenderMesh("RedPotion", false);
		//if (obj->type == "Blue Potion")
		//Renderer->RenderMesh("BluePotion", false);
		if (obj->type == "Attack Potion")
			Renderer->RenderMesh("AttackPotion", false);
		if (obj->type == "Defence Potion")
			Renderer->RenderMesh("DefencePotion", false);
		if (obj->type == "Bandage")
			Renderer->RenderMesh("Bandage", false);
		if (obj->type == "Auto Attack")
			Renderer->RenderMesh("Bandage", false);
		if (obj->type == "Skill 1")
			Renderer->RenderMesh("Bandage", false);
		if (obj->type == "Skill 2")
			Renderer->RenderMesh("Bandage", false);
		if (obj->type == "Skill 3")
			Renderer->RenderMesh("Bandage", false);
		if (obj->type == "AI 1")
			Renderer->RenderMesh("RedPotion", false);
		if (obj->type == "AI 2")
			Renderer->RenderMesh("RedPotion", false);
		if (obj->type == "AI 3")
			Renderer->RenderMesh("RedPotion", false);
		modelStack->PopMatrix();
	}

	for (map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetPlayerTroops().begin(); itr != BattleSystem::Instance().GetPlayerTroops().end(); itr++)
	{
		
		CharacterEntity* entity = (CharacterEntity*)itr->second;
		float entityhealth = (float)entity->GetHealth() / (float)entity->GetMaxHealth();
		modelStack->PushMatrix();
		modelStack->Translate(entity->GetVectorPosition().x, entity->GetVectorPosition().y, 10);
		modelStack->Scale(entity->GetScale().x * 10, entity->GetScale().y * 10, 1);
		if (entity->GetName() == "Warrior")
		{
			if (entity->GetDefeated())
			{
				Renderer->RenderMesh("PlayerWarriorDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("PlayerWarriorDying",false);
			}
			else
			{
				Renderer->RenderMesh("PlayerWarriorMesh", false);
			}
		}
		if (entity->GetName() == "Mage")
		{
			if (entity->GetDefeated())
			{
				Renderer->RenderMesh("PlayerMageDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("PlayerMageDying", false);
			}
			else
			{
				Renderer->RenderMesh("PlayerMageMesh", false);
			}
		}
		if (entity->GetName() == "Priest")
		{
			if (entity->GetDefeated())
			{
				Renderer->RenderMesh("PlayerPriestDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("PlayerPriestDying", false);
			}
			else
			{
				Renderer->RenderMesh("PlayerPriestMesh", false);
			}
		}
		modelStack->PopMatrix();
	}

	for (map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetAITroops().begin(); itr != BattleSystem::Instance().GetAITroops().end(); itr++)
	{

		CharacterEntity* entity = (CharacterEntity*)itr->second;
		modelStack->PushMatrix();
		modelStack->Translate(entity->GetVectorPosition().x, entity->GetVectorPosition().y, 10);
		modelStack->Scale(entity->GetScale().x * 10, entity->GetScale().y * 10, 1);
		if (entity->GetName() == "Warrior")
		{
			if (entity->GetDefeated())
			{
				Renderer->RenderMesh("WarriorDead", false);
			}
			else
				Renderer->RenderMesh("WarriorMesh", false);
		}
		if (entity->GetName() == "Mage")
		{
			Renderer->RenderMesh("MageMesh", false);
		}
		if (entity->GetName() == "Priest")
		{
			Renderer->RenderMesh("PriestMesh", false);
		}
		modelStack->PopMatrix();
	}
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.3f, -5.f);
	modelStack->Scale(BattleSystem::Instance().GetTurnCost() / 2,5,1);
	Renderer->RenderMesh("Test",false);
	modelStack->PopMatrix();
	//std::cout <<BattleSystem::Instance().GetTurnCost() << std::endl;

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	//RenderMesh(meshList[GEO_BACKGROUND], false);
	//Renderer->SetHUD(true);
	Renderer->RenderMesh("BattleScene", false);
	//Renderer->SetHUD(false);
	modelStack->PopMatrix();

	
}

void SceneBattles::HandleUserInput()
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
	//	SceneSystem::Instance().SwitchScene("ResultScene");
		SButtonState = true;
	}
	else if (SButtonState && !Application::IsKeyPressed('S'))
	{
		SButtonState = false;
	}

	static bool DButtonState = false;
	if (!DButtonState && Application::IsKeyPressed('D'))
	{
		BattleSystem::Instance().GetPlayerTroops().at(1)->SetBleeding(true);
		BattleSystem::Instance().GetPlayerTroops().at(1)->SetBleedTimer(3);
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
		BattleSystem::Instance().SetPlayerTurn(false);
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

void SceneBattles::Exit()
{
	//SceneBase::Exit();
	//Cleanup Objects
	ObjectManager::Instance().Exit();
	//button->Exit();
}