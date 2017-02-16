#pragma once

#include "Vector3.h"
#include "Button.h"
#include <iostream>

class Description
{
private:

	double x, y;
	float maxHeight, maxWidth, minHeight, minWidth;
	Vector3 position;
	Vector3 scale;
	
public:

	Description();
	~Description();

	void Init(Vector3 Position, Vector3 Scale, std::string type);
	void Update(double dt);
	std::string type;
	
	Vector3 GetPosition();
	Vector3 GetScale();
};

