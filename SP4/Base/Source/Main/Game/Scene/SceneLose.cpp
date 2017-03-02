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
	timer += dt;
	if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK && timer > 5.f)
	{
		for (auto it : BattleSystem::Instance().GetPlayerTroops())
		{
			if (it.second->GetDefeated())
			{
				for (auto it2 : Player::Instance().GetAllUnitList())
				{
					if (it2.first == "Warrior")
					{
						for (auto it3 : Player::Instance().GetClassUnitList("Warrior"))
						{
							if (it3.second == it.second)
							{
								Player::Instance().GetAllUnitList().at("Warrior").erase(it3.first);
								CharacterEntity* mage = new Warrior();
								mage->Init(1);
								Player::Instance().AddCharacter("Warrior", mage);
								delete it.second;
								it.second = nullptr;
								break;
							}
						}
					}
					else if (it2.first == "Mage")
					{
						for (auto it3 : Player::Instance().GetClassUnitList("Mage"))
						{
							if (it3.second == it.second)
							{
								Player::Instance().GetAllUnitList().at("Mage").erase(it3.first);
								CharacterEntity* mage = new Mage();
								mage->Init(1);
								Player::Instance().AddCharacter("Mage", mage);
								delete it.second;
								it.second = nullptr;
								break;
							}
						}
					}
					else if (it2.first == "Synergist")
					{
						for (auto it3 : Player::Instance().GetClassUnitList("Synergist"))
						{
							if (it3.second == it.second)
							{
								Player::Instance().GetAllUnitList().at("Synergist").erase(it3.first);
								CharacterEntity* mage = new Synergist();
								mage->Init(1);
								Player::Instance().AddCharacter("Synergist", mage);
								delete it.second;
								it.second = nullptr;
								break;
							}
						}
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