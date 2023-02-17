#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Scuttle_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Scuttle_Sea();
	~Scuttle_Sea();

	// delete Function
	Scuttle_Sea(const Scuttle_Sea& _Other) = delete;
	Scuttle_Sea(Scuttle_Sea&& _Other) noexcept = delete;
	Scuttle_Sea& operator=(const Scuttle_Sea& _Other) = delete;
	Scuttle_Sea& operator=(Scuttle_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

