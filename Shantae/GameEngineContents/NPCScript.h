#pragma once

#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void Kill();

	GameEngineRender* TextRender = nullptr;

	float4 BoxScale = float4::Zero;

	std::string Script = "오류";

	int TextCount = 1;
};

