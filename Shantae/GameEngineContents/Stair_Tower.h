#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Stair_Tower : public GameEngineActor
{
public:
	// constrcuter destructer
	Stair_Tower();
	~Stair_Tower();

	// delete Function
	Stair_Tower(const Stair_Tower& _Other) = delete;
	Stair_Tower(Stair_Tower&& _Other) noexcept = delete;
	Stair_Tower& operator=(const Stair_Tower& _Other) = delete;
	Stair_Tower& operator=(Stair_Tower&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

