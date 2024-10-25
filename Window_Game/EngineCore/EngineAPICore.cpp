#include "PreCompile.h"
#include "EngineAPICore.h"
#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;


UEngineAPICore::UEngineAPICore()
{

}

UEngineAPICore::~UEngineAPICore()
{
	std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Levels.clear();
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	UserCore = _UserCore;
	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core;

	Core.EngineMainWindow.Open("Yoshi's Island");	//	임시제목
	MainCore = &Core;
	
	return UEngineWindow::WindowMessageLoop(EngineBeginPlay, EngineTick);
}

void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick()
{
	//	의미x
	UserCore->Tick();
	//	중요
	MainCore->Tick();
}



void UEngineAPICore::Tick()
{
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();
	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진 코어에 현재 레벨이 지정되지 않았습니다");
		return;
	}

	CurLevel->Tick(DeltaTime);
	CurLevel->Render();
}


void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();
	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(ChangeName + "라는 이름의 레벨은 존재하지 않습니다.");
		return;
	}
	CurLevel = FindIter->second;
}
