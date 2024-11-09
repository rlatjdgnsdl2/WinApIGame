#include "PreCompile.h"
#include "2DCollision.h"
#include <EngineCore/EngineCoreDebug.h>


U2DCollision::U2DCollision()
{
}

U2DCollision::~U2DCollision()
{
}

void U2DCollision::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	if (0 > CollisionGroup)
	{
		MSGASSERT("충돌 그룹은 음수가 될수 없습니다.");
		return;
	}

	Level->PushCollision(this);
}

void U2DCollision::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);

	if (true == IsDebug() || true == GetActor()->IsDebug())
	{

		FTransform ActorTransform = GetActorTransform();
		FVector2D CameraPos = GetActor()->GetWorld()->GetCameraPos();

		ActorTransform.Location -= CameraPos;

		switch (CollisionType)
		{
		case ECollisionType::Rect:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Rect);
			break;
		case ECollisionType::CirCle:
			UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Circle);
			break;
		default:
			break;
		}
	}
}



bool U2DCollision::Collision(int _OtherCollisionGroup, std::vector<AActor*>& _Result, FVector2D _NextPos, unsigned int  _Limite)
{
	// 내가 xxxx 그룹이랑 충돌하는거죠.
	// 모든 충돌체를 한곳에 모아놓는게 Level

	std::list<class U2DCollision*>& OtherCollisions = GetActor()->GetWorld()->Collisions[_OtherCollisionGroup];

	std::list<class U2DCollision*>::iterator StartIter = OtherCollisions.begin();
	std::list<class U2DCollision*>::iterator EndIter = OtherCollisions.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		U2DCollision* ThisCollision = this;
		U2DCollision* DestCollision = *StartIter;
		// 
		FTransform ThisTrans = ThisCollision->GetActorTransform();
		FTransform DestTrans = DestCollision->GetActorTransform();

		ThisTrans.Location += _NextPos;

		ECollisionType ThisType = ThisCollision->CollisionType;
		ECollisionType DestType = DestCollision->CollisionType;

		bool Result = FTransform::Collision(ThisType, ThisTrans, DestType, DestTrans);

		// 충돌 true
		if (true == Result)
		{
			_Result.push_back(DestCollision->GetActor());
			--_Limite;

			if (0 == _Limite)
			{
				return 0 != _Result.size();
			}
		}
	}

	return 0 != _Result.size();
}