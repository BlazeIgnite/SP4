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
	/*temp = new Button();
	temp->Init(Vector3(25, 20, 0), Vector3(5, 5, 1), "Blue Potion");
	buttonList.push_back(temp);*/
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
	temp->Init(Vector3(70, 15, 0), Vector3(7, 7, 1), "Auto Attack");
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
	temp->Init(Vector3(120, 22.5, 0), Vector3(10, 10, 1), "AI 1");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(140, 22.5, 0), Vector3(10, 10, 1), "AI 2");
	buttonList.push_back(temp);
	temp = new Button();
	temp->Init(Vector3(160, 22.5, 0), Vector3(10, 10, 1), "AI 3");
	buttonList.push_back(temp);

	tempscale = Vector3(10, 10, 1);
}

void BattleButton::Update(float dt)
{
	if (Application::IsKeyPressed('A'))
	{

		std::cout << BattleSystem::Instance().GetPlayerTroopAttacking(0)->GetName()<< std::endl;
		std::cout << BattleSystem::Instance().GetPlayerTroopAttacking(1)->GetName() << std::endl;
		std::cout << BattleSystem::Instance().GetPlayerTroopAttacking(2)->GetName() << std::endl;
	}

	for (std::map<size_t, CharacterEntity*>::iterator itr = BattleSystem::Instance().GetPlayerTroops().begin(); itr != BattleSystem::Instance().GetPlayerTroops().end(); itr++)
	{
		CharacterEntity* entity = (CharacterEntity*)itr->second;
		for (std::vector<Button*>::iterator itr2 = buttonList.begin(); itr2 != buttonList.end(); itr2++)
		{
			//if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
			if (entity->GetName() == "Warrior" && entity->isitHover())
			{
				if (!entity->GetisPressed() && !entity->GetisSelected())
				{
					if (Application::IsMousePressed(0))
					{
						//if (!entity->GetisSelected())
						{
							for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
							{
								CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
								if (entity2->GetName() == "Mage")
									entity2->SetScale(Vector3(10, 10, 1));
								if (entity2->GetName() == "Priest")
									entity2->SetScale(Vector3(10, 10, 1));
								entity2->SetisSelected(false);
							}

							entity->SetScale(entity->GetScale() + Vector3(5, 5, 1));

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
		//	else
		//	{
		//		if ((*itr)->GetisPressed())
		//			(*itr)->SetisPressed(false);
		//	}
		//}
		////Character 2 (Middle)
		//if ((*itr)->type == "Character 2" && (*itr)->isitHover())
		//{
		//	if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)

			if (entity->GetName() == "Mage" && entity->isitHover())
			{
				if (!entity->GetisPressed() && !entity->GetisSelected())
				{
					if (Application::IsMousePressed(0))
					{
						//if (!entity->GetisSelected())
						{
							for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
							{
								CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
								if (entity2->GetName() == "Warrior")
									entity2->SetScale(Vector3(10, 10, 1));
								if (entity2->GetName() == "Priest")
									entity2->SetScale(Vector3(10, 10, 1));
								entity2->SetisSelected(false);
							}
						
							entity->SetScale(entity->GetScale() + Vector3(5, 5, 1));

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
		//	else
		//	{
		//		if ((*itr)->GetisPressed())
		//			(*itr)->SetisPressed(false);
		//	}
		//}
		////Character 3 (Most Left)
		//if ((*itr)->type == "Character 3" && (*itr)->isitHover())
		//{
		//	if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)

			if (entity->GetName() == "Priest" && entity->isitHover())
			{
				if (!entity->GetisPressed() && !entity->GetisSelected() )
				{
					if (Application::IsMousePressed(0))
					{
						//if (entity->GetisSelected())
						{
							for (std::map<size_t, CharacterEntity*>::iterator itr2 = BattleSystem::Instance().GetPlayerTroops().begin(); itr2 != BattleSystem::Instance().GetPlayerTroops().end(); itr2++)
							{
								CharacterEntity* entity2 = (CharacterEntity*)itr2->second;
								if (entity2->GetName() == "Warrior")
									entity2->SetScale(Vector3(10, 10, 1));
								if (entity2->GetName() == "Mage")
									entity2->SetScale(Vector3(10, 10, 1));
								entity2->SetisSelected(false);
							}

							entity->SetScale(entity->GetScale() + Vector3(5, 5, 1));
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
	}
	for (std::vector<Button*>::iterator itr = buttonList.begin(); itr != buttonList.end(); itr++)
	{
		if (BattleSystem::Instance().GetSelectedTroop() != NULL)
		{
			(*itr)->UpdateBattleScene(dt);
		}
		//Character 1 (Most Right)
		//if ((*itr)->type == "Character 1" && (*itr)->isitHover())
		//{
		//	if (Application::IsMousePressed(0))
		//	{
		//		if (!(*itr)->GetisPressed())
		//		{
		//			for (std::vector<Button*>::iterator itr2 = buttonList.begin(); itr2 != buttonList.end(); itr2++)
		//			{
		//				if ((*itr2)->type == "Character 2")
		//					(*itr2)->SetScale(Vector3(10,10,1));
		//				if ((*itr2)->type == "Character 3")
		//					(*itr2)->SetScale(Vector3(10, 10, 1));
		//				(*itr2)->SetisSelected(false);
		//			}
		//			(*itr)->SetScale((*itr)->GetScale() + Vector3(5, 5, 1));
		//			BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking(0));
		//			std::cout << BattleSystem::Instance().GetSelectedTroop()->GetName() << std::endl;
		//			(*itr)->SetisSelected(true);
		//			(*itr)->SetisPressed(true);
		//		}
		//	}
		//	else
		//	{
		//		if ((*itr)->GetisPressed())
		//			(*itr)->SetisPressed(false);
		//	}
		//}
		////Character 2 (Middle)
		//if ((*itr)->type == "Character 2" && (*itr)->isitHover())
		//{
		//	if (Application::IsMousePressed(0))
		//	{
		//		if (!(*itr)->GetisPressed())
		//		{
		//			for (std::vector<Button*>::iterator itr2 = buttonList.begin(); itr2 != buttonList.end(); itr2++)
		//			{
		//				if ((*itr2)->type == "Character 1")
		//					(*itr2)->SetScale(Vector3(10, 10, 1));
		//				if ((*itr2)->type == "Character 3")
		//					(*itr2)->SetScale(Vector3(10, 10, 1));
		//				(*itr2)->SetisSelected(false);
		//			}
		//			(*itr)->SetScale((*itr)->GetScale() + Vector3(5, 5, 1));
		//			BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking(1));
		//			std::cout << BattleSystem::Instance().GetSelectedTroop()->GetName() << std::endl;
		//			(*itr)->SetisSelected(true);
		//			(*itr)->SetisPressed(true);
		//		}
		//	}
		//	else
		//	{
		//		if ((*itr)->GetisPressed())
		//			(*itr)->SetisPressed(false);
		//	}
		//}
		////Character 3 (Most Left)
		//if ((*itr)->type == "Character 3" && (*itr)->isitHover())
		//{
		//	if (Application::IsMousePressed(0))
		//	{
		//		if (!(*itr)->GetisPressed())
		//		{
		//			for (std::vector<Button*>::iterator itr2 = buttonList.begin(); itr2 != buttonList.end(); itr2++)
		//			{
		//				if ((*itr2)->type == "Character 1")
		//					(*itr2)->SetScale(Vector3(10, 10, 1));
		//				if ((*itr2)->type == "Character 2")
		//					(*itr2)->SetScale(Vector3(10, 10, 1));
		//				(*itr2)->SetisSelected(false);
		//			}
		//			(*itr)->SetScale((*itr)->GetScale() + Vector3(5, 5, 1));
		//			BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking(1));
		//			std::cout << BattleSystem::Instance().GetSelectedTroop()->GetName() << std::endl;
		//			(*itr)->SetisSelected(true);
		//			(*itr)->SetisPressed(true);
		//		}
		//	}
		//	else
		//	{
		//		if ((*itr)->GetisPressed())
		//			(*itr)->SetisPressed(false);
		//	}
		//}
		//AI 1 
		if ((*itr)->type == "AI 1" && (*itr)->isitHover())
		{
			if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
			{
				if (!(*itr)->GetisPressed())
				{
					for (std::vector<Button*>::iterator itr2 = buttonList.begin(); itr2 != buttonList.end(); itr2++)
					{
						(*itr2)->SetisTarget(false);
					}
					//BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking(0));
					(*itr)->SetisTarget(true);
					(*itr)->SetisPressed(true);
				}
			}
			else
			{
				if ((*itr)->GetisPressed())
					(*itr)->SetisPressed(false);
			}
		}
		if ((*itr)->type == "AI 2" && (*itr)->isitHover())
		{
			if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
			{
				if (!(*itr)->GetisPressed())
				{
					for (std::vector<Button*>::iterator itr2 = buttonList.begin(); itr2 != buttonList.end(); itr2++)
					{
						(*itr2)->SetisTarget(false);
					}
					//BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking(0));
					(*itr)->SetisTarget(true);
					(*itr)->SetisPressed(true);
				}
			}
			else
			{
				if ((*itr)->GetisPressed())
					(*itr)->SetisPressed(false);
			}
		}
		if ((*itr)->type == "AI 3" && (*itr)->isitHover())
		{
			if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK)
			{
				if (!(*itr)->GetisPressed())
				{
					for (std::vector<Button*>::iterator itr2 = buttonList.begin(); itr2 != buttonList.end(); itr2++)
					{
						(*itr2)->SetisTarget(false);
					}
					//BattleSystem::Instance().SetSelectedTroop(BattleSystem::Instance().GetPlayerTroopAttacking(0));
					(*itr)->SetisTarget(true);
					(*itr)->SetisPressed(true);
				}
			}
			else
			{
				if ((*itr)->GetisPressed())
					(*itr)->SetisPressed(false);
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