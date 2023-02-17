#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
class Scuttle_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Scuttle_ColMap();
	~Scuttle_ColMap();

	// delete Function
	Scuttle_ColMap(const Scuttle_ColMap& _Other) = delete;
	Scuttle_ColMap(Scuttle_ColMap&& _Other) noexcept = delete;
	Scuttle_ColMap& operator=(const Scuttle_ColMap& _Other) = delete;
	Scuttle_ColMap& operator=(Scuttle_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

