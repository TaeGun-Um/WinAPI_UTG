#pragma once

#include <list>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

class GameEngineLevel;
class GameEngineRender;
class GameEngineCollision;

// ���� : ��ġ�� �־�� �ϴ� ����, ��ġ�� ������� �̵�, ������
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	// Actor Pos ����
	inline float4 GetPos() const
	{
		return Pos;
	}

	// Actor Pos �Է�
	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	// Actor Pos �̵�
	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	// �ڽ��� Parent ���� ȹ��
	GameEngineLevel* GetLevel();

	// Render ����(�����Ҵ�), GELevel.map, GEActor.list �� ����, ������ �̹��� �ε�
	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
	GameEngineRender* CreateRender(int _Order = 0);

#pragma region CreateRenderEnumOverLoadings

	// �Ʒ� �Լ� ȣ��
	template<typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	// Render �����Ҵ� �� ���� �Է�
	template<typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));
	}

#pragma endregion

	template<typename EnumType>
	GameEngineCollision* CreateCollision(EnumType _GroupIndex)
	{
		return CreateCollision(static_cast<int>(_GroupIndex));
	}

	// Collision ����(�����Ҵ�), GELevel.map, GEActor.list �� ����
	GameEngineCollision* CreateCollision(int _GroupIndex = 0);

protected:
	virtual void Start() {}                      // Loop ���� �� �⺻ �غ���� (��ġ, Ű, ������ �̹��� ��)
	virtual void Update(float _DeltaTime) {}     // Loop �� ��ȭ�� ������ ���� (�̵�, �ִϸ��̼�, ��ȣ�ۿ� ��)
	virtual void LateUpdate(float _DeltaTime) {} // ���� ��� ����
	virtual void Render(float _DeltaTime) {}     // ���� ��� ����

	// Actor ���� �� �ð� ����
	inline float GetLiveTime() const
	{
		return LiveTime;
	}

private:
	GameEngineLevel* Level = nullptr;              // Actor �ڽ��� ��ü (ȣ�� ���)
	float4 Pos             = { 0.0f, 0.0f };       // Actor ��ġ           
	float LiveTime         = 0.0;                  // Actor ���� �� �ð�
	std::list<GameEngineRender*> RenderList;       // ȣ���� Level�� ���ϴ� Actor�� Render��
	std::list<GameEngineCollision*> CollisionList; // ȣ���� Level�� ���ϴ� Actor�� Collision��

	float TimeScale = 0.0; // �׷�ȭ �����Ͽ� DeltaTime�� ����(0222)

	void Release();
};
