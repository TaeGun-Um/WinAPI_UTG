#include "WhiteBox.h"

//#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"

WhiteBox::WhiteBox() 
{
}

WhiteBox::~WhiteBox() 
{
}

void WhiteBox::Start()
{
	BoxRender = CreateRender("WhiteBox.Bmp", RenderOrder::Box);
	BoxRender->SetScale(BoxRender->GetImage()->GetImageScale());

	float4 InitRendPos = GetLevel()->GetCameraPos();
	float4 ModifyPos = float4::Zero;

	ModifyPos = { InitRendPos.x + GameEngineWindow::GetScreenSize().hx(), InitRendPos.y + GameEngineWindow::GetScreenSize().hy() };

	BoxRender->SetPosition(ModifyPos);
}

void WhiteBox::Update(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeIn(_DeltaTime);
	}
	if (true == IsFadeOut)
	{
		FadeOut(_DeltaTime);
	}

	//if (true == FadeInOver) // �� ä��
	//{
	//	Kill();
	//}
	if (true == FadeOutOver) // �� ����
	{
		Kill();
	}
}
void WhiteBox::Render(float _DeltaTime)
{

}

void WhiteBox::FadeInStart(unsigned int _doubling, float _waittime)
{
	if (0 > _doubling)
	{
		MsgAssert("���� ������ �־��ּ���");
		return;
	}

	IsFadeIn = true;
	Doubling = _doubling;
	WaitTime = _waittime;
}

void WhiteBox::FadeOutStart(unsigned int _doubling, float _waittime)
{
	if (0 > _doubling)
	{
		MsgAssert("���� ������ �־��ּ���");
		return;
	}

	IsFadeOut = true;
	Doubling = _doubling;
	WaitTime = _waittime;
}

// �� ä��
void WhiteBox::FadeIn(float _DeltaTime)
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
	}
}

// �� ����
void WhiteBox::FadeOut(float _DeltaTime)
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
	}
}

void WhiteBox::FadeInBoxKill()
{
	Kill();
}

void WhiteBox::Kill()
{
	GameEngineActor* Actor = BoxRender->GetActor();
	Actor->Off();
	Actor->Death();
}