#pragma once

#include <GameEngineCore/GameEngineActor.h>

// ¼³¸í : Move0ÀÇ ÇÏ´Ã
class Sky : public GameEngineActor
{
public:
	// constrcuter destructer
	Sky();
	~Sky();

	// delete Function
	Sky(const Sky& _Other) = delete;
	Sky(Sky&& _Other) noexcept = delete;
	Sky& operator=(const Sky& _Other) = delete;
	Sky& operator=(Sky&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

private:

};

