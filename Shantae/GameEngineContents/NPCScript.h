#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "BlueTextBox.h"

enum class NPCDialogType_Dialog
{
	Sky,
	Bathwoman,
	Merchant,
	Squidsmith,
	Town_Guard,
	Town_Guard_Pass,
};

class ShopSelect;
class ShopBlueBox;

// 설명 :
class NPCScript : public GameEngineActor
{
public:

	friend BlueTextBox;

	// constrcuter destructer
	NPCScript();
	~NPCScript();

	// delete Function
	NPCScript(const NPCScript& _Other) = delete;
	NPCScript(NPCScript&& _Other) noexcept = delete;
	NPCScript& operator=(const NPCScript& _Other) = delete;
	NPCScript& operator=(NPCScript&& _Other) noexcept = delete;

	bool GetIsOver()
	{
		return IsOver;
	}

	void SetNPCDialogType(NPCDialogType_Dialog _Is)
	{
		NPCValue = _Is;
	}

	void NextScript()
	{
		++TextnNextCount;
	}

	void TextOn()
	{
		TextRender->On();
	}

	void TextOff()
	{
		TextRender->Off();
	}

	bool GetShopOpen()
	{
		return ShopOpen;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void NPCType();

	void TownGuard();
	void Bathwoman();
	void TownGuard_Pass();
	void Sky();
	void Merchant();
	void Squidsmith();

	void DialogType();
	
	void NormalTextCreate();
	void TownGuard_PassCreate();
	void SquidsmithCreate();
	void SkyCreate();
	void MerchantCreate();
	
	void ShopCreate();
	void SelectMove();
	void UpSet();
	void DownSet();

	void Kill();

	GameEngineSoundPlayer BGMPlayer;

	GameEngineRender* TextRender = nullptr;

	GameEngineRender* ShopText1 = nullptr;
	GameEngineRender* ShopText2 = nullptr;
	GameEngineRender* ShopText3 = nullptr;
	GameEngineRender* ShopText4 = nullptr;

	float4 Pos1 = float4::Zero;
	float4 Pos2 = float4::Zero;
	float4 Pos3 = float4::Zero;

	std::string ShopScript1 = "오류";
	std::string ShopScript2 = "오류";
	std::string ShopScript3 = "오류";
	std::string ShopScript4 = "오류";

	ShopSelect* SelectButton = nullptr;
	ShopBlueBox* ShopBox = nullptr;
	NPCDialogType_Dialog NPCValue = NPCDialogType_Dialog::Town_Guard;
	float4 BoxScale = float4::Zero;

	std::string Script = "오류";
	std::vector<std::string> NPCTexts;

	int NPCCount = 1;
	int IDCardCreate = 1;
	int TextInsertCount = 0;
	int TextnNextCount = 0;
	int SelectCreate = 1;
	int ShopCount = 1;
	
	int OctopusTextPlus = 1;
	int OctopusfullCount = 1;
	int OctopusAction = 1;

	bool IsTextEnd = false;
	bool IsOver = false;

	bool Octopusless = false;
	bool Octopusenough = false;
	bool Octopusfull = false;
	bool ShopOpen = false;

};

