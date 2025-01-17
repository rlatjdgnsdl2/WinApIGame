#pragma once
#include <EngineCore/GameMode.h>

//	설명:
class AUIManager :public AGameMode
{
public:
	//	constrcuter, destructer
	AUIManager();
	virtual ~AUIManager();

	//	delete Function
	AUIManager(const AUIManager& _Other) = delete;
	AUIManager(AUIManager&& _Other) noexcept = delete;
	AUIManager& operator=(const AUIManager& _Other) = delete;
	AUIManager& operator=(AUIManager&& _Other) noexcept = delete;

	virtual void BeginPlay()override;
	virtual void LevelChangeStart()override;
	virtual void Tick(float _DeltaTime)override;

	MenuType GetCurMenuType() const {
		return CurMenu;
	}
	void SetCurMenuType(MenuType _CurMenuType) {
		CurMenu = _CurMenuType;
	}
	void SetPartner(class APartner* _Partner) {
		Partner = _Partner;
	}
	void SetDungeon(class ADungeon_BSP* _Dungeon) {
		Dungeon = _Dungeon;
	}
	void SetCurLevelName(std::string_view _LevelName) {
		CurLevelName = _LevelName.data();
	}

	void NewLogMessage(const std::string_view _Message, Color _Color = Color::White);
	void NewLogMessage(const std::vector<std::string>& _Message, const std::vector<Color>& _Colors);

	void SetItemList(std::list<std::string>& _ItemList) {
		ItemList = &_ItemList;
	}



	

	//void OpenItem();


protected:

private:
	FVector2D UIStartPos = FVector2D(20.0f, 20.0f);
	float CurDuration = 0.0f;
	//	UI정보
	class APlayer* Player = nullptr;
	class APartner* Partner = nullptr;
	class ADungeon_BSP* Dungeon = nullptr;
	std::list<std::string>* ItemList;
	std::string CurLevelName;
	MenuType CurMenu;
	TurnType CurTurn;

	//	UI
	class ABoxUI* MenuUI = nullptr;
	class ABoxUI* MyInfoUI = nullptr;

	class ABoxUI* SkillUI = nullptr;
	class ABoxUI* SkillInfoUI = nullptr;

	class AInventory* ItemUI = nullptr;
	class ABoxUI* ItemInfoUI = nullptr;

	//	던전
	//	상단 UI
	std::unordered_map<std::string, class USpriteRenderer*> TopUI;
	std::vector<class USpriteRenderer* > HpBar;
	class ABoxUI* DungeonNameUI = nullptr;

	class ABoxUI* Q_NextFloorUI = nullptr;
	class ABoxUI* A_AnswerUI = nullptr;

	class ADungeonLogBox* LogBoxUI = nullptr;

	void CreateTopUI(const std::string& key, const std::string& spriteName, float offsetX = 0.0f);

	void OpenMenu();
	void ShowMenu();
	void CloseMenu();

	void OpenSkill();
	void ShowSkill();
	void CloseSkill();

	void OpenItem();
	void ShowItem();
	void CloseItem();

	void OpenNextFloor();
	void ShowNextFloor();
	void CloseNextFloor();

	void OpenLog();
	void ShowLog(float _DeltaTime);
	void CloseLog();


};

