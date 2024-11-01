#include "PreCompile.h"
#include "TitleGameMode.h"

#include "TitleAnimActor.h"
#include "TitleBackground.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

float ATitleGameMode::TitlePlayTime = 0.0f;

ATitleGameMode::ATitleGameMode()
{
	UEngineDirectory TItle;
	TItle.MoveParentToDirectory("Resources");
	TItle.Append("Title");
	UImageManager::GetInst().LoadFolder(TItle.GetPathToString());
}

ATitleGameMode::~ATitleGameMode()
{

}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	ATitleBackground* Background = GetWorld()->SpawnActor<ATitleBackground>();
	ATitleAnimActor* AnimCharacter = GetWorld()->SpawnActor<ATitleAnimActor>();
	GetWorld()->SetCameraToMainPawn(false);
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	TitlePlayTime += _DeltaTime;
}

float ATitleGameMode::GetTitlePlayTime()
{
	return TitlePlayTime;
}

void ATitleGameMode::ResetTitlePlayTime()
{
	TitlePlayTime = 0.0f;
}



