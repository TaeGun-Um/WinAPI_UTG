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

// 윈도우 메세지 매크로 처리
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
    case WM_KEYDOWN: // 키보드 입력 시
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
        return DefWindowProc(_hWnd, _message, _wParam, _lParam); // 윈도우 디폴트 실행 규칙
    }
    return 0;
}

// 윈도우(창) 생성 구조체 정의
void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName, float4 _Size, float4 _Pos)
{
// --------------------------------- 윈도우 객체를 만들어내는 class 정의 ---------------------------------
    
    // 윈도우(창)의 옵션들
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
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }

// --------------------------------- 위의 정의대로 윈도우(창) 생성 ---------------------------------
    
    // 핸들값 HWnd에 저장
    HWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW, 
                        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    // 윈도우(창)이 만들어지면서 생성된 색깔 2차원배열 수정 권한 획득
    WindowBackBufferHdc = GetDC(HWnd);

    // 창 생성
    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);
    
    // 창 크기, 위치 변경
    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    // 백버퍼 HDC 저장은 Size, Pos 결정 후 실시 (Info 정보 업데이트를 위함)
    BackBufferImage = new GameEngineImage();
    BackBufferImage->ImageCreate(WindowBackBufferHdc);

    return;
}

// 호출한 이미지 HDC 정보로 덧씌우기, 빈버퍼가 호출 시 흰색으로 덧씌움
void GameEngineWindow::DoubleBufferClear()
{
    DoubleBufferImage->ImageClear();
}

// 백버퍼에 빈버퍼 BitCopy
void GameEngineWindow::DoubleBufferRender()
{
    BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize); // 0, 0 > WindowSize.half() 변경(0111)
}

// Loop
// 콜백 설계 방식
int GameEngineWindow::WindowLoop(void(*_Start)(), void(*_Loop)(), void(*_End)())
{
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg;

    while (IsWindowUpdate)
    {
        // 특별한 일 발생 시 메세지 처리
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            // 메세지 처리 시에도 실행 유지
            if (nullptr != _Loop)
            {
                _Loop();
            }

            GameEngineInput::IsAnyKeyOff(); // 1 Loop 후 AnyKey false

            continue;
        }
        
        // 데드타임
        if (nullptr != _Loop)
        {
            _Loop();
        }

        GameEngineInput::IsAnyKeyOff(); // 1 Loop 후 AnyKey false
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

// Size 입력
void GameEngineWindow::SettingWindowSize(float4 _Size)
{
    ScreenSize = _Size;

    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    // 창의 크기를 _Size로 설정
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 프레임, 타이틀 고려하여 윈도우 사이즈 복사
    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top) };

    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    // 완전히 똑같은 크기의 이미지입니다.
    if (nullptr != DoubleBufferImage)
    {
        delete DoubleBufferImage;
        DoubleBufferImage = nullptr;
    }

    DoubleBufferImage = new GameEngineImage();
    DoubleBufferImage->ImageCreate(ScreenSize);

}

// Position 입력
void GameEngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;

    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

// Mouse Pos 리턴
float4 GameEngineWindow::GetMousePosition()
{
    POINT MoniterPoint;               // POINT == long x, long y 구조체
    LPPOINT PointPtr = &MoniterPoint; // POINT 포인터
    GetCursorPos(PointPtr);           // 바탕화면에서의 마우스 커서를 받아온다.
    ScreenToClient(HWnd, PointPtr);   // 바탕화면 좌표를 클라이언트 좌표로 변환

    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
}