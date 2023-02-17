#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� :
class SaveRoom_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	SaveRoom_Sea();
	~SaveRoom_Sea();

	// delete Function
	SaveRoom_Sea(const SaveRoom_Sea& _Other) = delete;
	SaveRoom_Sea(SaveRoom_Sea&& _Other) noexcept = delete;
	SaveRoom_Sea& operator=(const SaveRoom_Sea& _Other) = delete;
	SaveRoom_Sea& operator=(SaveRoom_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

