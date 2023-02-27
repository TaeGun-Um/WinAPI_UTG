#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Mayor_Scuttlebutt : public GameEngineActor
{
public:
	// constrcuter destructer
	Mayor_Scuttlebutt();
	~Mayor_Scuttlebutt();

	// delete Function
	Mayor_Scuttlebutt(const Mayor_Scuttlebutt& _Other) = delete;
	Mayor_Scuttlebutt(Mayor_Scuttlebutt&& _Other) noexcept = delete;
	Mayor_Scuttlebutt& operator=(const Mayor_Scuttlebutt& _Other) = delete;
	Mayor_Scuttlebutt& operator=(Mayor_Scuttlebutt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DirCheck();

	GameEngineRender* AnimationRender = nullptr;
	bool MoveDirect = true; // true = Left, false = Right

};

