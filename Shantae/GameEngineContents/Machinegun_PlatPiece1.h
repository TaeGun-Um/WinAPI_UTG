#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

// Ό³Έν :
class Machinegun_PlatPiece1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Machinegun_PlatPiece1();
	~Machinegun_PlatPiece1();

	// delete Function
	Machinegun_PlatPiece1(const Machinegun_PlatPiece1& _Other) = delete;
	Machinegun_PlatPiece1(Machinegun_PlatPiece1&& _Other) noexcept = delete;
	Machinegun_PlatPiece1& operator=(const Machinegun_PlatPiece1& _Other) = delete;
	Machinegun_PlatPiece1& operator=(Machinegun_PlatPiece1&& _Other) noexcept = delete;

	void SetOwnerPos(float4 _OwnerPos)
	{
		OwnerPos = _OwnerPos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	void DirectCheckForKill();
	void MoveCalculation(float _DeltaTime);
	void Kill();

	GameEngineRender* AnimationRender = nullptr;

	float4 MoveDir = float4::Zero;
	float4 OwnerPos = float4::Zero;

};

