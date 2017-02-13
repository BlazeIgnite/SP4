#include "EventSystem.h"

void EventSystem::Init()
{
	std::vector<Vector3> SpawnPoints;
	// Left
	SpawnPoints.push_back(Vector3(-ObjectManager::Instance().WorldWidth * 0.1f, ObjectManager::Instance().WorldHeight * 0.5f));
	// Right
	SpawnPoints.push_back(Vector3(ObjectManager::Instance().WorldWidth * 1.1f, ObjectManager::Instance().WorldHeight * 0.5f));
	// Up
	SpawnPoints.push_back(Vector3(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 1.1f));
	// Down
	SpawnPoints.push_back(Vector3(ObjectManager::Instance().WorldWidth * 0.5f, -ObjectManager::Instance().WorldHeight * 0.1f));

	std::vector<Vector3> Temp;
	Math::InitRNG();
	while (SpawnPoints.size() > 0)
	{
		int RandomChoice = Math::RandIntMinMax(0, SpawnPoints.size() - 1);
		Vector3 Position = SpawnPoints[RandomChoice];
		Temp.push_back(Position);
		SpawnPoints.erase(SpawnPoints.begin() + RandomChoice);
	}

}

void EventSystem::Update(const float& dt)
{
	for (std::map<std::string, float>::iterator it = CollectiveTimers.begin(); it != CollectiveTimers.end(); ++it)
	{
		// Updating my timer.
		it->second += dt;
		float STime = SpawnTime.find((*it).first)->second;
		// Is spawn timer done?
		if (it->second > STime)
		{
			int CCount = CurrentCharacterCount.find(it->first)->second;
			int CLimit = CharacterCountLimit.find(it->first)->second;
			// Is there too many of this character?
			if (CCount < CLimit)
			{
				// Let's Spawn The Character!
				SpawnCharacter((*it).first);
				// Add To The Count.
				//CurrentCharacterCount.find((*it).first)->second += 1;
				// Reset The Timer.
				it->second = 0;
			}
		}
	}
}

void EventSystem::SpawnCharacter(std::string Name)
{
}

void EventSystem::ClearCharacterCount()
{
	for (std::map<std::string, int>::iterator it = CurrentCharacterCount.begin(); it != CurrentCharacterCount.end(); ++it)
	{
		it->second = 0;
	}
}