#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Impact : public GameEngineActor
{
public:
	// constrcuter destructer
	Impact();
	~Impact();

	// delete Function
	Impact(const Impact& _Other) = delete;
	Impact(Impact&& _Other) noexcept = delete;
	Impact& operator=(const Impact& _Other) = delete;
	Impact& operator=(Impact&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

