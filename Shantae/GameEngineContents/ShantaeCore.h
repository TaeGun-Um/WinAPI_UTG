#pragma once
#include <GameEngineCore/GameEngineCore.h>

// 설명 : 싱글톤 클래스, GameEngineCore를 상속받는 자식 클래스
class ShantaeCore : public GameEngineCore
{
public:
	// delete Function
	ShantaeCore(const ShantaeCore& _Other) = delete;
	ShantaeCore(ShantaeCore&& _Other) noexcept = delete;
	ShantaeCore& operator=(const ShantaeCore& _Other) = delete;
	ShantaeCore& operator=(ShantaeCore&& _Other) noexcept = delete;

	// 싱글톤
	static ShantaeCore& GetInst()
	{
		return Core;
	}

protected:
	// GameEngineCore 순수 가상함수 ovrride
	void Start() override;
	void Update() override;
	void End() override;

private:
	ShantaeCore();
	~ShantaeCore();

	static ShantaeCore Core;

};
