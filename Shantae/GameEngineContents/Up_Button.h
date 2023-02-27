#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Up_Button : public GameEngineActor
{
public:
	// constrcuter destructer
	Up_Button();
	~Up_Button();

	// delete Function
	Up_Button(const Up_Button& _Other) = delete;
	Up_Button(Up_Button&& _Other) noexcept = delete;
	Up_Button& operator=(const Up_Button& _Other) = delete;
	Up_Button& operator=(Up_Button&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

};

