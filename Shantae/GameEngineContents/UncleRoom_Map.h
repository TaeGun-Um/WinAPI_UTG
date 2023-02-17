#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UncleRoom_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	UncleRoom_Map();
	~UncleRoom_Map();

	// delete Function
	UncleRoom_Map(const UncleRoom_Map& _Other) = delete;
	UncleRoom_Map(UncleRoom_Map&& _Other) noexcept = delete;
	UncleRoom_Map& operator=(const UncleRoom_Map& _Other) = delete;
	UncleRoom_Map& operator=(UncleRoom_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

