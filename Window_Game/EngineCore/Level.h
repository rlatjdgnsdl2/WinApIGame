#pragma once
#include "GameMode.h"

// 설명 :
class ULevel
{
public:
	friend class USpriteRenderer;
	friend class UEngineAPICore;
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);
	void Release(float _DeltaTime);

	template<typename ActorType>
	ActorType* SpawnActor()
	{
		ActorType* NewActor = new ActorType();
		AActor* ActorPtr = dynamic_cast<AActor*>(NewActor);
		ActorPtr->World = this;
		BeginPlayList.push_back(ActorPtr);
		return NewActor;
	}

	void SetCameraToMainPawn(bool _IsCameraToMainPawn)
	{
		IsCameraToMainPawn = _IsCameraToMainPawn;
	}

	void SetCameraPivot(FVector2D _Pivot)
	{
		CameraPivot = _Pivot;
	}
	void SetCameraPos(FVector2D _Pos)
	{
		CameraPos = _Pos;
	}
	FVector2D GetCameraPivot()
	{
		return CameraPivot;
	}

	FVector2D GetCameraPos()
	{
		return CameraPos;
	}
	AActor* GetPawn()
	{
		return MainPawn;
	}

protected:

private:
	void ScreenClear();
	void DoubleBuffering();


	// 게임레벨과 메인폰 생성함수
	template<typename GameModeType, typename MainPawnType>
	void CreateGameMode()
	{
		GameMode = new GameModeType();
		MainPawn = new MainPawnType();

		MainPawn->World = this;
		GameMode->World = this;

		BeginPlayList.push_back(GameMode);
		BeginPlayList.push_back(MainPawn);

	}
	void LevelChangeStart();
	void LevelChangeEnd();
	void PushRenderer(class USpriteRenderer* _Renderer);
	void ChangeRenderOrder(class USpriteRenderer* _Renderer, int _PrevOrder);

	
	class AGameMode* GameMode = nullptr;
	// 주인공
	class AActor* MainPawn = nullptr;

	std::list<AActor*> AllActors;

	std::list<AActor*> BeginPlayList;
	bool IsCameraToMainPawn = true;
	
	FVector2D CameraPos;
	FVector2D CameraPivot;

	// 렌더 오더
	std::map<int, std::list<class USpriteRenderer*>> Renderers;
};

