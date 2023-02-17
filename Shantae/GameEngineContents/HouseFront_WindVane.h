#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ¼³¸í : Ç³Ç×°è
class HouseFront_WindVane : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_WindVane();
	~HouseFront_WindVane();

	// delete Function
	HouseFront_WindVane(const HouseFront_WindVane& _Other) = delete;
	HouseFront_WindVane(HouseFront_WindVane&& _Other) noexcept = delete;
	HouseFront_WindVane& operator=(const HouseFront_WindVane& _Other) = delete;
	HouseFront_WindVane& operator=(HouseFront_WindVane&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

