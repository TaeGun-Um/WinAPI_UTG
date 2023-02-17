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

class HeartRenderObject : public GameEngineObject
{
public:
	// constrcuter destructer
	HeartRenderObject();
	~HeartRenderObject();

	// delete Function
	HeartRenderObject(const HeartRenderObject& _Other) = delete;
	HeartRenderObject(HeartRenderObject&& _Other) noexcept = delete;
	HeartRenderObject& operator=(const HeartRenderObject& _Other) = delete;
	HeartRenderObject& operator=(HeartRenderObject&& _Other) noexcept = delete;

	// �̹����� find�� ��, ImageName, NumberScale, Order�� ���� ����
	void SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName = "");

	// �ѹ��� ��ġ, SetValue�� ���� ����
	void SetMove(float4 _RenderPos);
	void SetAlign(Align _Align);

	void SetValue(int _Value);

	// Number ��ġ ����
	inline void SetRenderPos(float4 _Pos)
	{
		Pos = _Pos;
	}

	// Number���� ī�޶� ȿ�� off
	void SetCameraEffect(bool _EffectSetting)
	{
		CameraEffect = _EffectSetting;
	}

	inline int GetValue()
	{
		return Value;
	}

protected:

private:
	float4 NumberScale = float4::Zero;
	float4 Pos = float4::Zero;

	std::string_view ImageName = std::string_view();
	std::string_view NegativeName = std::string_view();
	std::vector<GameEngineRender*> NumberRenders = std::vector<GameEngineRender*>();

	GameEngineRender* NegativeRender;

	int Order = 0;
	int Value = 0;
	int TransColor = RGB(255, 0, 255);

	bool CameraEffect = false;
	bool Negative = false;

	Align AlignState = Align::Left;

};

