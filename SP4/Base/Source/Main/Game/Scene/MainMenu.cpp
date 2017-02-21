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
	this->EntityID = "MainMenu_Scene";

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	EventSystem::Instance().Init();

	NewGame = new Button();
	NewGame->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 40, 1), Vector3(5, 5, 5), "NewGame");
	buttonList.push_back(NewGame);

	LoadGame = new Button();
	LoadGame->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 30, 1), Vector3(5, 5, 5), "LoadGame");
	buttonList.push_back(LoadGame);

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
		if (obj->type == "NewGame")
		{
			Renderer->RenderMesh("NewGame", false);
		}
		if (obj->type == "LoadGame")
		{
			Renderer->RenderMesh("LoadGame", false);
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

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.7f, -5.f);
	modelStack->Scale(60, 25, 1);
	Renderer->RenderMesh("ButtonBorder", false);
	modelStack->PopMatrix();

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 22.5 , ObjectManager::Instance().WorldHeight * 0.7f, -5.f);
	modelStack->Scale(5, 5, 1);
	Renderer->RenderText("text", "Super Crusader", Color(1, 1, 1));
	modelStack->PopMatrix();
	

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	//RenderMesh(meshList[GEO_BACKGROUND], false);
	//Renderer->SetHUD(true);
	Renderer->RenderMesh("MainMenu", false);
	//Renderer->SetHUD(false);
	modelStack->PopMatrix();
}

void MainMenu::Exit()
{
	ObjectManager::Instance().Exit();
	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}
	}
	//if (NewGame != nullptr)
	//{
	//	delete NewGame;
	//	NewGame = nullptr;
	//}
	//if (LoadGame)
	//{
	//	delete LoadGame;
	//	LoadGame = nullptr;
	//}
	//if (Setting)
	//{
	//	delete Setting;
	//	Setting = nullptr;
	//}
	//if (ExitGame)
	//{
	//	delete ExitGame;
	//	ExitGame = nullptr;
	//}
}