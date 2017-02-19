#include "MainMenu.h"
#include "../Systems/ObjectManager.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Systems/EventSystem.h"
#include "GL\glew.h"
#include "../Mains/Application.h"

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	EventSystem::Instance().Init();

	Start = new Button();
	Start->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f,30, 1), Vector3(5,5,5), "Start");
	buttonList.push_back(Start);

	Setting = new Button();
	Setting->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 20, 1), Vector3(5,5,5), "Setting");
	buttonList.push_back(Setting);

	ExitGame = new Button();
	ExitGame->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 10, 1), Vector3(5,5,5), "ExitGame");
	buttonList.push_back(ExitGame);
}

void MainMenu::Update(float dt)
{
}

void MainMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	Mtx44 projection;
	projection.SetToOrtho(0, ObjectManager::Instance().WorldWidth, 0, ObjectManager::Instance().WorldHeight, -10, 10);
	projectionStack->LoadMatrix(projection);

	// Camera matrix
	viewStack->LoadIdentity();
	viewStack->LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack->LoadIdentity();

	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		Button *obj = (Button *)*it;
		modelStack->PushMatrix();
		modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
		modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "Start")
		{
			Renderer->RenderMesh("Start", false);
		}
		if (obj->type == "Setting")
		{
			Renderer->RenderMesh("Setting", false);
		}
		if (obj->type == "ExitGame")
		{
			Renderer->RenderMesh("ExitGame", false);
		}
		modelStack->PopMatrix();
	}
}

void MainMenu::Exit()
{
	ObjectManager::Instance().Exit();

}