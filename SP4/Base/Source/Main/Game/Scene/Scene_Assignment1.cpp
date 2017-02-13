#include "Scene_Assignment1.h"
#include "GL\glew.h"
#include "../Mains/Application.h"
#include <sstream>
#include "../Systems/ObjectManager.h"
#include "../Systems/EventSystem.h"
#include "../../Engine/State/StateList.h"

static bool MessageBoardActive = false;

Scene_Assignment1::Scene_Assignment1()
{
}

Scene_Assignment1::~Scene_Assignment1()
{
}

void Scene_Assignment1::Init()
{
	// Init Scene
	SceneBase::Init();
	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	EventSystem::Instance().Init();

	//Physics Related
	TimeMultiplier = 1.f;
	Math::InitRNG();
}

void Scene_Assignment1::UpdateCharacterLogic(double dt)
{
}

void Scene_Assignment1::UpdateInternals(double dt)
{
}

bool Scene_Assignment1::CheckCollision(BaseObject* o1, BaseObject* o2, std::string type)
{
	if (type == "Circle")
	{
		// Simple BC.
		float CombinedRadiusSquared = (o1->GetDimensions().x + o2->GetDimensions().x) * (o1->GetDimensions().x + o2->GetDimensions().x);
		float DistSquared = (o1->GetPosition() - o2->GetPosition()).LengthSquared();
		if (DistSquared < CombinedRadiusSquared)
		{
			return true;
		}
		return false;
	}
	else if (type == "AABB")
	{
		return false;
	}
	else if (type == "OBB")
	{
		return false;
	}
	else return false;
}

void Scene_Assignment1::Update(double dt)
{
	SceneBase::Update(dt);
	EventSystem::Instance().Update((float)dt);

	// Update Calls
	UpdateCharacterLogic(dt);
	UpdateInternals(dt);
	HandleUserInput();
}


void Scene_Assignment1::RenderObjects(BaseObject *obj)
{
	if (obj->Active && obj->Visible && obj->GetEntityID() != "")
	{
		std::string Name = obj->GetEntityID();
		if (Name == "Scavenger")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_SCAVENGER], false);
			modelStack.PopMatrix();
		}
		else if (Name == "Drone")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_DRONE], false);
			modelStack.PopMatrix();
		}
		else if (Name == "Zombie")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_ZOMBIE], false);
			modelStack.PopMatrix();
		}
		else if (Name == "WildLife")
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_WILDLIFE], false);
			modelStack.PopMatrix();
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
			modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
			modelStack.Scale(obj->GetDimensions().x, obj->GetDimensions().y, obj->GetDimensions().z);
			RenderMesh(meshList[GEO_BULLET], false);
			modelStack.PopMatrix();
		}
	}
}

void Scene_Assignment1::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	ObjectManager::Instance().WorldHeight = 100.f;
	ObjectManager::Instance().WorldWidth = ObjectManager::Instance().WorldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, ObjectManager::Instance().WorldWidth, 0, ObjectManager::Instance().WorldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
	
	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5);
	modelStack.Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	RenderMesh(meshList[GEO_BACKGROUND], false);
	modelStack.PopMatrix();


	//On screen text
	std::stringstream ss;
	ss.str("");
}

void Scene_Assignment1::HandleUserInput()
{
	//Keys Section
	//Mouse Section
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float worldX = (float)x * ObjectManager::Instance().WorldWidth / (float)w;
	float worldY = ((float)h - (float)y) * ObjectManager::Instance().WorldHeight / (float)h;

	// Characters
	static bool SButtonState = false;
	float Radius = 1;
	if (!SButtonState && Application::IsKeyPressed('S'))
	{
		SButtonState = true;
	}
	else if (SButtonState && !Application::IsKeyPressed('S'))
	{
		SButtonState = false;
	}

	static bool DButtonState = false;
	if (!DButtonState && Application::IsKeyPressed('D'))
	{
		DButtonState = true;
	}
	else if (DButtonState && !Application::IsKeyPressed('D'))
	{
		DButtonState = false;
	}

	static bool WButtonState = false;
	if (!WButtonState && Application::IsKeyPressed('W'))
	{
		WButtonState = true;
	}
	else if (WButtonState && !Application::IsKeyPressed('W'))
	{
		WButtonState = false;
	}

	static bool AButtonState = false;
	if (!AButtonState && Application::IsKeyPressed('A'))
	{
		AButtonState = true;
	}
	else if (AButtonState && !Application::IsKeyPressed('A'))
	{
		AButtonState = false;
	}

	// Items
	static bool QButtonState = false;
	if (!QButtonState && Application::IsKeyPressed('Q'))
	{
		QButtonState = true;
	}
	else if (QButtonState && !Application::IsKeyPressed('Q'))
	{
		QButtonState = false;
	}

	static bool EButtonState = false;
	if (!EButtonState && Application::IsKeyPressed('E'))
	{
		EButtonState = true;
	}
	else if (EButtonState && !Application::IsKeyPressed('E'))
	{
		EButtonState = false;
	}

	if (Application::IsKeyPressed(VK_LBUTTON))
	{
		MessageBoardActive = true;
	}
	else if (Application::IsKeyPressed(VK_RBUTTON))
	{
		MessageBoardActive = false;
	}
}

void Scene_Assignment1::Exit()
{
	SceneBase::Exit();
	//Cleanup Objects
	ObjectManager::Instance().Exit();
	
	StateList::Instance().Exit();
}