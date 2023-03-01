#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

enum class HeartState
{
	Small,          // 1
	Large,          // 2
};

class GameEngineImage;

// Ό³Έν :
class Heart : public GameEngineActor
{
public:
	// constrcuter destructer
	Heart();
	~Heart();

	// delete Function
	Heart(const Heart& _Other) = delete;
	Heart(Heart&& _Other) noexcept = delete;
	Heart& operator=(const Heart& _Other) = delete;
	Heart& operator=(Heart&& _Other) noexcept = delete;

	void SetColMap(GameEngineImage* _NextColMap)
	{
		ColMap = _NextColMap;
	}

	void SetJarSize(const std::string_view& _Text)
	{
		JarSize = _Text;
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

	HeartState CreateHeart = HeartState::Small;
	std::string JarSize = "Small";

	float4 MoveDir = float4::Zero;
	float4 NextPos = float4::Zero;
	float4 OwnerPos = float4::Zero;

	float Jump = 800.0f;

	int CreateSet = 1;
	int Score = 0;
	int SoundCount = 1;

	bool IsStart = true;
	bool MoveDirect = true;

};

