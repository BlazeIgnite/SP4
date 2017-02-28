#include "SceneTutorial.h"
#include <time.h>
#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Miscellaneous/Button.h"
#include "../Objects/Characters/Warrior.h"
#include "../Objects/Characters/Mage.h"
#include "../Objects/Characters/Synergist.h"
#include "../Systems/BattleSystem.h"

SceneTutorial::SceneTutorial()
{
}


SceneTutorial::~SceneTutorial()
{
	if (AI != nullptr)
	{
		AI->Exit();
		delete AI;
	}
	AI = nullptr;
}

void SceneTutorial::Init()
{
	// Init Scene
	this->SetEntityID("Tutorial_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	button = new BattleButton();
	button->Init(x, y);

	m_Turn = 1;

	Warrior* warrior2 = new Warrior();
	warrior2->Init(5);
	warrior2->SetHealth(50);
	warrior2->SetAttack(5);

	/*Player::Instance().AddCharacter("Warrior", warrior);
	Player::Instance().AddCharacter("Mage", mage);
	Player::Instance().AddCharacter("Synergist", Synergist);*/



	BattleSystem::Instance().Init();
	BattleSystem::Instance().SetPlayerTroops(0, Player::Instance().GetCharacterEntityInClassUnit("Warrior", 0));
	BattleSystem::Instance().SetPlayerTroops(1, Player::Instance().GetCharacterEntityInClassUnit("Synergist", 0));

	BattleSystem::Instance().GetPlayerTroopAttacking(0)->SetHealth(13);

	for (size_t i = 0; i < BattleSystem::Instance().GetPlayerTroops().size(); i++)
	{
		for (size_t j = 0; j < BattleSystem::Instance().GetPlayerTroopAttacking(i)->GetSkillList()->size(); j++)
		{
			BattleSystem::Instance().SetPlayerTroopSkills(i, j);
		}
	}

	AudioPlayer::Instance().StopAllMusic();
	AudioPlayer::Instance().PlayMusic("Battle Music");

	BattleSystem::Instance().SetAITroops(0, warrior2);

	AI = new AITutorial();
	BattleSystem::Instance().Debugging();

	tempscale = Vector3(10, 10, 1);
	tempscale1 = Vector3(15, 15, 1);

	BattleSystem::Instance().SetTurnCost(26);
}

void SceneTutorial::UpdateCharacterLogic(double dt)
{
}

void SceneTutorial::UpdateInternals(double dt)
{
}

bool SceneTutorial::CheckCollision(BaseObject* o1, BaseObject* o2, std::string type)
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

void SceneTutorial::Update(float dt)
{
	HandleUserInput();

	for (std::map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetPlayerTroops().begin(); itr != BattleSystem::Instance().GetPlayerTroops().end(); itr++)
	{
		CharacterEntity* entity = (CharacterEntity*)itr->second;

		if (entity->GetName() == "Warrior" && entity->isitHover())
		{
			if (!entity->GetisPressed() && !entity->GetisSelected())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
					{
						CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
						if (entity2->GetName() == "Warrior" || entity2->GetName() == "Mage" || entity2->GetName() == "Synergist")
							entity2->SetScale(tempscale);
						entity2->SetisSelected(false);
					}

					entity->SetScale(tempscale1);

					BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking((*itr).first));
					std::cout << BattleSystem::Instance().GetSelectedTroop()->GetName() << std::endl;
					entity->SetisSelected(true);
					entity->SetisPressed(true);
				}
			}
			else
			{
				if (entity->GetisPressed())
					entity->SetisPressed(false);
			}
		}


		if (entity->GetName() == "Mage" && entity->isitHover())
		{
			if (!entity->GetisPressed() && !entity->GetisSelected())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					//if (!entity->GetisSelected())
					{
						for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
						{
							CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
							if (entity2->GetName() == "Warrior" || entity2->GetName() == "Mage" || entity2->GetName() == "Synergist")
								entity2->SetScale(tempscale);
							entity2->SetisSelected(false);
						}

						entity->SetScale(tempscale1);

						BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking((*itr).first));
						std::cout << BattleSystem::Instance().GetSelectedTroop()->GetName() << std::endl;
						entity->SetisSelected(true);
						entity->SetisPressed(true);
					}
				}
			}
			else
			{
				if (entity->GetisPressed())
					entity->SetisPressed(false);
			}
		}

		if (entity->GetName() == "Synergist" && entity->isitHover())
		{
			if (!entity->GetisPressed() && !entity->GetisSelected())
			{
				if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
				{
					//if (entity->GetisSelected())
					{
						for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
						{
							CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
							if (entity2->GetName() == "Warrior" || entity2->GetName() == "Mage" || entity2->GetName() == "Synergist")
								entity2->SetScale(tempscale);
							entity2->SetisSelected(false);
						}

						entity->SetScale(tempscale1);
						BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking((*itr).first));
						std::cout << BattleSystem::Instance().GetSelectedTroop()->GetName() << std::endl;
						entity->SetisSelected(true);
						entity->SetisPressed(true);
					}
				}
			}
			else
			{
				if (entity->GetisPressed())
					entity->SetisPressed(false);
			}
		}
	}

	for (std::map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetAITroops().begin(); itr != BattleSystem::Instance().GetAITroops().end(); itr++)
	{
		CharacterEntity* entity = (CharacterEntity*)itr->second;
		if (entity->GetName() == "Warrior" && entity->isitHover())
		{
			if (!entity->GetisPressed() && !entity->GetisSelected())
			{
				if (Application::IsMousePressed(0))
				{
					//if (!entity->GetisSelected())
					{
						for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetAITroops().begin(); itr2 != BattleSystem::Instance().GetAITroops().end(); itr2++)
						{
							CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
							if (entity2->GetName() == "Warrior")
								entity2->SetScale(Vector3(10, 10, 1));
							if (entity2->GetName() == "Mage")
								entity2->SetScale(Vector3(10, 10, 1));
							if (entity2->GetName() == "Synergist")
								entity2->SetScale(Vector3(10, 10, 1));
							entity2->SetisSelected(false);
						}

						entity->SetScale(entity->GetScale() + Vector3(5, 5, 1));

						BattleSystem::Instance().SetSelectedEnemyTroop(BattleSystem::Instance().GetAITroopAttacking((*itr).first));
						std::cout << BattleSystem::Instance().GetSelectedEnemyTroop()->GetName() << std::endl;
						entity->SetisSelected(true);
						entity->SetisPressed(true);
					}
				}
			}
			else
			{
				if (entity->GetisPressed())
					entity->SetisPressed(false);
			}
		}

		if (entity->GetName() == "Mage" && entity->isitHover())
		{
			if (!entity->GetisPressed() && !entity->GetisSelected())
			{
				if (Application::IsMousePressed(0))
				{
					//if (!entity->GetisSelected())
					{
						for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetAITroops().begin(); itr2 != BattleSystem::Instance().GetAITroops().end(); itr2++)
						{
							CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
							if (entity2->GetName() == "Warrior")
								entity2->SetScale(Vector3(10, 10, 1));
							if (entity2->GetName() == "Mage")
								entity2->SetScale(Vector3(10, 10, 1));
							if (entity2->GetName() == "Synergist")
								entity2->SetScale(Vector3(10, 10, 1));
							entity2->SetisSelected(false);
						}

						entity->SetScale(entity->GetScale() + Vector3(5, 5, 1));

						BattleSystem::Instance().SetSelectedEnemyTroop(BattleSystem::Instance().GetAITroopAttacking((*itr).first));
						std::cout << BattleSystem::Instance().GetSelectedEnemyTroop()->GetName() << std::endl;
						entity->SetisSelected(true);
						entity->SetisPressed(true);
					}
				}
			}
			else
			{
				if (entity->GetisPressed())
					entity->SetisPressed(false);
			}
		}
		if (entity->GetName() == "Synergist" && entity->isitHover())
		{
			if (!entity->GetisPressed() && !entity->GetisSelected())
			{
				if (Application::IsMousePressed(0))
				{
					//if (!entity->GetisSelected())
					{
						for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetAITroops().begin(); itr2 != BattleSystem::Instance().GetAITroops().end(); itr2++)
						{
							CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
							if (entity2->GetName() == "Warrior")
								entity2->SetScale(Vector3(10, 10, 1));
							if (entity2->GetName() == "Mage")
								entity2->SetScale(Vector3(10, 10, 1));
							if (entity2->GetName() == "Synergist")
								entity2->SetScale(Vector3(10, 10, 1));
							entity2->SetisSelected(false);
						}

						entity->SetScale(entity->GetScale() + Vector3(5, 5, 1));

						BattleSystem::Instance().SetSelectedEnemyTroop(BattleSystem::Instance().GetAITroopAttacking((*itr).first));
						std::cout << BattleSystem::Instance().GetSelectedEnemyTroop()->GetName() << std::endl;
						entity->SetisSelected(true);
						entity->SetisPressed(true);
					}
				}
			}
			else
			{
				if (entity->GetisPressed())
					entity->SetisPressed(false);
			}
		}
	}

	for (std::vector<Button*>::iterator itr = button->GetList()->begin(); itr != button->GetList()->end(); itr++)
	{
		if (BattleSystem::Instance().GetSelectedTroop() != NULL)
		{
			(*itr)->UpdateBattleScene(dt);
		}

		//skill
		if (((*itr)->type == "Default Attack" || (*itr)->type == "Skill 1" || (*itr)->type == "Skill 2" || (*itr)->type == "Skill 3") && (*itr)->isitHover())
		{
			if (Application::IsMousePressed(0))
			{
				if (!(*itr)->GetisPressed())
				{
					for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
					{
						CharacterEntity* entity = (CharacterEntity*)itr2->second;
						if (entity == BattleSystem::Instance().GetSelectedTroop())
						{
							if ((*itr)->type == "Default Attack")
								BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(0));
							else if ((*itr)->type == "Skill 1")
								BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(1));
						}
					}
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


		if ((*itr)->type == "Attack Button" && (*itr)->isitHover())
		{
			if (Application::IsMousePressed(0))
			{
				if (!(*itr)->GetisPressed())
				{
					size_t i = 0;
					CharacterEntity* temp = BattleSystem::Instance().GetSelectedEnemyTroop();
					for (map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetAITroops().begin(); itr2 != BattleSystem().Instance().GetAITroops().end(); itr2++)
					{
						if (itr2->second == temp)
							break;
						i++;
					}
					CharacterEntity* tempo = BattleSystem::Instance().GetSelectedTroop();
					Skill* tempi = BattleSystem::Instance().GetSelectedSkill();

					bool temp2 = BattleSystem::Instance().CanActivateSkill(BattleSystem::Instance().GetSelectedTroop(), i, BattleSystem::Instance().GetSelectedSkill());
					if (temp2)
						BattleSystem::Instance().DamageCalculation(i, BattleSystem::Instance().GetSelectedSkill());
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

		if ((*itr)->type == "End Turn" && (*itr)->isitHover())
		{
			if (Application::IsMousePressed(0))
			{
				BattleSystem::Instance().SetPlayerTurn(false);
				for (std::map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetPlayerTroops().begin(); itr != BattleSystem::Instance().GetPlayerTroops().end(); itr++)
				{
					CharacterEntity* entity = (CharacterEntity*)itr->second;
					if (entity->GetName() == "Warrior" || entity->GetName() == "Mage" || entity->GetName() == "Synergist")
						entity->SetScale(tempscale);
					entity->SetisSelected(false);
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
	AI->Update(dt);
}

void SceneTutorial::RenderObjects(BaseObject *obj)
{

}

void SceneTutorial::Render()
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

	if (BattleSystem::Instance().GetTurnCost() > 0){
		modelStack->PushMatrix();
		modelStack->Translate(((float)(ObjectManager::Instance().WorldWidth * 0.5f - ((float)(100 - BattleSystem::Instance().GetTurnCost()) / 4))), ObjectManager::Instance().WorldHeight * 0.3f, -5.f);
		modelStack->Scale((float)(BattleSystem::Instance().GetTurnCost() * 0.5f), 5, 1);
		Renderer->RenderMesh("Test", false);
		modelStack->PopMatrix();
	}

	modelStack->PushMatrix();
	modelStack->Translate(((float)(ObjectManager::Instance().WorldWidth * 0.5f)), ObjectManager::Instance().WorldHeight * 0.3f, -5.f);
	modelStack->Scale(50, 5, 1);
	Renderer->RenderMesh("Test1", false);
	modelStack->PopMatrix();

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	//Renderer->SetHUD(true);
	Renderer->RenderMesh("BattleScene", false);
	//Renderer->SetHUD(false);
	modelStack->PopMatrix();

	for (std::vector<Button*>::iterator itr = (*button->GetList()).begin(); itr != (*button->GetList()).end(); itr++)
	{
		Button* obj = (Button *)*itr;
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 10);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, 1);

		if (BattleSystem::Instance().GetSelectedTroop() != nullptr)
		{
			if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Warrior")
			{

				for (int i = 0; i < BattleSystem::Instance().GetSelectedTroop()->GetSkillList()->size(); i++)
				{
					if (BattleSystem::Instance().GetSelectedSkill(i) != nullptr)
					{
						if (BattleSystem::Instance().GetSelectedSkill(i) && obj->type == "Default Attack")
						{
							if (BattleSystem::Instance().GetSelectedSkill(i)->GetName() == "Basic Attack")
								Renderer->RenderMesh("DefaultAttack", false);
						}
						if (BattleSystem::Instance().GetSelectedSkill(i))
						{
							if (obj->type == "Skill 1")
							{
								if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Stab")
									Renderer->RenderMesh("Stab", false);
								else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Bash")
									Renderer->RenderMesh("Bash", false);
								else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Rush")
									Renderer->RenderMesh("Rush", false);
								else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Taunt")
									Renderer->RenderMesh("Taunt", false);
							}
							else if (obj->type == "Skill 2")
							{
								if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Stab")
									Renderer->RenderMesh("Stab", false);
								else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Bash")
									Renderer->RenderMesh("Bash", false);
								else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Rush")
									Renderer->RenderMesh("Rush", false);
								else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Taunt")
									Renderer->RenderMesh("Taunt", false);
							}
							else if (obj->type == "Skill 3")
							{
								if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Stab")
									Renderer->RenderMesh("Stab", false);
								else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Bash")
									Renderer->RenderMesh("Bash", false);
								else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Rush")
									Renderer->RenderMesh("Rush", false);
								else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Taunt")
									Renderer->RenderMesh("Taunt", false);
							}
						}
					}
				}
			}
			else if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Mage")
			{
				if (obj->type == "Default Attack")
					Renderer->RenderMesh("RedPotion", false);
				if (obj->type == "Skill 1")
					Renderer->RenderMesh("RedPotion", false);
				if (obj->type == "Skill 2")
					Renderer->RenderMesh("RedPotion", false);
				if (obj->type == "Skill 3")
					Renderer->RenderMesh("RedPotion", false);
			}
			else if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Synergist")
			{
				if (obj->type == "Default Attack")
					Renderer->RenderMesh("BluePotion", false);
				if (obj->type == "Skill 1")
					Renderer->RenderMesh("BluePotion", false);
				if (obj->type == "Skill 2")
					Renderer->RenderMesh("BluePotion", false);
				if (obj->type == "Skill 3")
					Renderer->RenderMesh("BluePotion", false);
			}
		}
		modelStack->PopMatrix();

		for (std::vector<Description*>::iterator itr2 = (*button->GetDescriList()).begin(); itr2 != (*button->GetDescriList()).end(); itr2++)
		{
			Description* obj2 = (Description*)*itr2;
			modelStack->PushMatrix();
			modelStack->Translate(obj2->GetPosition().x, obj2->GetPosition().y, /*obj2->GetPosition().z*/5);
			if ((*itr)->isitHover())
			{
				if (BattleSystem::Instance().GetSelectedTroop() != nullptr)
				{
					for (size_t i = 0; i < BattleSystem::Instance().GetSelectedTroop()->GetSkillList()->size(); i++)
					{
						if ((*itr)->type == "Default Attack" && obj2->type == "Default Attack")
						{
							modelStack->PushMatrix();
							modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
							//Renderer->RenderMesh("DescripRedPotion", false);
							modelStack->PopMatrix();
							if (obj2->text->GetType() == "Default Attack")
							{
								if (BattleSystem::Instance().GetSelectedSkill(i) != nullptr)
								{
									std::string temp = BattleSystem::Instance().GetSelectedSkill(i)->GetName();
									modelStack->PushMatrix();
									modelStack->Translate(obj2->text->GetPosition().x, obj2->text->GetPosition().y, /*obj2->GetPosition().z*/5);
									modelStack->Scale(obj2->text->GetScale().x, obj2->text->GetScale().y, obj2->text->GetScale().z);
									Renderer->RenderText("text", temp, Color(1, 1, 1));
									modelStack->PopMatrix();
								}
							}
						}
						else if ((*itr)->type == "Skill 1" && obj2->type == "Skill 1")
						{
							modelStack->PushMatrix();
							modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
							//Renderer->RenderMesh("DescripAttackPotion", false);
							modelStack->PopMatrix();
							if (obj2->text->GetType() == "Skill 1")
							{
								if (BattleSystem::Instance().GetSelectedSkill(i) != nullptr)
								{
									std::string temp = BattleSystem::Instance().GetSelectedSkill(i)->GetName();
									modelStack->PushMatrix();
									modelStack->Translate(obj2->text->GetPosition().x, obj2->text->GetPosition().y, /*obj2->GetPosition().z*/5);
									modelStack->Scale(obj2->text->GetScale().x, obj2->text->GetScale().y, obj2->text->GetScale().z);
									Renderer->RenderText("text", temp, Color(1, 1, 1));
									modelStack->PopMatrix();
								}
							}
						}
						else if ((*itr)->type == "Skill 2" && obj2->type == "Skill 2")
						{
							modelStack->PushMatrix();
							modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
							//Renderer->RenderMesh("DescripDefencePotion", false);
							modelStack->PopMatrix();
							if (obj2->text->GetType() == "Skill 2")
							{
								if (BattleSystem::Instance().GetSelectedSkill(i) != nullptr)
								{
									std::string temp = BattleSystem::Instance().GetSelectedSkill(i)->GetName();
									modelStack->PushMatrix();
									modelStack->Translate(obj2->text->GetPosition().x, obj2->text->GetPosition().y, /*obj2->GetPosition().z*/5);
									modelStack->Scale(obj2->text->GetScale().x, obj2->text->GetScale().y, obj2->text->GetScale().z);
									Renderer->RenderText("text", temp, Color(1, 1, 1));
									modelStack->PopMatrix();
								}
							}
						}
						else if ((*itr)->type == "Skill 3" && obj2->type == "Skill 3")
						{
							modelStack->PushMatrix();
							modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
							//Renderer->RenderMesh("DescripBandage", false);
							modelStack->PopMatrix();
							if (obj2->text->GetType() == "Skill 3")
							{
								if (BattleSystem::Instance().GetSelectedSkill(i) != nullptr)
								{
									std::string temp = BattleSystem::Instance().GetSelectedSkill(i)->GetName();
									modelStack->PushMatrix();
									modelStack->Translate(obj2->text->GetPosition().x, obj2->text->GetPosition().y, /*obj2->GetPosition().z*/5);
									modelStack->Scale(obj2->text->GetScale().x, obj2->text->GetScale().y, obj2->text->GetScale().z);
									Renderer->RenderText("text", temp, Color(1, 1, 1));
									modelStack->PopMatrix();
								}
							}
						}
					}
				}
				}
			modelStack->PopMatrix();
		}
	}

	for (std::vector<Button*>::iterator itr = (*button->GetList()).begin(); itr != (*button->GetList()).end(); itr++)
	{
		Button* obj = (Button *)*itr;
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 10);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, 1);
		if (obj->type == "Red Potion")
			Renderer->RenderMesh("RedPotion", false);
		if (obj->type == "Attack Potion")
			Renderer->RenderMesh("AttackPotion", false);
		if (obj->type == "Defence Potion")
			Renderer->RenderMesh("DefencePotion", false);
		if (obj->type == "Bandage")
			Renderer->RenderMesh("Bandage", false);
		if (obj->type == "Attack Button")
			Renderer->RenderMesh("Inventory", false);
		if (obj->type == "End Turn")
			Renderer->RenderMesh("Inventory", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x - 5.5, obj->GetPosition().y, 0.5);
		modelStack->Scale(2, 2, 1);
		if (obj->type == "Attack Button")
			Renderer->RenderText("text", "Attack", Color(1, 1, 1));
		if (obj->type == "End Turn")
			Renderer->RenderText("text", "End", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y - 10, 0.5);
		modelStack->Scale(3, 3, 1);
		std::string temp = std::to_string(Player::Instance().GetConsumableList().find("Red Potion")->second);
		if (obj->type == "Red Potion")
			Renderer->RenderText("text", temp, Color(1, 1, 1));
		temp = std::to_string(Player::Instance().GetConsumableList().find("Attack Potion")->second);
		if (obj->type == "Attack Potion")
			Renderer->RenderText("text", temp, Color(1, 1, 1));
		temp = std::to_string(Player::Instance().GetConsumableList().find("Defence Potion")->second);
		if (obj->type == "Defence Potion")
			Renderer->RenderText("text", temp, Color(1, 1, 1));
		temp = std::to_string(Player::Instance().GetConsumableList().find("Bandage")->second);
		if (obj->type == "Bandage")
			Renderer->RenderText("text", temp, Color(1, 1, 1));
		modelStack->PopMatrix();

	}

	for (map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetPlayerTroops().begin(); itr != BattleSystem::Instance().GetPlayerTroops().end(); itr++)
	{
		CharacterEntity* entity = (CharacterEntity*)itr->second;
		float entityhealth = (float)entity->GetHealth() / (float)entity->GetMaxHealth();
		modelStack->PushMatrix();
		modelStack->Translate(entity->GetVectorPosition().x, entity->GetVectorPosition().y, 10);
		modelStack->Scale(entity->GetScale().x, entity->GetScale().y, 1);
		if (entity->GetName() == "Warrior")
		{
			if (entity->GetDefeated())
			{
				Renderer->RenderMesh("PlayerWarriorDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("PlayerWarriorDying", false);
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
		if (entity->GetName() == "Synergist")
		{
			if (entity->GetDefeated())
			{
				Renderer->RenderMesh("PlayerSynergistDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("PlayerSynergistDying", false);
			}
			else
			{
				Renderer->RenderMesh("PlayerSynergistMesh", false);
			}
		}
		modelStack->PopMatrix();
	}

	for (map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetAITroops().begin(); itr != BattleSystem::Instance().GetAITroops().end(); itr++)
	{

		CharacterEntity* entity = (CharacterEntity*)itr->second;
		float entityhealth = (float)entity->GetHealth() / (float)entity->GetMaxHealth();
		modelStack->PushMatrix();
		modelStack->Translate(entity->GetVectorPosition().x, entity->GetVectorPosition().y, 10);
		modelStack->Scale(entity->GetScale().x, entity->GetScale().y, 1);
		if (entity->GetName() == "Warrior")
		{
			if (BattleSystem::Instance().GetPlayerTurn() == false)
			{
				Sleep(300); //Now Left to check when a Skill is used, will add into the condition
				Renderer->RenderMesh("WarriorAttackMesh", false);

			}
			else if (entity->GetDefeated())
			{
				Renderer->RenderMesh("WarriorDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("WarriorDying", false);
			}
			else
			{
				Renderer->RenderMesh("WarriorMesh", false);
			}
		}
		if (entity->GetName() == "Mage")
		{
			if (BattleSystem::Instance().GetPlayerTurn() == false)
			{
				Sleep(300);
				Renderer->RenderMesh("MageAttack", false);

			}
			else if (entity->GetDefeated())
			{
				Renderer->RenderMesh("MageDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("MageDying", false);
			}
			else
			{
				Renderer->RenderMesh("MageMesh", false);
			}
		}
		if (entity->GetName() == "Priest")
		{
			if (BattleSystem::Instance().GetPlayerTurn() == false)
			{
				Sleep(300);
				Renderer->RenderMesh("PriestAttack", false);

			}
			else if (entity->GetDefeated())
			{
				Renderer->RenderMesh("PriestDead", false);
			}
			else if (entityhealth <= 0.3f)
			{
				Renderer->RenderMesh("PriestDying", false);
			}
			else
			{
				Renderer->RenderMesh("PriestMesh", false);
			}
		}
		modelStack->PopMatrix();
	}
}

void SceneTutorial::HandleUserInput()
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
}

void SceneTutorial::Exit()
{
	//SceneBase::Exit();
	//Cleanup Objects
	ObjectManager::Instance().Exit();
	//button->Exit();
}