#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BoomBridge_Bridge2 : public GameEngineActor
{
public:
	// constrcuter destructer
	BoomBridge_Bridge2();
	~BoomBridge_Bridge2();

	// delete Function
	BoomBridge_Bridge2(const BoomBridge_Bridge2& _Other) = delete;
	BoomBridge_Bridge2(BoomBridge_Bridge2&& _Other) noexcept = delete;
	BoomBridge_Bridge2& operator=(const BoomBridge_Bridge2& _Other) = delete;
	BoomBridge_Bridge2& operator=(BoomBridge_Bridge2&& _Other) noexcept = delete;

	void SetAccTime(float _Timer)
	{
		AccTime = _Timer;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float4 MoveDir = float4::Zero;
	float4 CurrentPos = float4::Zero;

	float AccTime = 0.0f;

	int CurrentPosCount = 1;
	int SoundCount = 1;

	bool MoveStart = false;
	bool IsJump = true;

	void Kill();
	void RenderSet();
	void CollisionSet();
	void MoveCalculation(float _DeltaTime);
	void DirectCheckForKill();

};

