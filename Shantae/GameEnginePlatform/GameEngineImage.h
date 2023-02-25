#pragma once

#include <vector>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEnginePath;

// 설명 : Cut 함수 실행 시 저장되는 정보들을 지원하는 구조체
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

// 설명 : Image에 관련된 기능을 지원하는 클래스
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

	// 이미지 그릴 권환 리턴
	inline HDC GetImageDC() const
	{
		return ImageDC;
	}

	// 해당 이미지 x, y값 리턴
	inline float4 GetImageScale() const
	{
		return float4{ static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	// 아래 함수 실행
	bool ImageLoad(const GameEnginePath& _Path);

	// map에 저장한 이미지 HDC 적용
	bool ImageLoad(const std::string_view& _Path);

	// 백버퍼 HDC 적용
	bool ImageCreate(HDC _Hdc);

	// 빈버퍼(공백 이미지) HDC 적용
	bool ImageCreate(const float4& _Scale);

	// 호출한 이미지 HDC 정보로 덧씌우기
	void ImageClear();

	// HDC를 얻은 이미지에 대해 Cut
	void Cut(int _X, int _Y);

	// HDC를 얻은 이미지에서 좌표를 찾아서 Cut
	void Cut(float4 _Start, float4 _End, int _X, int _Y);

	inline bool IsImageCutting() const
	{
		return IsCut;
	}

	// ImageCutDatas의 사이즈값 리턴
	size_t GetImageCuttingCount()
	{
		return ImageCutDatas.size();
	}

	// ImageCutData 벡터에 인덱스별로 저장된 Cut 이미지 리턴
	ImageCutData GetCutData(int _Index) const
	{
		if (false == IsCutIndexValid(_Index))
		{
			MsgAssert("유효하지 않은 컷 인덱스 입니다.");
		}

		return ImageCutDatas[_Index];
	}

	// ImageCutData 벡터의 인덱스 유효성 검사
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

	// Pixel의 Color 정보 획득
	DWORD GetPixelColor(float4 _Pos, DWORD _OutColor);
	DWORD GetPixelColor(int _X, int _Y, DWORD _OutColor);

	// 단순 HDC 복사
	void BitCopy(const GameEngineImage* _OtherImage, float4 _CenterPos, float4 _Scale);

	// Cut한 이미지를 호출하여 TransparentBlt 실시
	void TransCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color = RGB(255, 0, 255));

	// RGB, 크기조절 HDC 복사
	void TransCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Color = RGB(255, 0, 255));

	// 반투명 이미지(Trans보다 느리다)
	void AlphaCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, int _Alpha);
	
	void AlphaCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, int _Color);

	// 이미지 회전을 위한 함수
	void PlgCopy(const GameEngineImage* _OtherImage, float4 _CopyCenterPos, float4 _CopySize, float4 _OtherImagePos, float4 _OtherImageSize, float _Angle, GameEngineImage* _FilterImage);

	void PlgCopy(const GameEngineImage* _OtherImage, int _CutIndex, float4 _CopyCenterPos, float4 _CopySize, float _Angle, GameEngineImage* _FilterImage);


protected:

private:
	std::vector<ImageCutData> ImageCutDatas;

	HDC ImageDC       = nullptr;  // 메모리 디바이스 컨텍스트(DC)
	HBITMAP BitMap    = nullptr;  // 로드된 이미지의 핸들
	HBITMAP OldBitMap = nullptr;  // 교체된 GDI Object 핸들 값
	BITMAP Info       = BITMAP();
	bool IsCut        = false;    // Cut 시 true

	void ImageScaleCheck();       // HDC 정보를 Info에 저장

};

