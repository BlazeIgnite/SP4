#pragma once

#include "../Mains/Application.h"
#include "../Scene/Scene_Assignment1.h"
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

	void Init(Vector3 Position, Vector3 Scale, std::string type);
	void Update(double dt);
	std::string type;

	bool isitHover();

	Vector3 GetPosition();
	Vector3 GetScale();
};

