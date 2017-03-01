#include "AIStatusEffect.h"
#include "../../Systems/BattleSystem.h"

#include <iostream>

using std::cout;
using std::endl;


AIStatusEffect::AIStatusEffect() 
{
	Init();
}

AIStatusEffect::~AIStatusEffect()
{
}

void AIStatusEffect::Init()
{
	//for (auto it = BattleSystem::Instance().GetAITroops().begin(); it != BattleSystem::Instance().GetAITroops().end();)
	//{
	//	for (auto it2 = it->second->GetSkillList().begin(); it2 != it->second->GetSkillList().end();)
	//	{
	//		for (auto it3 = (*it2)->GetStatusEffectMap().begin(); it3 != (*it2)->GetStatusEffectMap().end();)
	//		{
	//			if ((*it2)->GetStatusEffectMap().size() >= 0)
	//			{
	//				for (auto it4 = it3->second.begin(); it4 != it3->second.end();)
	//				{
	//					if ((*it4) == "Stun" || (*it4) == "Bleed")
	//					{
	//						m_SkillAvailable.push_back((*it).second->GetSkillInVector((*it2)GetName()));
	//					}
	//				}
	//			}
	//		}
	//	}
	//}


	for (map<size_t, CharacterEntity*>::iterator it = BattleSystem::Instance().GetAITroops().begin(); it != BattleSystem::Instance().GetAITroops().end(); it++)
	{
		vector<Skill*>::iterator it2 = it->second->GetSkillList()->begin();
		vector<Skill*>::iterator it2End = it->second->GetSkillList()->end();
		for (; it2 != it2End; it2++)
		{
			if ((*it2)->GetStatusEffectMap().size() > 0)
			{
				map<size_t, vector<string>>::iterator it3 = (*it2)->GetStatusEffectMap().begin();
				for (; it3 != (*it2)->GetStatusEffectMap().end(); it3++)
				{
					vector<string>::iterator it4 = it3->second.begin();
					for (; it4 != it3->second.end(); it4++)
					{
						if (((*it4) == "Stun" || (*it4) == "Bleed" || (*it4) == "Stab" || (*it4) == "Dark Hail" || (*it4) == "Quake") && ((*it2)->GetName() != "Ars Arcanum"))
						{
							m_SkillAvailable[it->second].push_back((*it).second->GetSkillInVector((*it2)->GetName()));
						}
					}
				}
			}
		}
	}
	m_SkillAvailableIterator = m_SkillAvailable.begin();
	m_SkillIterator = m_SkillAvailableIterator->second.begin();
} 

void AIStatusEffect::Update(double dt)
{
	if (!BattleSystem::Instance().GetPlayerTurn())
	{
		if (stateHolder->GetState(""))
			stateHolder->SetState("Planning");
		else if (stateHolder->GetState("Planning"))
			Planning();
		else if (stateHolder->GetState("Execute"))
			Execute();
	}
}

void AIStatusEffect::Planning()
{
	//if (m_Turns > 0)
	//	BattlePlanHolder->SetBattlePlan("All Basic Attack");
	//else
	//{
	//	m_target = 0;
	//	for (map<size_t, CharacterEntity*>::iterator it = BattleSystem::Instance().GetPlayerTroops().begin(); it != BattleSystem::Instance().GetPlayerTroops().end(); it++)
	//	{
	//		if (BattleSystem::Instance().CanActivateSkill(m_SkillAvailableIterator->first, it->first, (*m_SkillIterator)))
	//		{
	//			/*if (!(*it).second->GetDefeated() && (*m_StatusEffectEIterator) == "Stun")
	//			{
	//				BattlePlanHolder->SetBattlePlan("Use Stun");
	//				break;
	//			}
	//			else if (!(*it).second->GetDefeated() && (*m_StatusEffectEIterator) == "Bleed")
	//			{
	//				BattlePlanHolder->SetBattlePlan("Use Bleed");
	//				break;
	//			}*/
	//			if (!(*it).second->GetDefeated())
	//			{
	//				BattlePlanHolder->SetBattlePlan("Use Status Skill");
	//				break;
	//			}
	//		}
	//		m_target++;
	//	}
	//}

	//	/*int temp = Math::RandIntMinMax(0, 1);
	//	for (vector<Skill*>::iterator iterate = m_SkillAvailable.begin(); iterate != m_SkillAvailable.end(); iterate++)
	//	{
	//		for (map<size_t, vector<string>>::iterator iterate2 = (*iterate)->GetStatusEffectMap().begin; iterate2 != (*iterate)->GetStatusEffectMap().begin; iterate2++)
	//		{
	//			for (vector<string>::iterator iterate3 = iterate2->second.begin(); iterate3 != iterate2->second.end(); iterate3++)
	//			{
	//				if ((*iterate3) == "Stun" && temp == 0)
	//				{
	//					BattlePlanHolder->SetBattlePlan("Stun Time");
	//					stateHolder->SetState("Execute");
	//				}
	//			}
	//		}
	//	}
	//	if (temp == 0)
	//		BattlePlanHolder->SetBattlePlan("Stun Time");
	//	else
	//		BattlePlanHolder->SetBattlePlan("Bleed Time");
	//		*/

	//if (!BattlePlanHolder->GetBattlePlan(""))
	//	stateHolder->SetState("Execute");
}

void AIStatusEffect::Execute()
{
	/*if (BattlePlanHolder->GetBattlePlan("All Basic Attack"))
	{
		for (size_t i = 0; i < BattleSystem::Instance().GetNumberOfAITroopAlive(); i++)
		{
			if (BattleSystem::Instance().CanActivateSkill(BattleSystem::Instance().GetAITroopAttacking(i), 0, BattleSystem::Instance().GetAITroopAttacking(i)->GetSkillInVector("Basic Attack")))
			BattleSystem::Instance().DamageCalculation(0, BattleSystem::Instance().GetAITroopAttacking(i)->GetSkillInVector("Basic Attack"));
		}
		cout << "Enemy Used : " << BattlePlanHolder->GetBattlePlan() << endl;
		int temp = (int)m_Turns;
		if ((temp - 1) >= 0)
			m_Turns--;
	}
	else
	{
		m_Turns = 1;
		BattleSystem::Instance().DamageCalculation(m_target, (*m_SkillIterator));
		m_SkillIterator++;
		if (m_SkillIterator == m_SkillAvailableIterator->second.end())
		{
			m_SkillAvailableIterator++;
			if (m_SkillAvailableIterator == m_SkillAvailable.end())
				m_SkillAvailableIterator = m_SkillAvailable.begin();
			m_SkillIterator = m_SkillAvailableIterator->second.begin();
		}
		cout << "Enemy Used : " << BattlePlanHolder->GetBattlePlan() << endl;
	}
	
	cout << "m_Turns : " << m_Turns << endl;

	BattleSystem::Instance().SetPlayerTurn(true);
	stateHolder->SetState("");
	BattlePlanHolder->SetBattlePlan("");*/
}

void AIStatusEffect::Exit()
{
	AIBase::Exit();
}