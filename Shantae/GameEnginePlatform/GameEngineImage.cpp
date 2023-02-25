#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineImage.h"
#include "GameEngineWindow.h"

#pragma comment(lib, "msimg32.lib")  // �ٸ� lib ���

GameEngineImage::GameEngineImage()
{
}

// Windows OS�� �˾Ƽ� �ڵ��� ��ȯ������, ��������� �ϴ°� ����
GameEngineImage::~GameEngineImage()
{
	if (nullptr != BitMap)
	{
		DeleteObject(BitMap);  // DeleteObject == Object ����
		BitMap = nullptr;
	}

	if (nullptr != OldBitMap)
	{
		DeleteObject(OldBitMap);
		OldBitMap = nullptr;
	}

	if (nullptr != ImageDC)
	{
		DeleteDC(ImageDC);     // DeleteDC == DC ����
		ImageDC = nullptr;
	}
}

// �Ʒ� �Լ� ����
bool GameEngineImage::ImageLoad(const GameEnginePath& _Path)
{
	return ImageLoad(_Path.GetPathToString().c_str());
}

// map�� ������ �̹��� HDC ����
bool GameEngineImage::ImageLoad(const std::string_view& _Path)
{
	// LoadImageA : ������, Ŀ��, �ִϸ��̼� Ŀ�� �Ǵ� ��Ʈ���� �ε�. �Լ��� �����ϸ� ��ȯ ���� ���� �ε�� �̹����� �ڵ�.
	BitMap = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.data(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (nullptr == BitMap)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " �̹��� �ε忡 �����߽��ϴ�.");
		return false;
	}

	// CreateCompatibleDC : ������ ��ġ�� ȣȯ�Ǵ� �޸� ����̽� ���ؽ�Ʈ(DC) ����
	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		std::string Path = _Path.data();
		MsgAssert(Path + " �̹��� HDC ������ �����߽��ϴ�.");
		return false;
	}

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));
	ImageScaleCheck();
	return true;
}

// ����� HDC ����
bool GameEngineImage::ImageCreate(HDC _Hdc)
{
	if (nullptr == _Hdc)
	{
		MsgAssert("�̹��� ������ �����߽��ϴ� nullptr �� HDC�� �־�����ϴ�.");
		return false;
	}

	ImageDC = _Hdc;
	ImageScaleCheck();
	return true;
}

// �����(���� �̹���) HDC ����
bool GameEngineImage::ImageCreate(const float4& _Scale)
{
	if (true == _Scale.IsZero())
	{
		MsgAssert("ũ�Ⱑ 0�� �̹����� ���� ���� �����ϴ�");
		return false;
	}

	BitMap = CreateCompatibleBitmap(GameEngineWindow::GetWindowBackBufferHdc(), _Scale.ix(), _Scale.iy());

	if (nullptr == BitMap)
	{
		MsgAssert("�̹��� ������ �����߽��ϴ�.");
		return false;
	}

	ImageDC = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC)
	{
		MsgAssert("�̹��� HDC ������ �����߽��ϴ�.");
		return false;
	}

	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ImageScaleCheck();

	ImageClear();

	return true;
}

// ȣ���� �̹��� HDC ������ �������, ����۰� ȣ�� �� ������� ������
void GameEngineImage::ImageClear()
{
	Rectangle(ImageDC, 0, 0, Info.bmWidth, Info.bmHeight);
}

// HDC ������ Info�� ����
void GameEngineImage::ImageScaleCheck()
{
	// GetCurrentObject  = ������ ������Ʈ(ȣ���� ������Ʈ)�� �˷��ش�.
	HBITMAP CurrentBitMap = static_cast<HBITMAP>(GetCurrentObject(ImageDC, OBJ_BITMAP));
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info);
}

// HDC�� ���� �̹����� ���� Cut �ǽ�
void GameEngineImage::Cut(int _X, int _Y)
{
	ImageCutData Data;

	Data.SizeX = static_cast<float>(GetImageScale().ix() / _X); // �̹��� ũ�⸦ X��ŭ ����
	Data.SizeY = static_cast<float>(GetImageScale().iy() / _Y); // �̹��� ũ�⸦ Y��ŭ ����

	for (size_t i = 0; i < _Y; i++)
	{
		for (size_t i = 0; i < _X; i++)
		{
			ImageCutDatas.push_back(Data);  // ó�� Size �� ���� �� �ǽ�(���� �߿�)
			Data.StartX += Data.SizeX;      // Data.SizeX �� �����ϸ� �� ĭ �̵�
		}

		Data.StartX = 0.0f;                 // Y�� �̵��� ��, X�� ���� ��ġ�� �̵�
		Data.StartY += Data.SizeY;          // Data.SizeY �� �����ϸ� �� ĭ �̵�
	}

	IsCut = true;
}

// HDC�� ���� �̹������� ��ǥ�� ã�Ƽ� Cut
void GameEngineImage::Cut(float4 _Start, float4 _End, int _X, int _Y)
{
	ImageCutData Data;

	Data.SizeX = static_cast<float>((_End.x - _Start.x) / _X); // �̹��� ũ�⸦ X��ŭ ����
	Data.SizeY = static_cast<float>((_End.y - _Start.y) / _Y); // �̹��� ũ�⸦ Y��ŭ ����

	Data.StartX = _Start.x; // Start�� �Ǵ� x, y�� 0�� �ƴϱ� ������ ���޹��� Start ����
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

// Pixel �÷����� ȹ��
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

// �ܼ� Copy
void GameEngineImage::BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale)
{
	BitBlt(
		ImageDC,
		_CenterPos.ix() - _Scale.hix(), // ��� �̹��� ������ x
		_CenterPos.iy() - _Scale.hiy(), // ��� �̹��� ������ y
		_Scale.ix(),                    // ���, ������ �̹��� �簢�� �ʺ� x
		_Scale.iy(),                    // ���, ������ �̹��� �簢�� �ʺ� y
		_OtherImage->GetImageDC(),
		0,                              // ������ �̹��� ������ x
		0,                              // ������ �̹��� ������ y
		SRCCOPY                         // ������ ���� �ڵ�
	);
}

// Cut�� �̹����� ȣ���Ͽ� TransparentBlt �ǽ�
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" �߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	// ���ڷ� ������ �ε��� ��ȣ�� �´� �̹��� ȣ��(����)
	ImageCutData Data = _OtherImage->GetCutData(_CutIndex);

	// TransparentBlt ����
	TransCopy(_OtherImage, _CopyCenterPos, _CopySize, Data.GetStartPos(), Data.GetScale(), _Color);
}

// RGB, ũ������ HDC ����
void GameEngineImage::TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color)
{
	TransparentBlt(ImageDC,
		_CopyCenterPos.ix() - _CopySize.hix(),	 // ��� �̹��� ������ x
		_CopyCenterPos.iy() - _CopySize.hiy(),	 // ��� �̹��� ������ y
		_CopySize.ix(),				             // ��� �̹��� �簢�� �ʺ� x
		_CopySize.iy(),				             // ��� �̹��� �簢�� �ʺ� y
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),		             // ������ �̹��� ������ x
		_OtherImagePos.iy(),		             // ������ �̹��� ������ y
		_OtherImageSize.ix(),		             // ������ �̹��� �簢�� �ʺ� x
		_OtherImageSize.iy(),                    // ������ �̹��� �簢�� �ʺ� y
		_Color);                                 // ������ ����
}

void GameEngineImage::AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" �߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
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

	AlphaBlend(ImageDC, // ���⿡ �׷���.
		_CopyCenterPos.ix() - _CopySize.hix(), // ���⸦ ��������
		_CopyCenterPos.iy() - _CopySize.hiy(),
		_CopySize.ix(), // �� ũ���
		_CopySize.iy(),
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),// �̹����� x y��������
		_OtherImagePos.iy(),
		_OtherImageSize.ix(), // �̹����� x y������ ��ġ��
		_OtherImageSize.iy(),
		BF);
}

// �̹��� ȸ���� ���� �Լ�
void GameEngineImage::PlgCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, float _Angle, GameEngineImage* _FilterImage)
{
	if (false == _OtherImage->IsCut)
	{
		MsgAssert(" �߸��� ���� �̹����� cut��� �Լ��� ����Ϸ��� �߽��ϴ�.");
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

	PlgBlt(ImageDC, // ���⿡ �׷���.
		ArrRotPoint,
		_OtherImage->GetImageDC(),
		_OtherImagePos.ix(),// �̹����� x y��������
		_OtherImagePos.iy(),
		_OtherImageSize.ix(), // �̹����� x y������ ��ġ��
		_OtherImageSize.iy(),
		_FilterImage->BitMap,
		_OtherImagePos.ix(),
		_OtherImagePos.iy()
		);

}