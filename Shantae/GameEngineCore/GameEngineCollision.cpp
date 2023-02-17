
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>

#include "GameEngineCollision.h"
#include "GameEngineActor.h" // 메모리 삭제 권한을 가진건 액터지만
#include "GameEngineLevel.h" // 모든 Collision을 관리하고 있는건 Level

// 함수 포인터 배열 (switch를 활용하지 않아도 되는 좋은 방법)
// CT_Max로 설정하면 종류가 늘때마다 배열 크기도 알아서 늘어남
static bool(*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);

// 편법인데, 전역에 선언해두면 무조건 만들어지고 main이 실행되기도 전에 생성자가 호출된다
// 그리고 여기에 선언하면 있는지 없는지도 알 수 없음
class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		// 함수 포인터 생성, 초기화
		ColFunctionPtr[CT_CirCle][CT_CirCle] = GameEngineCollision::CollisionCirCleToCirCle;
		ColFunctionPtr[CT_CirCle][CT_Point] = GameEngineCollision::CollisionCirCleToPoint;
		ColFunctionPtr[CT_Rect][CT_Rect] = GameEngineCollision::CollisionRectToRect;
		ColFunctionPtr[CT_Rect][CT_Point] = GameEngineCollision::CollisionRectToPoint;
	}
	~CollisionFunctionInit()
	{

	}
};
CollisionFunctionInit Init = CollisionFunctionInit();

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

// Collision 정보를 GELevel.Collisions에 그룹화하여 저장
void GameEngineCollision::SetOrder(int _Order)
{
	// 상속받은 것은 부모가 이미 가지고 있을 수 있기 때문에 호출해주는 것이 좋다.
	// 실제로는 Object인데 호출하면 부모까지 타고 올라간다.
	// GELevel에 그룹화해서 푸쉬백
	GetActor()->GetLevel()->PushCollision(this, _Order);
}

// Collision의 충돌 데이터 획득
CollisionData GameEngineCollision::GetCollisionData()
{
	return { GetActorPlusPos(), GetScale() };
}

// 원과 점 충돌
bool GameEngineCollision::CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();
	float RadiusSum = _Left.Scale.hx();
	return RadiusSum > Size;
}

// 원과 원 충돌
bool GameEngineCollision::CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
	// 두 Position 간의 거리를 알아낼 수 있음
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();

	// 둘의 반지름을 더한 것
	float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();

	// 둘의 반지름 길이가 둘 사이의 거리보다 커지면 충돌(원충돌)
	return RadiusSum > Size;
}

// 사각형과 점 충돌
bool GameEngineCollision::CollisionRectToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Position.y)
	{
		return false;
	}
	if (_Left.Top() >= _Right.Position.y)
	{
		return false;
	}
	if (_Left.Left() >= _Right.Position.x)
	{
		return false;
	}
	if (_Left.Right() <= _Right.Position.x)
	{
		return false;
	}

	return true;
}

// 사각형과 사각형 충돌
bool GameEngineCollision::CollisionRectToRect(const CollisionData& _Left, const CollisionData& _Right)
{
	if (_Left.Bot() <= _Right.Top())
	{
		return false;
	}
	if (_Left.Top() >= _Right.Bot())
	{
		return false;
	}
	if (_Left.Left() >= _Right.Right())
	{
		return false;
	}
	if (_Left.Right() <= _Right.Left())
	{
		return false;
	}

	return true;
}

// 단순하게 충돌 했다는 것만 알려주는 기능
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	if (false == IsUpdate())
	{
		return false;
	}

	// 그룹들의 정보를 가져온다.
	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (OtherCollision == this)
		{
			continue;
		}

		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		// 함수 포인터
		// 아직(0201) 원과 원 충돌 상황만 만들었기 때문에 이외에는 예외처리 되도록 함
		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}
		// 충돌이 true면 
		// 단순히 함수 내용만 보면 몬스터가 100마리라도, 그 중 하나만 충돌해도 충돌인 것으로 설정
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}
	// 모든 것을 다 비교했는데 없었으면 false
	return false;
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	if (false == IsUpdate())
	{
		return false;
	}

	// 기존에 뭐가 들어있었건 clear 한 뒤 실행한다.
	// 이전에 충돌했던 것은 무시하고 새롭게 집어넣는 방식의 인터페이스
	_Collision.clear();

	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	// Collision 충돌 형태 변경
	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		// Collision 충돌 형태 변경
		OtherCollision->SetDebugRenderType(OtherType);

		// 함수 포인터
		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("아직 충돌함수를 만들지 않은 충돌 타입입니다");
		}
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			_Collision.push_back(OtherCollision);
		}
	}

	// 0이 아니라면 충돌한 것이 하나라도 있음
	// 0이면 충돌한 것이 하나도 없음
	return _Collision.size() != 0;
}

// Collision 충돌 형태 변경
void GameEngineCollision::DebugRender()
{
	HDC BackBufferDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	float4 DebugRenderPos = GetActorPlusPos() - GetActor()->GetLevel()->GetCameraPos();
	switch (DebugRenderType)
	{
	case CT_Point:
		break;
	case CT_CirCle:
	{
		int Radius = GetScale().hix();
		Ellipse(BackBufferDc,
			DebugRenderPos.ix() - Radius,
			DebugRenderPos.iy() - Radius,
			DebugRenderPos.ix() + Radius,
			DebugRenderPos.iy() + Radius);
		break;
	}
	case CT_Rect:
	{
		Rectangle(BackBufferDc,
			DebugRenderPos.ix() - GetScale().hix(),
			DebugRenderPos.iy() - GetScale().hiy(),
			DebugRenderPos.ix() + GetScale().hix(),
			DebugRenderPos.iy() + GetScale().hiy());
		break;
	}
	case CT_Max:
		break;
	default:
		break;
	}
}