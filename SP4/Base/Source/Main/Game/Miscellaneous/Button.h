#pragma once

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

	Vector3 GetPosition();
	Vector3 GetScale();
	void Init(Vector3 Position, Vector3 Scale, std::string type);
	void UpdateCrafting(float dt);
	void UpdateBattleScene(float dt);
	void Update(float dt);

	std::string type;

	bool isitHover();
	bool isPressed;
	bool isSelected;

	
};