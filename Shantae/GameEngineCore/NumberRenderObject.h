#pragma once

#include <vector>

#include "GameEngineObject.h"
#include "GameEngineRender.h"

// < has a is a >
// 
// 클래스가 부모 클래스를 상속했다  => Is A 관계
// 클래스 내부에 이너 클래스가 있다 => Has A 관계

enum class Align
{
	Left,
	Right,
	Center
};

// 설명 : 숫자를 Image로 출력해주는 클래스. 해당 클래스는 무조건 액터가 지니고 있어야 한다(Player, Monster 등).
//        세팅되는 이미지는 무조건 10개로 커팅되야 함(0123456789)
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

	// Number들의 카메라 효과 off
	void SetCameraEffect(bool _EffectSetting)
	{
		CameraEffect = _EffectSetting;
	}

	inline int GetValue()
	{
		return Value;
	}

	// 랜더 할 숫자 길이 설정
	inline void SetNumOfDigits(int _Num) 
	{ 
		NumOfDigits = _Num;
	}

	// 숫자길이 리셋 (Value만큼 랜더)
	inline void ResetDigits() 
	{ 
		SetNumOfDigits(-1);
	}

	// 이미지를 find한 뒤, ImageName, NumberScale, Order에 정보 저장
	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");

	void SetValue(int _Value);

	// 넘버즈 배치, SetValue에 인자 전달
	void SetMove(float4 _RenderPos);

	void EffectCameraOff();

	void SetAlign(Align _Align);

	// Number 위치 조정
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

	int NumOfDigits = -1; // 렌더할 숫자 길이
	// GameEngineImage* NumberImage;

	int Order = 0;
	int Value = 0;
	int TransColor = RGB(255, 0, 255);

	bool CameraEffect = false;
	bool Negative = false;

	Align AlignState = Align::Left;

	void SetNumberRenders(size_t _Index, int _TransColor, float4 _Pos, const std::string_view& _ImageName, float4 _Scale, bool _CameraEffect, int _Frame = -1);

};

