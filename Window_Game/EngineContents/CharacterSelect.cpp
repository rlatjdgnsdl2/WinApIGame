#include "PreCompile.h"
#include "CharacterSelect.h"

#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWindow.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

#include "Box.h"
#include "GameDataManager.h"




ACharacterSelect::ACharacterSelect()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation(WindowSize.Half());
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Mudkip.png");
		SpriteRenderer->SetSpriteScale(0.5f);
		SpriteRenderer->SetComponentLocation({ -200,0 });
		SpriteRenderer->SetOrder(ERenderOrder::UI_IMAGE);
		CharacterImages.insert({ "Mudkip",SpriteRenderer });
	}

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Chikorita.png");
		SpriteRenderer->SetSpriteScale(0.5f);
		SpriteRenderer->SetComponentLocation({ 0,0 });
		SpriteRenderer->SetOrder(ERenderOrder::UI_IMAGE);
		CharacterImages.insert({ "Chikorita",SpriteRenderer });
	}

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Pikachu.png");
		SpriteRenderer->SetSpriteScale(0.5f);
		SpriteRenderer->SetComponentLocation({ 200,0 });
		SpriteRenderer->SetOrder(ERenderOrder::UI_IMAGE);
		CharacterImages.insert({ "Pikachu",SpriteRenderer });
	}

}

ACharacterSelect::~ACharacterSelect()
{

}

void ACharacterSelect::BeginPlay()
{
	Super::BeginPlay();
	Box = GetWorld()->SpawnActor<ABox>();
	Box->SetActorLocation({ 60,60 });
	Box->SetCharacterSelectBox();
	GetWorld()->SetCameraToMainPawn(false);
	CurIter = CharacterImages.begin();
	CurIter->second->SetSpriteScale(1.0f);
}

void ACharacterSelect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	UEngineDebug::CoreOutPutString(std::to_string(MousePos.X));
	UEngineDebug::CoreOutPutString(std::to_string(MousePos.Y));



	switch (CurSelectType)
	{
	case ACharacterSelect::SelectType::Player:
		if (true == UEngineInput::GetInst().IsDown('D')) {
			CurIter->second->SetSpriteScale(0.5f);
			CurIter++;
			if (CurIter == CharacterImages.end()) {
				CurIter = CharacterImages.begin();
			}
			CurIter->second->SetSpriteScale(1.0f);
		}

		if (true == UEngineInput::GetInst().IsDown('A')) {
			CurIter->second->SetSpriteScale(0.5f);
			if (CurIter == CharacterImages.begin()) {
				CurIter = CharacterImages.end();
			}
			CurIter--;
			CurIter->second->SetSpriteScale(1.0f);
		}
		if (true == UEngineInput::GetInst().IsDown('G')) {
			std::string PlayerName = CurIter->first;
			UGameDataManager::GetInst().SetSelectPlayer(PlayerName);
			UGameDataManager::GetInst().InsertPlayerAbility(PlayerName, PokemonInfo(PokemonType::WATER, 5, 45, 20, 15));
			//	�ӽ�
			std::string PartnerName = "Vulpix";
			UGameDataManager::GetInst().InsertPlayerAbility(PartnerName, PokemonInfo(PokemonType::FIRE, 5, 45, 20, 15));
			UEngineAPICore::GetCore()->OpenLevel("DungeonSelectLevel");


		}

		break;
	case ACharacterSelect::SelectType::Partner:
		/*if (true == UEngineInput::GetInst().IsDown('G')) {
			UGameDataManager::GetInst().InsertPlayerAbility(PlayerName, PokemonInfo(PokemonType::FIRE, 5, 45, 20, 15));
			UEngineAPICore::GetCore()->OpenLevel("DungeonSelectLevel");
		}*/
		break;
	default:
		break;
	}








}
