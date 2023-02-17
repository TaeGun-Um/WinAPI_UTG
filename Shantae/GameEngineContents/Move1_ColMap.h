#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class Move1_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;

	// constrcuter destructer
	Move1_ColMap();
	~Move1_ColMap();

	// delete Function
	Move1_ColMap(const Move1_ColMap& _Other) = delete;
	Move1_ColMap(Move1_ColMap&& _Other) noexcept = delete;
	Move1_ColMap& operator=(const Move1_ColMap& _Other) = delete;
	Move1_ColMap& operator=(Move1_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

