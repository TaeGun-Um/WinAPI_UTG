#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BoomBridge_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	BoomBridge_Background();
	~BoomBridge_Background();

	// delete Function
	BoomBridge_Background(const BoomBridge_Background& _Other) = delete;
	BoomBridge_Background(BoomBridge_Background&& _Other) noexcept = delete;
	BoomBridge_Background& operator=(const BoomBridge_Background& _Other) = delete;
	BoomBridge_Background& operator=(BoomBridge_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

