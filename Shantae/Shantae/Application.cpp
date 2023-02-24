#include <Windows.h>
#include <GameEngineContents/ShantaeCore.h>

// <키 바인딩>

// <Player>
// 방향키 : 플레이어 이동, 선택 이동
// Z : 플레이어 공격, 선택
// X : 플레이어 점프
// C : 플레이어 총알발사
// ESC : 시작화면
// 1 : FreeMove On
// 2 : FreeMove Off
// 3 : ColMap OnOff
// 4 : PlayerPosText OnOff
// 5 : CollisionRender OnOff

// <Level 공통>
// P : 다음레벨
// O : 이전레벨

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance,           
	_In_ LPWSTR    lpCmdLine,                   
	_In_ int       nCmdShow)                    
{
	ShantaeCore::GetInst().CoreStart(hInstance);
	return 1;
}