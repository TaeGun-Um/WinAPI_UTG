#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
class Smith_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Smith_ColMap();
	~Smith_ColMap();

	// delete Function
	Smith_ColMap(const Smith_ColMap& _Other) = delete;
	Smith_ColMap(Smith_ColMap&& _Other) noexcept = delete;
	Smith_ColMap& operator=(const Smith_ColMap& _Other) = delete;
	Smith_ColMap& operator=(Smith_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

