#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class Spa_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Spa_ColMap();
	~Spa_ColMap();

	// delete Function
	Spa_ColMap(const Spa_ColMap& _Other) = delete;
	Spa_ColMap(Spa_ColMap&& _Other) noexcept = delete;
	Spa_ColMap& operator=(const Spa_ColMap& _Other) = delete;
	Spa_ColMap& operator=(Spa_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

