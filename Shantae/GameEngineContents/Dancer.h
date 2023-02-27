#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : Player Chracter
class Dancer : public GameEngineActor
{
public:
	// constrcuter destructer
	Dancer();
	~Dancer();

	// delete Function
	Dancer(const Dancer& _Other) = delete;
	Dancer(Dancer&& _Other) noexcept = delete;
	Dancer& operator=(const Dancer& _Other) = delete;
	Dancer& operator=(Dancer&& _Other) noexcept = delete;

	void SetDirect(bool _Is)
	{
		Direct = _Is;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	GameEngineRender* AnimationRender = nullptr;

	bool Direct = false;
	int Set = 1;

};

