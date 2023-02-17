#include <GameEngineBase/GameEngineDebug.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineWindow.h"
#include "GameEngineInput.h"

HWND GameEngineWindow::HWnd               = nullptr;
HDC GameEngineWindow::WindowBackBufferHdc = nullptr;
float4 GameEngineWindow::WindowSize       = { 100, 100 };
float4 GameEngineWindow::WindowPos        = { 100, 100 };
float4 GameEngineWindow::ScreenSize       = { 100, 100 };

GameEngineImage* GameEngineWindow::BackBufferImage   = nullptr;
GameEngineImage* GameEngineWindow::DoubleBufferImage = nullptr;

bool GameEngineWindow::IsWindowUpdate = true;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
}

// ������ �޼��� ��ũ�� ó��
LRESULT CALLBACK GameEngineWindow::MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_MOUSEMOVE:
    {
        int a = 0;
        break;
    }
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_ACTIVATE:
    {
        int a = 0;
        break;
    }
    case WM_KILLFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_KEYDOWN: // Ű���� �Է� ��
    {
        GameEngineInput::IsAnyKeyOn();
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam); // ������ ����Ʈ ���� ��Ģ
    }
    return 0;
}

// ������(â) ���� ����ü ����
void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
// --------------------------------- ������ ��ü�� ������ class ���� ---------------------------------
    
    // ������(â)�� �ɼǵ�
    WNDCLASSEX wcex;                                     

    wcex.cbSize        = sizeof(WNDCLASSEX);             

    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = &GameEngineWindow::MessageFunction;
    wcex.cbClsExtra    = 0;                              
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = _hInstance;                     
    wcex.hIcon         = nullptr;                        
    wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW); 
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);     
    wcex.lpszMenuName  = nullptr;                        
    wcex.lpszClassName = "GameEngineWindowDefault";      
    wcex.hIconSm       = nullptr;                        

    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }

// --------------------------------- ���� ���Ǵ�� ������(â) ���� ---------------------------------
    
    // �ڵ鰪 HWnd�� ����
    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW, 
                        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    // ������(â)�� ��������鼭 ������ ���� 2�����迭 ���� ���� ȹ��
    WindowBackBufferHdc = GetDC(HWnd);

    // â ����
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);
    
    // â ũ��, ��ġ ����
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    // ����� HDC ������ Size, Pos ���� �� �ǽ� (Info ���� ������Ʈ�� ����)
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    return;
}

// ȣ���� �̹��� HDC ������ �������, ����۰� ȣ�� �� ������� ������
void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

// ����ۿ� ����� BitCopy
void GameEngineWindow::DoubleBufferRender()
{
    BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize); // 0, 0 > WindowSize.half() ����(0111)
}

// Loop
// �ݹ� ���� ���
int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;

    while (IsWindowUpdate)
    {
        // Ư���� �� �߻� �� �޼��� ó��
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // �޼��� ó�� �ÿ��� ���� ����
            if (nullptr != _Loop)
            {
                _Loop();
            }

            GameEngineInput::IsAnyKeyOff(); // 1 Loop �� AnyKey false

            continue;
        }
        
        // ����Ÿ��
        if (nullptr != _Loop)
        {
            _Loop();
        }

        GameEngineInput::IsAnyKeyOff(); // 1 Loop �� AnyKey false
    }

    if (nullptr != _End)
    {
        _End();
    }

    if (nullptr != BackBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;

        delete BackBufferImage;
        BackBufferImage = nullptr;
    }

    return (int)msg.wParam;
}

// Size �Է�
void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    ScreenSize = _Size;

    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    // â�� ũ�⸦ _Size�� ����
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    // ������, Ÿ��Ʋ ����Ͽ� ������ ������ ����
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };

    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    // ������ �Ȱ��� ũ���� �̹����Դϴ�.
    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);

}

// Position �Է�
void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;

    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

// Mouse Pos ����
float4 GameEngineWindow::GetMousePosition()
{
    POINT MoniterPoint;               // POINT == long x, long y ����ü
    LPPOINT PointPtr = &MoniterPoint; // POINT ������
    GetCursorPos(PointPtr);           // ����ȭ�鿡���� ���콺 Ŀ���� �޾ƿ´�.
    ScreenToClient(HWnd, PointPtr);   // ����ȭ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ

    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
}