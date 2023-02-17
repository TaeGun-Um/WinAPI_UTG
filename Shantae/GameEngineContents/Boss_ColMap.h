#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class Boss_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Boss_ColMap();
	~Boss_ColMap();

	// delete Function
	Boss_ColMap(const Boss_ColMap& _Other) = delete;
	Boss_ColMap(Boss_ColMap&& _Other) noexcept = delete;
	Boss_ColMap& operator=(const Boss_ColMap& _Other) = delete;
	Boss_ColMap& operator=(Boss_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

