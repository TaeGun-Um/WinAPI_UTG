#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

// Ό³Έν :
class Jar : public GameEngineActor
{
public:
	// constrcuter destructer
	Jar();
	~Jar();

	// delete Function
	Jar(const Jar& _Other) = delete;
	Jar(Jar&& _Other) noexcept = delete;
	Jar& operator=(const Jar& _Other) = delete;
	Jar& operator=(Jar&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetGround(float _Value)
	{
		GroundPos = float4::Down * _Value;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void Break();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineSoundPlayer BGMPlayer;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;
	float4 GroundPos = float4::Zero;

	int SoundCount = 1;

};

