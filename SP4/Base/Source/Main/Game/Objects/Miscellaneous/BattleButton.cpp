#include "BattleButton.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../../Mains/Application.h"
#include "../../Game/Systems/BattleSystem.h"

BattleButton::BattleButton()
{
}


BattleButton::~BattleButton()
{
}

void BattleButton::Init()
{
	Button* temp;
	temp = new Button();
	temp->Init(Vector3(55, 22.5, 0), Vector3(10, 10, 1), "Character 1");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(35, 22.5, 0), Vector3(10, 10, 1), "Character 2");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(15, 22.5, 0), Vector3(10, 10, 1), "Character 3");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(17.5, 10, 0), Vector3(7, 7, 1), "Red Potion");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(27.5, 10, 0), Vector3(7, 7, 1), "Bandage");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(37.5, 10, 0), Vector3(7, 7, 1), "Attack Potion");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(47.5, 10, 0), Vector3(7, 7, 1), "Defence Potion");
	buttonList.push_back(temp);


	temp = new Button();
	temp->Init(Vector3(70, 15, 0), Vector3(7, 7, 1), "Default Attack");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(80, 15, 0), Vector3(7, 7, 1), "Skill 1");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(90, 15, 0), Vector3(7, 7, 1), "Skill 2");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(100, 15, 0), Vector3(7, 7, 1), "Skill 3");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(150, 15, 0), Vector3(15, 15, 1), "Attack Button");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(160, 15, 0), Vector3(15, 15, 1), "End Turn");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(120, 22.5, 0), Vector3(10, 10, 1), "AI 1");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(140, 22.5, 0), Vector3(10, 10, 1), "AI 2");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(160, 22.5, 0), Vector3(10, 10, 1), "AI 3");
	buttonList.push_back(temp);

	temp->SetisPressed(false);
	temp->SetisSelected(false);
	temp->SetisTarget(false);

	tempscale = Vector3(10, 10, 1);
	tempscale1 = Vector3(15, 15, 1);
}

void BattleButton::Update(float dt)
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
							if (entity2->GetName() == "Warrior" || entity2->GetName() == "Mage" || entity2->GetName() == "Priest")
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
							if (entity2->GetName() == "Warrior" || entity2->GetName() == "Mage" || entity2->GetName() == "Priest")
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

		if (entity->GetName() == "Priest" && entity->isitHover())
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
							if (entity2->GetName() == "Warrior" || entity2->GetName() == "Mage" || entity2->GetName() == "Priest")
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
							if (entity2->GetName() == "Priest")
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
							if (entity2->GetName() == "Priest")
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
		if (entity->GetName() == "Priest" && entity->isitHover())
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
							if (entity2->GetName() == "Priest")
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

	for (std::vector<Button*>::iterator itr = buttonList.begin(); itr != buttonList.end(); itr++)
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
								BattleSystem::Instance().SetSelectedSkill(BattleSystem::Instance().GetSelectedSkill(0));
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
					if (entity->GetName() == "Warrior" || entity->GetName() == "Mage" || entity->GetName() == "Priest")
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

void BattleButton::Exit()
{
	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
}

std::vector<Button*>* BattleButton::GetList()
{
	return &buttonList;
}