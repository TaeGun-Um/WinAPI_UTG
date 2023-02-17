#pragma once

#include <vector>

#include "GameEngineObject.h"
#include "GameEngineRender.h"

// < has a is a >
// 
// Ŭ������ �θ� Ŭ������ ����ߴ�  => Is A ����
// Ŭ���� ���ο� �̳� Ŭ������ �ִ� => Has A ����

enum class Align
{
	Left,
	Right,
	Center
};

// ���� : ���ڸ� Image�� ������ִ� Ŭ����. �ش� Ŭ������ ������ ���Ͱ� ���ϰ� �־�� �Ѵ�(Player, Monster ��).
//        ���õǴ� �̹����� ������ 10���� Ŀ�õǾ� ��(0123456789)
class GameEngineActor;

class NumberRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	NumberRenderObject();
	~NumberRenderObject();

	// delete Function
	NumberRenderObject(const NumberRenderObject& _Other) = delete;
	NumberRenderObject(NumberRenderObject&& _Other) noexcept = delete;
	NumberRenderObject& operator=(const NumberRenderObject& _Other) = delete;
	NumberRenderObject& operator=(NumberRenderObject&& _Other) noexcept = delete;

	// Number���� ī�޶� ȿ�� off
	void SetCameraEffect(bool _EffectSetting)
	{
		CameraEffect = _EffectSetting;
	}

	inline int GetValue()
	{
		return Value;
	}

	// ���� �� ���� ���� ����
	inline void SetNumOfDigits(int _Num) 
	{ 
		NumOfDigits = _Num;
	}

	// ���ڱ��� ���� (Value��ŭ ����)
	inline void ResetDigits() 
	{ 
		SetNumOfDigits(-1);
	}

	// �̹����� find�� ��, ImageName, NumberScale, Order�� ���� ����
	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");

	void SetValue(int _Value);

	// �ѹ��� ��ġ, SetValue�� ���� ����
	void SetMove(float4 _RenderPos);

	void EffectCameraOff();

	void SetAlign(Align _Align);

	// Number ��ġ ����
	void SetRenderPos(float4 _Pos);
	void On() override;
	void Off() override;

protected:

private:
	float4 NumberScale = float4::Zero;
	float4 Pos = float4::Zero;

	std::string_view ImageName = std::string_view();
	std::string_view NegativeName = std::string_view();
	std::vector<GameEngineRender*> NumberRenders = std::vector<GameEngineRender*>();

	GameEngineRender* NegativeRender = nullptr;

	int NumOfDigits = -1; // ������ ���� ����
	// GameEngineImage* NumberImage;

	int Order = 0;
	int Value = 0;
	int TransColor = RGB(255, 0, 255);

	bool CameraEffect = false;
	bool Negative = false;

	Align AlignState = Align::Left;

	void SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame = -1);

};

