#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
class Machinegun_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;
	// constrcuter destructer
	Machinegun_ColMap();
	~Machinegun_ColMap();

	// delete Function
	Machinegun_ColMap(const Machinegun_ColMap& _Other) = delete;
	Machinegun_ColMap(Machinegun_ColMap&& _Other) noexcept = delete;
	Machinegun_ColMap& operator=(const Machinegun_ColMap& _Other) = delete;
	Machinegun_ColMap& operator=(Machinegun_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

