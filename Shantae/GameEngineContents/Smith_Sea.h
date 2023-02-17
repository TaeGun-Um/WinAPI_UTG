#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ���� :
class Smith_Sea : public GameEngineActor
{
public:
	// constrcuter destructer
	Smith_Sea();
	~Smith_Sea();

	// delete Function
	Smith_Sea(const Smith_Sea& _Other) = delete;
	Smith_Sea(Smith_Sea&& _Other) noexcept = delete;
	Smith_Sea& operator=(const Smith_Sea& _Other) = delete;
	Smith_Sea& operator=(Smith_Sea&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

