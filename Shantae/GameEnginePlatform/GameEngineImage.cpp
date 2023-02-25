#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineImage.h"
#include "GameEngineWindow.h"

#pragma comment(lib, "msimg32.lib")  // 다른 lib 사용

GameEngineImage::GameEngineImage()
{
}

// Windows OS는 알아서 핸들을 반환하지만, 명시적으로 하는게 좋음
GameEngineImage::~GameEngineImage()
{
	if (nullptr != BitMap)
	{
		DeleteObject(BitMap);  // DeleteObject == Object 삭제
		BitMap = nullptr;
	}

	if (nullptr != OldBitMap)
	{
		DeleteObject(OldBitMap);
		OldBitMap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);     // DeleteDC == DC 삭제
		ImageDC = nullptr;
	}
}

// 아래 함수 실행
bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

// map에 저장한 이미지 HDC 적용
bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
	// LoadImageA : 아이콘, 커서, 애니메이션 커서 또는 비트맵을 로드. 함수가 성공하면 반환 값은 새로 로드된 이미지의 핸들.
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 로드에 실패했습니다.");
		return false;
	}

	// CreateCompatibleDC : 지정된 장치와 호환되는 메모리 디바이스 컨텍스트(DC) 생성
	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " 이미지 HDC 생성에 실패했습니다.");
		return false;
	}

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));
	ImageScaleCheck();
	return true;
}

// 백버퍼 HDC 적용
bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	if (nullptr == _Hdc)
	{
		MsgAssert("이미지 생성에 실패했습니다 nullptr 인 HDC를 넣어줬습니다.");
		return false;
	}

	ImageDC = _Hdc;
	ImageScaleCheck();
	return true;
}

// 빈버퍼(공백 이미지) HDC 적용
bool GameEngineImage::ImageCreate(const float4& _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("크기가 0인 이미지를 만들 수는 없습니다");
		return false;
	}

	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("이미지 생성에 실패했습니다.");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		MsgAssert("이미지 HDC 생성에 실패했습니다.");
		return false;
	}

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ImageScaleCheck();

	ImageClear();

	return true;
}

// 호출한 이미지 HDC 정보로 덧씌우기, 빈버퍼가 호출 시 흰색으로 덧씌움
void GameEngineImage::ImageClear()
{
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}

// HDC 정보를 Info에 저장
void GameEngineImage::ImageScaleCheck()
{
	// GetCurrentObject  = 현재의 오브젝트(호출한 오브젝트)를 알려준다.
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

// HDC를 얻은 이미지에 대해 Cut 실시
void GameEngineImage::Cut(int _X, int _Y)
{
	ImageCutData Data;

	Data.SizeX = static_cast<float>(GetImageScale().ix() / _X); // 이미지 크기를 X만큼 나눔
	Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y); // 이미지 크기를 Y만큼 나눔

	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			ImageCutDatas.push_back(Data);  // 처음 Size 값 저장 후 실시(순서 중요)
			Data.StartX += Data.SizeX;      // Data.SizeX 씩 증가하면 한 칸 이동
		}

		Data.StartX = 0.0f;                 // Y로 이동할 때, X는 본래 위치로 이동
		Data.StartY += Data.SizeY;          // Data.SizeY 씩 증가하면 한 칸 이동
	}

	IsCut = true;
}

// HDC를 얻은 이미지에서 좌표를 찾아서 Cut
void GameEngineImage::Cut(float4 _Start, float4 _End, int _X, int _Y)
{
	ImageCutData Data;

	Data.SizeX = static_cast<float>((_End.x - _Start.x) / _X); // 이미지 크기를 X만큼 나눔
	Data.SizeY = static_cast<float>((_End.y - _Start.y) / _Y); // 이미지 크기를 Y만큼 나눔

	Data.StartX = _Start.x; // Start가 되는 x, y가 0이 아니기 때문에 전달받은 Start 복사
	Data.StartY = _Start.y; 

	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			ImageCutDatas.push_back(Data);
			Data.StartX += Data.SizeX;
		}

		Data.StartX = _Start.x;
		Data.StartY += Data.SizeY;
	}

	IsCut = true;
}

// Pixel 컬러정보 획득
DWORD GameEngineImage::GetPixelColor(float4 _Pos, DWORD _OutColor)
{
	return GetPixelColor(_Pos.ix(), _Pos.iy(), _OutColor);
}

DWORD GameEngineImage::GetPixelColor(int _X, int _Y, DWORD _OutColor)
{
	if (_X < 0)
	{
		return _OutColor;
	}
	if (_X >= GetImageScale().ix())
	{
		return _OutColor;
	}
	if (_Y < 0)
	{
		return _OutColor;
	}
	if (_Y >= GetImageScale().iy())
	{
		return _OutColor;
	}
	return GetPixel(ImageDC, _X, _Y);
}

// 단순 Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale)
{
	BitBlt(
		ImageDC,
		_CenterPos.ix() - _Scale.hix(), // 대상 이미지 시작점 x
		_CenterPos.iy() - _Scale.hiy(), // 대상 이미지 시작점 y
		_Scale.ix(),                    // 대상, 복사할 이미지 사각형 너비 x
		_Scale.iy(),                    // 대상, 복사할 이미지 사각형 너비 y
		_OtherImage->GetImageDC(),
		0,                              // 복사할 이미지 시작점 x
		0,                              // 복사할 이미지 시작점 y
		SRCCOPY                         // 래스터 연산 코드
	);
}

// Cut한 이미지를 호출하여 TransparentBlt 실시
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" 잘리지 않은 이미지로 cut출력 함수를 사용하려고 했습니다.");
		return;
	}

	// 인자로 전달한 인덱스 번호에 맞는 이미지 호출(복사)
	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	// TransparentBlt 실행
	TransCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

// RGB, 크기조절 HDC 복사
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	TransparentBlt(ImageDC,
		_CopyCenterPos.ix() - _CopySize.hix(),	 // 대상 이미지 시작점 x
		_CopyCenterPos.iy() - _CopySize.hiy(),	 // 대상 이미지 시작점 y
		_CopySize.ix(),				             // 대상 이미지 사각형 너비 x
		_CopySize.iy(),				             // 대상 이미지 사각형 너비 y
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),		             // 복사할 이미지 시작점 x
		_OtherImagePos.iy(),		             // 복사할 이미지 시작점 y
		_OtherImageSize.ix(),		             // 복사할 이미지 사각형 너비 x
		_OtherImageSize.iy(),                    // 복사할 이미지 사각형 너비 y
		_Color);                                 // 제외할 색상
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" 잘리지 않은 이미지로 cut출력 함수를 사용하려고 했습니다.");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	AlphaCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha)
{
	BLENDFUNCTION BF;

	BF.BlendOp = AC_SRC_OVER;
	BF.BlendFlags = 0;
	BF.SourceConstantAlpha = _Alpha;
	BF.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(ImageDC, // 여기에 그려라.
		_CopyCenterPos.ix() - _CopySize.hix(), // 여기를 시작으로
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(), // 이 크기로
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),// 이미지의 x y에서부터
		_OtherImagePos.iy(),
		_OtherImageSize.ix(), // 이미지의 x y까지의 위치를
		_OtherImageSize.iy(),
		BF);
}

// 이미지 회전을 위한 함수
void GameEngineImage::PlgCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, float _Angle, GameEngineImage* _FilterImage)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" 잘리지 않은 이미지로 cut출력 함수를 사용하려고 했습니다.");
		return;
	}

	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	PlgCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Angle, _FilterImage);
}

void GameEngineImage::PlgCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, float _Angle, GameEngineImage* _FilterImage)
{
	POINT ArrRotPoint[3];

	CollisionData Data = { float4::Zero, _CopySize };

	float4 LeftTop = Data.LeftTop();
	float4 RightTop = Data.RightTop();
	float4 LeftBot = Data.LeftBot();

	ArrRotPoint[0] = (LeftTop.RotaitonZDegReturn(_Angle) + _CopyCenterPos).ToWindowPOINT();
	ArrRotPoint[1] = (RightTop.RotaitonZDegReturn(_Angle) + _CopyCenterPos).ToWindowPOINT();
	ArrRotPoint[2] = (LeftBot.RotaitonZDegReturn(_Angle) + _CopyCenterPos).ToWindowPOINT();

	PlgBlt(ImageDC, // 여기에 그려라.
		ArrRotPoint,
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),// 이미지의 x y에서부터
		_OtherImagePos.iy(),
		_OtherImageSize.ix(), // 이미지의 x y까지의 위치를
		_OtherImageSize.iy(),
		_FilterImage->BitMap,
		_OtherImagePos.ix(),
		_OtherImagePos.iy()
		);

}