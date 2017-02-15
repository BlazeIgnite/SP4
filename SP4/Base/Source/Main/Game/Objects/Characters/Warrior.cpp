#include "Warrior.h"


Warrior::Warrior()
{

}

Warrior::~Warrior()
{

}

void Warrior::Init()
{
	//Sets up Skills used
	skill_1->SetAbilityCost(5);
	skill_1->SetMultiplier(0.65f);
	skill_1->SetActionCost(20.f);
	skill_1->SetSkillPosition(Position_Front);
	skill_1->SetSkillTarget(Target_Front);


}