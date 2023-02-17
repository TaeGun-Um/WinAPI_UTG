#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 등대
class HouseFront_LightHouse : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_LightHouse();
	~HouseFront_LightHouse();

	// delete Function
	HouseFront_LightHouse(const HouseFront_LightHouse& _Other) = delete;
	HouseFront_LightHouse(HouseFront_LightHouse&& _Other) noexcept = delete;
	HouseFront_LightHouse& operator=(const HouseFront_LightHouse& _Other) = delete;
	HouseFront_LightHouse& operator=(HouseFront_LightHouse&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

