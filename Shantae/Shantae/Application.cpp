#include <Windows.h>
#include <GameEngineContents/ShantaeCore.h>

// <Ű ���ε�>

// <Player>
// ����Ű : �÷��̾� �̵�, ���� �̵�
// Z : �÷��̾� ����, ����
// X : �÷��̾� ����
// C : �÷��̾� �Ѿ˹߻�
// ESC : ����ȭ��
// 1 : FreeMove On
// 2 : FreeMove Off
// 3 : ColMap OnOff
// 4 : PlayerPosText OnOff
// 5 : CollisionRender OnOff

// <Level ����>
// P : ��������
// O : ��������

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance,           
	_In_ LPWSTR    lpCmdLine,                   
	_In_ int       nCmdShow)                    
{
	ShantaeCore::GetInst().CoreStart(hInstance);
	return 1;
}