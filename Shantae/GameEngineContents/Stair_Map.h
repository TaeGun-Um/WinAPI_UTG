#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Stair_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Stair_Map();
	~Stair_Map();

	// delete Function
	Stair_Map(const Stair_Map& _Other) = delete;
	Stair_Map(Stair_Map&& _Other) noexcept = delete;
	Stair_Map& operator=(const Stair_Map& _Other) = delete;
	Stair_Map& operator=(Stair_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

