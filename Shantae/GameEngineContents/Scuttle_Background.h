#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Scuttle_Background : public GameEngineActor
{
public:
	// constrcuter destructer
	Scuttle_Background();
	~Scuttle_Background();

	// delete Function
	Scuttle_Background(const Scuttle_Background& _Other) = delete;
	Scuttle_Background(Scuttle_Background&& _Other) noexcept = delete;
	Scuttle_Background& operator=(const Scuttle_Background& _Other) = delete;
	Scuttle_Background& operator=(Scuttle_Background&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

