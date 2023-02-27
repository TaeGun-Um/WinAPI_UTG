#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Sailor : public GameEngineActor
{
public:
	// constrcuter destructer
	Sailor();
	~Sailor();

	// delete Function
	Sailor(const Sailor& _Other) = delete;
	Sailor(Sailor&& _Other) noexcept = delete;
	Sailor& operator=(const Sailor& _Other) = delete;
	Sailor& operator=(Sailor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DirCheck();

	GameEngineRender* AnimationRender = nullptr;
	bool MoveDirect = true; // true = Left, false = Right

};

