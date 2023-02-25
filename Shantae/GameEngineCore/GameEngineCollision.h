#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineComponent.h"

// switch로 정해도 되지만, 하나가 추가되면 굉장한 수정을 거쳐야 한다.
// 따라서 함수 포인터 배열로 활용하기 위해 enum 활용
// enum class는 캐스팅이 강제되기 때문에, 간단한 코드이지만 너무 길어져서 그냥 enum으로 했다.
enum CollisionType
{
	CT_Point,
	CT_CirCle,
	CT_Rect,
	CT_Max,
};

// Collision 함수 인자 클래스
class CollisionCheckParameter
{
public:
	int TargetGroup = -342367842;                           // 제대로 입력 안하면 터질만한 값으로 초기화
	CollisionType TargetColType = CollisionType::CT_CirCle; // 충돌할 대상 Collition type
	CollisionType ThisColType = CollisionType::CT_CirCle;   // 자신의 Collistion type
};

// 설명 :
class CollisionFunctionInit;
class GameEngineCollision : public GameEngineComponent
{
	friend CollisionFunctionInit; // 전역 선언을 위한 friend, 또한 GameEngineCollision:: 하면 종류가 나오도록 하기 위함

private:

public:
	// Collision 도형 종류 함수는 계속해서 추가할 예정
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
	
	// Collision 정보를 GELevel.Collisions에 그룹화하여 저장
	void SetOrder(int _Order) override;

	// Collision의 충돌 데이터 획득
	CollisionData GetCollisionData();

	// 단순하게 충돌 했다는 것만 알려주는 기능
	bool Collision(const CollisionCheckParameter& _CollisionCheck);

	bool Collision(const CollisionCheckParameter& _CollisionCheck, std::vector<GameEngineCollision*>& _Collision);

	// Collision 충돌 형태 변경
	void DebugRender();

	// Collision 충돌 형태 직접 변경
	void SetDebugRenderType(CollisionType _DebugRenderType)
	{
		DebugRenderType = _DebugRenderType;
	}

protected:

private:
	// 특정 충돌체로 보고싶다면 랜더링하기전에 호출해서 값을 고정하도록 한다. (SetDebugRenderType())
	CollisionType DebugRenderType = CollisionType::CT_CirCle;

};

