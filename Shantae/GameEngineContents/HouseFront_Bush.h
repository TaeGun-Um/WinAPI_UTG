#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 수풀
class HouseFront_Bush : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_Bush();
	~HouseFront_Bush();

	// delete Function
	HouseFront_Bush(const HouseFront_Bush& _Other) = delete;
	HouseFront_Bush(HouseFront_Bush&& _Other) noexcept = delete;
	HouseFront_Bush& operator=(const HouseFront_Bush& _Other) = delete;
	HouseFront_Bush& operator=(HouseFront_Bush&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

