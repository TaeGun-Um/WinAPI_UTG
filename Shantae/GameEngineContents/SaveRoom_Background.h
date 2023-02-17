#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SaveRoom_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	SaveRoom_Background();
	~SaveRoom_Background();

	// delete Function
	SaveRoom_Background(const SaveRoom_Background& _Other) = delete;
	SaveRoom_Background(SaveRoom_Background&& _Other) noexcept = delete;
	SaveRoom_Background& operator=(const SaveRoom_Background& _Other) = delete;
	SaveRoom_Background& operator=(SaveRoom_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

