#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

class GameEngineImage;

enum class Scarecrow_BlackState
{
	MOVE,
	HIT,
};

// Ό³Έν : Player Chracter
class Scarecrow_Black : public GameEngineActor
{
public:
	// constrcuter destructer
	Scarecrow_Black();
	~Scarecrow_Black();

	// delete Function
	Scarecrow_Black(const Scarecrow_Black& _Other) = delete;
	Scarecrow_Black(Scarecrow_Black&& _Other) noexcept = delete;
	Scarecrow_Black& operator=(const Scarecrow_Black& _Other) = delete;
	Scarecrow_Black& operator=(Scarecrow_Black&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	NumberRenderObject TestNumber;

};

