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
	std::vector<Button*> ButtonList;
	int SelectedSkill[3];
	float MaxSkillSelectedTimer;

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
	void RenderCharacterList();
	void RenderCharacterInfo();
	void RenderSelectedCharacters();
	

protected:

	Camera camera;
};

#endif //SCENE_CHARACTER_SELECTION