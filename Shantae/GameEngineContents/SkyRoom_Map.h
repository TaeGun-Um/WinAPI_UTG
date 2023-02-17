#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SkyRoom_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	SkyRoom_Map();
	~SkyRoom_Map();

	// delete Function
	SkyRoom_Map(const SkyRoom_Map& _Other) = delete;
	SkyRoom_Map(SkyRoom_Map&& _Other) noexcept = delete;
	SkyRoom_Map& operator=(const SkyRoom_Map& _Other) = delete;
	SkyRoom_Map& operator=(SkyRoom_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

