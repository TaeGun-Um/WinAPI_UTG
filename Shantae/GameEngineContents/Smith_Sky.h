#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Smith_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Smith_Sky();
	~Smith_Sky();

	// delete Function
	Smith_Sky(const Smith_Sky& _Other) = delete;
	Smith_Sky(Smith_Sky&& _Other) noexcept = delete;
	Smith_Sky& operator=(const Smith_Sky& _Other) = delete;
	Smith_Sky& operator=(Smith_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

