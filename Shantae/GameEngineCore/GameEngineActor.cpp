#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor() 
{
}

// Render�� Collision ���� å���� Actor���� �ֱ� ������ ���⼭ ������ delete ���ش�
GameEngineActor::~GameEngineActor() 
{
	for (GameEngineRender* _Render : RenderList)
	{
		if (nullptr == _Render)
		{
			continue;
		}

		delete _Render;
		_Render = nullptr;
	}

	for (GameEngineCollision* _Collision : CollisionList)
	{
		if (nullptr == _Collision)
		{
			continue;
		}

		delete _Collision;
		_Collision = nullptr;
	}
}

// �ڽ��� Parent ���� ȹ��
GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}

// Render �̹����ε� (�Ʒ��Լ� ���� ��)
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order)
{
	GameEngineRender* Render = CreateRender(_Order); // �Ʒ� �Լ� ȣ��

	Render->SetImage(_Image); // GEResource.map �� ����� �̹����� ã�� �ڽ��� �̹����� ����

	return Render;
}

// Render ����(�����Ҵ�) �� GELevel.map, GEActor.list �� data ����
GameEngineRender* GameEngineActor::CreateRender(int _Order)
{
	GameEngineRender* Render = new GameEngineRender();

	Render->SetOwner(this);       // Owner�� ȣ���� Actor
	Render->SetOrder(_Order);     // GELevel�� map�� Group���� ����
	RenderList.push_back(Render); // GEActor.list�� ����

	return Render;
}

// Collision ����(�����Ҵ�) �� GELevel.map, GEActor.list �� data ����
GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
	GameEngineCollision* Collision = new GameEngineCollision();

	Collision->SetOwner(this);           // Owner�� ȣ���� Actor
	Collision->SetOrder(_GroupIndex);    // GELevel�� map�� Group���� ����
	CollisionList.push_back(Collision);  // GEActor.list�� ����

	return Collision;
}

void GameEngineActor::Release()
{
	{
		std::list<GameEngineRender*>::iterator StartIter = RenderList.begin();
		std::list<GameEngineRender*>::iterator EndIter = RenderList.end();

		for (; StartIter != EndIter; )
		{
			GameEngineRender* ReleaseRender = *StartIter;

			if (nullptr == ReleaseRender)
			{
				MsgAssert("nullptr �� ������ ���ο� ����ֽ��ϴ�.");
			}

			if (false == ReleaseRender->IsDeath())
			{
				++StartIter;
				continue;
			}

			StartIter = RenderList.erase(StartIter);

			delete ReleaseRender;
			ReleaseRender = nullptr;
		}
	}
	{
		std::list<GameEngineCollision*>::iterator StartIter = CollisionList.begin();
		std::list<GameEngineCollision*>::iterator EndIter = CollisionList.end();

		for (; StartIter != EndIter; )
		{
			GameEngineCollision* ReleaseCollision = *StartIter;

			if (nullptr == ReleaseCollision)
			{
				MsgAssert("nullptr �� ������ ���ο� ����ֽ��ϴ�.");
			}

			if (false == ReleaseCollision->IsDeath())
			{
				++StartIter;
				continue;
			}

			StartIter = CollisionList.erase(StartIter);

			delete ReleaseCollision;
			ReleaseCollision = nullptr;
		}
	}
}