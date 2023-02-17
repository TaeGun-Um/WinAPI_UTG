#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SkyRoom_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyRoom_Sky();
	~SkyRoom_Sky();

	// delete Function
	SkyRoom_Sky(const SkyRoom_Sky& _Other) = delete;
	SkyRoom_Sky(SkyRoom_Sky&& _Other) noexcept = delete;
	SkyRoom_Sky& operator=(const SkyRoom_Sky& _Other) = delete;
	SkyRoom_Sky& operator=(SkyRoom_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

