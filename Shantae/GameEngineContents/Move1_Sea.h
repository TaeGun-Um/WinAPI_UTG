#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : Move1 바다
class Move1_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Move1_Sea();
	~Move1_Sea();

	// delete Function
	Move1_Sea(const Move1_Sea& _Other) = delete;
	Move1_Sea(Move1_Sea&& _Other) noexcept = delete;
	Move1_Sea& operator=(const Move1_Sea& _Other) = delete;
	Move1_Sea& operator=(Move1_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

