#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/NumberRenderObject.h>

// Ό³Έν :
class Machinegun_Bulletmarks : public GameEngineActor
{
public:
	// constrcuter destructer
	Machinegun_Bulletmarks();
	~Machinegun_Bulletmarks();

	// delete Function
	Machinegun_Bulletmarks(const Machinegun_Bulletmarks& _Other) = delete;
	Machinegun_Bulletmarks(Machinegun_Bulletmarks&& _Other) noexcept = delete;
	Machinegun_Bulletmarks& operator=(const Machinegun_Bulletmarks& _Other) = delete;
	Machinegun_Bulletmarks& operator=(Machinegun_Bulletmarks&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

};

