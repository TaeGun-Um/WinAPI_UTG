#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

enum class GemState
{
	Blue,          // 1
	Green,         // 2
	Pupple,        // 3
	Red,           // 4
	Yellow,        // 5
	Blue_Big,      // 6
	Green_Big,     // 7
	Pupple_Big,    // 8
	Red_Big,       // 9
	Yellow_Big,    // 10
};

class GameEngineImage;

// Ό³Έν :
class Gem : public GameEngineActor
{
public:
	// constrcuter destructer
	Gem();
	~Gem();

	// delete Function
	Gem(const Gem& _Other) = delete;
	Gem(Gem&& _Other) noexcept = delete;
	Gem& operator=(const Gem& _Other) = delete;
	Gem& operator=(Gem&& _Other) noexcept = delete;

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
	void GemSetting();
	void ApplyScore();
	void Kill();

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineSoundPlayer BGMPlayer;

	GemState CreateGem = GemState::Blue;

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;

	float Jump = 800.0f;

	int CreateSet = 1;
	int Score = 0;
	int SoundCount = 1;
	bool IsStart = true;

};

