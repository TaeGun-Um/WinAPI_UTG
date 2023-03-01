#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

// Ό³Έν :
class Jar_Big : public GameEngineActor
{
public:
	// constrcuter destructer
	Jar_Big();
	~Jar_Big();

	// delete Function
	Jar_Big(const Jar_Big& _Other) = delete;
	Jar_Big(Jar_Big&& _Other) noexcept = delete;
	Jar_Big& operator=(const Jar_Big& _Other) = delete;
	Jar_Big& operator=(Jar_Big&& _Other) noexcept = delete;
	
	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void MoveCalculation(float _DeltaTime);
	void CollisionCheck(float _DeltaTime);
	void Break();
	void CreateItem();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineSoundPlayer BGMPlayer;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	int SoundCount = 1;

};

