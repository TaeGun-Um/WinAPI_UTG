#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 건물
class HouseFront_Building : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_Building();
	~HouseFront_Building();

	// delete Function
	HouseFront_Building(const HouseFront_Building& _Other) = delete;
	HouseFront_Building(HouseFront_Building&& _Other) noexcept = delete;
	HouseFront_Building& operator=(const HouseFront_Building& _Other) = delete;
	HouseFront_Building& operator=(HouseFront_Building&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

