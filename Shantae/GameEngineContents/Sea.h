#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : Move0의 바다
class Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Sea();
	~Sea();

	// delete Function
	Sea(const Sea& _Other) = delete;
	Sea(Sea&& _Other) noexcept = delete;
	Sea& operator=(const Sea& _Other) = delete;
	Sea& operator=(Sea&& _Other) noexcept = delete;

	void SetCount()
	{
		InitCount = 1;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	void Perspective();

	GameEngineRender* SeaRender_one = nullptr;
	GameEngineRender* SeaRender_two = nullptr;

	float4 InitSeaonePos = float4::Zero;
	float4 InitSeatwoPos = float4::Zero;
	float4 InitCameraPos = float4::Zero;
	float InitSeaYPos = 0.0f;
	float MoveSpeed = 10.0f;
	int InitCount = 1;
};

