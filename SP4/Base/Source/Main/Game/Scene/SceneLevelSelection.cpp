#include "SceneLevelSelection.h"


#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Miscellaneous/Button.h"


SceneLevelSelection::SceneLevelSelection()
{

}

SceneLevelSelection::~SceneLevelSelection()
{

}

void SceneLevelSelection::Init()
{
	this->SetEntityID("LevelSelection_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Button* m_button = new Button();
	m_button->Init(Vector3(140, 92, 0), Vector3(15, 10, 10), "Town Button");
	m_buttonList.push_back(m_button);

	m_button = new Button();
	m_button->Init(Vector3(130, 60, 0), Vector3(15, 10, 10), "Tutorial");
	m_buttonList.push_back(m_button);

	m_button = new Button();
	m_button->Init(Vector3(75, 87, 0), Vector3(15, 10, 1), "Level 1 Button");
	m_buttonList.push_back(m_button);
}

void SceneLevelSelection::Update(float dt)
{
	for (vector<Button*>::iterator it = m_buttonList.begin(); it != m_buttonList.end(); it++)
	{
		Button* button = (Button*)(*it);

		if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK && button->isitHover())
		{
			if (button->type == "Town Button")
				SceneSystem::Instance().SwitchScene("Town_Scene");
			else if (button->type == "Tutorial")
				SceneSystem::Instance().SwitchScene("Tutorial_Scene");
			else if (button->type == "Level 1 Button")
			{
			}
		}
	}
}

void SceneLevelSelection::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculating aspect ratio
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	// Projection matrix : Orthographic Projection
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

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(200, 100, 1);
	Renderer->RenderMesh("LevelSelection", false);
	modelStack->PopMatrix();

	for (vector<Button*>::iterator it = m_buttonList.begin(); it != m_buttonList.end(); it++)
	{
		Button* button = (Button*)(*it);
		modelStack->PushMatrix();
		modelStack->Translate(button->GetPosition().x, button->GetPosition().y, button->GetPosition().z);
		modelStack->Scale(button->GetScale().x, button->GetScale().y, button->GetScale().z);

		if (button->type == "Town Button")
			Renderer->RenderMesh("MainMenu", false);
		else if (button->type == "Tutorial")
			Renderer->RenderMesh("TutorialLevel", false);
		else if (button->type == "Level 1 Button")
			Renderer->RenderMesh("Level1", false);
		
		modelStack->PopMatrix();
	}
}

void SceneLevelSelection::Exit()
{
	ObjectManager::Instance().Exit();
}