#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ¼³¸í : Move1 ÇÏ´Ã
class Move1_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Move1_Sky();
	~Move1_Sky();

	// delete Function
	Move1_Sky(const Move1_Sky& _Other) = delete;
	Move1_Sky(Move1_Sky&& _Other) noexcept = delete;
	Move1_Sky& operator=(const Move1_Sky& _Other) = delete;
	Move1_Sky& operator=(Move1_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

