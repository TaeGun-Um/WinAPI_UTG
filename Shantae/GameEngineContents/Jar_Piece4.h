#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Jar_Piece4 : public GameEngineActor
{
public:
	// constrcuter destructer
	Jar_Piece4();
	~Jar_Piece4();

	// delete Function
	Jar_Piece4(const Jar_Piece4& _Other) = delete;
	Jar_Piece4(Jar_Piece4&& _Other) noexcept = delete;
	Jar_Piece4& operator=(const Jar_Piece4& _Other) = delete;
	Jar_Piece4& operator=(Jar_Piece4&& _Other) noexcept = delete;
	
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

