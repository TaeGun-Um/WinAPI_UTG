#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class ScarecrowState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class Scarecrow : public GameEngineActor
{
public:
	// constrcuter destructer
	Scarecrow();
	~Scarecrow();

	// delete Function
	Scarecrow(const Scarecrow& _Other) = delete;
	Scarecrow(Scarecrow&& _Other) noexcept = delete;
	Scarecrow& operator=(const Scarecrow& _Other) = delete;
	Scarecrow& operator=(Scarecrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	NumberRenderObject TestNumber;

};

