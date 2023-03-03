#pragma once

#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Kill();
	void NPCType();

	GameEngineRender* TextRender = nullptr;
	NPCDialogType_Dialog NPCValue = NPCDialogType_Dialog::Town_Guard;
	float4 BoxScale = float4::Zero;

	std::string Script = "오류";

	int TextCount = 1;

	bool IsOver = false;

	bool SKY = false;
};

