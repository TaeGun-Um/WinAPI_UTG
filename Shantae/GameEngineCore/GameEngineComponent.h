#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// ���� : GERender���� �ʹ� ���� ����� ����ϰ� �ְ�, GECollision�� ����� ��ġ�� ������ ���� ����ϱ� ���� Ŭ����
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

	// Render, Collision ��ġ ���� ȹ��
	inline float4 GetPosition()
	{
		return Position;
	}

	// Render, Collision ��ġ ����
	inline void SetPosition(float4 _Position)
	{
		Position = _Position;
	}

	// Render, Collision ��ġ �̵�
	inline void SetMove(float4 _Position)
	{
		Position += _Position;
	}

	// Render, Collision ũ�� ���� ȹ��
	inline float4 GetScale()
	{
		return Scale;
	}

	// Render, Collision ũ�� ����
	inline void SetScale(float4 _Scale)
	{
		Scale = _Scale;
	}

	// �ڽ��� �����ϴ� Actor ���� ȹ��
	GameEngineActor* GetActor();

	// �ڽ��� �����ϴ� Actor�� �ڽ��� �Ÿ� ����
	float4 GetActorPlusPos();

protected:

private:
	float4 Position = float4::Zero;
	float4 Scale = float4::Zero;

};

