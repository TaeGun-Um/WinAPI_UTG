#pragma once

#include <GameEngineCore/GameEngineActor.h>

class A_Button;

// Ό³Έν : Player Chracter
class Merchant : public GameEngineActor
{
public:
	// constrcuter destructer
	Merchant();
	~Merchant();

	// delete Function
	Merchant(const Merchant& _Other) = delete;
	Merchant(Merchant&& _Other) noexcept = delete;
	Merchant& operator=(const Merchant& _Other) = delete;
	Merchant& operator=(Merchant&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void Run(float _DeltaTime);
	void CollisionCheck();
	void DirectCheckForKill();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	A_Button* AButton = nullptr;

	float4 CurrentPos = float4::Zero;

	int CurrentPosCount = 1;
	int CreateAButtion = 1;

	bool IsRun = false;

};

