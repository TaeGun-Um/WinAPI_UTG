#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BeforeBoss_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	BeforeBoss_Background();
	~BeforeBoss_Background();

	// delete Function
	BeforeBoss_Background(const BeforeBoss_Background& _Other) = delete;
	BeforeBoss_Background(BeforeBoss_Background&& _Other) noexcept = delete;
	BeforeBoss_Background& operator=(const BeforeBoss_Background& _Other) = delete;
	BeforeBoss_Background& operator=(BeforeBoss_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

