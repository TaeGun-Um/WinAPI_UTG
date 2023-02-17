#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BoomBridge_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	BoomBridge_Map();
	~BoomBridge_Map();

	// delete Function
	BoomBridge_Map(const BoomBridge_Map& _Other) = delete;
	BoomBridge_Map(BoomBridge_Map&& _Other) noexcept = delete;
	BoomBridge_Map& operator=(const BoomBridge_Map& _Other) = delete;
	BoomBridge_Map& operator=(BoomBridge_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

