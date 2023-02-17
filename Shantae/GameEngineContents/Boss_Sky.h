#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Boss_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_Sky();
	~Boss_Sky();

	// delete Function
	Boss_Sky(const Boss_Sky& _Other) = delete;
	Boss_Sky(Boss_Sky&& _Other) noexcept = delete;
	Boss_Sky& operator=(const Boss_Sky& _Other) = delete;
	Boss_Sky& operator=(Boss_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

