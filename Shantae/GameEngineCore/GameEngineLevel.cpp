
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineRender.h"
#include "GameEngineCollision.h"

bool GameEngineLevel::IsDebugRender = false;
float4 GameEngineLevel::TextOutStart = float4::Zero;
std::vector<std::string> GameEngineLevel::DebugTexts;

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
	for (std::pair<int, std::list<GameEngineActor*>> UpdateGroup : Actors)
	{
		std::list<GameEngineActor*>& ActorList = UpdateGroup.second;

		for (GameEngineActor* Actor : ActorList)
		{
			if (nullptr != Actor)
			{
				delete Actor;
				Actor = nullptr;
			}
		}
	}
	Actors.clear();
}

float4 GameEngineLevel::GetMousePos()
{
	return GameEngineWindow::GetMousePosition();
}

float4 GameEngineLevel::GetMousePosToCamera()
{
	return GameEngineWindow::GetMousePosition() + CameraPos;
}

// 동적할당후 정보를 입력한 Render를 list에 그룹화해서 푸쉬백
void GameEngineLevel::PushRender(GameEngineRender* _Render)
{
	if (nullptr == _Render)
	{
		MsgAssert("nullptr인 랜더를 랜더링 그룹속에 넣으려고 했습니다.");
	}

	// 그룹으로 저장
	Renders[_Render->GetOrder()].push_back(_Render);
}

// 동적할당후 정보를 입력한 Collision을 list에 그룹화해서 푸쉬백
void GameEngineLevel::PushCollision(GameEngineCollision* _Collision, int _ChangeOrder)
{
	Collisions[_Collision->GetOrder()].remove(_Collision);

	_Collision->GameEngineObject::SetOrder(_ChangeOrder);

	if (nullptr == _Collision)
	{
		MsgAssert("nullptr인 충돌체를 충돌 그룹속에 넣으려고 했습니다.");
	}

	// 먼저 이미 들어가있을수도 있다.
	Collisions[_Collision->GetOrder()].push_back(_Collision);
}

// 동적할당된 Actor에 data 입력
void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr 액터를 Start하려고 했습니다.");
		return;
	}
	_Actor->SetOwner(this);   // 호출한 Level을 Owner로 설정
	_Actor->SetOrder(_Order); // index 번호가 될 숫자 입력
	_Actor->Start();          // 상속한 Actor의 Start 콜
}

// 상속한 Actor->Update 콜, Actor의 Position setting
void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;
			int Order = GroupStartIter->first;
			float CurTimeScale = 1.0f;
			if (TimeScales.end() != TimeScales.find(Order))
			{
				CurTimeScale = TimeScales[Order];
			}

			for (GameEngineActor* Actor : ActorList)
			{
				// Actors.erase()
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}

				Actor->TimeScale = CurTimeScale;
				Actor->LiveTime += _DeltaTime;
				Actor->Update(_DeltaTime * CurTimeScale);
			}
		}
	}
}

// Actor->Render->Render, Actor->Render 콜, Actor의 이미지 랜더링
void GameEngineLevel::ActorsRender(float _DeltaTime)
{
	{
		// GELevel map : GERender의 Render 콜
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			for (GameEngineRender* Renderer : RenderList)
			{
				if (nullptr == Renderer || false == Renderer->IsUpdate())
				{
					continue;
				}
				Renderer->Render(_DeltaTime * Renderer->GetActor()->TimeScale); // Render Pos setting, Transcopy 콜
			}
		}
	}

	{
		// GELevel map : 상속한 Actor의 Render 콜
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			for (GameEngineActor* Actor : ActorList)
			{
				if (nullptr == Actor || false == Actor->IsUpdate())
				{
					continue;
				}
				Actor->Render(_DeltaTime); // Load image HDC + Doubblebuffer HDC
			}
		}
	}

	// 디버그 충돌체(5) 랜더링
	{
		if (true == IsDebugRender)
		{
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
			std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

			for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
			{
				std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;
				std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
				std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

				for (; CollisionIterStart != CollisionIterEnd; ++CollisionIterStart)
				{
					GameEngineCollision* DebugCollision = *CollisionIterStart;
					if (nullptr == DebugCollision || false == DebugCollision->IsUpdate())
					{
						continue;
					}
					DebugCollision->DebugRender();
				}
			}
		}
	}

	// 디버그 텍스트(4) 출력
	{
		TextOutStart = float4::Zero;

		for (size_t i = 0; i < DebugTexts.size(); i++)
		{
			HDC ImageDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();

			// 텍스트 박스 크기
			RECT Rect;
			Rect.left = TextOutStart.ix();
			Rect.top = TextOutStart.iy();
			Rect.right = TextOutStart.ix() + 500;
			Rect.bottom = TextOutStart.iy() + 100;

			DrawTextA(ImageDc, DebugTexts[i].c_str(), static_cast<int>(DebugTexts[i].size()), &Rect, DT_LEFT);
			
			TextOutStart.y += 20.0f;
		}

		DebugTexts.clear();
	}
}

// 상호작용 후 메모리 구조에서 소거해야 하는 Actor, Render, Collision을 처리하는 구조
void GameEngineLevel::Release()
{
	// Collistion delete
	{ 
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupStartIter = Collisions.begin();
		std::map<int, std::list<GameEngineCollision*>>::iterator GroupEndIter = Collisions.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineCollision*>& CollisionList = GroupStartIter->second;

			std::list<GameEngineCollision*>::iterator CollisionIterStart = CollisionList.begin();
			std::list<GameEngineCollision*>::iterator CollisionIterEnd = CollisionList.end();

			for (; CollisionIterStart != CollisionIterEnd; )
			{
				GameEngineCollision* ReleaseCollision = *CollisionIterStart;

				// Actors.erase()
				if (nullptr != ReleaseCollision && false == ReleaseCollision->IsDeath())
				{
					++CollisionIterStart;
					continue;
				}

				CollisionIterStart = CollisionList.erase(CollisionIterStart);
			}
		}
	}

	// Render delete
	{
		std::map<int, std::list<GameEngineRender*>>::iterator GroupStartIter = Renders.begin();
		std::map<int, std::list<GameEngineRender*>>::iterator GroupEndIter = Renders.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineRender*>& RenderList = GroupStartIter->second;

			std::list<GameEngineRender*>::iterator RenderIterStart = RenderList.begin();
			std::list<GameEngineRender*>::iterator RenderIterEnd = RenderList.end();

			for (; RenderIterStart != RenderIterEnd; )
			{
				GameEngineRender* ReleaseRender = *RenderIterStart;

				// Actors.erase()
				if (nullptr != ReleaseRender && false == ReleaseRender->IsDeath())
				{
					++RenderIterStart;
					continue;
				}

				RenderIterStart = RenderList.erase(RenderIterStart);
			}
		}
	}

	// Actor delete
	{ 

		std::map<int, std::list<GameEngineActor*>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<GameEngineActor*>& ActorList = GroupStartIter->second;

			std::list<GameEngineActor*>::iterator ActorIterStart = ActorList.begin();
			std::list<GameEngineActor*>::iterator ActorIterEnd = ActorList.end();

			for (; ActorIterStart != ActorIterEnd; )
			{
				GameEngineActor* ReleaseActor = *ActorIterStart;

				// Actors.erase()
				if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
				{
					ReleaseActor->Release(); // 0202
					++ActorIterStart;
					continue;
				}

				ActorIterStart = ActorList.erase(ActorIterStart);

				delete ReleaseActor;
				ReleaseActor = nullptr;
			}
		}
	}
}