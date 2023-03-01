#include "Inventory.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "ItemSelect.h"

Inventory* Inventory::PlayerInven = nullptr;

Inventory::Inventory() 
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	PlayerInven = this;

	AnimationRender = CreateRender("Inventory.Bmp", RenderOrder::UI);
	AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());
	AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
	AnimationRender->EffectCameraOff();
	AnimationRender->Off();
}

void Inventory::Update(float _DeltaTime)
{
	if (1 == SelectCreate)
	{
		SelectCreate = 0;
		Select = nullptr;
		float4 SelectPos = GetPos() + float4::Up * 50;

		Select = GetLevel()->CreateActor<ItemSelect>();
		Select->SetPos(SelectPos);
	}

	if (false == AnimationRender->IsUpdate())
	{
		Select->Off();
	}
	else
	{
		Select->On();
	}

	SelectMove(_DeltaTime);
}

void Inventory::Render(float _DeltaTime)
{

}

void Inventory::SelectMove(float _DeltaTime)
{
	if (GameEngineInput::IsPress("UpMove"))
	{
		Select->SetMove(float4::Up * 100.0f * _DeltaTime);
	}

	if (GameEngineInput::IsPress("DownMove"))
	{
		Select->SetMove(float4::Down * 100.0f * _DeltaTime);
	}

	if (GameEngineInput::IsPress("LeftMove"))
	{
		Select->SetMove(float4::Left * 100.0f * _DeltaTime);
	}

	if (GameEngineInput::IsPress("RightMove"))
	{
		Select->SetMove(float4::Right * 100.0f * _DeltaTime);
	}
}