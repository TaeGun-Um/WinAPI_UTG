#include "BlackBox.h"

//#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

BlackBox::BlackBox() 
{
}

BlackBox::~BlackBox() 
{
}

void BlackBox::Start()
{
	BoxRender = CreateRender("BlackBox.Bmp", RenderOrder::Box);
	BoxRender->SetScale(BoxRender->GetImage()->GetImageScale());

	float4 InitRendPos = GetLevel()->GetCameraPos();
	float4 ModifyPos = float4::Zero;

	ModifyPos = { InitRendPos.x + GameEngineWindow::GetScreenSize().hx(), InitRendPos.y + GameEngineWindow::GetScreenSize().hy() };

	BoxRender->SetPosition(ModifyPos);
}

void BlackBox::Update(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeIn(_DeltaTime);
	}
	if (true == IsFadeOut)
	{
		FadeOut(_DeltaTime);
	}

	//if (true == FadeInOver) // 색 채움
	//{
	//	Kill();
	//}
	if (true == FadeOutOver) // 색 빠짐
	{
		Kill();
	}
}
void BlackBox::Render(float _DeltaTime)
{

}

void BlackBox::FadeInStart(unsigned int _doubling, float _waittime)
{
	if (0 > _doubling)
	{
		MsgAssert("양의 정수만 넣어주세요");
		return;
	}

	IsFadeIn = true;
	Doubling = _doubling;
	WaitTime = _waittime;
}

void BlackBox::FadeOutStart(unsigned int _doubling, float _waittime)
{
	if (0 > _doubling)
	{
		MsgAssert("양의 정수만 넣어주세요");
		return;
	}

	IsFadeOut = true;
	Doubling = _doubling;
	WaitTime = _waittime;
}

// 색 채움
void BlackBox::FadeIn(float _DeltaTime)
{
	FadeInCount = FadeInCount + Doubling;

	if (FadeInCount <= 254)
	{
		BoxRender->SetAlpha(++FadeInCount);
	}

	if (FadeInCount >= 254)
	{
		FadeInTime += _DeltaTime;
	}

	if (FadeInTime <= WaitTime)
	{
		return;
	}

	if (FadeInCount == 255)
	{
		FadeInOver = true;
		IsFadeIn = false;
		FadeInCount = 0;
		FadeInTime = 0.0f;
	}
}

// 색 빠짐
void BlackBox::FadeOut(float _DeltaTime)
{
	FadeOutTime += _DeltaTime;

	if (FadeOutTime <= WaitTime)
	{
		return;
	}

	FadeOutCount = FadeOutCount - Doubling;

	if (FadeOutCount >= 1)
	{
		BoxRender->SetAlpha(--FadeOutCount);
	}

	if (FadeOutCount == 0)
	{
		FadeOutOver = true;
		IsFadeIn = false;
		FadeOutCount = 255;
		FadeInTime = 0.0f;
	}
}

void BlackBox::FadeInBoxKill()
{
	Kill();
}

void BlackBox::Kill()
{
	GameEngineActor* Actor = BoxRender->GetActor();
	Actor->Off();
	Actor->Death();
}