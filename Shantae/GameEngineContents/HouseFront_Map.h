#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : HouseFront Map
class HouseFront_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_Map();
	~HouseFront_Map();

	// delete Function
	HouseFront_Map(const HouseFront_Map& _Other) = delete;
	HouseFront_Map(HouseFront_Map&& _Other) noexcept = delete;
	HouseFront_Map& operator=(const HouseFront_Map& _Other) = delete;
	HouseFront_Map& operator=(HouseFront_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

