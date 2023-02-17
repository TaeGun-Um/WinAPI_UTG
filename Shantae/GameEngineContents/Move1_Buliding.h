#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : Move1 전경
class Move1_Buliding : public GameEngineActor
{
public:
	// constrcuter destructer
	Move1_Buliding();
	~Move1_Buliding();

	// delete Function
	Move1_Buliding(const Move1_Buliding& _Other) = delete;
	Move1_Buliding(Move1_Buliding&& _Other) noexcept = delete;
	Move1_Buliding& operator=(const Move1_Buliding& _Other) = delete;
	Move1_Buliding& operator=(Move1_Buliding&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

