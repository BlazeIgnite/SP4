#include "MainMenu.h"
#include "../Systems/ObjectManager.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../../Base/Source/Main/Game/Miscellaneous/Button.h"
#include "../Systems/EventSystem.h"
#include "GL\glew.h"
#include "../Mains/Application.h"
#include "../Objects/Characters/Player.h"
#include "State.h"

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

	InitButtons();

	NewName = "";
	isPressed = false;
	LoadFile = false;
	NewGame = false;
	NameInput = false;
}

void MainMenu::InitButtons()
{
	button = new Button();
	Player::Instance().Init(1);
	Button* temp;
	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 40, 1), Vector3(15, 5, 5), "First");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 30, 1), Vector3(15, 5, 5), "Second");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 20, 1), Vector3(15, 5, 5), "Third");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.5f, 10, 1), Vector3(15, 5, 5), "Forth");
	buttonList.push_back(temp);


	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.3f, 10, 1), Vector3(15, 5, 5), "Enter");
	buttonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth* 0.7f, 10, 1), Vector3(15, 5, 5), "Back");
	buttonList.push_back(temp);

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
		(*itr)->Update();
		if (!NewGame && !LoadFile && !NameInput)
		{
			if ((*itr)->type == "First" && (*itr)->GetCurrentState() == CLICK)
			{
				NewGame = true;
				LoadFile = false;
			}
			else if ((*itr)->type == "Second" && (*itr)->GetCurrentState() == CLICK)
			{
				NewGame = false;
				LoadFile = true;
			}
			else if ((*itr)->type == "Third" && (*itr)->GetCurrentState() == CLICK)
			{
				SceneSystem::Instance().SwitchScene("Settings");
			}
			else if ((*itr)->type == "Forth" && (*itr)->GetCurrentState() == CLICK)
			{
				Application::GetInstance().QuitGame();
			}
		}
		else if (!NewGame && !NameInput && LoadFile)
		{
			if ((*itr)->type == "First" && (*itr)->GetCurrentState() == CLICK)
			{
				Player::Instance().LoadPlayer(1);
				SceneSystem::Instance().SwitchScene("Town_Scene");
			}
			else if ((*itr)->type == "Second" && (*itr)->GetCurrentState() == CLICK)
			{
				Player::Instance().LoadPlayer(2);
				SceneSystem::Instance().SwitchScene("Town_Scene");
			}
			else if ((*itr)->type == "Third" && (*itr)->GetCurrentState() == CLICK)
			{
				Player::Instance().LoadPlayer(3);
				SceneSystem::Instance().SwitchScene("Town_Scene");
			}
			else if ((*itr)->type == "Forth" && (*itr)->GetCurrentState() == CLICK)
			{
				LoadFile = false;
			}
		}
		else if (NewGame && !NameInput && !LoadFile)
		{
			if ((*itr)->type == "Forth" && (*itr)->GetCurrentState() == CLICK)
				NewGame = false;
			else if ((*itr)->GetCurrentState() == CLICK)
				NameInput = true;
		}
		else if (NameInput)
		{
			if ((*itr)->type == "Enter" && (*itr)->GetCurrentState() == CLICK)
			{
				Player::Instance().LoadPlayer(1);
				Player::Instance().SetPlayerName(NewName);
				std::cout << Player::Instance().GetPlayerName() << std::endl;
				SceneSystem::Instance().SwitchScene("Town_Scene");
			}
			else if ((*itr)->type == "Back" && (*itr)->GetCurrentState() == CLICK)
			{
				NewName = "";
				NameInput = false;
			}
		}
	}
	if (NameInput)
	{
		if (InputManager::Instance().GetKeyPressed() != NULL)
		{
			if (InputManager::Instance().GetKeyPressed() != VK_BACK && NewName.size() < 18)
				NewName += InputManager::Instance().GetKeyPressed();
			else if (InputManager::Instance().GetKeyPressed() == VK_BACK && NewName.size() > 0)
				NewName.erase(NewName.size() - 1);
		}
	}
	if (InputManager::Instance().CheckKeyPressed('G') == CLICK)
	{
		SceneSystem::Instance().SceneReset("MainMenu_Scene");
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

	//Background
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	//Renderer->SetHUD(true);
	Renderer->RenderMesh("MainMenu", false);
	//Renderer->SetHUD(false);
	modelStack->PopMatrix();
	
	//Title
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.7f, -4.f);
	modelStack->Scale(60, 25, 1);
	Renderer->RenderMesh("ButtonBorder", false);
	modelStack->PopMatrix();
	
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 22.5, ObjectManager::Instance().WorldHeight * 0.7f, 1.f);
	modelStack->Scale(3, 3, 1);
	Renderer->RenderText("Test", "Super Crusader", Color(1, 1, 1));
	modelStack->PopMatrix();

	if (NameInput)
	{
		RenderNameInput();
	}
	else
	{
		NewName = "";
		RenderButtons();
	}
}

void MainMenu::RenderNameInput()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.3f, -4.f);
	modelStack->Scale(60, 20, 1);
	Renderer->RenderMesh("ButtonBorder", false);
	modelStack->PopMatrix();

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - 12, ObjectManager::Instance().WorldHeight * 0.35f, -4.f);
	modelStack->Scale(3, 3, 1);
	Renderer->RenderText("text", "Enter a name", Color(1, 1, 1));
	modelStack->PopMatrix();
		
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f - (NewName.size() * 1.05f), ObjectManager::Instance().WorldHeight * 0.25f, -4.f);
	modelStack->Scale(3, 3, 1);
	Renderer->RenderText("text", NewName, Color(1, 1, 1));
	modelStack->PopMatrix();

	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		Button *obj = (Button *)*it;

		if (obj->type == "Enter")
		{
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0.5f);
			modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 4.7, obj->GetPosition().y, 0.5);
			modelStack->Scale(2, 2, 1);
			Renderer->RenderText("text", "Enter", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		else if (obj->type == "Back")
		{
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0.5f);
			modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 4.7, obj->GetPosition().y, 0);
			modelStack->Scale(2, 2, 1);
			Renderer->RenderText("text", "Back", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
	}
}

void MainMenu::RenderButtons()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());

	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end(); it++)
	{
		Button *obj = (Button *)*it;
		if (obj->type == "First")
		{
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0.5 /*obj->GetPosition().z*/);
			//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 4.7, obj->GetPosition().y, 0.5);
			modelStack->Scale(2, 2, 1);
			if (!NewGame && !LoadFile && !NameInput)
				Renderer->RenderText("text", "New Game", Color(1, 1, 1));
			else if (!NameInput)
				Renderer->RenderText("text", "File 1", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		else if (obj->type == "Second")
		{
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0.5 /*obj->GetPosition().z*/);
			//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 5.5, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			if (!NewGame && !LoadFile && !NameInput)
				Renderer->RenderText("text", "Load Game", Color(1, 1, 1));
			else if (!NameInput)
				Renderer->RenderText("text", "File 2", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		else if (obj->type == "Third")
		{
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0.5 /*obj->GetPosition().z*/);
			//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 4, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			if (!NewGame && !LoadFile && !NameInput)
				Renderer->RenderText("text", "Setting", Color(1, 1, 1));
			else if (!NameInput)
				Renderer->RenderText("text", "File 3", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
		else if (obj->type == "Forth")
		{
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x, obj->GetPosition().y, 0.5 /*obj->GetPosition().z*/);
			//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack->Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			//Text on Box
			modelStack->PushMatrix();
			modelStack->Translate(obj->GetPosition().x - 5.5, obj->GetPosition().y, obj->GetPosition().z);
			modelStack->Scale(2, 2, 1);
			if (!NewGame && !LoadFile && !NameInput)
				Renderer->RenderText("text", "Exit Game", Color(1, 1, 1));
			else if (!NameInput)
				Renderer->RenderText("text", "Return", Color(1, 1, 1));
			modelStack->PopMatrix();
		}
	}
}

void MainMenu::Exit()
{
	ObjectManager::Instance().Exit();
	if (button != nullptr)
	{
		delete button;
		button = nullptr;
	}
	for (std::vector<Button*>::iterator it = buttonList.begin(); it != buttonList.end();)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
			it = buttonList.erase(it);
		}
	}
}