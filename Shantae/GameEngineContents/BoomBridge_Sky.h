#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BoomBridge_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	BoomBridge_Sky();
	~BoomBridge_Sky();

	// delete Function
	BoomBridge_Sky(const BoomBridge_Sky& _Other) = delete;
	BoomBridge_Sky(BoomBridge_Sky&& _Other) noexcept = delete;
	BoomBridge_Sky& operator=(const BoomBridge_Sky& _Other) = delete;
	BoomBridge_Sky& operator=(BoomBridge_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

