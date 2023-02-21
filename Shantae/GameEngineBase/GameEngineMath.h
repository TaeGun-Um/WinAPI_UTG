#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <vector>

// 설명 : 고립된 추상 클래스, 전역변수 선언용
class GameEngineMath final
{
public:
	static std::vector<unsigned int> GetDigits(int _Value); // int를 문자열로 변환
	static unsigned int GetLenth(int _Value);               // 문자열 길이 체크

	static const float PIE;    // 파이
	static const float PIE2;   // 파이*2
	static const float DegToRad;
	static const float RadToDeg;

private:
	virtual ~GameEngineMath() = 0;
};

// 설명 : 프로젝트(Shantae)의 모든 자료형 관리
class float4
{
public:
	static const float4 Left;   // 윈도우 좌표계 기준 왼쪽   : x 증가
	static const float4 Right;  // 윈도우 좌표계 기준 오른쪽 : x 감소
	static const float4 Up;     // 윈도우 좌표계 기준 위     : y 감소
	static const float4 Down;   // 윈도우 좌표계 기준 아래   : y 증가
	static const float4 Zero;   // x, y, z    == 0
	static const float4 Null;   // x, y, z, w == 0
	// 3D
	static const float4 Forward;
	static const float4 Back;   

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}

public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;

	// x, y, z, w을 int로 리턴
	inline int ix() const
	{
		return static_cast<int>(x);
	}

	inline int iy() const
	{
		return static_cast<int>(y);
	}

	inline int iz() const
	{
		return static_cast<int>(z);
	}

	inline int iw() const
	{
		return static_cast<int>(w);
	}

	// x, y, z, w의 절반(half)을 int로 리턴
	inline int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	inline int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	inline int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	inline int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}

	inline bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	inline float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		// 1.5 + 0.5 * 2.5;
		return Start * (1.0f - Ratio) + (End * Ratio);
	}

	static float4 LerpClamp(const float4& Start, const float4& End, float Ratio)
	{
		if (0 >= Ratio)
		{
			Ratio = 0.0f;
		}

		if (1.0f <= Ratio)
		{
			Ratio = 1.0f;
		}

		return Lerp(Start, End, Ratio);
	}

	float Size() const
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;

	}

	float4 operator +(const float4 _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4 _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator *(const float4 _Value) const
	{
		float4 Return;
		Return.x = x * _Value.x;
		Return.y = y * _Value.y;
		Return.z = z * _Value.z;
		return Return;
	}

	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	float4 operator /(const float4 _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}

	float4 operator -() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4& operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;
		return *this;
	}

	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}

	float4& operator *=(const float& _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		return *this;
	}

	// swprintf == 1번인자를 printf 해주는 함수
	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}

};