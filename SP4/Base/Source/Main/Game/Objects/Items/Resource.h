#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>
#include <map>

class Resource
{
public:
	Resource();
	~Resource();

	void Init();
	//void Update(double dt);
	void CraftRedPotion(std::string name, int Amount);
};

#endif

