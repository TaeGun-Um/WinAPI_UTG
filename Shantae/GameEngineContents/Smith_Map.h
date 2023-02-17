#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Smith_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Smith_Map();
	~Smith_Map();

	// delete Function
	Smith_Map(const Smith_Map& _Other) = delete;
	Smith_Map(Smith_Map&& _Other) noexcept = delete;
	Smith_Map& operator=(const Smith_Map& _Other) = delete;
	Smith_Map& operator=(Smith_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

