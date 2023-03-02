#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class IDCard : public GameEngineActor
{
public:
	// constrcuter destructer
	IDCard();
	~IDCard();

	// delete Function
	IDCard(const IDCard& _Other) = delete;
	IDCard(IDCard&& _Other) noexcept = delete;
	IDCard& operator=(const IDCard& _Other) = delete;
	IDCard& operator=(IDCard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void ApplyScore();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	float4 UpPos = float4::Zero;

	GameEngineSoundPlayer BGMPlayer;

	int SoundCount = 1;
	int UpCount = 1;

	bool IsUp = false;

};

