#include "SceneLose.h"


#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Systems/BattleSystem.h"
#include "../Miscellaneous/Button.h"


SceneLose::SceneLose()
{

}

SceneLose::~SceneLose()
{

}

void SceneLose::Init()
{
	this->SetEntityID("Lose_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	timer = 0.f;
	youlose = "You Lost!";
}

void SceneLose::Update(float dt)
{
	if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
	{
		for (auto it : BattleSystem::Instance().GetPlayerTroops())
		{
			if (it.second != nullptr)
				delete it.second;
			it.second = nullptr;
		}
		for (auto it : Player::Instance().GetAllUnitList())
		{
			if (it.first == "Warrior")
			{
				for (auto it2 : Player::Instance().GetClassUnitList("Warrior"))
				{
					if (it2.second == nullptr)
					{
						Warrior* warrior = new Warrior();
						warrior->Init(1);
						it2.second = warrior;
					}
				}
			}
			else if (it.first == "Mage")
			{
				for (auto it2 : Player::Instance().GetClassUnitList("Mage"))
				{
					if (it2.second == nullptr)
					{
						Mage* mage = new Mage();
						mage->Init(1);
						it2.second = mage;
					}
				}
			}
			else if (it.first == "Synergist")
			{
				for (auto it2 : Player::Instance().GetClassUnitList("Synergist"))
				{
					if (it2.second == nullptr)
					{
						Synergist* synergist = new Synergist();
						synergist->Init(1);
						it2.second = synergist;
					}
				}
			}

		}
		BattleSystem::Instance().Reset();
		SceneSystem::Instance().SwitchScene("Town_Scene");
	}
}

void SceneLose::Render()
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

	modelStack->PushMatrix();
	modelStack->Translate((ObjectManager::Instance().WorldWidth * 0.5f) - (youlose.size() * 4.3f), ObjectManager::Instance().WorldHeight * 0.8f, -5.f);
	modelStack->Scale(15, 15, 1);
	Renderer->RenderText("text", youlose, Color(1, 0, 0));
	modelStack->PopMatrix();
}

void SceneLose::Exit()
{
	ObjectManager::Instance().Exit();
}