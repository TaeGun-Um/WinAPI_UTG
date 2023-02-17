#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
class SkyRoom_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	SkyRoom_ColMap();
	~SkyRoom_ColMap();

	// delete Function
	SkyRoom_ColMap(const SkyRoom_ColMap& _Other) = delete;
	SkyRoom_ColMap(SkyRoom_ColMap&& _Other) noexcept = delete;
	SkyRoom_ColMap& operator=(const SkyRoom_ColMap& _Other) = delete;
	SkyRoom_ColMap& operator=(SkyRoom_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

