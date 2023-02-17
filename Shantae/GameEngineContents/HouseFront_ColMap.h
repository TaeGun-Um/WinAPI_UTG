#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class HouseFront_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	HouseFront_ColMap();
	~HouseFront_ColMap();

	// delete Function
	HouseFront_ColMap(const HouseFront_ColMap& _Other) = delete;
	HouseFront_ColMap(HouseFront_ColMap&& _Other) noexcept = delete;
	HouseFront_ColMap& operator=(const HouseFront_ColMap& _Other) = delete;
	HouseFront_ColMap& operator=(HouseFront_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

