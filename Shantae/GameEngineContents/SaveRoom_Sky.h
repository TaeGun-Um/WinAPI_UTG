#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SaveRoom_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	SaveRoom_Sky();
	~SaveRoom_Sky();

	// delete Function
	SaveRoom_Sky(const SaveRoom_Sky& _Other) = delete;
	SaveRoom_Sky(SaveRoom_Sky&& _Other) noexcept = delete;
	SaveRoom_Sky& operator=(const SaveRoom_Sky& _Other) = delete;
	SaveRoom_Sky& operator=(SaveRoom_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

