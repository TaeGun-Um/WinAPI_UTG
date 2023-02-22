#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class BoomBridge_Bridge1 : public GameEngineActor
{
public:
	// constrcuter destructer
	BoomBridge_Bridge1();
	~BoomBridge_Bridge1();

	// delete Function
	BoomBridge_Bridge1(const BoomBridge_Bridge1& _Other) = delete;
	BoomBridge_Bridge1(BoomBridge_Bridge1&& _Other) noexcept = delete;
	BoomBridge_Bridge1& operator=(const BoomBridge_Bridge1& _Other) = delete;
	BoomBridge_Bridge1& operator=(BoomBridge_Bridge1&& _Other) noexcept = delete;

	void SetAccTime(float _Timer)
	{
		AccTime = _Timer;
	}

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float AccTime = 0.0f;

	void Kill();
	void RenderSet();
	void CollisionSet();

};

