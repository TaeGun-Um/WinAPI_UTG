#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� ���ڼ�
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

