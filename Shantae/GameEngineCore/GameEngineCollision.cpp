
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>

#include "GameEngineCollision.h"
#include "GameEngineActor.h" // �޸� ���� ������ ������ ��������
#include "GameEngineLevel.h" // ��� Collision�� �����ϰ� �ִ°� Level

// �Լ� ������ �迭 (switch�� Ȱ������ �ʾƵ� �Ǵ� ���� ���)
// CT_Max�� �����ϸ� ������ �ö����� �迭 ũ�⵵ �˾Ƽ� �þ
static bool(*ColFunctionPtr[CT_Max][CT_Max])(const CollisionData& _Left, const CollisionData& _Right);

// �����ε�, ������ �����صθ� ������ ��������� main�� ����Ǳ⵵ ���� �����ڰ� ȣ��ȴ�
// �׸��� ���⿡ �����ϸ� �ִ��� �������� �� �� ����
class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		// �Լ� ������ ����, �ʱ�ȭ
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

// Collision ������ GELevel.Collisions�� �׷�ȭ�Ͽ� ����
void GameEngineCollision::SetOrder(int _Order)
{
	// ��ӹ��� ���� �θ� �̹� ������ ���� �� �ֱ� ������ ȣ�����ִ� ���� ����.
	// �����δ� Object�ε� ȣ���ϸ� �θ���� Ÿ�� �ö󰣴�.
	// GELevel�� �׷�ȭ�ؼ� Ǫ����
	GetActor()->GetLevel()->PushCollision(this, _Order);
}

// Collision�� �浹 ������ ȹ��
CollisionData GameEngineCollision::GetCollisionData()
{
	return { GetActorPlusPos(), GetScale() };
}

// ���� �� �浹
bool GameEngineCollision::CollisionCirCleToPoint(const CollisionData& _Left, const CollisionData& _Right)
{
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();
	float RadiusSum = _Left.Scale.hx();
	return RadiusSum > Size;
}

// ���� �� �浹
bool GameEngineCollision::CollisionCirCleToCirCle(const CollisionData& _Left, const CollisionData& _Right)
{
	// �� Position ���� �Ÿ��� �˾Ƴ� �� ����
	float4 Len = _Left.Position - _Right.Position;
	float Size = Len.Size();

	// ���� �������� ���� ��
	float RadiusSum = _Left.Scale.hx() + _Right.Scale.hx();

	// ���� ������ ���̰� �� ������ �Ÿ����� Ŀ���� �浹(���浹)
	return RadiusSum > Size;
}

// �簢���� �� �浹
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

// �簢���� �簢�� �浹
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

// �ܼ��ϰ� �浹 �ߴٴ� �͸� �˷��ִ� ���
bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter)
{
	if (false == IsUpdate())
	{
		return false;
	}

	// �׷���� ������ �����´�.
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

		// �Լ� ������
		// ����(0201) ���� �� �浹 ��Ȳ�� ������� ������ �̿ܿ��� ����ó�� �ǵ��� ��
		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("���� �浹�Լ��� ������ ���� �浹 Ÿ���Դϴ�");
		}
		// �浹�� true�� 
		// �ܼ��� �Լ� ���븸 ���� ���Ͱ� 100������, �� �� �ϳ��� �浹�ص� �浹�� ������ ����
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			return true;
		}
	}
	// ��� ���� �� ���ߴµ� �������� false
	return false;
}

bool GameEngineCollision::Collision(const CollisionCheckParameter& _Parameter, std::vector<GameEngineCollision*>& _Collision)
{
	if (false == IsUpdate())
	{
		return false;
	}

	// ������ ���� ����־��� clear �� �� �����Ѵ�.
	// ������ �浹�ߴ� ���� �����ϰ� ���Ӱ� ����ִ� ����� �������̽�
	_Collision.clear();

	std::list<GameEngineCollision*>& _TargetGroup = GetActor()->GetLevel()->Collisions[_Parameter.TargetGroup];

	// Collision �浹 ���� ����
	SetDebugRenderType(_Parameter.ThisColType);

	for (GameEngineCollision* OtherCollision : _TargetGroup)
	{
		if (false == OtherCollision->IsUpdate())
		{
			continue;
		}

		CollisionType Type = _Parameter.ThisColType;
		CollisionType OtherType = _Parameter.TargetColType;

		// Collision �浹 ���� ����
		OtherCollision->SetDebugRenderType(OtherType);

		// �Լ� ������
		if (nullptr == ColFunctionPtr[Type][OtherType])
		{
			MsgAssert("���� �浹�Լ��� ������ ���� �浹 Ÿ���Դϴ�");
		}
		if (true == ColFunctionPtr[Type][OtherType](GetCollisionData(), OtherCollision->GetCollisionData()))
		{
			_Collision.push_back(OtherCollision);
		}
	}

	// 0�� �ƴ϶�� �浹�� ���� �ϳ��� ����
	// 0�̸� �浹�� ���� �ϳ��� ����
	return _Collision.size() != 0;
}

// Collision �浹 ���� ����
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