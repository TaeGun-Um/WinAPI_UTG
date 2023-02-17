#include "GemWindow.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>

#include "ContentsEnum.h"
#include "Player.h"

GemWindow* GemWindow::GemWindowPtr = nullptr;

GemWindow::GemWindow() 
{
}

GemWindow::~GemWindow() 
{
}

void GemWindow::Start()
{
	GemWindowPtr = this;

	GameEngineRender* Render = CreateRender("GemWindow.Bmp", RenderOrder::UI);
	Render->SetPosition({1205, 30});
	Render->SetScale(Render->GetImage()->GetImageScale());
	Render->EffectCameraOff();

	// Number
	GemNumber.SetOwner(this);
	GemNumber.SetImage("Numbers.Bmp", { 20, 26 }, 6, RGB(255, 0, 255), "GemWindow.bmp");
	GemNumber.SetValue(NumberOfGems);
	GemNumber.SetAlign(Align::Right);
	GemNumber.SetNumOfDigits(3);
	GemNumber.SetRenderPos({ 1250, 35 });
}

void GemWindow::Update(float _DeltaTime)
{
	CurrentPlayerGem();
	GemNumberControl();
}

void GemWindow::CurrentPlayerGem()
{
	NumberOfGems = Player::MainPlayer->GetPlayerGem();
}

void GemWindow::GemNumberControl()
{
	GemNumber.SetValue(NumberOfGems);
}