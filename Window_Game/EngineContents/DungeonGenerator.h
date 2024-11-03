#pragma once
#include <EngineBase/Object.h>

//	����:
class UDungeonGenerator :public UObject
{
public:
	//	constrcuter, destructer
	UDungeonGenerator();
	virtual ~UDungeonGenerator();

	//	delete Function
	UDungeonGenerator(const UDungeonGenerator& _Other) = delete;
	UDungeonGenerator(UDungeonGenerator&& _Other) noexcept = delete;
	UDungeonGenerator& operator=(const UDungeonGenerator& _Other) = delete;
	UDungeonGenerator& operator=(UDungeonGenerator&& _Other) noexcept = delete;

	virtual void GenerateDungeon(class ADungeon* _Dungeon);
	
	virtual void SetAllWall();
	virtual void SetRandomSizeRoom();
	virtual void SetRandomHallWay();
	


protected:

private:
	class ADungeon* Dungeon = nullptr;

};

