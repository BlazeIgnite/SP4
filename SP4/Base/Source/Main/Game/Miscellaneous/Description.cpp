#include "Description.h"
#include "GL\glew.h"
#include "../Systems/EventSystem.h"
#include "../Mains/Application.h"

Description::Description()
{
}


Description::~Description()
{
	Exit();
}

void Description::Init(Vector3 Position, Vector3 Scale, std::string type)
{
	x, y = 0;
	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();


	position = Position;
	scale = Scale;
	maxHeight = position.y + scale.y * 0.5f;
	maxWidth = position.x + scale.x * 0.5f;
	minHeight = position.y - scale.y * 0.5f;
	minWidth = position.x - scale.x * 0.5f;

	this->type = type;

	text = new DescriptionText();
	text->Init(Vector3(0,0,0), Vector3(2 ,2, 1), type, "Test");
}

void Description::Update(double dt)
{
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float worldX = (float)x * ObjectManager::Instance().WorldWidth / (float)w;
	float worldY = ((float)h - (float)y) * ObjectManager::Instance().WorldHeight / (float)h;
	position = Vector3(worldX + scale.x * 0.5f, worldY - scale.y * 0.5f, 2);
}

void Description::Exit()
{
	if (text)
	{
		delete text;
		text = nullptr;
	}
}

Vector3 Description::GetPosition()
{
	return position;
}

Vector3 Description::GetScale()
{
	return scale;
}