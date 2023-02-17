#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 야자수
class HouseFront_PalmTree : public GameEngineActor
{
public:
	// constrcuter destructer
	HouseFront_PalmTree();
	~HouseFront_PalmTree();

	// delete Function
	HouseFront_PalmTree(const HouseFront_PalmTree& _Other) = delete;
	HouseFront_PalmTree(HouseFront_PalmTree&& _Other) noexcept = delete;
	HouseFront_PalmTree& operator=(const HouseFront_PalmTree& _Other) = delete;
	HouseFront_PalmTree& operator=(HouseFront_PalmTree&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

