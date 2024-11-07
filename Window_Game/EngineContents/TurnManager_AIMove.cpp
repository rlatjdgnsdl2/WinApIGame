#include "PreCompile.h"
#include "TurnManager.h"
#include "Pokemon.h"

void ATurnManager::AIMove(float _DeltaTime) 
{
	std::map<float, APokemon*>::iterator StartIter = MoveMaps.begin();
	std::map<float, APokemon*>::iterator EndIter = MoveMaps.end();

	for (; StartIter != EndIter; StartIter++)
	{
		APokemon* CurPokemon = StartIter->second;
		CurPokemon->Move(_DeltaTime);
	}
	CurTurnType = TurnType::AI_Skill;
}