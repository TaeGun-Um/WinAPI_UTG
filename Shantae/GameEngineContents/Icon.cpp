#include "Icon.h"

#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"

Icon::Icon() 
{
}

Icon::~Icon() 
{
}

void Icon::Start()
{
	AnimationRender = CreateRender(RenderOrder::UI);
	AnimationRender->SetScale({ 300, 300 });
	AnimationRender->CreateAnimation({ .AnimationName = "MonsterMilk",  .ImageName = "Items.bmp", .Start = 1, .End = 1, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Meat",  .ImageName = "Items.bmp", .Start = 2, .End = 2, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Bubble",  .ImageName = "Items.bmp", .Start = 5, .End = 5, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "PikeBall",  .ImageName = "Items.bmp", .Start = 6, .End = 6, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Octopus",  .ImageName = "Items.bmp", .Start = 8, .End = 8, .InterTime = 10.0f, .Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "Pass",  .ImageName = "Items.bmp", .Start = 10, .End = 10, .InterTime = 10.0f, .Loop = false });
	
	AnimationRender->EffectCameraOff();
	AnimationRender->ChangeAnimation("Meat");

}

void Icon::Update(float _DeltaTime)
{
	IconSelect();

	CreateNumber();

	if (true == IsNumberCreate)
	{
		CurrentPlayerItemNumber();
		ItemNumberControl();
	}

}

void Icon::Render(float _DeltaTime)
{

}

void Icon::CreateNumber()
{
	if (1 == NumberCreate)
	{
		NumberCreate = 0;
		ItemNumber.SetOwner(this);
		ItemNumber.SetImage("Numbers.Bmp", { 20, 26 }, 8, RGB(255, 0, 255), "GemWindow.bmp");
		ItemNumber.SetValue(ItemCount);
		ItemNumber.SetAlign(Align::Right);
		ItemNumber.SetNumOfDigits(1);
		ItemNumber.SetRenderPos({ 30 , 25 });
		IsNumberCreate = true;
	}
}

void Icon::CurrentPlayerItemNumber()
{
	// ItemCount = Player::MainPlayer->GetPlayerGem();
}

void Icon::ItemNumberControl()
{
	ItemNumber.SetValue(ItemCount);
}

void Icon::IconSelect()
{
	std::string UpperName = GameEngineString::ToUpper(IconName);

	std::string UpperName_comparison1 = GameEngineString::ToUpper("MonsterMilk");
	std::string UpperName_comparison2 = GameEngineString::ToUpper("Meat");
	std::string UpperName_comparison3 = GameEngineString::ToUpper("Bubble");
	std::string UpperName_comparison4 = GameEngineString::ToUpper("PikeBall");
	std::string UpperName_comparison5 = GameEngineString::ToUpper("Octopus");
	std::string UpperName_comparison6 = GameEngineString::ToUpper("Pass");

	if (UpperName_comparison1 == UpperName)
	{
		AnimationRender->ChangeAnimation("MonsterMilk");
	}
	else if (UpperName_comparison2 == UpperName)
	{
		AnimationRender->ChangeAnimation("Meat");
	}
	else if (UpperName_comparison3 == UpperName)
	{
		AnimationRender->ChangeAnimation("Bubble");
	}
	else if (UpperName_comparison4 == UpperName)
	{
		AnimationRender->ChangeAnimation("PikeBall");
	}
	else if (UpperName_comparison5 == UpperName)
	{
		AnimationRender->ChangeAnimation("Octopus");
	}
	else if (UpperName_comparison6 == UpperName)
	{
		AnimationRender->ChangeAnimation("Pass");
	}
}