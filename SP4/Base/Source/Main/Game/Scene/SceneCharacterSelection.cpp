#include "SceneCharacterSelection.h"


#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Miscellaneous/Button.h"
#include "../Objects/Characters/Player.h"


SceneCharacterSelection::SceneCharacterSelection()
{

}

SceneCharacterSelection::~SceneCharacterSelection()
{

}

void SceneCharacterSelection::Init()
{
	this->SetEntityID("CharacterSelection_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	InitButtons();
	CharacterList = std::vector<CharacterEntity*>();
	SelectedCharacter = nullptr;
	ClassNameText = "Warrior";
}

void SceneCharacterSelection::Update(float dt)
{

}

void SceneCharacterSelection::Render()
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

	//Background
	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.5f, -5.f);
	modelStack->Scale(ObjectManager::Instance().WorldWidth, ObjectManager::Instance().WorldHeight, 1);
	Renderer->RenderMesh("MainMenu", false);
	modelStack->PopMatrix();

	RenderPlayerCharacterList();
}

void SceneCharacterSelection::Exit()
{
	ObjectManager::Instance().Exit();
}

void SceneCharacterSelection::RenderPlayerCharacterList()
{
	//Calculating aspect ratio
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());

	for (auto it2 : ButtonList)
	{
		modelStack->PushMatrix();
		modelStack->Translate(it2->GetPosition().x, it2->GetPosition().y, it2->GetPosition().z);
		modelStack->Scale(it2->GetScale().x, it2->GetScale().y, it2->GetScale().z);
		Renderer->RenderMesh("ButtonBorder", false);
		modelStack->PopMatrix();
	}

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f, 0);



		modelStack->PushMatrix();
		modelStack->Scale(ObjectManager::Instance().WorldWidth * 0.4f, ObjectManager::Instance().WorldHeight * 0.8f, 1);
		Renderer->RenderMesh("ButtonBorder", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(0, ObjectManager::Instance().WorldHeight * 0.35f, 1);

			modelStack->PushMatrix();
			modelStack->Scale(25, 8, 1);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate((int)(-ClassNameText.size()), 0, 0);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", ClassNameText, Color(1,1,1));
			modelStack->PopMatrix();

		modelStack->PopMatrix();

		int UnitCount = 0;
		for (auto it : Player::Instance().GetClassUnitList(ClassNameText))
		{
			modelStack->PushMatrix();
			modelStack->Translate(0, 25 - (12 * UnitCount), 0);

				//modelStack->PushMatrix();
				//modelStack->Scale(50, 10, 1);
				//Renderer->RenderMesh("ButtonBorder", false);
				//modelStack->PopMatrix();

				modelStack->PushMatrix();
				modelStack->Translate(-15, 0, 1);
				modelStack->Scale(7.5f, 7.5f, 1);
				Renderer->RenderMesh("ButtonBorder", false);
				modelStack->PopMatrix();

				modelStack->PushMatrix();
				modelStack->Translate(-5, 0, 1);
				modelStack->Scale(3, 3, 1);
				Renderer->RenderText("text", ("Level: " + std::to_string(it.second->GetLevel())), Color(1, 1, 1));
				modelStack->PopMatrix();

			modelStack->PopMatrix();
			UnitCount++;
		}

	modelStack->PopMatrix();

}

void SceneCharacterSelection::RenderSelectedCharacterInfo()
{

}

void SceneCharacterSelection::RenderCharacterList()
{

}

void SceneCharacterSelection::InitButtons()
{
	Button* temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f + 25, 0), Vector3(50, 10, 1), "CharacterFirst");
	ButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f + 13, 0), Vector3(50, 10, 1), "CharacterSecond");
	ButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 0), Vector3(50, 10, 1), "CharacterThird");
	ButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f - 11, 0), Vector3(50, 10, 1), "CharacterForth");
	ButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f - 23, 0), Vector3(50, 10, 1), "CharacterFifth");
	ButtonList.push_back(temp);
}