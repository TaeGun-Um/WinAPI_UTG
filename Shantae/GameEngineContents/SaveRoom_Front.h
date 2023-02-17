#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SaveRoom_Front : public GameEngineActor
{
public:
	// constrcuter destructer
	SaveRoom_Front();
	~SaveRoom_Front();

	// delete Function
	SaveRoom_Front(const SaveRoom_Front& _Other) = delete;
	SaveRoom_Front(SaveRoom_Front&& _Other) noexcept = delete;
	SaveRoom_Front& operator=(const SaveRoom_Front& _Other) = delete;
	SaveRoom_Front& operator=(SaveRoom_Front&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

