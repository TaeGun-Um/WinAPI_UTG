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

	void SetSoundOff()
	{
		IsSound = false;
	}

	void SetDirect(bool _Is)
	{
		Direct = _Is;
	}

	GameEngineSoundPlayer BGMPlayer;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

	float AccTime = 0.0f;
	float BoomTime = 0.0f;

	int SoundCount = 1;
	int BoomCount = 4;

	bool IsDeath = false;
	bool IsSound = true;
	bool Direct = true; // true = Left, false = right

	void Kill();
	void Explosion();
	void Explosions(float4 _Value);
	void RightCreateExplosion(float _DeltaTime);
	void LeftCreateExplosion(float _DeltaTime);

};