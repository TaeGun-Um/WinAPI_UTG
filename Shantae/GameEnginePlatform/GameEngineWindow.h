#pragma once

#include <string>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineImage;

// ���� : ������(â)�� ���� �� �ִ� ����ü�� �����ϰ� �����츦 �����Ѵ�.
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

	// ������(â) Ŭ���� ����
	static void WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos);

	// ������(â) Size, Position ����
	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	// ���α׷� Loop(����)
	static int WindowLoop(void(*Start)(), void(*Loop)(), void(*End)());

	// Mouse Pos ����
	static float4 GetMousePosition();

	// ���α׷� �ڵ鰪
	inline static HWND GetHWnd()
	{
		return HWnd;
	}

	// �����(���� �̹���)
	inline static GameEngineImage* GetDoubleBufferImage()
	{
		return DoubleBufferImage;
	}

	// ������ ����� HDC : �����찡 ������ �� ��� ������ ���� �ڵ�
	inline static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	// ������(â)�� â ũ��
	inline static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	// ȣ���� �̹��� HDC ������ �������
	static void DoubleBufferClear();

	// ����ۿ� ����� BitCopy
	static void DoubleBufferRender();

	// Loop Ż�� -> End ���� (���μ��� ����)
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

