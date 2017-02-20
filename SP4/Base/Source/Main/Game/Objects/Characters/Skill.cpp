#include "Skill.h"
//#include "CharacterDatabase.h"

/************************************************/
/*                   Skills                     */

Ability::Ability()
{
	
}

void Ability::ApplyAbility(CharacterEntity* Character, CharacterEntity* target)
{
	
}


Bash::Bash()
{
	name = "Bash";
	id = 0001;
	actioncost = 30;
	statuseffect = Stun;
	timer = 3;
	multiplier = 0.30f;
	shiftposition = 0;
}

Rush::Rush()
{
	name = "Rush";
	id = 0002;
	actioncost = 25;
	statuseffect = No_Effect;
	timer = 3;
	multiplier = 0.30f;
	shiftposition = 1;
}

Taunt::Taunt()
{
	name = "Taunt";
	id = 0003;
	actioncost = 35;
	statuseffect = Buff;
	timer = 1;
}

Stab::Stab()
{
	name = "Stab";
	id = 0004;
	actioncost = 25;
	statuseffect = Bleed;
	timer = 3;
}

DivineE::DivineE()
{
	name = "Divine Execution";
	id = 0005;
	actioncost = 75;
	multiplier = 1.50f;
}

MagicB::MagicB()
{
	name = "Magic Bolt";
	id = 0006;
	actioncost = 30;
	multiplier = 0.75f;
}

BFlash::BFlash()
{
	name = "Blinding Flash";
	id = 0007;
	actioncost = 30;
	multiplier = 0.15f;
	statuseffect = Stun;
	timer = 1;
}

UnholyI::UnholyI()
{
	name = "Unholy Incantation";
	id = 0010;
	actioncost = 40;
	multiplier = 0.20f;
	shiftposition = 2;

}

MiasmicC::MiasmicC()
{
	name = "Miasmic Cloud";
	id = 0011;
	actioncost = 40;
	statuseffect = Debuff;
	timer = 3;
}

Ars::Ars()
{
	name = "Ars Arcanum";
	id = 0012;
	actioncost = 100;
	multiplier - 0.90f;
	statuseffect = Bleed;
	statuseffect2 = Debuff;
	timer = 2;
}

Heal::Heal()
{
	name = "Heal";
	id = 0013;
	actioncost = 25;
	multiplier = 0.45f;
}

Esuna::Esuna()
{
	name = "Esuna";
	id = 0014;
	actioncost = 40;
}

UnholyG::UnholyG()
{
	name = "Unholy Gift";
	id = 0015;
	actioncost = 35;
	multiplier = 0.50f;
}

DivineG::DivineG()
{
	name = "Divine Guidance";
	id = 0016;
	actioncost = 30;
	statuseffect = Buff;
	timer = 3;
}

GuardianA::GuardianA()
{
	name = "Guardian Angel";
	id = 0017;
	actioncost = 80;
	statuseffect = Buff;
	timer = 3;
}