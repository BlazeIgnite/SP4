#include "SceneWin.h"


#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Miscellaneous/Button.h"


SceneWin::SceneWin()
{
	timer = 0;
}

SceneWin::~SceneWin()
{

}

void SceneWin::Init()
{
	this->SetEntityID("Win_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	youwin = "You Win!";
	timer = 0.f;
}

void SceneWin::Update(float dt)
{
	//if (InputManager::Instance().GetMouseState(MOUSE_L) == RELEASE)
	//	SceneSystem::Instance().SwitchScene("Town_Scene");

	timer += dt;

	if (InputManager::Instance().GetMouseState(MOUSE_L) == CLICK && timer > 5.f)
	{
		timer = 0.f;
		SceneSystem::Instance().SwitchScene("Town_Scene");
	}
		
}

void SceneWin::Render()
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

	/*modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.3f, -5.f);
	modelStack->Scale(10, 10, 1);
	Renderer->RenderMesh("RedPotion", false);
	modelStack->PopMatrix();*/

	modelStack->PushMatrix();
	modelStack->Translate((ObjectManager::Instance().WorldWidth * 0.5f) - (youwin.size() * 4.3f), ObjectManager::Instance().WorldHeight * 0.8f, -5.f);
	modelStack->Scale(15, 15, 1);
	Renderer->RenderText("text", youwin, Color(1, 0, 0));
	modelStack->PopMatrix();
}

void SceneWin::Exit()
{
	ObjectManager::Instance().Exit();
}