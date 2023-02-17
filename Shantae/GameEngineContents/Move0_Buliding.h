#pragma once

#include <GameEngineCore/GameEngineActor.h>

// 설명 : Move0 전경
class Move0_Buliding : public GameEngineActor
{
public:
	// constrcuter destructer
	Move0_Buliding();
	~Move0_Buliding();

	// delete Function
	Move0_Buliding(const Move0_Buliding& _Other) = delete;
	Move0_Buliding(Move0_Buliding&& _Other) noexcept = delete;
	Move0_Buliding& operator=(const Move0_Buliding& _Other) = delete;
	Move0_Buliding& operator=(Move0_Buliding&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

