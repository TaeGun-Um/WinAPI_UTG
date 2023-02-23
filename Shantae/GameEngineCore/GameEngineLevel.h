#pragma once

#include <list>
#include <map>
#include <vector>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineObject.h>

class GameEngineCore;
class GameEngineActor;
class GameEngineRender;
class GameEngineCollision;      // friend�� ���漱�� �ʿ�

// ���� : �߻� Ŭ����. Actor(ĳ����, ����, ���, ������Ʈ)���� list�� �����Ѵ�.
class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;
	friend GameEngineCollision; // Collision�� �������ִ� �Լ��� public���� �����, �ܺο� ����� ���� �ִ�. ���⼭ friend�� �ǵ� GECollision���� �ٷ� ����ϵ��� ��
	                            // Render�� ��������. ���� �̷������� �������� �ʰ� PushRender, PushCollision�� �ܺη� ����Ǹ� �������� ���Ƿ� ���� ������ �� �ִ�.

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	static void DebugRenderSwitch()
	{
		IsDebugRender = !IsDebugRender;
	}

	static void DebugTextPush(const std::string& _DebugText)
	{
		DebugTexts.push_back(_DebugText);
	}

	float4 GetMousePos();
	float4 GetMousePosToCamera();

	// ������ ī�޶� ��ġ ȹ��
	float4 GetCameraPos()
	{
		return CameraPos;
	}

	// ������ ī�޶� ��ġ ����
	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	// ������ ī�޶� ��ġ �̵�
	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}

	// Actor ����(�����Ҵ�)
	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();
		ActorStart(Actor, _Order);
		Actors[_Order].push_back(Actor);

		return dynamic_cast<ActorType*>(Actor);
	}

	template<typename ConvertType>
	std::vector<ConvertType*> GetConvertActors(int _GroupIndex)
	{
		// vector�� �����ϴ� ������ ���� ��Ƽ� �������ֱ� ����(reserve())
		// list ���� �Լ��� ���� ��, Actors[_index] ���·� ���� �����ϸ� Level�� ���� Actors�� ���� �ܺη� �������ִ� ���°� �ȴ�.
		// �̰� �ܺο��� clear() �Ѵٸ�, ���� ���� �� ����
		std::vector<ConvertType*> Result;

		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

			if (nullptr == ConvertType)
			{
				MsgAssert("����Ʈ �Ҽ� ���� ��ȯ�Դϴ�.");
			}

			Result.push_back(ConvertPtr);
		}

		return Result;
	}

	// Enum���� �����ص� �Ʒ� �Լ� ����ǵ��� ����
	template<typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex)
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}

	// �׷����� ������ ���͵��� �����´�
	std::vector<GameEngineActor*> GetActors(int _GroupIndex)
	{
		std::vector<GameEngineActor*> Result;

		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			Result.push_back(ActorPtr);
		}

		return Result;
	}

	// �׷��� �����Ͽ� deletaTime�� �����ϴ� �������̽��� ����
	template<typename EnumType>
	void SetTimeScale(EnumType _GroupIndex, float _Time)
	{
		SetTimeScale(static_cast<int>(_GroupIndex), _Time);
	}

	void SetTimeScale(int _GroupIndex, float _Time)
	{
		TimeScales[_GroupIndex] = _Time;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;   // ���� Level�� �ٸ� Level�� ��ü
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0; // ��ü�� Level�� data Ȱ��

private:
	static float4 TextOutStart;
	static bool IsDebugRender;
	static std::vector<std::string> DebugTexts;

	float4 CameraPos = float4::Zero;                           // ������ ī�޶� Position

	std::map<int, std::list<GameEngineActor*>> Actors;         // ȣ���� Level�� ���ϴ� Actor��
	
	void ActorStart(GameEngineActor* _Actor, int _Order);      // �����Ҵ�� Actor�� data �Է�
	void ActorsUpdate(float _DeltaTime);                       // ����� Actor->Update ��, Actor�� Position setting
	void ActorsRender(float _DeltaTime);                       // Actor->Render->Render, Actor->Render ��, Actor�� �̹��� ������

	// �ܺ� ������ ���� ���� private�� ����, friend�� ���� ����� �� �ֵ��� �ϰ�..
	std::map<int, std::list<GameEngineRender*>> Renders;       // ȣ���� Level�� ���ϴ� Actor�� Render�� (�׷�ȭ)
	void PushRender(GameEngineRender* _Render); 	           // �����Ҵ��� ������ �Է��� Render�� �׷�ȭ�ؼ� list�� Ǫ����

	std::map<int, std::list<GameEngineCollision*>> Collisions; // ȣ���� Level�� ���ϴ� Actor�� Collsion�� (�׷�ȭ)
	void PushCollision(GameEngineCollision* _Collision, int _ChangeOrder);       // �����Ҵ��� ������ �Է��� Collsion�� �׷�ȭ�ؼ� list�� Ǫ����

	void Release();                                            // Rlease ������ ���� ������ ����̱� ������ private(�߿�)

	std::map<int, float> TimeScales; // �׷��� �����Ͽ� deletaTime�� �����ϴ� �������̽��� ����
};
