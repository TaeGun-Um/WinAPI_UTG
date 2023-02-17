#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� : HouseFront�� �ٴ� �� ��
class UncleRoom_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	UncleRoom_ColMap();
	~UncleRoom_ColMap();

	// delete Function
	UncleRoom_ColMap(const UncleRoom_ColMap& _Other) = delete;
	UncleRoom_ColMap(UncleRoom_ColMap&& _Other) noexcept = delete;
	UncleRoom_ColMap& operator=(const UncleRoom_ColMap& _Other) = delete;
	UncleRoom_ColMap& operator=(UncleRoom_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

