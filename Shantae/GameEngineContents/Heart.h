#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineSoundPlayer BGMPlayer;

};

