#include "PreCompile.h"
#include "TurnManager.h"
#include "Player.h"

void ATurnManager::SelectSkill(int _PlayerInput)
{
	switch (_PlayerInput)
	{
	case'A':
		Player->SetCurSKillType(SkillType::NormalAttack);
		break;

	default:
		break;
	}
	CurTurnType = TurnType::Player_Skill;
}