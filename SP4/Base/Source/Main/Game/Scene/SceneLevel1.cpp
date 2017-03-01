#include "SceneLevel1.h"
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

SceneLevel1::SceneLevel1()
{
}


SceneLevel1::~SceneLevel1()
{
	if (AI != nullptr)
	{
		AI->Exit();
		delete AI;
	}
	AI = nullptr;
}

void SceneLevel1::Init()
{
	// Init Scene
	this->SetEntityID("Level1");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	button = new BattleButton();
	button->Init(x, y);

	Warrior* warrior;
	Mage* mage;
	Synergist* synergist;

	for (int i = 0; i < 2; ++i)
	{
		int test = Math::RandIntMinMax(1, 3);
		switch (test)
		{
		case 1:
			warrior = new Warrior();
			warrior->Init(Math::RandIntMinMax(1, 2));
			BattleSystem::Instance().SetAITroops(i, warrior);
			break;
		case 2:
			mage = new Mage();
			mage->Init(Math::RandIntMinMax(1, 2));
			BattleSystem::Instance().SetAITroops(i, mage);
			break;
		case 3:
			synergist = new Synergist();
			synergist->Init(Math::RandIntMinMax(1, 2));
			BattleSystem::Instance().SetAITroops(i, synergist);
			break;
		}

	}

	AudioPlayer::Instance().StopAllMusic();
	AudioPlayer::Instance().PlayMusic("Battle Music");

	for (size_t i = 0; i < BattleSystem::Instance().GetAITroops().size(); i++)
	{
		string emptyString = "";
		AIDamaged.push_back(emptyString);
	}

	for (size_t i = 0; i < BattleSystem::Instance().GetPlayerTroops().size(); i++)
	{
		string emptyString = "";
		PlayerDamaged.push_back(emptyString);
	}

	BattleSystem::Instance().CheckTroopPositions();

	AI = new AIAllAttack();
	//BattleSystem::Instance().Debugging();

	tempscale = Vector3(10, 10, 1);
	tempscale1 = Vector3(15, 15, 1);

	for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
	{
		CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
		if (entity2 != NULL)
		{
			if (entity2->GetName() == "Warrior" || entity2->GetName() == "Mage" || entity2->GetName() == "Synergist")
				entity2->SetScale(tempscale);
			entity2->SetisSelected(false);
		}
	}
	timer = 0;
	textPos = 0;
	renderDamage = false;
}

void SceneLevel1::UpdateCharacterLogic(double dt)
{
}

void SceneLevel1::UpdateInternals(double dt)
{
}

bool SceneLevel1::CheckCollision(BaseObject* o1, BaseObject* o2, std::string type)
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

void SceneLevel1::Update(float dt)
{
	button->UpdateDescription(dt);

	for (std::map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetPlayerTroops().begin(); itr != BattleSystem::Instance().GetPlayerTroops().end(); itr++)
	{
		CharacterEntity* entity = (CharacterEntity*)itr->second;

		if (entity->GetName() == "Warrior" && entity->isitHover())
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
						textPos = BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().y;
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
						textPos = BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().y;
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
						textPos = BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().y;
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
							else if ((*itr)->type == "Skill 2")
								BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(2));
							else if ((*itr)->type == "Skill 3")
								BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(3));
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
					{
						BattleSystem::Instance().DamageCalculation(i, BattleSystem::Instance().GetSelectedSkill());
						if (tempo->GetName() == "Warrior")
						{
							AudioPlayer::Instance().PlayWarriorAttack();
						}
						else if (tempo->GetName() == "Mage")
						{
							AudioPlayer::Instance().PlayMageAttack();
						}
						else if (tempo->GetName() == "Synergist")
						{
							AudioPlayer::Instance().PlayPriestAttack();
						}
						damage = "-" + std::to_string(BattleSystem::Instance().DamageCalculation(i, BattleSystem::Instance().GetSelectedSkill()));
						renderDamage = true;
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

	if (renderDamage)
	{
		timer += dt;
		textPos += 10 * dt;
		if (timer > 2.f)
		{
			timer = 0.f;
			renderDamage = false;
			if (BattleSystem::Instance().GetSelectedEnemyTroop() != nullptr)
				textPos = BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().y;
		}
	}
	if (BattleSystem::Instance().GetNumberOfAITroopAlive() == 0)
	{
		SceneSystem::Instance().SwitchScene("Win_Scene");
		//BattleSystem::Instance().SetPlayerWon(2);
	}
	else if (BattleSystem::Instance().GetNumberOfPlayerTroopAlive() == 0)
	{
		BattleSystem::Instance().GetNumberOfPlayerTroopAlive();
		SceneSystem::Instance().SwitchScene("Lose_Scene");
		//BattleSystem::Instance().SetPlayerWon(1);
	}
}

void SceneLevel1::RenderObjects(BaseObject *obj)
{

}

void SceneLevel1::Render()
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
				if (obj->type == "Default Attack" && BattleSystem::Instance().GetSelectedSkill(0))
				{
					if (BattleSystem::Instance().GetSelectedSkill(0)->GetName() == "Basic Attack")
						Renderer->RenderMesh("DefaultAttack", false);
				}
				else if (obj->type == "Skill 1" && BattleSystem::Instance().GetSelectedSkill(1))
				{
					if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Stab")
						Renderer->RenderMesh("Stab", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Bash")
						Renderer->RenderMesh("Bash", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Rush")
						Renderer->RenderMesh("Rush", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Quick Blitz")
						Renderer->RenderMesh("QuickBlitz", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Divine Execution")
						Renderer->RenderMesh("Divine Execution", false);
				}
				else if (obj->type == "Skill 2" && BattleSystem::Instance().GetSelectedSkill(2))
				{
					if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Stab")
						Renderer->RenderMesh("Stab", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Bash")
						Renderer->RenderMesh("Bash", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Rush")
						Renderer->RenderMesh("Rush", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Quick Blitz")
						Renderer->RenderMesh("QuickBlitz", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Divine Execution")
						Renderer->RenderMesh("Divine Execution", false);
				}
				else if (obj->type == "Skill 3" && BattleSystem::Instance().GetSelectedSkill(3))
				{
					if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Stab")
						Renderer->RenderMesh("Stab", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Bash")
						Renderer->RenderMesh("Bash", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Rush")
						Renderer->RenderMesh("Rush", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Quick Blitz")
						Renderer->RenderMesh("QuickBlitz", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Divine Execution")
						Renderer->RenderMesh("Divine Execution", false);
				}
			}
			else if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Mage")
			{
				if (BattleSystem::Instance().GetSelectedSkill(0) && obj->type == "Default Attack")
				{
					if (BattleSystem::Instance().GetSelectedSkill(0)->GetName() == "Basic Attack")
						Renderer->RenderMesh("DefaultAttack", false);
				}
				else if (obj->type == "Skill 1" && BattleSystem::Instance().GetSelectedSkill(1))
				{
					if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Magic Bolt")
						Renderer->RenderMesh("MagicBolt", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Blinding Flash")
						Renderer->RenderMesh("BlindingFlash", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Unholy Incantation")
						Renderer->RenderMesh("Unholy Incantation", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Miasmic cloud")
						Renderer->RenderMesh("MiasmicCloud", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Ars Arcanum")
						Renderer->RenderMesh("Ars Arcanum", false);
				}
				else if (obj->type == "Skill 2" && BattleSystem::Instance().GetSelectedSkill(2))
				{
					if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Magic Bolt")
						Renderer->RenderMesh("MagicBolt", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Blinding Flash")
						Renderer->RenderMesh("BlindingFlash", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Unholy Incantation")
						Renderer->RenderMesh("Unholy Incantation", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Miasmic cloud")
						Renderer->RenderMesh("MiasmicCloud", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Ars Arcanum")
						Renderer->RenderMesh("Ars Arcanum", false);
				}
				else if (obj->type == "Skill 3" && BattleSystem::Instance().GetSelectedSkill(3))
				{
					if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Magic Bolt")
						Renderer->RenderMesh("MagicBolt", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Blinding Flash")
						Renderer->RenderMesh("BlindingFlash", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Unholy Incantation")
						Renderer->RenderMesh("Unholy Incantation", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Miasmic cloud")
						Renderer->RenderMesh("MiasmicCloud", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Ars Arcanum")
						Renderer->RenderMesh("Ars Arcanum", false);
				}
			}
			else if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Synergist")
			{
				if (obj->type == "Default Attack" && BattleSystem::Instance().GetSelectedSkill(0))
				{
					if (BattleSystem::Instance().GetSelectedSkill(0)->GetName() == "Basic Attack")
						Renderer->RenderMesh("DefaultAttack", false);
				}
				else if (obj->type == "Skill 1" && BattleSystem::Instance().GetSelectedSkill(1))
				{
					if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Life Drain")
						Renderer->RenderMesh("LifeDrain", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Dark Hail")
						Renderer->RenderMesh("DarkHail", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Unholy Gift")
						Renderer->RenderMesh("UnholyGift", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Power Breakdown")
						Renderer->RenderMesh("PowerBreakdown", false);
					else if (BattleSystem::Instance().GetSelectedSkill(1)->GetName() == "Quake")
						Renderer->RenderMesh("Quake", false);
				}
				else if (obj->type == "Skill 2" && BattleSystem::Instance().GetSelectedSkill(2))
				{
					if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Life Drain")
						Renderer->RenderMesh("LifeDrain", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Dark Hail")
						Renderer->RenderMesh("DarkHail", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Unholy Gift")
						Renderer->RenderMesh("UnholyGift", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Power Breakdown")
						Renderer->RenderMesh("PowerBreakdown", false);
					else if (BattleSystem::Instance().GetSelectedSkill(2)->GetName() == "Quake")
						Renderer->RenderMesh("Quake", false);
				}
				else if (obj->type == "Skill 3" && BattleSystem::Instance().GetSelectedSkill(3))
				{
					if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Life Drain")
						Renderer->RenderMesh("LifeDrain", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Dark Hail")
						Renderer->RenderMesh("DarkHail", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Unholy Gift")
						Renderer->RenderMesh("UnholyGift", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Power Breakdown")
						Renderer->RenderMesh("PowerBreakdown", false);
					else if (BattleSystem::Instance().GetSelectedSkill(3)->GetName() == "Quake")
						Renderer->RenderMesh("Quake", false);
				}
			}
		}
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x + obj->GetScale().x * 0.25, obj->GetPosition().y, 11);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, 1);

		if (BattleSystem::Instance().GetSelectedTroop() != nullptr)
		{
			if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Warrior")
			{
				if (BattleSystem::Instance().GetSelectedSkill(1) && obj->type == "Skill 1" && BattleSystem::Instance().GetSelectedSkill(1)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(1)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
				if (BattleSystem::Instance().GetSelectedSkill(2) && obj->type == "Skill 2" && BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
				if (BattleSystem::Instance().GetSelectedSkill(3) && obj->type == "Skill 3" && BattleSystem::Instance().GetSelectedSkill(3)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(3)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
			}
			else if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Mage")
			{
				if (BattleSystem::Instance().GetSelectedSkill(1) && obj->type == "Skill 1" && BattleSystem::Instance().GetSelectedSkill(1)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(1)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
				if (BattleSystem::Instance().GetSelectedSkill(2) && obj->type == "Skill 2" && BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
				if (BattleSystem::Instance().GetSelectedSkill(3) && obj->type == "Skill 3" && BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(3)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
			}
			else if (BattleSystem::Instance().GetSelectedTroop()->GetName() == "Synergist")
			{
				if (BattleSystem::Instance().GetSelectedSkill(1) && obj->type == "Skill 1" && BattleSystem::Instance().GetSelectedSkill(1)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(1)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
				if (BattleSystem::Instance().GetSelectedSkill(2) && obj->type == "Skill 2" && BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
				if (BattleSystem::Instance().GetSelectedSkill(3) && obj->type == "Skill 3" && BattleSystem::Instance().GetSelectedSkill(2)->GetTurnCooldown() > 0)
				{
					std::string temp = std::to_string(BattleSystem::Instance().GetSelectedSkill(3)->GetTurnCooldown());
					Renderer->RenderText("text", temp, Color(1, 1, 1));
				}
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
				if ((*itr)->type == "Default Attack" && obj2->type == "Default Attack")
				{
					modelStack->PushMatrix();
					modelStack->Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
					//Renderer->RenderMesh("DescripRedPotion", false);
					modelStack->PopMatrix();
					if (obj2->text->GetType() == "Default Attack")
					{
						if (BattleSystem::Instance().GetSelectedSkill(0) != nullptr)
						{
							std::string temp = BattleSystem::Instance().GetSelectedSkill(0)->GetName();
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
						if (BattleSystem::Instance().GetSelectedSkill(1) != nullptr)
						{
							std::string temp = BattleSystem::Instance().GetSelectedSkill(1)->GetName();
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
						if (BattleSystem::Instance().GetSelectedSkill(2) != nullptr)
						{
							std::string temp = BattleSystem::Instance().GetSelectedSkill(2)->GetName();
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
						if (BattleSystem::Instance().GetSelectedSkill(3) != nullptr)
						{
							std::string temp = BattleSystem::Instance().GetSelectedSkill(3)->GetName();
							modelStack->PushMatrix();
							modelStack->Translate(obj2->text->GetPosition().x, obj2->text->GetPosition().y, /*obj2->GetPosition().z*/5);
							modelStack->Scale(obj2->text->GetScale().x, obj2->text->GetScale().y, obj2->text->GetScale().z);
							Renderer->RenderText("text", temp, Color(1, 1, 1));
							modelStack->PopMatrix();
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
		if (entity != NULL)
		{
			float entityhealth = (float)entity->GetHealth() / (float)entity->GetMaxHealth();
			modelStack->PushMatrix();
			modelStack->Translate(entity->GetVectorPosition().x, entity->GetVectorPosition().y, 9);
			modelStack->Scale(entity->GetScale().x, entity->GetScale().y, 1);
			if (!entity->GetDefeated())
			{
				if (entity->GetName() == "Warrior")
				{
					if (BattleSystem::Instance().GetSelectedTroop() == entity)
					{
						Renderer->RenderMesh("PlayerWarriorAttackMesh", false);
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
					if (BattleSystem::Instance().GetSelectedTroop() == entity)
					{
						Renderer->RenderMesh("PlayerMageAttack", false);
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
					if (BattleSystem::Instance().GetSelectedTroop() == entity)
					{
						Renderer->RenderMesh("PlayerSynergistAttack", false);
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
			}
			else
			{
				if (entity->GetName() == "Warrior")
				{
					Renderer->RenderMesh("PlayerWarriorDead", false);
				}
				if (entity->GetName() == "Mage")
				{
					Renderer->RenderMesh("PlayerMageDead", false);
				}
				if (entity->GetName() == "Synergist")
				{
					Renderer->RenderMesh("PlayerSynergistDead", false);
				}
			}

			if (entity->GetStunned() == true)
			{
				modelStack->PushMatrix();
				modelStack->Translate(-entity->GetScale().y / 30, -entity->GetScale().y / 15, 1);
				modelStack->Scale(.2f, 0.2f, 1.f);
				Renderer->RenderMesh("StunIcon", false);
				modelStack->PopMatrix();
			}
			if (entity->GetBleeding() == true)
			{
				modelStack->PushMatrix();
				modelStack->Translate(-entity->GetScale().y / 100, -entity->GetScale().y / 15, 1);
				modelStack->Scale(.2f, 0.2f, 1.f);
				Renderer->RenderMesh("BleedIcon", false);
				modelStack->PopMatrix();
			}
			if (entity->GetDebuffed() == true)
			{
				modelStack->PushMatrix();
				modelStack->Translate(entity->GetScale().y / 100, -entity->GetScale().y / 15, 1);
				modelStack->Scale(.2f, 0.2f, 1.f);
				Renderer->RenderMesh("DebuffIcon", false);
				modelStack->PopMatrix();
			}
			if (entity->GetBuffed() == true)
			{
				modelStack->PushMatrix();
				modelStack->Translate(entity->GetScale().y / 30, -entity->GetScale().y / 15, 1);
				modelStack->Scale(.2f, 0.2f, 1.f);
				Renderer->RenderMesh("BuffIcon", false);
				modelStack->PopMatrix();
			}
			modelStack->PopMatrix();
		}

	}

	for (map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetAITroops().begin(); itr != BattleSystem::Instance().GetAITroops().end(); itr++)
	{
		CharacterEntity* entity = (CharacterEntity*)itr->second;
		float entityhealth = (float)entity->GetHealth() / (float)entity->GetMaxHealth();
		modelStack->PushMatrix();
		modelStack->Translate(entity->GetVectorPosition().x, entity->GetVectorPosition().y, 10);
		modelStack->Scale(entity->GetScale().x, entity->GetScale().y, 1);
		if (!entity->GetDefeated())
		{
			if (entity->GetName() == "Warrior")
			{
				if (entityhealth <= 0.3f)
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
				if (entityhealth <= 0.3f)
				{
					Renderer->RenderMesh("MageDying", false);
				}
				else
				{
					Renderer->RenderMesh("MageMesh", false);
				}
			}
			if (entity->GetName() == "Synergist")
			{
				if (entityhealth <= 0.3f)
				{
					Renderer->RenderMesh("SynergistDying", false);
				}
				else
				{
					Renderer->RenderMesh("SynergistMesh", false);
				}
			}
		}
		else
		{
			if (entity->GetName() == "Warrior")
			{
				Renderer->RenderMesh("WarriorDead", false);
			}
			if (entity->GetName() == "Mage")
			{
				Renderer->RenderMesh("MageDead", false);
			}
			if (entity->GetName() == "Synergist")
			{
				Renderer->RenderMesh("SynergistDead", false);
			}
		}

		if (entity->GetStunned() == true)
		{
			modelStack->PushMatrix();
			modelStack->Translate(-entity->GetScale().y / 30, -entity->GetScale().y / 15, 1);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("StunIcon", false);
			modelStack->PopMatrix();
		}
		if (entity->GetBleeding() == true)
		{
			modelStack->PushMatrix();
			modelStack->Translate(-entity->GetScale().y / 100, -entity->GetScale().y / 15, 1);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("BleedIcon", false);
			modelStack->PopMatrix();
		}
		if (entity->GetDebuffed() == true)
		{
			modelStack->PushMatrix();
			modelStack->Translate(entity->GetScale().y / 100, -entity->GetScale().y / 15, 1);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("DebuffIcon", false);
			modelStack->PopMatrix();
		}
		if (entity->GetBuffed() == true)
		{
			modelStack->PushMatrix();
			modelStack->Translate(entity->GetScale().y / 30, -entity->GetScale().y / 15, 1);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("BuffIcon", false);
			modelStack->PopMatrix();
		}
		modelStack->PopMatrix();
	}
	if (renderDamage && BattleSystem::Instance().GetSelectedEnemyTroop() != nullptr)
	{
		modelStack->PushMatrix();
		modelStack->Translate(BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().x, textPos, BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().z);
		modelStack->Scale(5.f, 5.f, 5.f);
		Renderer->RenderText("text", damage, Color(1, 0, 0));
		modelStack->PopMatrix();
	}
}

void SceneLevel1::Exit()
{
	//Cleanup Objects
	ObjectManager::Instance().Exit();
	//button->Exit();
}