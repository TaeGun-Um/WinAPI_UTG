#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Boss_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Map();
	~Boss_Map();

	// delete Function
	Boss_Map(const Boss_Map& _Other) = delete;
	Boss_Map(Boss_Map&& _Other) noexcept = delete;
	Boss_Map& operator=(const Boss_Map& _Other) = delete;
	Boss_Map& operator=(Boss_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

