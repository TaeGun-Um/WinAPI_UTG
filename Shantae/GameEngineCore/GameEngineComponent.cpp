#include "GameEngineComponent.h"
#include "GameEngineActor.h"

GameEngineComponent::GameEngineComponent()
{
}

GameEngineComponent::~GameEngineComponent()
{
}

// 자신을 소유하는 Actor 정보 획득
GameEngineActor* GameEngineComponent::GetActor()
{
	return GetOwner<GameEngineActor>();
}

// 자신을 소유하는 Actor와 자신의 거리 차이
float4 GameEngineComponent::GetActorPlusPos()
{
	return GetActor()->GetPos() + Position;
}