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
class GameEngineCollision;      // friend는 전방선언 필요

// 설명 : 추상 클래스. Actor(캐릭터, 몬스터, 배경, 오브젝트)들을 list에 저장한다.
class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;
	friend GameEngineCollision; // Collision을 리턴해주는 함수를 public으로 만들면, 외부에 유출될 수도 있다. 여기서 friend를 건뒤 GECollision에서 바로 사용하도록 함
	                            // Render도 마찬가지. 만약 이런식으로 구성하지 않고 PushRender, PushCollision이 외부로 유출되면 누군가는 임의로 값을 변경할 수 있다.

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

	// 레벨의 카메라 위치 획득
	float4 GetCameraPos()
	{
		return CameraPos;
	}

	// 레벨의 카메라 위치 결정
	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	// 레벨의 카메라 위치 이동
	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	template<typename ActorType, typename EnumType>
	ActorType* CreateActor(EnumType _Order)
	{
		return CreateActor<ActorType>(static_cast<int>(_Order));
	}

	// Actor 생성(동적할당)
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
		// vector로 리턴하는 이유는 따로 담아서 리턴해주기 위함(reserve())
		// list 리턴 함수로 만든 뒤, Actors[_index] 형태로 값을 리턴하면 Level이 지닌 Actors의 값을 외부로 리턴해주는 형태가 된다.
		// 이걸 외부에서 clear() 한다면, 답이 없을 수 있음
		std::vector<ConvertType*> Result;

		std::list<GameEngineActor*>& Group = Actors[_GroupIndex];
		Result.reserve(Group.size());

		for (GameEngineActor* ActorPtr : Group)
		{
			ConvertType* ConvertPtr = dynamic_cast<ConvertType*>(ActorPtr);

			if (nullptr == ConvertType)
			{
				MsgAssert("컨버트 할수 없는 변환입니다.");
			}

			Result.push_back(ConvertPtr);
		}

		return Result;
	}

	// Enum으로 적용해도 아래 함수 실행되도록 설정
	template<typename EnumType>
	std::vector<GameEngineActor*> GetActors(EnumType _GroupIndex)
	{
		return GetActors(static_cast<int>(_GroupIndex));
	}

	// 그룹으로 지정한 액터들을 가져온다
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

	// 그룹을 지정하여 deletaTime을 조정하는 인터페이스로 설계
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
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;   // 현재 Level을 다른 Level로 교체
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0; // 교체된 Level의 data 활용

private:
	static float4 TextOutStart;
	static bool IsDebugRender;
	static std::vector<std::string> DebugTexts;

	float4 CameraPos = float4::Zero;                           // 레벨의 카메라 Position

	std::map<int, std::list<GameEngineActor*>> Actors;         // 호출한 Level이 지니는 Actor들
	
	void ActorStart(GameEngineActor* _Actor, int _Order);      // 동적할당된 Actor에 data 입력
	void ActorsUpdate(float _DeltaTime);                       // 상속한 Actor->Update 콜, Actor의 Position setting
	void ActorsRender(float _DeltaTime);                       // Actor->Render->Render, Actor->Render 콜, Actor의 이미지 랜더링

	// 외부 유출을 막기 위해 private로 막고, friend를 통해 사용할 수 있도록 하고..
	std::map<int, std::list<GameEngineRender*>> Renders;       // 호출한 Level이 지니는 Actor의 Render들 (그룹화)
	void PushRender(GameEngineRender* _Render); 	           // 동적할당후 정보를 입력한 Render를 그룹화해서 list에 푸쉬백

	std::map<int, std::list<GameEngineCollision*>> Collisions; // 호출한 Level이 지니는 Actor의 Collsion들 (그룹화)
	void PushCollision(GameEngineCollision* _Collision, int _ChangeOrder);       // 동적할당후 정보를 입력한 Collsion를 그룹화해서 list에 푸쉬백

	void Release();                                            // Rlease 구조는 엔진 수준의 기능이기 때문에 private(중요)

	std::map<int, float> TimeScales; // 그룹을 지정하여 deletaTime을 조정하는 인터페이스로 설계
};
