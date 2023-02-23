#pragma once

#include <list>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

class GameEngineLevel;
class GameEngineRender;
class GameEngineCollision;

// 설명 : 위치가 있어야 하는 존재, 위치를 기반으로 이동, 랜더링
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	// Actor Pos 리턴
	inline float4 GetPos() const
	{
		return Pos;
	}

	// Actor Pos 입력
	inline void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	// Actor Pos 이동
	inline void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	// 자신의 Parent 정보 획득
	GameEngineLevel* GetLevel();

	// Render 생성(동적할당), GELevel.map, GEActor.list 에 저장, 랜더할 이미지 로드
	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
	GameEngineRender* CreateRender(int _Order = 0);

#pragma region CreateRenderEnumOverLoadings

	// 아래 함수 호출
	template<typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	// Render 동적할당 후 정보 입력
	template<typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));
	}

#pragma endregion

	template<typename EnumType>
	GameEngineCollision* CreateCollision(EnumType _GroupIndex)
	{
		return CreateCollision(static_cast<int>(_GroupIndex));
	}

	// Collision 생성(동적할당), GELevel.map, GEActor.list 에 저장
	GameEngineCollision* CreateCollision(int _GroupIndex = 0);

protected:
	virtual void Start() {}                      // Loop 실행 전 기본 준비과정 (위치, 키, 랜더링 이미지 등)
	virtual void Update(float _DeltaTime) {}     // Loop 시 변화한 데이터 수정 (이동, 애니메이션, 상호작용 등)
	virtual void LateUpdate(float _DeltaTime) {} // 아직 사용 안함
	virtual void Render(float _DeltaTime) {}     // 아직 사용 안함

	// Actor 생성 후 시간 리턴
	inline float GetLiveTime() const
	{
		return LiveTime;
	}

private:
	GameEngineLevel* Level = nullptr;              // Actor 자신의 주체 (호출 대상)
	float4 Pos             = { 0.0f, 0.0f };       // Actor 위치           
	float LiveTime         = 0.0;                  // Actor 생성 후 시간
	std::list<GameEngineRender*> RenderList;       // 호출한 Level이 지니는 Actor의 Render들
	std::list<GameEngineCollision*> CollisionList; // 호출한 Level이 지니는 Actor의 Collision들

	float TimeScale = 0.0; // 그룹화 지정하여 DeltaTime을 조정(0222)

	void Release();
};
