#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"

// switch�� ���ص� ������, �ϳ��� �߰��Ǹ� ������ ������ ���ľ� �Ѵ�.
// ���� �Լ� ������ �迭�� Ȱ���ϱ� ���� enum Ȱ��
// enum class�� ĳ������ �����Ǳ� ������, ������ �ڵ������� �ʹ� ������� �׳� enum���� �ߴ�.
enum CollisionType
{
	CT_Point,
	CT_CirCle,
	CT_Rect,
	CT_Max,
};

// Collision �Լ� ���� Ŭ����
class CollisionCheckParameter
{
public:
	int TargetGroup = -342367842;                           // ����� �Է� ���ϸ� �������� ������ �ʱ�ȭ
	CollisionType TargetColType = CollisionType::CT_CirCle; // �浹�� ��� Collition type
	CollisionType ThisColType = CollisionType::CT_CirCle;   // �ڽ��� Collistion type
};

// ���� :
class CollisionFunctionInit;
class GameEngineCollision : public GameEngineComponent
{
	friend CollisionFunctionInit; // ���� ������ ���� friend, ���� GameEngineCollision:: �ϸ� ������ �������� �ϱ� ����

private:

public:
	// Collision ���� ���� �Լ��� ����ؼ� �߰��� ����
	static bool CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right);

	static bool CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right);
	static bool CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right);


	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;
	
	// Collision ������ GELevel.Collisions�� �׷�ȭ�Ͽ� ����
	void SetOrder(int _Order) override;

	// Collision�� �浹 ������ ȹ��
	CollisionData GetCollisionData();

	// �ܼ��ϰ� �浹 �ߴٴ� �͸� �˷��ִ� ���
	bool Collision(const CollisionCheckParameter& _CollisionCheck);

	bool Collision(const CollisionCheckParameter& _CollisionCheck, std::vector<GameEngineCollision*>& _Collision);

	// Collision �浹 ���� ����
	void DebugRender();

	// Collision �浹 ���� ���� ����
	void SetDebugRenderType(CollisionType _DebugRenderType)
	{
		DebugRenderType = _DebugRenderType;
	}

protected:

private:
	// Ư�� �浹ü�� ����ʹٸ� �������ϱ����� ȣ���ؼ� ���� �����ϵ��� �Ѵ�. (SetDebugRenderType())
	CollisionType DebugRenderType = CollisionType::CT_CirCle;

};

