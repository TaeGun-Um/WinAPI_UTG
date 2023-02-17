#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� :
class AnimationBox : public GameEngineActor
{
public:
	// constrcuter destructer
	AnimationBox();
	~AnimationBox();

	// delete Function
	AnimationBox(const AnimationBox& _Other) = delete;
	AnimationBox(AnimationBox&& _Other) noexcept = delete;
	AnimationBox& operator=(const AnimationBox& _Other) = delete;
	AnimationBox& operator=(AnimationBox&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

