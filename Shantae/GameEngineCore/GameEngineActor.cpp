#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineActor::GameEngineActor() 
{
}

// Render와 Collision 생성 책임은 Actor에게 있기 때문에 여기서 데이터 delete 해준다
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

// 자신의 Parent 정보 획득
GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetOwner<GameEngineLevel>();
}

// Render 이미지로드 (아래함수 실행 후)
GameEngineRender* GameEngineActor::CreateRender(const std::string_view& _Image, int _Order)
{
	GameEngineRender* Render = CreateRender(_Order); // 아래 함수 호출

	Render->SetImage(_Image); // GEResource.map 에 저장된 이미지를 찾아 자신의 이미지로 설정

	return Render;
}

// Render 생성(동적할당) 후 GELevel.map, GEActor.list 에 data 저장
GameEngineRender* GameEngineActor::CreateRender(int _Order)
{
	GameEngineRender* Render = new GameEngineRender();

	Render->SetOwner(this);       // Owner는 호출한 Actor
	Render->SetOrder(_Order);     // GELevel의 map에 Group으로 저장
	RenderList.push_back(Render); // GEActor.list에 저장

	return Render;
}

// Collision 생성(동적할당) 후 GELevel.map, GEActor.list 에 data 저장
GameEngineCollision* GameEngineActor::CreateCollision(int _GroupIndex)
{
	GameEngineCollision* Collision = new GameEngineCollision();

	Collision->SetOwner(this);           // Owner는 호출한 Actor
	Collision->SetOrder(_GroupIndex);    // GELevel의 map에 Group으로 저장
	CollisionList.push_back(Collision);  // GEActor.list에 저장

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
				MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
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
				MsgAssert("nullptr 인 랜더가 내부에 들어있습니다.");
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