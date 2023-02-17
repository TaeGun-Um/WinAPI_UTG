#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Boss_ETCBackground : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss_ETCBackground();
	~Boss_ETCBackground();

	// delete Function
	Boss_ETCBackground(const Boss_ETCBackground& _Other) = delete;
	Boss_ETCBackground(Boss_ETCBackground&& _Other) noexcept = delete;
	Boss_ETCBackground& operator=(const Boss_ETCBackground& _Other) = delete;
	Boss_ETCBackground& operator=(Boss_ETCBackground&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

