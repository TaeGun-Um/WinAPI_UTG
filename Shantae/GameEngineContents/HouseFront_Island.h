#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class HouseFront_Island : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_Island();
	~HouseFront_Island();

	// delete Function
	HouseFront_Island(const HouseFront_Island& _Other) = delete;
	HouseFront_Island(HouseFront_Island&& _Other) noexcept = delete;
	HouseFront_Island& operator=(const HouseFront_Island& _Other) = delete;
	HouseFront_Island& operator=(HouseFront_Island&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

