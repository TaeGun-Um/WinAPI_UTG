#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ¼³¸í : Move0ÀÇ ÇÏ´Ã
class Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Sky();
	~Sky();

	// delete Function
	Sky(const Sky& _Other) = delete;
	Sky(Sky&& _Other) noexcept = delete;
	Sky& operator=(const Sky& _Other) = delete;
	Sky& operator=(Sky&& _Other) noexcept = delete;

	void SetSkyYPos(float _YPos)
	{
		YPos = _YPos;
	}

	void SetSkySpeed(float _Speed)
	{
		MoveSpeed = _Speed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:
	void SkyMove(float _DeltaTime);

	GameEngineRender* Sky_one = nullptr;
	GameEngineRender* Sky_two = nullptr;
	
	float4 OneInitPos = float4::Zero;
	float4 TwoInitPos = float4::Zero;

	float MoveSpeed = 50.0f;
	float YPos = 0.0f;

	int InitCount = 1;
	int Minus = 0;
};

