#pragma once

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Kill();
	void NPCType();
	void TextCreate();

	GameEngineRender* TextRender = nullptr;
	NPCDialogType_Dialog NPCValue = NPCDialogType_Dialog::Town_Guard;
	float4 BoxScale = float4::Zero;

	std::string Script = "오류";
	std::vector<std::string> SkyTexts;
	std::vector<std::string> BathwomanTexts;
	std::vector<std::string> MerchantTexts;
	std::vector<std::string> SquidsmithTexts;
	std::vector<std::string> Town_GuardTexts;
	std::vector<std::string> Town_Guard_PassTexts;
	std::vector<std::string> PlayerTexts;

	std::vector<std::string> NPCTexts;

	int TextCount = 1;
	int TextInsertCount = 0;
	int TextnNextCount = 0;

	bool IsTextEnd = false;
	bool IsOver = false;

	void TownGuard();
	void TownGuard_Pass();
	void Bathwoman();
	void Sky();
	void Merchant();
	void Squidsmith();
};

