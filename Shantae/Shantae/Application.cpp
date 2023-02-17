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

// 0209
// 32비트 이미지여야함
// 자연스럽게 채널에 알파가 있을 것
// 없으면 채널 복제로 알파채널을 만들어줘야함
// 만들고 반투명이 되길 원하는 부분은 흰색
// 색이 제거되기 원하는 부분은 검은색으로 칠한 뒤
// 저장
// 포토샵에서 알파채널 편집 -> 알파블랜드 사용
// 
// 페이드인 페이드아웃도 검은색 32비트 채우면 됨
// 
// 알파카피()
// RGB 인자 부분을 알파값으로 변경
// 
// 
// 
// 
//