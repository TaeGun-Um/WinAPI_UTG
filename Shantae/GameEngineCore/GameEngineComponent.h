#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// 설명 : GERender에서 너무 많은 기능을 담당하고 있고, GECollision과 기능이 겹치기 때문에 둘을 상속하기 위한 클래스
class GameEngineActor;
class GameEngineComponent : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineComponent();
	~GameEngineComponent();

	// delete Function
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

	// Render, Collision 위치 정보 획득
	inline float4 GetPosition()
	{
		return Position;
	}

	// Render, Collision 위치 결정
	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	// Render, Collision 위치 이동
	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	// Render, Collision 크기 정보 획득
	inline float4 GetScale()
	{
		return Scale;
	}

	// Render, Collision 크기 결정
	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	// 자신을 소유하는 Actor 정보 획득
	GameEngineActor* GetActor();

	// 자신을 소유하는 Actor와 자신의 거리 차이
	float4 GetActorPlusPos();

protected:

private:
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;

};

