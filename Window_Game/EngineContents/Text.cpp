#include "PreCompile.h"
#include "Text.h"
#include <EngineCore/SpriteRenderer.h>


AText::AText()
{

}

AText::~AText()
{

}

void AText::Reserve(int _Count)
{
	// 기존에 있던 글자 제거
	for (size_t i = 0; i < TextRenderer.size(); i++)
	{
		TextRenderer[i]->Destroy();
	}
	TextRenderer.resize(_Count);
	for (size_t i = 0; i < TextRenderer.size(); i++)
	{
		USpriteRenderer* NewText = CreateDefaultSubObject<USpriteRenderer>();
		NewText->SetOrder(ERenderOrder::UI_Text);
		NewText->SetCameraEffect(false);
		TextRenderer[i] = NewText;
	}
}


void AText::ShowText(float _DeltaTime)
{
	int Size = static_cast<int>(StringValue.size());
	for (size_t i = 0; i < Size; i++) {
		TextRenderer[i]->SetActive(false);
	}

	if (Time == 0.0f) {
		CurCount = Size;
	}

	CurTime += _DeltaTime;

	if (CurTime > Time) {
		++CurCount;
		CurTime = 0.0f;
	}
	if (CurCount >= Size) {
		CurCount = Size;
	}

	for (size_t i = 0; i < CurCount; i++) {
		TextRenderer[i]->SetActive(true);
	}
}

void AText::SetString(std::string_view _StringValue, std::string_view _color, FVector2D _TextSize, float _Time)
{
	StringValue = _StringValue;
	TextSize = _TextSize;
	Time = _Time;
	Color = _color.data();
	Reserve(static_cast<int>(StringValue.size()));
	CurCount = 0;
	for (size_t i = 0; i < StringValue.size(); i++)
	{
		char c = StringValue[i];
		int TextIndex = CharToTextIndex(c);
		TextRenderer[i]->SetSprite(Color + "_Text.png", TextIndex);
		TextRenderer[i]->SetSpriteScale();
		TextRenderer[i]->SetComponentLocation(FVector2D({ TextSize.X * i,TextSize.Y }));
		TextRenderer[i]->SetActive(false);
	}
}




void AText::SetColor(std::string_view _color)
{
	std::string Color = _color.data();
	for (size_t i = 0; i < StringValue.size(); i++)
	{
		char c = StringValue[i];
		int TextIndex = CharToTextIndex(c);
		TextRenderer[i]->SetSprite(Color + "_Text.png", TextIndex);
	}
}

void AText::SetParticialColor(int _StartIndex, int _EndIndex, std::string_view _color)
{
	std::string Color = _color.data();
	for (int i = _StartIndex; i < _EndIndex; i++)
	{
		char c = StringValue[i];
		int TextIndex = CharToTextIndex(c);
		TextRenderer[i]->SetSprite(Color + "_Text.png", TextIndex);
	}
}

int AText::CharToTextIndex(char _C)
{
	if (_C >= 'a' && _C <= 'z') {
		return (_C - 'a');
	}
	if (_C >= 'A' && _C <= 'Z') {
		return(_C - 'A' + 26);
	}
	if (_C >= '1' && _C <= '9') {
		return (_C - '1' + 52);
	}
	if (_C == '0') {
		return 61;
	}
	switch (_C) {
	case '!': return static_cast<int>(Text_Index::Exclamation);
	case '?': return static_cast<int>(Text_Index::Question);
	case',': return static_cast<int>(Text_Index::Comma);
	case '+': return static_cast<int>(Text_Index::Plus);
	case '-': return static_cast<int>(Text_Index::Minus);
	case '.': return static_cast<int>(Text_Index::Dot);
	default: return static_cast<int>(Text_Index::MAX);
	}
}


