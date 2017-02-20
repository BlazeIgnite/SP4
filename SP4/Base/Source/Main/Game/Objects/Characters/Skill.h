#ifndef SKILL_H_
#define SKILL_H_

#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

// Revised skill codes here, will replace the Old Skill with the New Skill
class Skill
{
	map<size_t, vector<string>> StatusEffect;
	string Name;
	size_t Damage;
	size_t Heal;
	size_t ShiftPosition;
	size_t ActionCost;
	size_t TurnCooldown;
	size_t MaxTurnCooldown;


	bool RequiredPosition[3];
	bool SelectableTarget[3];

public:
	Skill();
	~Skill();

	// Setters
	void SetStatusEffect(size_t StatusEffectTimer, string newStatusEffect);
	void SetName(string newName);
	void SetDamage(size_t newDamage);
	void SetHeal(size_t newHeal);
	void SetShiftPosition(size_t newShiftPosition);
	void SetActionCost(size_t newActionCost);
	void SetTurnCooldown(size_t newTurnCooldown);
	void SetMaxTurnCooldown(size_t newMaxTurnCooldown);
	void SetRequiredPosition(size_t position, bool newRequiredPosition);
	void SetSelectableTarget(size_t position, bool newSelectableTarget);


	// Getters
	map<size_t, vector<string>> GetStringStatusEffect();
	string GetName();
	size_t GetStatusEffectTimer();
	size_t GetDamage();
	size_t GetHeal();
	size_t GetShiftPosition();
	size_t GetActionCost();
	size_t GetTurnCooldown();
	size_t GetMaxTurnCooldown();
	bool GetRequiredPosition(size_t position);
	bool GetSelectableTarget(size_t position);
};

#endif