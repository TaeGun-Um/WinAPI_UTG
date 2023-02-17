#include "GameEngineComponent.h"
#include "GameEngineActor.h"

GameEngineComponent::GameEngineComponent()
{
}

GameEngineComponent::~GameEngineComponent()
{
}

// �ڽ��� �����ϴ� Actor ���� ȹ��
GameEngineActor* GameEngineComponent::GetActor()
{
	return GetOwner<GameEngineActor>();
}

// �ڽ��� �����ϴ� Actor�� �ڽ��� �Ÿ� ����
float4 GameEngineComponent::GetActorPlusPos()
{
	return GetActor()->GetPos() + Position;
}