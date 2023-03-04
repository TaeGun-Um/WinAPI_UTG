#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Wavesplash : public GameEngineActor
{
public:
	// constrcuter destructer
	Wavesplash();
	~Wavesplash();

	// delete Function
	Wavesplash(const Wavesplash& _Other) = delete;
	Wavesplash(Wavesplash&& _Other) noexcept = delete;
	Wavesplash& operator=(const Wavesplash& _Other) = delete;
	Wavesplash& operator=(Wavesplash&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineCollision* BodyCollision = nullptr;

};

