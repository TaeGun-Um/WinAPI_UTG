#pragma once

#include <map>

#include <GameEnginePlatform/GameEngineImage.h>
#include "GameEngineComponent.h"

enum class TextAlign
{
	Left = DT_LEFT,
	Right = DT_RIGHT,
	Center = DT_CENTER
};

// 최신문법 FrameAnimation의 인자들
class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";                   // 저장한 애니메이션 이름
	std::string_view ImageName     = "";                   // 애니메이션에 사용한 이미지 이름
	std::string_view FilterName    = "";				   // 회전을 위한 필터 지정
	int Start                      = 0;                    // 애니메이션 시작 인덱스
	int End                        = 0;                    // 애니메이션 종료 인덱스
	int CurrentIndex               = 0;                    // 현재 애니메이션 나오는 인덱스 번호
	float InterTime                = 0.1f;                 // 프레임 하나당 지연 시간
	bool Loop                      = true;                 // 애니메이션 실행여부
	std::vector<int> FrameIndex    = std::vector<int>();   // 프레임 번호
	std::vector<float> FrameTime   = std::vector<float>(); // 프레임 지연시간
};

class GameEngineActor;
class GameEngineLevel;

// 설명 : 랜더링에 관련된 기능을 모두 집약
class GameEngineRender : public GameEngineComponent
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRender();
	~GameEngineRender();

	// delete Function
	GameEngineRender(const GameEngineRender& _Other) = delete;
	GameEngineRender(GameEngineRender&& _Other) noexcept = delete;
	GameEngineRender& operator=(const GameEngineRender& _Other) = delete;
	GameEngineRender& operator=(GameEngineRender&& _Other) noexcept = delete;

	// Render의 순서(cut시 저장된 순서) 리턴
	inline int GetFrame() const
	{
		return Frame;
	}

	// Render의 이미지 리턴
	inline GameEngineImage* GetImage() const
	{
		return Image;
	}

	// TransColor 변경
	void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	// 카메라 무브 (직접 설정)
	inline void SetEffectCamera(bool _Effect)
	{
		IsEffectCamera = _Effect;
	}

	// 카메라 무브 off
	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}

	// 카메라 무브 on
	inline void EffectCameraOn()
	{
		SetEffectCamera(true);
	}

	// 이미지 세팅한 뒤 크기를 자신의 크기로 설정
	void SetImageToScaleToImage(const std::string_view& _ImageName);

	// 이미지 크기를 자신의 크기로 설정
	void SetScaleToImage();

	// Render의 순서(Frame) 수정
	void SetFrame(int _Frame);

	// GEResource.map 에 저장된 이미지를 찾아 자신의 이미지로 설정
	void SetImage(const std::string_view& _ImageName);

	// 해당 Animation이 끝났는지 확인(FrameAnimation->IsEnd())
	bool IsAnimationEnd();

	// 애니메이션 생성
	void CreateAnimation(const FrameAnimationParameter& _Paramter);

	// 애니메이션 교체
	void ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange = false);

	void SetOrder(int _Order) override;

	// 알파블랜더
	void SetAlpha(int _Alpha)
	{
		Alpha = _Alpha;
	}

	// 인자로 전달받은 string_view&를 RenderText로 설정
	void SetText(const std::string_view& _Text, const int _TextHeight = 20, const std::string_view& _TextType = "굴림", const TextAlign _TextAlign = TextAlign::Center, const COLORREF _TextColor = RGB(0, 0, 0), float4 _TextBoxScale = float4::Zero);

	inline int GetTextHeight()
	{
		return TextHeight;
	}

	// 필터 이미지 세팅
	void SetRotFilter(const std::string_view& _ImageName);

	inline void SetAngle(float _Angle)
	{
		Angle = _Angle;
	}

	// 회전값 확인, 세팅
	inline float GetAngle(float _Angle)
	{
		return Angle;
	}

	inline void SetAngleAdd(float _Angle)
	{
		Angle += _Angle;
	}

protected:

private:
	GameEngineActor* Owner = nullptr;		   // 자신의 주체
	GameEngineImage* Image = nullptr;		   // 랜더할 이미지
	GameEngineImage* RotationFilter = nullptr; // 필터용 이미지
	int Frame              = 0;				   // Cut시 프레임

	// 회전하면서 반투명 >> 안됨
	int Alpha = 255;
	float Angle = 0.0f;

	bool IsEffectCamera = true;
	int TransColor = RGB(255, 0, 255);

	// Render할 Image의 Pos, Scale를 빈버퍼에 transcopy
	void Render(float _DeltaTime);       // 조건에 따라 TextRender, ImageRender 중 하나 선택
	void ImageRender(float _DeltaTime);  // Image를 transcopy

	class FrameAnimation
	{
	public:
		GameEngineRender* Parent = nullptr; 
		GameEngineImage* Image   = nullptr;		// find 한 이미지(cut 상태 확인)
		GameEngineImage* FilterImage = nullptr; 
		std::vector<int> FrameIndex;			// 프레임 번호
		std::vector<float> FrameTime;			// 프레임 지연시간
		int CurrentIndex         = 0;			// 현재 인덱스의 번호
		float CurrentTime        = 0.0f;		// 현재 인덱스의 시간(프레임 유지)
		bool Loop                = true;		// 애니메이션 실행여부

		bool IsEnd();

		void Render(float _DeltaTime);

		void Reset()
		{
			CurrentIndex = 0;
			CurrentTime = 0.0f;
		}
	};

	std::map<std::string, FrameAnimation> Animation;
	FrameAnimation* CurrentAnimation = nullptr;

	void TextRender(float _DeltaTime);   // Text를 특정 위치에 출력

	/// <summary>
	/// TextRender
	/// </summary>
	std::string RenderText = std::string();
	int TextHeight = 0;
	std::string TextType = std::string();
	TextAlign Align = TextAlign::Left;
	COLORREF TextColor = RGB(0, 0, 0);
	float4 TextBoxScale;

};

