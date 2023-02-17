#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SaveRoom_Map : public GameEngineActor
{
public:
	// constrcuter destructer
	SaveRoom_Map();
	~SaveRoom_Map();

	// delete Function
	SaveRoom_Map(const SaveRoom_Map& _Other) = delete;
	SaveRoom_Map(SaveRoom_Map&& _Other) noexcept = delete;
	SaveRoom_Map& operator=(const SaveRoom_Map& _Other) = delete;
	SaveRoom_Map& operator=(SaveRoom_Map&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

