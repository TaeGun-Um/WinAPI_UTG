#include "UILoad.h"

#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

UILoad::UILoad() 
{
}

UILoad::~UILoad() 
{
}

void UILoad::Loading()
{
	// °æ·Î
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("Shantae_Resource");
	Dir.Move("Shantae_Resource");
	Dir.Move("Image");
	Dir.Move("UI");

	GameEngineImage* Image0 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GemWindow.bmp"));
	GameEngineImage* Image1 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Health.bmp"));
	Image1->Cut(5, 1);
	GameEngineImage* Image2 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Numbers.bmp"));
	Image2->Cut(10, 1);
	GameEngineImage* Image3 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueTextBox_Open.bmp"));
	Image3->Cut(1, 3);
	GameEngineImage* Image4 = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BlueTextBox_Close.bmp"));
	Image4->Cut(1, 3);

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ShopSelect.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TextButton.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("A.bmp"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Up.bmp"));
}