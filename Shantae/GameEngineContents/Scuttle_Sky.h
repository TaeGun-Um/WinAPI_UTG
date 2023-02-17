#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Scuttle_Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Scuttle_Sky();
	~Scuttle_Sky();

	// delete Function
	Scuttle_Sky(const Scuttle_Sky& _Other) = delete;
	Scuttle_Sky(Scuttle_Sky&& _Other) noexcept = delete;
	Scuttle_Sky& operator=(const Scuttle_Sky& _Other) = delete;
	Scuttle_Sky& operator=(Scuttle_Sky&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

