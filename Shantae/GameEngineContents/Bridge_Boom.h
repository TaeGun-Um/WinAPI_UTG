#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν : Player Chracter
class Bridge_Boom : public GameEngineActor
{
public:
	// constrcuter destructer
	Bridge_Boom();
	~Bridge_Boom();

	// delete Function
	Bridge_Boom(const Bridge_Boom& _Other) = delete;
	Bridge_Boom(Bridge_Boom&& _Other) noexcept = delete;
	Bridge_Boom& operator=(const Bridge_Boom& _Other) = delete;
	Bridge_Boom& operator=(Bridge_Boom&& _Other) noexcept = delete;

	void SetDeath(bool _IsDeath)
	{
		IsDeath = _IsDeath;
	}

	void SetAccTime(float _Timer)
	{
		AccTime = _Timer;
	}

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

	float AccTime = 0.0f;

	int SoundCount = 1;

	bool IsDeath = false;

	void Kill();
	void Explosion();

};