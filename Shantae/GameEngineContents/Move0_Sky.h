#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ¼³¸í : Move0ÀÇ ÇÏ´Ã
class Move0_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Move0_Sky();
	~Move0_Sky();

	// delete Function
	Move0_Sky(const Move0_Sky& _Other) = delete;
	Move0_Sky(Move0_Sky&& _Other) noexcept = delete;
	Move0_Sky& operator=(const Move0_Sky& _Other) = delete;
	Move0_Sky& operator=(Move0_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:

};

