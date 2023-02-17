#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SkyRoom_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyRoom_Background();
	~SkyRoom_Background();

	// delete Function
	SkyRoom_Background(const SkyRoom_Background& _Other) = delete;
	SkyRoom_Background(SkyRoom_Background&& _Other) noexcept = delete;
	SkyRoom_Background& operator=(const SkyRoom_Background& _Other) = delete;
	SkyRoom_Background& operator=(SkyRoom_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

