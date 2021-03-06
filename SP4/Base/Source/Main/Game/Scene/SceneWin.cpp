#include "SceneWin.h"


#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Systems/BattleSystem.h"
#include "../Miscellaneous/Button.h"


SceneWin::SceneWin()
{
	timer = 0;
}

SceneWin::~SceneWin()
{

}

void SceneWin::Init()
{
	this->SetEntityID("Win_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	youwin = "You Win!";
	timer = 0.f;
	for (int i = 0; i < 5; i++)
	{
		drops[i] = Math::RandIntMinMax(0, 5);
	}
	item[0] = "Red Herb";
	item[1] = "Blue Herb";
	item[2] = "White Herb";
	item[3] = "Empty Bottle";
	item[4] = "Cloth";
	itemmesh[0] = "RedHerb";
	itemmesh[1] = "BlueHerb";
	itemmesh[2] = "WhiteHerb";
	itemmesh[3] = "Empty Bottle";
	itemmesh[4] = "Cloth";

}

void SceneWin::Update(float dt)
{
	//if (InputManager::Instance().GetMouseState(MOUSE_L) == RELEASE)
	//	SceneSystem::Instance().SwitchScene("Town_Scene");

	timer += dt;

	std::map<std::string, std::map<int, CharacterEntity*>> test = Player::Instance().GetAllUnitList();

	if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK && timer > 5.f)
	{
		timer = 0.f;
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
			else
			{
				it.second->SetExperiencePoints(Math::RandIntMinMax(10, 300));
				it.second->LevelUp(false);
			}
		}
		
		std::map<std::string, std::map<int, CharacterEntity*>> test2 = Player::Instance().GetAllUnitList();

		Drop();
		BattleSystem::Instance().Reset();
		SceneSystem::Instance().SwitchScene("Town_Scene");
	}
		
}

void SceneWin::Render()
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

	/*modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.3f, -5.f);
	modelStack->Scale(10, 10, 1);
	Renderer->RenderMesh("RedPotion", false);
	modelStack->PopMatrix();*/

	modelStack->PushMatrix();
	modelStack->Translate((ObjectManager::Instance().WorldWidth * 0.5f) - (youwin.size() * 4.3f), ObjectManager::Instance().WorldHeight * 0.8f, -5.f);
	modelStack->Scale(15, 15, 1);
	Renderer->RenderText("text", youwin, Color(1, 0, 0));
	modelStack->PopMatrix();


	modelStack->PushMatrix(); 
	modelStack->Translate((ObjectManager::Instance().WorldWidth * 0.2f), ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(5, 5, 1);
	Renderer->RenderText("text", "Material Earned: ", Color(1, 0, 0));
	modelStack->PopMatrix();

	for (int i = 0; i < 5; i++)
	{
		string temp = std::to_string(drops[i]);
		modelStack->PushMatrix();
		modelStack->Translate((ObjectManager::Instance().WorldWidth * 0.5f) + i * 10, ObjectManager::Instance().WorldHeight * 0.4f, -5.f);
		modelStack->Scale(5, 5, 1);
		Renderer->RenderText("text", temp , Color(1, 0, 0));

		modelStack->PushMatrix();
		modelStack->Translate(0, 1, 0);
		modelStack->Scale(1, 1, 1);
		Renderer->RenderMesh(itemmesh[i], false);
		modelStack->PopMatrix();

		modelStack->PopMatrix();
	}
	
}


void SceneWin::Drop()
{
	for (int i = 0; i < 5; i++)
	{
		Player::Instance().AddMaterialItem(item[i],drops[i]);
	}
}

void SceneWin::Exit()
{
	ObjectManager::Instance().Exit();
}