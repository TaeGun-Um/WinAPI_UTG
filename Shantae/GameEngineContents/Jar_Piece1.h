#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Jar_Piece1 : public GameEngineActor
{
public:
	// constrcuter destructer
	Jar_Piece1();
	~Jar_Piece1();

	// delete Function
	Jar_Piece1(const Jar_Piece1& _Other) = delete;
	Jar_Piece1(Jar_Piece1&& _Other) noexcept = delete;
	Jar_Piece1& operator=(const Jar_Piece1& _Other) = delete;
	Jar_Piece1& operator=(Jar_Piece1&& _Other) noexcept = delete;

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

	bool IsStart = true;

};

