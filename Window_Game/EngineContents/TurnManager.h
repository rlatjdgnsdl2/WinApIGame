#pragma once
#include <EngineCore/GameMode.h>



//	����:
class ATurnManager : public AGameMode
{
public:
	//	constrcuter, destructer
	ATurnManager();
	virtual ~ATurnManager();

	//	delete Function
	ATurnManager(const ATurnManager& _Other) = delete;
	ATurnManager(ATurnManager&& _Other) noexcept = delete;
	ATurnManager& operator=(const ATurnManager& _Other) = delete;
	ATurnManager& operator=(ATurnManager&& _Other) noexcept = delete;

	void LevelChangeStart() override;
	void Tick(float _DeltaTime) override;



	void SetSpawnPos();


	void SetDungeon(class  ADungeon_BSP* _Dungeon)
	{
		Dungeon = _Dungeon;
	}
	void SetPatner(class APartner* _Partner)
	{
		Partner = _Partner;
	}
	void PushEnemy(class APokemon* _Enemy) {
		EnemyCamp.push_back(_Enemy);
	}

protected:

private:
	class ADungeon_BSP* Dungeon;
	class APlayer* Player;
	class APartner* Partner;

	TurnType CurTurnType;
	float CurDuration = 0.0f;

	SkillType PlayerSkillType;
	int PlayerInput;
	
	std::vector<class APokemon*> IdleVec;
	std::vector<class APokemon*> MoveVec;
	std::vector<class APokemon*> SkillVec;

	std::vector<class APokemon*> PlayerCamp;
	std::vector<class APokemon*> EnemyCamp;


	//	idle
	void PlayerSelect();
	//	Select Type
	void SelectMove(int _PlayerInput);
	void SelectSkill(int _PlayerInput);
	//	AI Check
	void Move_AISelect(float _DeltaTime);
	void Skill_AISelect(float _DeltaTime);
	//	Select Play
	void PlayerMove(float _DeltaTime);
	void PlayerSkill(float _DeltaTime);
	// AI Select Play
	void AIMove(float _DeltaTime);
	void AISkill(float _DeltaTime);
	

	//	move
	bool InitPlayerMove(DIR direction, FVector2D moveVector);




};
