#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다
class HouseFront_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_Sea();
	~HouseFront_Sea();

	// delete Function
	HouseFront_Sea(const HouseFront_Sea& _Other) = delete;
	HouseFront_Sea(HouseFront_Sea&& _Other) noexcept = delete;
	HouseFront_Sea& operator=(const HouseFront_Sea& _Other) = delete;
	HouseFront_Sea& operator=(HouseFront_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

