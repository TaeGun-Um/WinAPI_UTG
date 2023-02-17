#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Smith_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Smith_Background();
	~Smith_Background();

	// delete Function
	Smith_Background(const Smith_Background& _Other) = delete;
	Smith_Background(Smith_Background&& _Other) noexcept = delete;
	Smith_Background& operator=(const Smith_Background& _Other) = delete;
	Smith_Background& operator=(Smith_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

