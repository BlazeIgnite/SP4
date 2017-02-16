#include "Scene_Assignment1.h"
#include "GL\glew.h"
#include "../Mains/Application.h"
#include <sstream>
//#include "../Systems/ObjectManager.h"
#include "../Systems/EventSystem.h"
#include "../../Engine/State/StateList.h"
#include "../Objects/Characters/CharacterDatabase.h"
#include "../Systems/BattleSystem.h"

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
	
	//buttonVector.push_back(button);
	
	EventSystem::Instance().Init();
	x, y = 0;
	//HP = 10;

	GameStage = true;

	//Physics Related
	TimeMultiplier = 1.f;
	Math::InitRNG();

	Warrior* warrior = new Warrior();
	Warrior* warrior1 = new Warrior();
	player = new Player();
	AI = new AIDefault();

	player->AddCharacter("Warrior", warrior);
	AI->AddTroop("Warrior", warrior1);

	BattleSystem::Instance().SetPlayerTroops(1, *(player->GetClassUnitList("Warrior").begin()));
	BattleSystem::Instance().SetAITroops(1, *(AI->GetClassAIList("Warrior").begin()));

	button = new Button();
	button->Init(Vector3(100, 50, 0), Vector3(5,5,1), "HOVER");
	buttonVector.push_back(button);

	display = new Description();
	display->Init(Vector3(x, y, 0), Vector3(10, 10, 1), "HOVER");
	DescriptionVector.push_back(display);

	button2 = new Button();
	button2->Init(Vector3(50, 50, 0), Vector3(5, 5, 1), "ITEM");
	buttonVector.push_back(button2);
	warrior1 = new Warrior();
	warrior1->Initvalues(112);

	warrior = new Warrior();
	warrior->Initvalues(1);
	warrior->skill_1->SetTarget(warrior1);
	
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
	for (std::vector<Button*>::iterator itr = buttonVector.begin(); itr != buttonVector.end(); itr++)
	{
		(*itr)->Update(dt);
	}
	for (std::vector<Description*>::iterator itr2 = DescriptionVector.begin(); itr2 != DescriptionVector.end(); itr2++)
	{
		(*itr2)->Update(dt);
	}
	/*if (Application::IsKeyPressed('A'))
	{
		warrior->skill_1->SkillBehavior(warrior1->GetDamageMitigation());
		warrior1->Update(dt);
	}
	if (Application::IsKeyPressed('D'))
	{
		warrior1->Levelup();
		warrior1->Update(dt);
	}*/
	//for (std::vector<Description*>::iterator itr2 = DescriptionVector.begin(); itr2 != DescriptionVector.end(); itr2++)
	//{
	//	(*itr2)->Update(dt);
	//}
	//if (Application::IsKeyPressed('A'))
	//{
	//	warrior1->skill_1->SkillBehavior(warrior2->GetDamageMitigation());
	//	warrior2->Update(dt);
	//}
	
}

void Scene_Assignment1::RenderObjects(BaseObject *obj)
{
	/*if (obj->Active && obj->Visible && obj->GetEntityID() != "")
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
	}*/
}

void Scene_Assignment1::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Calculating aspect ratio
	
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

	for (std::vector<Button*>::iterator itr = buttonVector.begin(); itr != buttonVector.end(); itr++)
	{
		Button *obj = (Button *)*itr;
		
		modelStack.PushMatrix();
		modelStack.Translate(obj->GetPosition().x, obj->GetPosition().y, obj->GetPosition().z);
		//modelStack.Rotate(obj->GetRotationAngle(), obj->GetRotationAxis().x, obj->GetRotationAxis().y, obj->GetRotationAxis().z);
		modelStack.Scale(obj->GetScale().x, obj->GetScale().y, obj->GetScale().z);
		if (obj->type == "HOVER")
		{
			RenderMesh(meshList[GEO_HOVER], false);
		}
		if (obj->type == "ITEM")
		{
			RenderMesh(meshList[GEO_HOVER], false);
		}
		modelStack.PopMatrix();
		for (std::vector<Description*>::iterator itr2 = DescriptionVector.begin(); itr2 != DescriptionVector.end(); itr2++)
		{
			Description* obj2 = (Description*)*itr2;
			modelStack.PushMatrix();
			modelStack.Translate(obj2->GetPosition().x, obj2->GetPosition().y, /*obj2->GetPosition().z*/10);
			modelStack.Scale(obj2->GetScale().x, obj2->GetScale().y, obj2->GetScale().z);
			if (obj->isitHover() && obj->type == "HOVER" && obj2->type == "HOVER")
			{
				RenderMesh(meshList[GEO_DESCRIPTION], false);
			}
			modelStack.PopMatrix();
		}
 	}

	//On screen text
	std::stringstream ss;
	ss.str("");
}

void Scene_Assignment1::HandleUserInput()
{
	//Keys Section
	//Mouse Section
	
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