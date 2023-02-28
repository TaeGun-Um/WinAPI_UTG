#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class EndingAnimation : public GameEngineActor
{
public:
	// constrcuter destructer
	EndingAnimation();
	~EndingAnimation();

	// delete Function
	EndingAnimation(const EndingAnimation& _Other) = delete;
	EndingAnimation(EndingAnimation&& _Other) noexcept = delete;
	EndingAnimation& operator=(const EndingAnimation& _Other) = delete;
	EndingAnimation& operator=(EndingAnimation&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

