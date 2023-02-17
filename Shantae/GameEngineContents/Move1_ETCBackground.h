#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : Move1_Map 뒤에 배치되는 오브젝트들
class Move1_ETCBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	Move1_ETCBackground();
	~Move1_ETCBackground();

	// delete Function
	Move1_ETCBackground(const Move1_ETCBackground& _Other) = delete;
	Move1_ETCBackground(Move1_ETCBackground&& _Other) noexcept = delete;
	Move1_ETCBackground& operator=(const Move1_ETCBackground& _Other) = delete;
	Move1_ETCBackground& operator=(Move1_ETCBackground&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

