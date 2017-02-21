#pragma once

#include "Vector3.h"
#include <string>

class DescriptionText
{
private:
	Vector3 position;
	Vector3 scale;
	std::string text;
	std::string type;

public:
	DescriptionText();
	~DescriptionText();

	void Init(Vector3 Position, Vector3 Scale, std::string type , std::string Text);
	void Text();

	std::string GetText();
	std::string GetType();
	Vector3 GetPosition();
	Vector3 GetScale();
};

