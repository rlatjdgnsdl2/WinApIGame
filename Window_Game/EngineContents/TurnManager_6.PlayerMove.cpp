#include "PreCompile.h"
#include "TurnManager.h"


#include <EnginePlatform/EngineInput.h>
#include <EngineCore/SpriteRenderer.h>

#include "Pokemon.h"
#include "Player.h"




void ATurnManager::PlayerMove(float _DeltaTime)
{
	CurDuration += _DeltaTime;
	//	Player move
	Player->Move(_DeltaTime);

	std::vector<APokemon*>::iterator StartIter = MoveVec.begin();
	std::vector<APokemon*>::iterator EndIter = MoveVec.end();

	// �÷��̾ �̵��Ҷ� MoveVec�� �ִ� ���ϸ� ��� �̵���
	for (; StartIter != EndIter; StartIter++)
	{
		APokemon* CurPokemon = *StartIter;
		CurPokemon->Move(_DeltaTime);
	}

	if (Player->GetActorLocation() == Player->GetTargetLocation())	//����������
	{
		std::vector<APokemon*>::iterator StartIter = MoveVec.begin();
		std::vector<APokemon*>::iterator EndIter = MoveVec.end();
		for (; StartIter != EndIter; StartIter++)
		{
			APokemon* CurPokemon = *StartIter;
			CurPokemon->Move(1.0f);
			CurPokemon->SetCurDuration(0.0f);
		}
		//	�̵��� ���͵� �� Vec���� ����
		MoveVec.clear();
		CurDuration = 0.0f;
		//	�����ܰ�
		CurTurnType = TurnType::AI_Skill;
	}
}