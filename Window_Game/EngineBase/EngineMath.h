#pragma once


class UEngineMath
{
public:
	static float Sqrt(float _Value) { return ::sqrtf(_Value); }
};

class FIntPoint
{
public:
	int X = 0;
	int Y = 0;

	static const FIntPoint LEFT;
	static const FIntPoint RIGHT;
	static const FIntPoint UP;
	static const FIntPoint DOWN;

	FIntPoint()
	{

	}

	FIntPoint(int _X, int _Y) : X(_X), Y(_Y)
	{

	}


	FIntPoint operator+(FIntPoint _Other) const
	{
		FIntPoint Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FIntPoint operator-(FIntPoint _Other) const
	{
		FIntPoint Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}

	FIntPoint operator/(int _Value) const
	{
		FIntPoint Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}

	bool operator==(FIntPoint _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	FIntPoint& operator+=(FIntPoint _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}
};


class FVector2D
{
public:
	float X = 0.0f;
	float Y = 0.0f;

	FVector2D() {}
	FVector2D(float _X, float _Y) : X(_X), Y(_Y) {}
	FVector2D(int _X, int _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)) {}
	FVector2D(long _X, long _Y) : X(static_cast<float>(_X)), Y(static_cast<float>(_Y)) {}

	static const FVector2D ZERO;
	static const FVector2D LEFT;
	static const FVector2D RIGHT;
	static const FVector2D UP;
	static const FVector2D DOWN;

	//	선형보간
	static FVector2D LerpClamp(FVector2D _StartLocation, FVector2D _TargetLocation, float _t);

	//	벡터길이
	float Length() const { return UEngineMath::Sqrt(X * X + Y * Y); }

	//	정규화
	static FVector2D Normalize(FVector2D _Value);

	//	정규화
	void Normalize();

	int iX() const { return static_cast<int>(X); }
	int iY() const { return static_cast<int>(Y); }

	//	중앙값
	FVector2D Half() const { return { X * 0.5f, Y * 0.5f }; }
	float hX() const { return X * 0.5f; }
	float hY() const { return Y * 0.5f; }


	//	IntPoint로 변환
	FIntPoint ConvertToPoint() const { return { iX(), iY() }; }

	//	내적
	float Dot(FVector2D _Other) const { return X * _Other.X + Y * _Other.Y; }

	//	0이 있으면 true;
	bool IsZeroed() const { return X == 0.0f || Y == 0.0f; }

	//	연산자들

	FVector2D operator+(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X + _Other.X;
		Result.Y = Y + _Other.Y;
		return Result;
	}

	FVector2D operator-(FVector2D _Other) const
	{
		FVector2D Result;
		Result.X = X - _Other.X;
		Result.Y = Y - _Other.Y;
		return Result;
	}

	FVector2D operator/(int _Value) const
	{
		FVector2D Result;
		Result.X = X / _Value;
		Result.Y = Y / _Value;
		return Result;
	}

	FVector2D operator*(float _Value) const
	{
		FVector2D Result;
		Result.X = X * _Value;
		Result.Y = Y * _Value;
		return Result;
	}
	FVector2D& operator+=(FVector2D _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		return *this;
	}

	FVector2D& operator-=(FVector2D _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		return *this;
	}

	FVector2D operator-() const
	{
		FVector2D Result;
		Result.X = -X;
		Result.Y = -Y;
		return Result;
	}

	//	출력용
	std::string ToString()
	{
		std::string Stream;

		Stream += "X : [";
		Stream += std::to_string(X);
		Stream += "] Y : [";
		Stream += std::to_string(Y);
		Stream += "]";
		return Stream;
	}

	bool operator==(FVector2D _Other) const
	{
		return X == _Other.X && Y == _Other.Y;
	}

	bool EqualToInt(FVector2D _Other) const
	{
		return iX() == _Other.iX() && iY() == _Other.iY();
	}

};
enum class ECollisionType
{
	Point,
	Rect,
	CirCle,
	Max

};

class FTransform
{
private:
	friend class CollisionFunctionInit;
	static std::function<bool(const FTransform&, const FTransform&)> AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)];

public:
	static bool Collision(ECollisionType _LeftType, const FTransform& _Left, ECollisionType _RightType, const FTransform& _Right);
	static bool RectToRect(const FTransform& _Left, const FTransform& _Right);
	static bool CircleToCircle(const FTransform& _Left, const FTransform& _Right);
	
	FVector2D Scale;
	FVector2D Location;


	FVector2D CenterLeftTop() const
	{
		return Location - Scale.Half();
	}

	float CenterLeft() const
	{
		return Location.X - Scale.hX();
	}

	float CenterTop() const
	{
		return Location.Y - Scale.hY();
	}

	FVector2D CenterRightBottom() const
	{
		return Location + Scale.Half();
	}

	float CenterRight() const
	{
		return Location.X + Scale.hX();
	}

	float CenterBottom() const
	{
		return Location.Y + Scale.hY();
	}
};


class UColor
{
public:
	static const UColor WHITE;
	static const UColor BLACK;

	union
	{
		int Color;
		struct
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};
	};

	UColor(unsigned long _Value)
		:Color(_Value)
	{

	}

	bool operator==(const UColor& _Other)
	{
		return R == _Other.R && G == _Other.G && B == _Other.B;
	}


	UColor(unsigned char _R, unsigned char _G, unsigned char _B, unsigned char _A)
		:R(_R), G(_G), B(_B), A(_A)
	{

	}
};



