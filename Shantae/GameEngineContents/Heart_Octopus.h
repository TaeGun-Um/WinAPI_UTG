#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

// Ό³Έν :
class Heart_Octopus : public GameEngineActor
{
public:
	// constrcuter destructer
	Heart_Octopus();
	~Heart_Octopus();

	// delete Function
	Heart_Octopus(const Heart_Octopus& _Other) = delete;
	Heart_Octopus(Heart_Octopus&& _Other) noexcept = delete;
	Heart_Octopus& operator=(const Heart_Octopus& _Other) = delete;
	Heart_Octopus& operator=(Heart_Octopus&& _Other) noexcept = delete;

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
	void ApplyScore();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineSoundPlayer BGMPlayer;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	float Jump = 800.0f;

	int SoundCount = 1;
	bool IsStart = true;

};

