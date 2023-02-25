#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Building1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Building1();
	~Building1();

	// delete Function
	Building1(const Building1& _Other) = delete;
	Building1(Building1&& _Other) noexcept = delete;
	Building1& operator=(const Building1& _Other) = delete;
	Building1& operator=(Building1&& _Other) noexcept = delete;

	void SetRightBreak()
	{
		Right = true;
	}

	void SetLeftBreak()
	{
		Left = true;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void CollisionCheck();
	void LeftBreak(float _DeltaTime);
	void RightBreak(float _DeltaTime);
	void MoveCalculation(float _DeltaTime);
	void DirectCheckForKill();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	float4 InitPos = float4::Zero;
	float4 MoveDir = float4::Zero;

	float MoveSpeed = 250.0f;
	float RightB = 0.0f;
	float RightBTime = 0.0f;
	float LeftB = 0.0f;
	float LeftBTime = 0.0f;
	float BreakDelay = 0.0f;
	
	int InitCount = 1;

	bool Break = false;
	bool Right = false;
	bool Left = false;
};

