#include "PreCompile.h"
#include "Player.h"
#include "GameDataManager.h"





APlayer::APlayer()
{
	
}



APlayer::~APlayer()
{

}


void APlayer::SetPokemon(std::string_view _PokemonName)
{
	APokemon::SetPokemon(_PokemonName);
	CurCamp = CampType::Player;
	CurPokemonAbility = UGameDataManager::GetInst().GetPlayerAbility(CurPokemonName);
}









