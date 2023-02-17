#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Stair_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Stair_Sky();
	~Stair_Sky();

	// delete Function
	Stair_Sky(const Stair_Sky& _Other) = delete;
	Stair_Sky(Stair_Sky&& _Other) noexcept = delete;
	Stair_Sky& operator=(const Stair_Sky& _Other) = delete;
	Stair_Sky& operator=(Stair_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

