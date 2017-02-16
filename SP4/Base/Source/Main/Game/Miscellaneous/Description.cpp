#include "Description.h"
#include "GL\glew.h"
#include "../Systems/EventSystem.h"

Description::Description()
{
}


Description::~Description()
{
}

void Description::Init(Vector3 Position, Vector3 Scale, std::string type)
{
	x, y = 0;
	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();


	position = Position;
	scale = Scale;
	maxHeight = position.y + scale.y * 0.5;
	maxWidth = position.x + scale.x * 0.5;
	minHeight = position.y - scale.y * 0.5;
	minWidth = position.x - scale.x * 0.5;

	this->type = type;

}

void Description::Update(double dt)
{
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float worldX = (float)x * ObjectManager::Instance().WorldWidth / (float)w;
	float worldY = ((float)h - (float)y) * ObjectManager::Instance().WorldHeight / (float)h;

	position = Vector3(worldX + scale.x * 0.5, worldY -  scale.y * 0.5, 2);

	std::cout << position << std::endl;
}

Vector3 Description::GetPosition()
{
	return position;
}

Vector3 Description::GetScale()
{
	return scale;
}