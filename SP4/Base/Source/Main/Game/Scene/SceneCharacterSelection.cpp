#include "SceneCharacterSelection.h"


#include "../Mains/Application.h"
#include "../Systems/EventSystem.h"
#include "../Audio/Audio_Player.h"
#include "../../Base/Source/Main/Engine/System/SceneSystem.h"
#include "../../Base/Source/Main/Engine/System/RenderSystem.h"
#include "../Miscellaneous/Button.h"
#include "../Objects/Characters/Player.h"
#include "../Systems/BattleSystem.h"


SceneCharacterSelection::SceneCharacterSelection()
{

}

SceneCharacterSelection::~SceneCharacterSelection()
{
	for (auto it : SkillButtonList)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : CharacterButtonList)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : CharacterClassList)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : FinalChoiceList)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : ChangeSceneList)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : CharacterSelectedSkill)
	{
		it.second.clear();
	}
	SkillButtonList.clear();
	CharacterButtonList.clear();
	CharacterClassList.clear();
	FinalChoiceList.clear();
	ChangeSceneList.clear();
	CharacterSelectedSkill.clear();
}

void SceneCharacterSelection::Init()
{
	this->SetEntityID("CharacterSelection_Scene");
	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	InitButtons();
	CharacterList = std::vector<CharacterEntity*>();
	SelectedCharacter = -1;
	ClassNameText = "Warrior";
	MaxSkillSelectedTimer = 1.f;
	SelectedSkills = std::vector<int>();
	SelectedSkill = -1;
	CharacterSelectedSkill = std::map <Button*, std::vector<int>>();
}

void SceneCharacterSelection::InitButtons()
{
	Button* temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f + 25, 0), Vector3(50, 10, 1), "CharacterFirst");
	CharacterButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f + 13, 0), Vector3(50, 10, 1), "CharacterSecond");
	CharacterButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 0), Vector3(50, 10, 1), "CharacterThird");
	CharacterButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f - 11, 0), Vector3(50, 10, 1), "CharacterForth");
	CharacterButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f - 23, 0), Vector3(50, 10, 1), "CharacterFifth");
	CharacterButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.65f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 1), Vector3(10, 10, 1), "SkillFirst");
	SkillButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.725f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 1), Vector3(10, 10, 1), "SkillSecond");
	SkillButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.8f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 1), Vector3(10, 10, 1), "SkillThird");
	SkillButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.875f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 1), Vector3(10, 10, 1), "SkillForth");
	SkillButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.95f, ObjectManager::Instance().WorldHeight * 0.6f + 1, 1), Vector3(10, 10, 1), "SkillFifth");
	SkillButtonList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f - 15, ObjectManager::Instance().WorldHeight * 0.95f, 1), Vector3(5, 5, 1), "ClassLeft");
	CharacterClassList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.2f + 15, ObjectManager::Instance().WorldHeight * 0.95f, 1), Vector3(5, 5, 1), "ClassRight");
	CharacterClassList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.5f + 15, ObjectManager::Instance().WorldHeight * 0.1f, 1), Vector3(8, 8, 1), "FinalChoiceFirst");
	FinalChoiceList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.1f, 1), Vector3(8, 8, 1), "FinalChoiceSecond");
	FinalChoiceList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.5f - 15, ObjectManager::Instance().WorldHeight * 0.1f, 1), Vector3(8, 8, 1), "FinalChoiceThird");
	FinalChoiceList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.85f, ObjectManager::Instance().WorldHeight * 0.1f, 1), Vector3(15, 7, 1), "Start");
	ChangeSceneList.push_back(temp);

	temp = new Button();
	temp->Init(Vector3(ObjectManager::Instance().WorldWidth * 0.15f, ObjectManager::Instance().WorldHeight * 0.1f, 1), Vector3(15, 7, 1), "Return");
	ChangeSceneList.push_back(temp);
}

void SceneCharacterSelection::Update(float dt)
{
	int CharacterCount = 0;
	int SkillCount = 0;
	int FinalCount = 0;
	bool SelectChar = false;
	bool SelectSkill = false;
	Math::Clamp(MaxSkillSelectedTimer += dt, 0.f, 1.f);
	ClickingOtherButtons = false;

	for (auto it : CharacterButtonList)
	{
		it->Update();
		if (it->CurrentState == CLICK || it->CurrentState == HOLD)
			ClickingOtherButtons = true;
		if (it->GetisSelected() && it->CurrentState == CLICK)
		{
			SelectedSkill = -1;
			SelectedSkills.clear();
			SelectedSkills = std::vector<int>();
			SelectedCharacter = CharacterCount;
			SelectChar = true;
		}
		else if (it->CurrentStateR == CLICK)
		{
			SelectedSkill = -1;
			SelectedSkills.clear();
			SelectedSkills = std::vector<int>();
			SelectedCharacter = -1;
			SelectChar = false;
		}
		++CharacterCount;
	}

	for (auto it : SkillButtonList)
	{
		it->Update();
		if (it->CurrentState == CLICK || it->CurrentState == HOLD)
			ClickingOtherButtons = true;
		if (it->GetisSelected() && it->CurrentState == CLICK)
		{
			SelectedSkill = SkillCount;
			SelectSkill = true;
			if (std::find(SelectedSkills.begin(), SelectedSkills.end(), SkillCount) == SelectedSkills.end())
			{
				if (SelectedCharacter <= -1 || SelectedCharacter >= Player::Instance().GetClassUnitList(ClassNameText).size() || SelectedSkill >= Player::Instance().GetClassUnitList(ClassNameText).at(SelectedCharacter)->GetSkillList()->size() - 1)
				{
					SelectedSkill = -1;
					SelectSkill = false;
					continue;
				}
				SelectedSkills.push_back(SkillCount);
				if (SelectedSkills.size() > 3)
				{
					SelectedSkills.pop_back();
					MaxSkillSelectedTimer = 0.f;
				}
			}
		}
		++SkillCount;
	}
	for (std::vector<int>::iterator it = SelectedSkills.begin(); it != SelectedSkills.end();)
	{
		if (!SkillButtonList[*it]->GetisSelected() && SkillButtonList[*it]->CurrentStateR == CLICK && SkillButtonList[*it]->isitHover())
			it = SelectedSkills.erase(it);
		else
			++it;
	}
	for (auto it : CharacterClassList)
	{
		it->Update();
		if (it->CurrentState == CLICK || it->CurrentState == HOLD)
			ClickingOtherButtons = true;
		if (it->GetisSelected() && it->CurrentState == CLICK && it->type.find("Left") != string::npos)
		{
			if (ClassNameText == "Warrior")
				ClassNameText = "Synergist";
			else if (ClassNameText == "Synergist")
				ClassNameText = "Mage";
			else if (ClassNameText == "Mage")
				ClassNameText = "Warrior";
		}
		else if (it->GetisSelected() && it->CurrentState == CLICK && it->type.find("Right") != string::npos)
		{
			if (ClassNameText == "Warrior")
				ClassNameText = "Mage";
			else if (ClassNameText == "Mage")
				ClassNameText = "Synergist";
			else if (ClassNameText == "Synergist")
				ClassNameText = "Warrior";
		}
	}

	for (auto it : FinalChoiceList)
	{
		it->Update();
		if (it->CurrentState == RELEASE && SelectedCharacter >-1 && SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size())
		{
			for (auto it2 : FinalChoiceList)
				if (it2->type == ClassNameText + std::to_string(SelectedCharacter))
					it2->type = "";
			it->type = ClassNameText + std::to_string(SelectedCharacter);
			if (CharacterSelectedSkill.find(it) == CharacterSelectedSkill.end())
				CharacterSelectedSkill.insert(std::pair<Button*, std::vector<int>>(it, SelectedSkills));
			else
				CharacterSelectedSkill.find(it)->second = SelectedSkills;
		}
		++FinalCount;
	}
	for (auto it : ChangeSceneList)
	{
		it->Update();
		if (it->GetisSelected())
			if (it->type == "Return")
				SceneSystem::Instance().SwitchScene("Town_Scene");
			else if (it->type == "Start")
			{
				BattleSystem::Instance().Init();
				for (auto it2 : CharacterSelectedSkill)
				{
					int Position;
					if (it2.first->type.find("Warrior") != string::npos)
					{
						it2.first->type.replace(it2.first->type.find("Warrior"), 7, "");
						if (it2.first == FinalChoiceList[0])
							Position = 0;
						else if (it2.first == FinalChoiceList[1])
							Position = 1;
						else if (it2.first == FinalChoiceList[2])
							Position = 2;
						BattleSystem::Instance().SetPlayerTroops(Position, Player::Instance().GetClassUnitList("Warrior").at(std::stoi(it2.first->type)));
						BattleSystem::Instance().SetPlayerTroopSkills(Position, 0);
						for (auto it3 : it2.second)
							BattleSystem::Instance().SetPlayerTroopSkills(Position, it3 + 1);
					}
					else if (it2.first->type.find("Mage") != string::npos)
					{
						it2.first->type.replace(it2.first->type.find("Mage"), 4, "");
						if (it2.first == FinalChoiceList[0])
							Position = 0;
						else if (it2.first == FinalChoiceList[1])
							Position = 1;
						else if (it2.first == FinalChoiceList[2])
							Position = 2;
						BattleSystem::Instance().SetPlayerTroops(Position, Player::Instance().GetClassUnitList("Mage").at(std::stoi(it2.first->type)));
						BattleSystem::Instance().SetPlayerTroopSkills(Position, 0);
						for (auto it3 : it2.second)
							BattleSystem::Instance().SetPlayerTroopSkills(Position, it3 + 1);
					}
					else if (it2.first->type.find("Synergist") != string::npos)
					{
						it2.first->type.replace(it2.first->type.find("Synergist"), 9, "");
						if (it2.first == FinalChoiceList[0])
							Position = 0;
						else if (it2.first == FinalChoiceList[1])
							Position = 1;
						else if (it2.first == FinalChoiceList[2])
							Position = 2;
						BattleSystem::Instance().SetPlayerTroops(Position, Player::Instance().GetClassUnitList("Synergist").at(std::stoi(it2.first->type)));
						BattleSystem::Instance().SetPlayerTroopSkills(Position, 0);
						for (auto it3 : it2.second)
							BattleSystem::Instance().SetPlayerTroopSkills(Position, it3 + 1);
					}
				}


				//BattleSystem::Instance().Init();
				//BattleSystem::Instance().SetPlayerTroops(0, );
				//BattleSystem::Instance().SetPlayerTroops(1, mage);
				//BattleSystem::Instance().SetPlayerTroops(2, synergist);
				SceneSystem::Instance().SwitchScene("Battle_Scene");
			}
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
	RenderFinalChoiceInfo();

	for (auto it : ChangeSceneList)
	{
		modelStack->PushMatrix();
		modelStack->Translate(it->GetPosition().x, it->GetPosition().y, it->GetPosition().z);

			modelStack->PushMatrix();
			modelStack->Scale(it->GetScale().x, it->GetScale().y, it->GetScale().z);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate((int)(it->type.size() * -0.85f), 0, 0);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText(it->type, Color(1,1,1));
			modelStack->PopMatrix();

		modelStack->PopMatrix();
	}

	if (MaxSkillSelectedTimer < 1.f)
	{
		std::string AnnouncementText = "MAXIMUM NUMBER OF SKILLS SELECTED";
		modelStack->PushMatrix();
		modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.8f, ObjectManager::Instance().WorldHeight * 0.5f + 1, 10);
			modelStack->PushMatrix();
			modelStack->Scale(AnnouncementText.size() * 2, 10, 1);
			Renderer->RenderMesh("Alert", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate((AnnouncementText.size() * -(0.7f)), 0, 1);
			modelStack->Scale(2, 3, 1);
			Renderer->RenderText("text", AnnouncementText, Color(1, 1, 1));
			modelStack->PopMatrix();
		modelStack->PopMatrix();
	}
}

void SceneCharacterSelection::Exit()
{
	ObjectManager::Instance().Exit();
}

void SceneCharacterSelection::RenderPlayerCharacterList()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	int SelectButton = 0;
	for (auto it : CharacterButtonList)
	{
		if (it->type.find("Character") != string::npos)
		{
			//Render Character's selection button
			modelStack->PushMatrix();
			modelStack->Translate(it->GetPosition().x, it->GetPosition().y, it->GetPosition().z);
			modelStack->Scale(it->GetScale().x, it->GetScale().y, it->GetScale().z);
			if (SelectButton != SelectedCharacter)
				Renderer->RenderMesh("ButtonBorder", false);
			else
				Renderer->RenderMesh("ButtonBorderRed", false);

			modelStack->PopMatrix();
		}
		++SelectButton;
	}

	for (auto it : CharacterClassList)
	{
		modelStack->PushMatrix();
		modelStack->Translate(it->GetPosition().x, it->GetPosition().y, it->GetPosition().z);
		modelStack->Scale(it->GetScale().x, it->GetScale().y, it->GetScale().z);
		Renderer->RenderMesh("ButtonBorderBlue", false);
		modelStack->PopMatrix();
	}

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.2f, ObjectManager::Instance().WorldHeight * 0.6f, 0);

		//Left Border
		modelStack->PushMatrix();
		modelStack->Scale(ObjectManager::Instance().WorldWidth * 0.4f, ObjectManager::Instance().WorldHeight * 0.8f, 1);
		Renderer->RenderMesh("ButtonBorder", false);
		modelStack->PopMatrix();

		//Class Name
		modelStack->PushMatrix();
		modelStack->Translate(0, ObjectManager::Instance().WorldHeight * 0.35f, 1);

			modelStack->PushMatrix();
			modelStack->Scale(25, 8, 1);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			modelStack->PushMatrix();
			modelStack->Translate((int)-(ClassNameText.size()), 0, 1);
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
				//Render Character Icon
				modelStack->PushMatrix();
				if (InputManager::Instance().GetMouseState(MOUSE_L) == HOLD && Count == SelectedCharacter && ClickingOtherButtons == false)
					modelStack->Translate(InputManager::Instance().GetMousePosition().x - ObjectManager::Instance().WorldWidth * 0.2f, InputManager::Instance().GetMousePosition().y - (25 - (12 * Count) + ObjectManager::Instance().WorldHeight * 0.6f), 1);
				else
					modelStack->Translate(-15, 0, 1);
				modelStack->Scale(7.5f, 7.5f, 1);
				Renderer->RenderMesh("ButtonBorder", false);
				modelStack->PopMatrix();

				//Render Character Level
				modelStack->PushMatrix();
				modelStack->Translate(-5, 0, 1);
				modelStack->Scale(3, 3, 1);
				Renderer->RenderText("text", ("Level: " + std::to_string(it->second->GetLevel())), Color(1, 1, 1));
				modelStack->PopMatrix();
				++it;
			}
			else
			{
				//Render Blank
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

void SceneCharacterSelection::RenderSelectedCharacterInfo()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.8f, ObjectManager::Instance().WorldHeight * 0.6f, 0);

		//Render Right Border
		modelStack->PushMatrix();
		modelStack->Scale(ObjectManager::Instance().WorldWidth * 0.4f, ObjectManager::Instance().WorldHeight * 0.8f, 3);
		Renderer->RenderMesh("ButtonBorder", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(0, ObjectManager::Instance().WorldHeight * 0.35f, 1);

			//Selected Character Class Border
			modelStack->PushMatrix();
			modelStack->Scale(25, 8, 1);
			Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();

			//Selected Character Class Name
			modelStack->PushMatrix();
			modelStack->Translate((int)-(ClassNameText.size()), 0, 0);
			modelStack->Scale(3, 3, 1);
			Renderer->RenderText("text", ClassNameText, Color(1, 1, 1));
			modelStack->PopMatrix();

		modelStack->PopMatrix();

		RenderCharacterInfo();
		RenderSkillInfo();
	modelStack->PopMatrix();

	int Count = 0;
	for (auto it : SkillButtonList)
	{
		bool SkillSelectedCheck = false;
		if (it->type.find("Skill") != string::npos)
		{
			//Render Selected Character's Skill's border
			modelStack->PushMatrix();
			modelStack->Translate(it->GetPosition().x, it->GetPosition().y, it->GetPosition().z);
			modelStack->Scale(it->GetScale().x, it->GetScale().y, it->GetScale().z);
			if (it->GetisSelected())
			{
				Renderer->RenderMesh("ButtonBorderRed", false);
				SkillSelectedCheck = true;
			}
			for (auto it2 : SelectedSkills)
			{
				if (!SkillSelectedCheck && it == SkillButtonList[it2])
				{
					Renderer->RenderMesh("ButtonBorderBlue", false);
					SkillSelectedCheck = true;
				}
			}
			if (!SkillSelectedCheck)
				Renderer->RenderMesh("ButtonBorder", false);
			modelStack->PopMatrix();
		}
		++Count;
	}
}

void SceneCharacterSelection::RenderCharacterInfo()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	CharacterEntity* CurrentlySelected = nullptr;

	if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size())
		CurrentlySelected = Player::Instance().GetClassUnitList(ClassNameText).at(SelectedCharacter);
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
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size())
			Renderer->RenderText("text", "Level: " + std::to_string(CurrentlySelected->GetLevel()), Color(1, 1, 1));
		else
			Renderer->RenderText("text", "Level: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(16, 5, 0);
		modelStack->Scale(2.5f, 2.5f, 1.f);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size())
			Renderer->RenderText("text", "Health: " + std::to_string(CurrentlySelected->GetHealth()), Color(1, 1, 1));
		else
			Renderer->RenderText("text", "Health: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(16, 2, 0);
		modelStack->Scale(2.5f, 2.5f, 1.f);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size())
			Renderer->RenderText("text", "Attack: " + std::to_string(CurrentlySelected->GetAttack()), Color(1, 1, 1));
		else
			Renderer->RenderText("text", "Attack: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(16, -1, 0);
		modelStack->Scale(2.5f, 2.5f, 1.f);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size())
			Renderer->RenderText("text", "Defence: " + std::to_string(CurrentlySelected->GetDefence()), Color(1, 1, 1));
		else
			Renderer->RenderText("text", "Defence: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

	modelStack->PopMatrix();


}

void SceneCharacterSelection::RenderSkillInfo()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());
	Skill* CurrentlySelected = nullptr;
	if (SelectedCharacter > -1 && SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size())
		if (SelectedSkill < Player::Instance().GetClassUnitList(ClassNameText).at(SelectedCharacter)->GetSkillList()->size() - 1)
			CurrentlySelected = Player::Instance().GetClassUnitList(ClassNameText).at(SelectedCharacter)->GetSkillList()->at(SelectedSkill + 1);

	modelStack->PushMatrix();
	modelStack->Translate(0.f, -20.f, 1);

		modelStack->PushMatrix();
		modelStack->Scale(60, 30, 1);
		Renderer->RenderMesh("ButtonBorder", false);
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(-25, 8, 0);
		modelStack->Scale(2, 2, 1.f);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size() && CurrentlySelected != nullptr)
			Renderer->RenderText("text", "Name: " + CurrentlySelected->GetName(), Color(1, 1, 1));
		else
			Renderer->RenderText("text", "Name: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(-25, 5, 0);
		modelStack->Scale(2, 2, 1.f);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size() && CurrentlySelected != nullptr)
			Renderer->RenderText("text", "Damage: " + std::to_string(CurrentlySelected->GetDamage()), Color(1, 1, 1));
		else
			Renderer->RenderText("text", "Damage: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(-25, 2, 0);
		modelStack->Scale(2, 2, 1.f);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size() && CurrentlySelected != nullptr)
			Renderer->RenderText("text", "Cool Down: " + std::to_string(CurrentlySelected->GetMaxTurnCooldown()), Color(1, 1, 1));
		else
			Renderer->RenderText("text", "Cool Down: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(-25, -1, 0);
		modelStack->Scale(2, 2, 1.f);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size() && CurrentlySelected != nullptr)
		{
			std::string Position = "";
			for (int i = 0; i < 3; ++i)
			{
				if (CurrentlySelected->GetRequiredPosition(i))
				{
					switch (i)
					{
					case 0:
						Position += "FIRST ";
						break;
					case 1:
						Position += "SECOND ";
						break;
					case 2:
						Position += "THIRD ";
						break;
					default:
						break;
					}
				}

			}
			Renderer->RenderText("text", "Avaliable Position: " + Position, Color(1, 1, 1));
		}
		else
			Renderer->RenderText("text", "Avaliable Position: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

		modelStack->PushMatrix();
		modelStack->Translate(-25, -4, 0);
		modelStack->Scale(2, 2, 1);
		if (SelectedCharacter < Player::Instance().GetClassUnitList(ClassNameText).size() && CurrentlySelected != nullptr)
		{
			std::string Position = "";
			for (int i = 0; i < 3; ++i)
			{
				if (CurrentlySelected->GetSelectableTarget(i))
				{
					switch (i)
					{
					case 0:
						Position += "FIRST ";
						break;
					case 1:
						Position += "SECOND ";
						break;
					case 2:
						Position += "THIRD ";
						break;
					default:
						break;
					}
				}

			}
			Renderer->RenderText("text", "Target Position: " + Position, Color(1, 1, 1));
		}
		else
			Renderer->RenderText("text", "Target Position: ---", Color(1, 1, 1));
		modelStack->PopMatrix();

	modelStack->PopMatrix();
}

void SceneCharacterSelection::RenderFinalChoiceInfo()
{
	RenderSystem *Renderer = dynamic_cast<RenderSystem*>(&SceneSystem::Instance().GetRenderSystem());

	for (auto it : FinalChoiceList)
	{
		modelStack->PushMatrix();
		modelStack->Translate(it->GetPosition().x, it->GetPosition().y, it->GetPosition().z);
		modelStack->Scale(it->GetScale().x, it->GetScale().y, it->GetScale().z);
		if (it->type.find("Warrior") != string::npos)
			Renderer->RenderMesh("PlayerWarriorMesh", false);
		else if (it->type.find("Synergist") != string::npos)
			Renderer->RenderMesh("PlayerSynergistMesh", false);
		else if (it->type.find("Mage") != string::npos)
			Renderer->RenderMesh("PlayerMageMesh", false);
		else
			Renderer->RenderMesh("ButtonBorder", false);
		
		modelStack->PopMatrix();
	}

	modelStack->PushMatrix();
	modelStack->Translate(ObjectManager::Instance().WorldWidth * 0.5f, ObjectManager::Instance().WorldHeight * 0.1f, 1);

		modelStack->PushMatrix();
		modelStack->Scale(50, 10, 1);
		Renderer->RenderMesh("Inventory", false);
		modelStack->PopMatrix();

	modelStack->PopMatrix();
}