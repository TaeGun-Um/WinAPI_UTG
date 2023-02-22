#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineResources.h>

class GameEngineImage;

// Ό³Έν :
class Machinegun_PlatPiece2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Machinegun_PlatPiece2();
	~Machinegun_PlatPiece2();

	// delete Function
	Machinegun_PlatPiece2(const Machinegun_PlatPiece2& _Other) = delete;
	Machinegun_PlatPiece2(Machinegun_PlatPiece2&& _Other) noexcept = delete;
	Machinegun_PlatPiece2& operator=(const Machinegun_PlatPiece2& _Other) = delete;
	Machinegun_PlatPiece2& operator=(Machinegun_PlatPiece2&& _Other) noexcept = delete;

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

