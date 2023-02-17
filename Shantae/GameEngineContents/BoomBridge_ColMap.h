#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : HouseFront의 바다 위 섬
class BoomBridge_ColMap : public GameEngineActor
{
public:
	static GameEngineRender* ColMap;
	// constrcuter destructer
	BoomBridge_ColMap();
	~BoomBridge_ColMap();

	// delete Function
	BoomBridge_ColMap(const BoomBridge_ColMap& _Other) = delete;
	BoomBridge_ColMap(BoomBridge_ColMap&& _Other) noexcept = delete;
	BoomBridge_ColMap& operator=(const BoomBridge_ColMap& _Other) = delete;
	BoomBridge_ColMap& operator=(BoomBridge_ColMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

