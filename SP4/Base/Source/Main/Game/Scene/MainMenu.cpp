#include "MainMenu.h"
#include "../Systems/ObjectManager.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Systems/EventSystem.h"
#include "GL\glew.h"
#include "../Mains/Application.h"
#include "../Objects/Characters/Player.h"

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

	button = new Button();
	Player::Instance().Init(1);
	Button* temp;
	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 40, 1), Vector3(15, 5, 5), "NewGame");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 30, 1), Vector3(15, 5, 5), "LoadGame");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 20, 1), Vector3(15, 5, 5), "Setting");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 10, 1), Vector3(15, 5, 5), "ExitGame");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(150, 40, 1), Vector3(40, 40, 5), "Inventory");
	buttonList.push_back(temp);

	OpenInventory = false;
	isPressed = false;
}

void MainMenu::Update(float dt)
{
	static bool LMouse = false;
	if (!LMouse && Application::IsKeyPressed(VK_LBUTTON))
	{
		LMouse = true;
	}
	else if (LMouse && Application::IsKeyPressed(VK_LBUTTON))
	{
		LMouse = false; 
	}
	for (std::vector<Button*>::iterator itr = buttonList.begin(); itr != buttonList.end(); itr++)
	{
		(*itr)->UpdateMainMenu(dt);
		if ((*itr)->type == "Inventory" && (*itr)->isitHover())
		{
			if (Application::IsMousePressed(0) && !OpenInventory && !(*itr)->GetisPressed())
			{
					OpenInventory = true;
					std::cout << "Open" << std::endl;
					(*itr)->SetisPressed(true);
			}
			else if (Application::IsMousePressed(0) && OpenInventory && !(*itr)->GetisPressed())
			{
				OpenInventory = false;
				std::cout << "Close" << std::endl;
				(*itr)->SetisPressed(true);
			}
			else
			{
				if ((*itr)->GetisPressed())
				{
					(*itr)->SetisPressed(false);
				}
			}
		}
	}

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
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 4.7, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			Renderer->RenderText("text", "New Game", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		if (obj->type == "LoadGame")
		{
			Renderer->RenderMesh("LoadGame", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 5.5, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			Renderer->RenderText("text", "Load Game", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		if (obj->type == "Setting")
		{
			Renderer->RenderMesh("Setting", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 4, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			Renderer->RenderText("text", "Setting", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		if (obj->type == "ExitGame")
		{
			Renderer->RenderMesh("ExitGame", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 5.5, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			Renderer->RenderText("text", "Exit Game", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		if (obj->type == "Inventory")
		{
			Renderer->RenderMesh("Inventory", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 5.5, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			Renderer->RenderText("text", "Inventory", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
	}

	if (OpenInventory)
	{
		modelStack->PushMatrix();
		modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, 5.f);
		modelStack->Scale(25, 25, 1);
		////Renderer->SetHUD(true);
		Renderer->RenderMesh("Inventory", false);
		////Renderer->SetHUD(false);
		modelStack->PopMatrix();
	}

	//Title
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.7f, -5.f);
	modelStack->Scale(60, 25, 1);
	Renderer->RenderMesh("ButtonBorder", false);
	modelStack->PopMatrix();

	//modelStack->PushMatrix();
	//modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 22.5 , ObjectManager::Instance().WorldHeight * 0.7f, -5.f);
	//modelStack->Scale(5, 5, 1);
	//Renderer->RenderText("text", "Super Crusader", Color(1, 1, 1));
	//modelStack->PopMatrix();
	
	//Background
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