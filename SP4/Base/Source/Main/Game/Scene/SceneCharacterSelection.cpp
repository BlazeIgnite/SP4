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
	SelectedCharacter = NULL;
	ClassNameText = "Warrior";
	MaxSkillSelectedTimer = 0.f;
}

void SceneCharacterSelection::Update(float dt)
{
	int Count = 0;
	for (auto it : ButtonList)
	{
		it->Update();
		if (it->GetisSelected())
			SelectedCharacter = Count;
		++Count;
	}
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
	RenderSelectedCharacterInfo();
}

void SceneCharacterSelection::Exit()
{
	ObjectManager::Instance().Exit();
}

void SceneCharacterSelection::RenderPlayerCharacterList()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());

	for (auto it2 : ButtonList)
	{
		modelStack->PushMatrix();
		modelStack->Translate(it2->GetPosition().x, it2->GetPosition().y, it2->GetPosition().z);
		modelStack->Scale(it2->GetScale().x, it2->GetScale().y, it2->GetScale().z);
		if (!it2->GetisSelected())
			Renderer->RenderMesh("ButtonBorder", false);
		else
			Renderer->RenderMesh("ButtonBorderRed", false);

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
			modelStack->Translate((int)-(ClassNameText.size()), 0, 0);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", ClassNameText, Color(1,1,1));
			modelStack->PopMatrix();

		modelStack->PopMatrix();

		bool ListEnd = false;
		std::map<int, CharacterEntity*>::iterator it = Player::Instance().GetClassUnitList(ClassNameText).begin();
		for (int Count = 0; Count < 5; ++Count)
		{
			modelStack->PushMatrix();
			modelStack->Translate(0, 25 - (12 * Count),0);

			if (!ListEnd && it != Player::Instance().GetClassUnitList(ClassNameText).end())
			{
				modelStack->PushMatrix();
				modelStack->Translate(-15, 0, 1);
				modelStack->Scale(7.5f, 7.5f, 1);
				Renderer->RenderMesh("ButtonBorder", false);
				modelStack->PopMatrix();

				modelStack->PushMatrix();
				modelStack->Translate(-5, 0, 1);
				modelStack->Scale(3, 3, 1);
				Renderer->RenderText("text", ("Level: " + std::to_string(it->second->GetLevel())), Color(1, 1, 1));
				modelStack->PopMatrix();
				++it;
			}
			else
			{
				modelStack->PushMatrix();
				modelStack->Translate(-5, 0, 1);
				modelStack->Scale(3, 3, 1);
				Renderer->RenderText("text", "-----", Color(1, 1, 1));
				modelStack->PopMatrix();
			}

			modelStack->PopMatrix();
			if (it == Player::Instance().GetClassUnitList(ClassNameText).end())
				ListEnd = true;
		}

	modelStack->PopMatrix();

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

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.6f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 0), Vector3(10, 10, 1), "SkillFirst");
	ButtonList.push_back(temp);
}

void SceneCharacterSelection::RenderSelectedCharacterInfo()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.8f, ObjectManager::Instance().WorldHeight * 0.6f, 0);

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
			modelStack->Translate((int)-(ClassNameText.size()), 0, 0);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", ClassNameText, Color(1, 1, 1));
			modelStack->PopMatrix();

		modelStack->PopMatrix();

		RenderCharacterInfo();

	modelStack->PopMatrix();
}

void SceneCharacterSelection::RenderCharacterInfo()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());

	CharacterEntity* CurrentlySelected = Player::Instance().GetClassUnitList(ClassNameText).at(SelectedCharacter);
	modelStack->PushMatrix();
	modelStack->Translate(-14.f, 20.f, 1);

		modelStack->PushMatrix();
		modelStack->Scale(20, 20, 1);
		Renderer->RenderMesh("ButtonBorder", false);
		modelStack->PopMatrix();
		//Render Character Image

		modelStack->PushMatrix();
		modelStack->Translate(16, 8, 0);
		modelStack->Scale(2.5f, 2.5f, 1.f);
		Renderer->RenderText("text", "Level: " + std::to_string(CurrentlySelected->GetLevel()), Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(16, 5, 0);
		modelStack->Scale(2.5f, 2.5f, 1.f);
		Renderer->RenderText("text", "Health: " + std::to_string(CurrentlySelected->GetHealth()), Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(16, 2, 0);
		modelStack->Scale(2.5f, 2.5f, 1.f);
		Renderer->RenderText("text", "Attack: " + std::to_string(CurrentlySelected->GetAttack()), Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(16, -1, 0);
		modelStack->Scale(2.5f, 2.5f, 1.f);
		Renderer->RenderText("text", "Defence: " + std::to_string(CurrentlySelected->GetDefence()), Color(1, 1, 1));
		modelStack->PopMatrix();

	modelStack->PopMatrix();
}