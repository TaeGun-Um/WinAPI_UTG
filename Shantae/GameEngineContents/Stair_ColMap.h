#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class Stair_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Stair_ColMap();
	~Stair_ColMap();

	// delete Function
	Stair_ColMap(const Stair_ColMap& _Other) = delete;
	Stair_ColMap(Stair_ColMap&& _Other) noexcept = delete;
	Stair_ColMap& operator=(const Stair_ColMap& _Other) = delete;
	Stair_ColMap& operator=(Stair_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

