#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
class SaveRoom_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	SaveRoom_ColMap();
	~SaveRoom_ColMap();

	// delete Function
	SaveRoom_ColMap(const SaveRoom_ColMap& _Other) = delete;
	SaveRoom_ColMap(SaveRoom_ColMap&& _Other) noexcept = delete;
	SaveRoom_ColMap& operator=(const SaveRoom_ColMap& _Other) = delete;
	SaveRoom_ColMap& operator=(SaveRoom_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

