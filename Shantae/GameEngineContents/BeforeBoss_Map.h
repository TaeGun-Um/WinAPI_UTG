#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BeforeBoss_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	BeforeBoss_Map();
	~BeforeBoss_Map();

	// delete Function
	BeforeBoss_Map(const BeforeBoss_Map& _Other) = delete;
	BeforeBoss_Map(BeforeBoss_Map&& _Other) noexcept = delete;
	BeforeBoss_Map& operator=(const BeforeBoss_Map& _Other) = delete;
	BeforeBoss_Map& operator=(BeforeBoss_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

