#pragma once

#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineImage;

// 설명 : 윈도우(창)을 만들 수 있는 구조체를 정의하고 윈도우를 생성한다.
class GameEngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

public:
	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	// 윈도우(창) 클래스 정의
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	// 윈도우(창) Size, Position 정의
	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	// 프로그램 Loop(실행)
	static int WindowLoop(void(*Start)(), void(*Loop)(), void(*End)());

	// Mouse Pos 리턴
	static float4 GetMousePosition();

	// 프로그램 핸들값
	inline static HWND GetHWnd()
	{
		return HWnd;
	}

	// 빈버퍼(공백 이미지)
	inline static GameEngineImage* GetDoubleBufferImage()
	{
		return DoubleBufferImage;
	}

	// 윈도우 백버퍼 HDC : 윈도우가 생성될 때 흰색 바탕에 대한 핸들
	inline static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	// 윈도우(창)의 창 크기
	inline static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	// 호출한 이미지 HDC 정보로 덧씌우기
	static void DoubleBufferClear();

	// 백버퍼에 빈버퍼 BitCopy
	static void DoubleBufferRender();

	// Loop 탈출 -> End 실행 (프로세스 종료)
	static void AppOff()
	{
		IsWindowUpdate = false;
	}

protected:

private:
	static float4 ScreenSize;
	static float4 WindowSize;
	static float4 WindowPos;
	static HWND HWnd;
	static HDC WindowBackBufferHdc;
	static GameEngineImage* BackBufferImage;
	static GameEngineImage* DoubleBufferImage;
	static bool IsWindowUpdate;

};

