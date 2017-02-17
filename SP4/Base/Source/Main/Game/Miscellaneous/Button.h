#pragma once
#include "../Objects/Characters/Player.h"

#include "Vector3.h"
#include <iostream>

class Button
{
private:
	
	double x, y;
	float maxHeight, maxWidth, minHeight, minWidth;
	Vector3 position;
	Vector3 scale;

public:

	Button();
	~Button();

	void Init(Vector3 Position, Vector3 Scale, std::string type, Player* player);
	void UpdateCrafting(double dt);
	void Update(double dt);

	Player* player;
	std::string type;
	bool isitHover();

	bool isPressed;

	Vector3 GetPosition();
	Vector3 GetScale();
};