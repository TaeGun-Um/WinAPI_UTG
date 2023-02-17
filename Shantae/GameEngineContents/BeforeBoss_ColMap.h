#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
class BeforeBoss_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;
	// constrcuter destructer
	BeforeBoss_ColMap();
	~BeforeBoss_ColMap();

	// delete Function
	BeforeBoss_ColMap(const BeforeBoss_ColMap& _Other) = delete;
	BeforeBoss_ColMap(BeforeBoss_ColMap&& _Other) noexcept = delete;
	BeforeBoss_ColMap& operator=(const BeforeBoss_ColMap& _Other) = delete;
	BeforeBoss_ColMap& operator=(BeforeBoss_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

