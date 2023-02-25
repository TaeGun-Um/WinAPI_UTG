#pragma once

#include <vector>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEnginePath;

// ���� : Cut �Լ� ���� �� ����Ǵ� �������� �����ϴ� ����ü
struct ImageCutData
{
	float StartX = 0.0f;
	float StartY = 0.0f;
	float SizeX = 0.0f;
	float SizeY = 0.0f;

	inline float4 GetStartPos() const
	{
		return { StartX, StartY };
	}

	inline float4 GetScale() const
	{
		return { SizeX, SizeY };
	}
};

// ���� : Image�� ���õ� ����� �����ϴ� Ŭ����
class GameEngineImage
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	// �̹��� �׸� ��ȯ ����
	inline HDC GetImageDC() const
	{
		return ImageDC;
	}

	// �ش� �̹��� x, y�� ����
	inline float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	// �Ʒ� �Լ� ����
	bool ImageLoad(const GameEnginePath& _Path);

	// map�� ������ �̹��� HDC ����
	bool ImageLoad(const std::string_view& _Path);

	// ����� HDC ����
	bool ImageCreate(HDC _Hdc);

	// �����(���� �̹���) HDC ����
	bool ImageCreate(const float4& _Scale);

	// ȣ���� �̹��� HDC ������ �������
	void ImageClear();

	// HDC�� ���� �̹����� ���� Cut
	void Cut(int _X, int _Y);

	// HDC�� ���� �̹������� ��ǥ�� ã�Ƽ� Cut
	void Cut(float4 _Start, float4 _End, int _X, int _Y);

	inline bool IsImageCutting() const
	{
		return IsCut;
	}

	// ImageCutDatas�� ����� ����
	size_t GetImageCuttingCount()
	{
		return ImageCutDatas.size();
	}

	// ImageCutData ���Ϳ� �ε������� ����� Cut �̹��� ����
	ImageCutData GetCutData(int _Index) const
	{
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("��ȿ���� ���� �� �ε��� �Դϴ�.");
		}

		return ImageCutDatas[_Index];
	}

	// ImageCutData ������ �ε��� ��ȿ�� �˻�
	bool IsCutIndexValid(int _Index) const
	{
		if (0 > _Index)
		{
			return false;
		}

		if (ImageCutDatas.size() <= _Index)
		{
			return false;
		}

		return true;
	}

	// Pixel�� Color ���� ȹ��
	DWORD GetPixelColor(float4 _Pos, DWORD _OutColor);
	DWORD GetPixelColor(int _X, int _Y, DWORD _OutColor);

	// �ܼ� HDC ����
	void BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale);

	// Cut�� �̹����� ȣ���Ͽ� TransparentBlt �ǽ�
	void TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color = RGB(255, 0, 255));

	// RGB, ũ������ HDC ����
	void TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color = RGB(255, 0, 255));

	// ������ �̹���(Trans���� ������)
	void AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha);
	
	void AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color);

	// �̹��� ȸ���� ���� �Լ�
	void PlgCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, float _Angle, GameEngineImage* _FilterImage);

	void PlgCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, float _Angle, GameEngineImage* _FilterImage);


protected:

private:
	std::vector<ImageCutData> ImageCutDatas;

	HDC ImageDC       = nullptr;  // �޸� ����̽� ���ؽ�Ʈ(DC)
	HBITMAP BitMap    = nullptr;  // �ε�� �̹����� �ڵ�
	HBITMAP OldBitMap = nullptr;  // ��ü�� GDI Object �ڵ� ��
	BITMAP Info       = BITMAP();
	bool IsCut        = false;    // Cut �� true

	void ImageScaleCheck();       // HDC ������ Info�� ����

};

