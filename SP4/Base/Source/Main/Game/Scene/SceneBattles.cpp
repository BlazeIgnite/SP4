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
}

void SceneBattles::Init()
{
	// Init Scene
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	button = new BattleButton();
	button->Init();

	Warrior* warrior = new Warrior();
	warrior->Init(1);
	Mage* mage = new Mage();
	mage->Init(1);
	Player::Instance().AddCharacter("Warrior", warrior);
	Player::Instance().AddCharacter("Mage", mage);
	BattleSystem::Instance().Init();
	BattleSystem::Instance().SetPlayerTroops(0, Player::Instance().GetCharacterEntityInClassUnit("Warrior", 0));
	BattleSystem::Instance().SetPlayerTroops(1, Player::Instance().GetCharacterEntityInClassUnit("Mage", 0));

	AudioPlayer::Instance().PlayMusic("Battle Music");
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
	button->Update(dt);
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
			if (!obj->isSelected)
				Renderer->RenderMesh("CraftRedPotion", false);
			else
				Renderer->RenderMesh("CraftBluePotion", false);
		}
		if (obj->type == "Character 2")
			Renderer->RenderMesh("CraftBluePotion", false);
		if (obj->type == "Character 3")
			Renderer->RenderMesh("CraftAttackPotion", false);
		if (obj->type == "Red Potion")
			Renderer->RenderMesh("CraftRedPotion", false);
		//if (obj->type == "Blue Potion")
		//Renderer->RenderMesh("CraftBluePotion", false);
		if (obj->type == "Attack Potion")
			Renderer->RenderMesh("CraftAttackPotion", false);
		if (obj->type == "Defence Potion")
			Renderer->RenderMesh("CraftDefencePotion", false);
		if (obj->type == "Bandage")
			Renderer->RenderMesh("CraftBandagePotion", false);
		if (obj->type == "Auto Attack")
			Renderer->RenderMesh("CraftBandagePotion", false);
		if (obj->type == "Skill 1")
			Renderer->RenderMesh("CraftBandagePotion", false);
		if (obj->type == "Skill 2")
			Renderer->RenderMesh("CraftBandagePotion", false);
		if (obj->type == "Skill 3")
			Renderer->RenderMesh("CraftBandagePotion", false);
		if (obj->type == "AI1")
			Renderer->RenderMesh("CraftRedPotion", false);
		if (obj->type == "AI2")
			Renderer->RenderMesh("CraftRedPotion", false);
		if (obj->type == "AI3")
			Renderer->RenderMesh("CraftRedPotion", false);
		modelStack->PopMatrix();
	}

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
		SButtonState = true;
	}
	else if (SButtonState && !Application::IsKeyPressed('S'))
	{
		SButtonState = false;
	}

	static bool DButtonState = false;
	if (!DButtonState && Application::IsKeyPressed('D'))
	{
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

void SceneBattles::Exit()
{
	//SceneBase::Exit();
	//Cleanup Objects
	ObjectManager::Instance().Exit();
	button->Exit();
}