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

