
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

// �����Ҵ��� ������ �Է��� Render�� list�� �׷�ȭ�ؼ� Ǫ����
void GameEngineLevel::PushRender(GameEngineRender* _Render)
{
	if (nullptr == _Render)
	{
		MsgAssert("nullptr�� ������ ������ �׷�ӿ� �������� �߽��ϴ�.");
	}

	// �׷����� ����
	Renders[_Render->GetOrder()].push_back(_Render);
}

// �����Ҵ��� ������ �Է��� Collision�� list�� �׷�ȭ�ؼ� Ǫ����
void GameEngineLevel::PushCollision(GameEngineCollision* _Collision, int _ChangeOrder)
{
	Collisions[_Collision->GetOrder()].remove(_Collision);

	_Collision->GameEngineObject::SetOrder(_ChangeOrder);

	if (nullptr == _Collision)
	{
		MsgAssert("nullptr�� �浹ü�� �浹 �׷�ӿ� �������� �߽��ϴ�.");
	}

	// ���� �̹� ���������� �ִ�.
	Collisions[_Collision->GetOrder()].push_back(_Collision);
}

// �����Ҵ�� Actor�� data �Է�
void GameEngineLevel::ActorStart(GameEngineActor* _Actor, int _Order)
{
	if (nullptr == _Actor)
	{
		MsgAssert("nullptr ���͸� Start�Ϸ��� �߽��ϴ�.");
		return;
	}
	_Actor->SetOwner(this);   // ȣ���� Level�� Owner�� ����
	_Actor->SetOrder(_Order); // index ��ȣ�� �� ���� �Է�
	_Actor->Start();          // ����� Actor�� Start ��
}

// ����� Actor->Update ��, Actor�� Position setting
void GameEngineLevel::ActorsUpdate(float _DeltaTime)
{
	{
		// GELevel map : ����� Actor�� Update ��
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
				Actor->LiveTime += _DeltaTime;
				Actor->Update(_DeltaTime); // Actor Pos SetMove
			}
		}
	}

	{
		// GELevel map : ����� Actor�� LateUpdate �� (���� �Ⱦ�)
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
				Actor->LateUpdate(_DeltaTime);
			}
		}
	}
}

// Actor->Render->Render, Actor->Render ��, Actor�� �̹��� ������
void GameEngineLevel::ActorsRender(float _DeltaTime)
{
	{
		// GELevel map : GERender�� Render ��
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
				Renderer->Render(_DeltaTime); // Render Pos setting, Transcopy ��
			}
		}
	}

	{
		// GELevel map : ����� Actor�� Render ��
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

	// CollisionDebugRender 0202 �浹ü ������ ����
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

	// �����е��� text ���
	{
		TextOutStart = float4::Zero;

		for (size_t i = 0; i < DebugTexts.size(); i++)
		{
			// 250�� 0216 ���� �߰��Ѱ�
			HDC ImageDc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
			TextOutA(ImageDc, TextOutStart.ix() + 250, TextOutStart.iy(), DebugTexts[i].c_str(), static_cast<int>(DebugTexts[i].size()));
			TextOutStart.y += 20.0f;
		}

		DebugTexts.clear();
	}
}

// ��ȣ�ۿ� �� �޸� �������� �Ұ��ؾ� �ϴ� Actor, Render, Collision�� ó���ϴ� ����
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