#include "AIStatusEffect.h"
#include "../../Systems/BattleSystem.h"


AIStatusEffect::AIStatusEffect()
{
	Init();
}

AIStatusEffect::~AIStatusEffect()
{
}

void AIStatusEffect::Init()
{
	for (size_t i = 0; i < BattleSystem::Instance().GetPlayerTroops().size(); i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			SetPlayerTroopStatusE(BattleSystem::Instance().GetPlayerTroops().find(i)->first, j, false);
		}
	}

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
		vector<Skill*>::iterator it2 = it->second->GetSkillList().begin();
		vector<Skill*>::iterator it2End = it->second->GetSkillList().end();
		for (; it2 != it2End; it2++)
		{
			if ((*it2)->GetStatusEffectMap().size() > 0)
			{
				map<size_t, vector<string>>::iterator it3 = (*it2)->GetStatusEffectMap().begin();
				map<size_t, vector<string>>::iterator it3End = (*it2)->GetStatusEffectMap().end();
				for (; it3 != it3End; it3++)
				{
					vector<string>::iterator it4 = it3->second.begin();
					vector<string>::iterator it4End = it3->second.end();
					for (; it4 != it4End; it4++)
					{
						if ((*it4) == "Stun" || (*it4) == "Bleed")
							m_SkillAvailable.push_back((*it).second->GetSkillInVector((*it2)->GetName()));
					}
				}
			}
		}
	}
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

	if (BattleSystem::Instance().GetNumberOfAITroopAlive() == BattleSystem::Instance().GetAITroops().size())
	{

	}
	else
	{
		BattlePlanHolder->SetBattlePlan("All Basic Attack");
	}

	if (!BattlePlanHolder->GetBattlePlan(""))
		stateHolder->SetState("Execute");
}

void AIStatusEffect::Execute()
{
	if (BattlePlanHolder->GetBattlePlan("All Basic Attack"))
	{
		/*for ()
		{
		}*/
	}
		//do this attack type;

}

void AIStatusEffect::Exit()
{
	AIBase::Exit();
}

void AIStatusEffect::SetPlayerTroopStatusE(size_t troopPosition, size_t statusID, bool newStatusE)
{
	map<size_t, map<size_t, bool>>::iterator it = m_PlayerTroopStatusE.find(troopPosition);
	if (it == m_PlayerTroopStatusE.end())
	{
		map<size_t, bool> EmptyMap;
		EmptyMap[statusID] = newStatusE;
		m_PlayerTroopStatusE[troopPosition] = EmptyMap;
	}
	else
	{
		map<size_t, bool>::iterator it2 = it->second.find(statusID);
		if (it2 == it->second.end())
			m_PlayerTroopStatusE.find(troopPosition)->second[statusID] = newStatusE;
		else
			m_PlayerTroopStatusE.find(troopPosition)->second.at(statusID) = newStatusE;
	}
}

bool AIStatusEffect::GetPlayerTroopStatusE(size_t troopPosition, size_t statusID)
{
	return m_PlayerTroopStatusE.find(troopPosition)->second.find(statusID)->second;
}