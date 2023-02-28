#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

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
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineImage* ColMap = nullptr;

	GameEngineSoundPlayer BGMPlayer;

};

