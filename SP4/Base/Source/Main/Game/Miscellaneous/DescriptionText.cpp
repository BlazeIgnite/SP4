#include "DescriptionText.h"


DescriptionText::DescriptionText()
{
}


DescriptionText::~DescriptionText()
{
}

void DescriptionText::Init(Vector3 Position, Vector3 Scale, std::string type, std::string text)
{
	position = Position;
	scale = Scale;
	this->type = type;
	this->text = text;
}

std::string DescriptionText::GetText()
{
	return text;
}

std::string DescriptionText::GetType()
{
	return type;
}

Vector3 DescriptionText::GetPosition()
{
	return position;
}

Vector3 DescriptionText::GetScale()
{
	return scale;
}