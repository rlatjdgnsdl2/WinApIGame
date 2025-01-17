#include "PreCompile.h"
#include "SpriteRenderer.h"
#include "ImageManager.h"

#include "EngineAPICore.h"
#include <EngineBase/EngineString.h>

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

// SpriteRenderer : public URenderer
// MeshRenderer : public URenderer
// StaticMeshRenderer : public URenderer
void USpriteRenderer::Render(float _DeltaTime)
{
	if (nullptr == Sprite)
	{
		MSGASSERT("스프라이트가 세팅되지 않은 액터를 랜더링을 할수 없습니다.");
		return;
	}
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	FTransform Trans = GetActorTransform();

	ULevel* Level = GetActor()->GetWorld();

	if (true == IsCameraEffect)
	{
		Trans.Location = Trans.Location - (Level->CameraPos * CameraEffectScale);
	}

	Trans.Location += Pivot;


	if (Alpha == 255)
	{
		CurData.Image->CopyToTrans(BackBufferImage, Trans, CurData.Transform);
	}
	else
	{
		CurData.Image->CopyToAlpha(BackBufferImage, Trans, CurData.Transform, Alpha);
	}
}

void USpriteRenderer::BeginPlay()
{
	// 부모 클래스의 함수를 호출하는걸 깜빡하면 안된다.
	// 습관되면 가장 언리얼 학습에서 걸림돌이 되는 습관이 된다.
	Super::BeginPlay();

	// 스프라이트 랜더러가 

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

	Level->ChangeRenderOrder(this, this->GetOrder());
}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);

	if (nullptr != CurAnimation)
	{
		
		std::vector<int>& Indexs = CurAnimation->FrameIndex;
		std::vector<float>& Times = CurAnimation->FrameTime;

		Sprite = CurAnimation->Sprite;


		CurAnimation->CurTime += _DeltaTime;

		float CurFrameTime = Times[CurAnimation->CurIndex];

		//                           0.1 0.1 0.1
		if (CurAnimation->CurTime > CurFrameTime)
		{
			


			CurAnimation->CurTime -= CurFrameTime;
			++CurAnimation->CurIndex;

			if (CurAnimation->Events.contains(CurIndex))
			{
				CurAnimation->Events[CurIndex]();
			}

			// 애니메이션 앤드
			if (CurAnimation->CurIndex >= Indexs.size())
			{
				CurAnimation->IsEnd = true;
			}
			else {
				CurAnimation->IsEnd = false;
			}

			if (CurAnimation->CurIndex >= Indexs.size())
			{
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurIndex = 0;

					if (CurAnimation->Events.contains(CurIndex))
					{
						CurAnimation->Events[CurIndex]();
					}
				}
				else
				{
					CurAnimation->IsEnd = true;
					--CurAnimation->CurIndex;
				}
			}

		}


		//         2 3 4           0
		CurIndex = Indexs[CurAnimation->CurIndex];
		// ++CurAnimation->CurIndex;
	}

}

void USpriteRenderer::SetSprite(std::string_view _Name, int _CurIndex /*= 0*/)
{
	
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("로드하지 않은 스프라이트를 사용하려고 했습니다" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}

void USpriteRenderer::SetOrder(int _Order)
{
	int PrevOrder = Order;

	Order = _Order;

	if (PrevOrder == Order)
	{
		return;
	}

	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != Level)
	{
		Level->ChangeRenderOrder(this, PrevOrder);
	}
}

FVector2D USpriteRenderer::SetSpriteScale(float _Ratio /*= 1.0f*/, int _CurIndex /*= 0*/)
{
	if (nullptr == Sprite)
	{
		//MSGASSERT("스프라이트를 세팅하지 않고 스프라이트 크기로 랜더러 크기를 조정할수 없습니다.");
		return FVector2D::ZERO;
	}

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(_CurIndex);

	FVector2D Scale = CurData.Transform.Scale * _Ratio;

	SetComponentScale(CurData.Transform.Scale * _Ratio);

	return Scale;
}


void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time /*= 0.1f*/, bool _Loop /*= true*/)
{

	int Inter = 0;

	std::vector<int> Indexs;
	std::vector<float> Times;

	if (_Start < _End)
	{
		Inter = (_End - _Start) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexs.push_back(_Start);
			Times.push_back(Time);
			++_Start;
		}
	}
	else
	{
		Inter = (_Start - _End) + 1;
		for (size_t i = 0; i < Inter; i++)
		{
			Indexs.push_back(_End);
			Times.push_back(Time);
			++_End;
		}
	}
	CreateAnimation(_AnimationName, _SpriteName, Indexs, Times, _Loop);
}


void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop /*= true*/)
{
	std::vector<float> Times;
	for (size_t i = 0; i < _Indexs.size(); i++)
	{
		Times.push_back(_Frame);
	}
	CreateAnimation(_AnimationName, _SpriteName, _Indexs, Times, _Loop);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop /*= true*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_Frame.size() != _Indexs.size())
	{
		MSGASSERT(UpperName + "을 만들다 에러가 났습니다 프레임과 타임의 카운트가 서로 다릅니다");
		return;
	}

	if (FrameAnimations.contains(UpperName))
	{
		return;
	}

	UEngineSprite* FindSprite = UImageManager::GetInst().FindSprite(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("로드하지 않은 스프라이트를 애니메이션 생서에 사용하려고 했습니다" + std::string(UpperName));
		return;
	}

	FrameAnimation NewAnimation;
	NewAnimation.Sprite = FindSprite;
	NewAnimation.FrameIndex = _Indexs;
	NewAnimation.FrameTime = _Frame;
	NewAnimation.Loop = _Loop;
	NewAnimation.Reset();

	FrameAnimations.insert({ UpperName ,NewAnimation });

}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 애니메이션으로 변경하려고 했습니다. = " + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && false == _Force)
	{
		return;
	}

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();
	CurIndex = CurAnimation->FrameIndex[CurAnimation->CurIndex];

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
	{
		CurAnimation->Events[CurAnimation->CurIndex]();
	}

	Sprite = CurAnimation->Sprite;
}


void USpriteRenderer::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("존재하지 않은 애니메이션으로 변경하려고 했습니다. = " + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	bool Check = false;

	for (size_t i = 0; i < ChangeAnimation->FrameIndex.size(); i++)
	{
		if (_Frame == ChangeAnimation->FrameIndex[i])
		{
			Check = true;
			break;
		}
	}

	if (false == Check)
	{
		MSGASSERT("존재하지 않는 프레임에 이벤트를 생성하려고 했습니다" + std::string(_AnimationName));
		return;
	}

	ChangeAnimation->Events[_Frame] += _Function;

}

void USpriteRenderer::SetCameraEffectScale(float _Effect)
{
	CameraEffectScale = _Effect;
}

// 여러분들이 애니메이션을 하거나
void USpriteRenderer::SetPivotType(PivotType _Type)
{
	if (PivotType::Center == _Type)
	{
		Pivot = FVector2D::ZERO;
		return;
	}

	if (nullptr == Sprite)
	{
		MSGASSERT("이미지를 기반으로한 피봇설정은 스프라이트가 세팅되지 않은 상태에서는 호출할수 없습니다");
		return;
	}

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	switch (_Type)
	{
	case PivotType::Bot:
		Pivot.X = 0.0f;
		Pivot.Y -= CurData.Transform.Scale.Y * 0.5f;
		break;
	case PivotType::Top:
		Pivot.X = 0.0f;
		Pivot.Y += CurData.Transform.Scale.Y * 0.5f;
		break;
	default:
		break;
	}
}
