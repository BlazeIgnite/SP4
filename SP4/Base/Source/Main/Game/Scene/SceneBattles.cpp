#include "SceneBattles.h"
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
	button->Init(x,y);

	Warrior* warrior2 = new Warrior();
	warrior2->Init(20);
	Mage* mage2 = new Mage();
	mage2->Init(20);
	Synergist* Synergist2 = new Synergist();
	Synergist2->Init(20);

	AudioPlayer::Instance().StopAllMusic();
	AudioPlayer::Instance().PlayMusic("Battle Music");

	BattleSystem::Instance().SetAITroops(0, warrior2);
	BattleSystem::Instance().SetAITroops(1, mage2);
	BattleSystem::Instance().SetAITroops(2, Synergist2);
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
	i = 0;
	timer = 0;
	startPosY = textPosY = BattleSystem::Instance().GetPlayerTroops().at(0)->GetVectorPosition().y;
	renderDamage = false;
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
	button->UpdateDescription(dt);

	if (BattleSystem::Instance().GetPlayerTurn())
	{
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
							//textPos = BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().y;

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
							//textPos = BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().y;
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
							//textPos = BattleSystem::Instance().GetSelectedEnemyTroop()->GetVectorPosition().y;
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
								{
									for (std::vector<Button*>::iterator itr3 = button->GetList()->begin(); itr3 != button->GetList()->end(); itr3++)
									{
										if (((*itr3)->type == "Default Attack" || (*itr3)->type == "Skill 1" || (*itr3)->type == "Skill 2" || (*itr3)->type == "Skill 3"))
											(*itr3)->SetScale(Vector3(6, 6, 1));
									}
									(*itr)->SetScale(Vector3(7, 7, 1));
									BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(0));
								}
								else if ((*itr)->type == "Skill 1")
								{
									for (std::vector<Button*>::iterator itr3 = button->GetList()->begin(); itr3 != button->GetList()->end(); itr3++)
									{
										if (((*itr3)->type == "Default Attack" || (*itr3)->type == "Skill 1" || (*itr3)->type == "Skill 2" || (*itr3)->type == "Skill 3"))
											(*itr3)->SetScale(Vector3(6, 6, 1));
									}
									(*itr)->SetScale(Vector3(7, 7, 1));
									BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(1));
								}
								else if ((*itr)->type == "Skill 2")
								{
									for (std::vector<Button*>::iterator itr3 = button->GetList()->begin(); itr3 != button->GetList()->end(); itr3++)
									{
										if (((*itr3)->type == "Default Attack" || (*itr3)->type == "Skill 1" || (*itr3)->type == "Skill 2" || (*itr3)->type == "Skill 3"))
											(*itr3)->SetScale(Vector3(6, 6, 1));
									}
									(*itr)->SetScale(Vector3(7, 7, 1));
									BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(2));
								}
								else if ((*itr)->type == "Skill 3")
								{
									for (std::vector<Button*>::iterator itr3 = button->GetList()->begin(); itr3 != button->GetList()->end(); itr3++)
									{
										if (((*itr3)->type == "Default Attack" || (*itr3)->type == "Skill 1" || (*itr3)->type == "Skill 2" || (*itr3)->type == "Skill 3"))
											(*itr3)->SetScale(Vector3(6, 6, 1));
									}
									(*itr)->SetScale(Vector3(7, 7, 1));
									BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(3));
								}
							}
						}
					}
					(*itr)->SetisPressed(true);
				}
				else
				{
					if ((*itr)->GetisPressed())
					{
						(*itr)->SetisPressed(false);
					}
				}
			}


			if ((*itr)->type == "Attack Button" && (*itr)->isitHover() && !renderDamage)
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
							//BattleSystem::Instance().DamageCalculation(i, BattleSystem::Instance().GetSelectedSkill());
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
							i = BattleSystem::Instance().GetSelectedEnemyTroopPosition();
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

			if ((*itr)->type == "End Turn" && (*itr)->isitHover() && !renderDamage)
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
	}
	

	AI->Update(dt);
	if (!BattleSystem::Instance().GetPlayerTurn() && AI->GetAttacking())
	{
		if (!renderDamage && AI->GetDamageCaused() >= 0 && damage == "")
		{
			damage = "-" + std::to_string(AI->GetDamageCaused());
			AI->SetDamageCaused(0);
			renderDamage = true;
		}

		if (renderDamage)
		{
			timer += dt;
			textPosY += 10 * dt;
			if (timer > 2.5f)
			{
				AI->SetAttacking(false);
				damage = "";
				renderDamage = false;
				timer = 0.f;
				textPosY = startPosY;
			}
		}
	}
	else if (BattleSystem::Instance().GetPlayerTurn())
	{
		if (renderDamage)
		{
			timer += dt;
			textPosY += 10 * dt;
			if (timer > 2.5f)
			{
				damage = "";
				renderDamage = false;
				timer = 0.f;
				textPosY = startPosY;
			}
		}
	}

	if (BattleSystem::Instance().GetNumberOfAITroopAlive() == 0)
	{
		SceneSystem::Instance().SwitchScene("Win_Scene");
		//BattleSystem::Instance().SetPlayerWon(2);
	}
	else if (BattleSystem::Instance().GetNumberOfPlayerTroopAlive() == 0)
	{
		SceneSystem::Instance().SwitchScene("Lose_Scene");
		//BattleSystem::Instance().SetPlayerWon(1);
	}
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

	if (BattleSystem::Instance().GetTurnCost() > 0){
		modelStack->PushMatrix();
		modelStack->Translate(((float)(ObjectManager::Instance().WorldWidth * 0.5f - ((float)(100 - BattleSystem::Instance().GetTurnCost()) * 0.25f))), ObjectManager::Instance().WorldHeight * 0.3f, -5.f);
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
			modelStack->PopMatrix();

			if (!entity->GetDefeated())
			{
				float temp = entity->GetHealth();
				float temp2 = entity->GetMaxHealth();
				float temp3 = (temp / temp2) * 10;
				if (entity->GetName() == "Warrior" || entity->GetName() == "Mage" || entity->GetName() == "Synergist")
				{
					modelStack->PushMatrix();
					modelStack->Translate(entity->GetVectorPosition().x, entity->GetVectorPosition().y + 10, 9);
					modelStack->Scale(temp3, 2, 1);
					{
						Renderer->RenderMesh("Health", false);
					}
					modelStack->PopMatrix();
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
				if (AI->GetAttacking() && itr->first == AI->GetAttacker())
				{
					Renderer->RenderMesh("WarriorAttackMesh", false);
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
			else if (entity->GetName() == "Mage")
			{
				if (AI->GetAttacking() && itr->first == AI->GetAttacker())
				{
					Renderer->RenderMesh("MageAttack", false);
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
			else if (entity->GetName() == "Synergist")
			{
				if (AI->GetAttacking() && itr->first == AI->GetAttacker())
				{
					Renderer->RenderMesh("SynergistAttack", false);
				}
				else if (entityhealth <= 0.3f)
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
			modelStack->Translate(-entity->GetScale().y / 30, -entity->GetScale().y / 15, 0);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("StunIcon", false);
			modelStack->PopMatrix();
		}
		if (entity->GetBleeding() == true)
		{
			modelStack->PushMatrix();
			modelStack->Translate(-entity->GetScale().y / 100, -entity->GetScale().y / 15, 0);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("BleedIcon", false);
			modelStack->PopMatrix();
		}
		if (entity->GetDebuffed() == true)
		{
			modelStack->PushMatrix();
			modelStack->Translate(entity->GetScale().y / 100, -entity->GetScale().y / 15, 0);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("DebuffIcon", false);
			modelStack->PopMatrix();
		}
		if (entity->GetBuffed() == true)
		{
			modelStack->PushMatrix();
			modelStack->Translate(entity->GetScale().y / 30, -entity->GetScale().y / 15, 0);
			modelStack->Scale(.2f, 0.2f, 1.f);
			Renderer->RenderMesh("BuffIcon", false);
			modelStack->PopMatrix();
		}
		modelStack->PopMatrix();
	}

	for (std::vector<Button*>::iterator itr = (*button->GetList()).begin(); itr != (*button->GetList()).end(); itr++)
	{
		Button* obj = (Button *)*itr;
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0);
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


		for (std::vector<Description*>::iterator itr2 = (* button->GetDescriList()).begin(); itr2 != (*button->GetDescriList()).end(); itr2++)
		{
			Description* obj2 = (Description*)*itr2;
			modelStack->PushMatrix();
			modelStack->Translate(obj2->GetPosition().x, obj2->GetPosition().y, /*obj2->GetPosition().z*/5);
			if ((*itr)->isitHover() && BattleSystem::Instance().GetSelectedTroop() != nullptr)
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
			Renderer->RenderMesh("Attack", false);
		if (obj->type == "End Turn")
			Renderer->RenderMesh("EndTurn", false);
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

	if (renderDamage && !BattleSystem::Instance().GetPlayerTurn())
	{
		modelStack->PushMatrix();
		modelStack->Translate(BattleSystem::Instance().GetPlayerTroops().at(AI->GetTarget())->GetVectorPosition().x, textPosY, BattleSystem::Instance().GetPlayerTroops().at(AI->GetTarget())->GetVectorPosition().z);
		modelStack->Scale(9, 9, 1);
		Renderer->RenderText("text", damage, Color(1, 0, 0));
		modelStack->PopMatrix();
	}
	else if (renderDamage && BattleSystem::Instance().GetPlayerTurn())
	{
		modelStack->PushMatrix();
		modelStack->Translate(BattleSystem::Instance().GetAITroops().at(i)->GetVectorPosition().x, textPosY, BattleSystem::Instance().GetPlayerTroops().at(i)->GetVectorPosition().z);
		modelStack->Scale(9, 9, 1);
		Renderer->RenderText("text", damage, Color(1, 0, 0));
		modelStack->PopMatrix();
	}
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
}

void SceneBattles::Exit()
{
	//SceneBase::Exit();
	//Cleanup Objects
	ObjectManager::Instance().Exit();
	//button->Exit();
}