#pragma once

#include "Vector3.h"
#include <iostream>
#include "DescriptionText.h"

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
	
	DescriptionText* text;

	Vector3 GetPosition();
	Vector3 GetScale();
};

