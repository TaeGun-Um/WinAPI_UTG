#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class Move0_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Move0_ColMap();
	~Move0_ColMap();

	// delete Function
	Move0_ColMap(const Move0_ColMap& _Other) = delete;
	Move0_ColMap(Move0_ColMap&& _Other) noexcept = delete;
	Move0_ColMap& operator=(const Move0_ColMap& _Other) = delete;
	Move0_ColMap& operator=(Move0_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

