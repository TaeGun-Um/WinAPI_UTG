#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class PikeBall : public GameEngineActor
{
public:
	// constrcuter destructer
	PikeBall();
	~PikeBall();

	// delete Function
	PikeBall(const PikeBall& _Other) = delete;
	PikeBall(PikeBall&& _Other) noexcept = delete;
	PikeBall& operator=(const PikeBall& _Other) = delete;
	PikeBall& operator=(PikeBall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

};

