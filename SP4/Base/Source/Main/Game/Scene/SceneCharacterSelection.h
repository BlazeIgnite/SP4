#ifndef SCENE_CHARACTER_SELECTION_H
#define SCENE_CHARACTER_SELECTION_H

#include <vector>

#include "SceneBase.h"
#include "../../Engine/Objects/SceneEntity.h"
#include "../../Base/Source/Main/Game/Objects/Characters/CharacterEntity.h"
#include "../../Base/Source/Main/Game/Miscellaneous/Button.h"

class SceneCharacterSelection : public SceneEntity
{
private:
	std::vector<CharacterEntity*> CharacterList;
	int SelectedCharacter;
	Button* Left;
	Button* Right;
	std::string ClassNameText;
	std::vector<Button*> CharacterButtonList;
	std::vector<Button*> SkillButtonList;
	std::vector<Button*> CharacterClassList;
	std::vector<Button*> FinalChoiceList;
	std::vector<Button*> ChangeSceneList;
	std::map<Button*, std::vector<int>> CharacterSelectedSkill;
	std::vector<int> SelectedSkills;
	int SelectedSkill;
	float MaxSkillSelectedTimer;
	float NoCharacterSelectedTimer;
	bool ClickingOtherButtons;

public:
	SceneCharacterSelection();
	~SceneCharacterSelection();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Exit();

	void InitButtons();

	void RenderPlayerCharacterList();
	void RenderSelectedCharacterInfo();
	void RenderCharacterInfo();
	void RenderSelectedCharacters();
	void RenderSkillInfo();
	void RenderFinalChoiceInfo();
	
protected:

	Camera camera;
};

#endif //SCENE_CHARACTER_SELECTION