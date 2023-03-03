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

// �ֽŹ��� FrameAnimation�� ���ڵ�
class FrameAnimationParameter
{
public:
	std::string_view AnimationName = "";                   // ������ �ִϸ��̼� �̸�
	std::string_view ImageName     = "";                   // �ִϸ��̼ǿ� ����� �̹��� �̸�
	std::string_view FilterName    = "";				   // ȸ���� ���� ���� ����
	int Start                      = 0;                    // �ִϸ��̼� ���� �ε���
	int End                        = 0;                    // �ִϸ��̼� ���� �ε���
	int CurrentIndex               = 0;                    // ���� �ִϸ��̼� ������ �ε��� ��ȣ
	float InterTime                = 0.1f;                 // ������ �ϳ��� ���� �ð�
	bool Loop                      = true;                 // �ִϸ��̼� ���࿩��
	std::vector<int> FrameIndex    = std::vector<int>();   // ������ ��ȣ
	std::vector<float> FrameTime   = std::vector<float>(); // ������ �����ð�
};

class GameEngineActor;
class GameEngineLevel;

// ���� : �������� ���õ� ����� ��� ����
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

	// Render�� ����(cut�� ����� ����) ����
	inline int GetFrame() const
	{
		return Frame;
	}

	// Render�� �̹��� ����
	inline GameEngineImage* GetImage() const
	{
		return Image;
	}

	// TransColor ����
	void SetTransColor(int _Color)
	{
		TransColor = _Color;
	}

	// ī�޶� ���� (���� ����)
	inline void SetEffectCamera(bool _Effect)
	{
		IsEffectCamera = _Effect;
	}

	// ī�޶� ���� off
	inline void EffectCameraOff()
	{
		SetEffectCamera(false);
	}

	// ī�޶� ���� on
	inline void EffectCameraOn()
	{
		SetEffectCamera(true);
	}

	// �̹��� ������ �� ũ�⸦ �ڽ��� ũ��� ����
	void SetImageToScaleToImage(const std::string_view& _ImageName);

	// �̹��� ũ�⸦ �ڽ��� ũ��� ����
	void SetScaleToImage();

	// Render�� ����(Frame) ����
	void SetFrame(int _Frame);

	// GEResource.map �� ����� �̹����� ã�� �ڽ��� �̹����� ����
	void SetImage(const std::string_view& _ImageName);

	// �ش� Animation�� �������� Ȯ��(FrameAnimation->IsEnd())
	bool IsAnimationEnd();

	// �ִϸ��̼� ����
	void CreateAnimation(const FrameAnimationParameter& _Paramter);

	// �ִϸ��̼� ��ü
	void ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange = false);

	void SetOrder(int _Order) override;

	// ���ĺ���
	void SetAlpha(int _Alpha)
	{
		Alpha = _Alpha;
	}

	// ���ڷ� ���޹��� string_view&�� RenderText�� ����
	void SetText(const std::string_view& _Text, const int _TextHeight = 20, const std::string_view& _TextType = "����", const TextAlign _TextAlign = TextAlign::Center, const COLORREF _TextColor = RGB(0, 0, 0), float4 _TextBoxScale = float4::Zero);

	inline int GetTextHeight()
	{
		return TextHeight;
	}

	// ���� �̹��� ����
	void SetRotFilter(const std::string_view& _ImageName);

	inline void SetAngle(float _Angle)
	{
		Angle = _Angle;
	}

	// ȸ���� Ȯ��, ����
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
	GameEngineActor* Owner = nullptr;		   // �ڽ��� ��ü
	GameEngineImage* Image = nullptr;		   // ������ �̹���
	GameEngineImage* RotationFilter = nullptr; // ���Ϳ� �̹���
	int Frame              = 0;				   // Cut�� ������

	// ȸ���ϸ鼭 ������ >> �ȵ�
	int Alpha = 255;
	float Angle = 0.0f;

	bool IsEffectCamera = true;
	int TransColor = RGB(255, 0, 255);

	// Render�� Image�� Pos, Scale�� ����ۿ� transcopy
	void Render(float _DeltaTime);       // ���ǿ� ���� TextRender, ImageRender �� �ϳ� ����
	void ImageRender(float _DeltaTime);  // Image�� transcopy

	class FrameAnimation
	{
	public:
		GameEngineRender* Parent = nullptr; 
		GameEngineImage* Image   = nullptr;		// find �� �̹���(cut ���� Ȯ��)
		GameEngineImage* FilterImage = nullptr; 
		std::vector<int> FrameIndex;			// ������ ��ȣ
		std::vector<float> FrameTime;			// ������ �����ð�
		int CurrentIndex         = 0;			// ���� �ε����� ��ȣ
		float CurrentTime        = 0.0f;		// ���� �ε����� �ð�(������ ����)
		bool Loop                = true;		// �ִϸ��̼� ���࿩��

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

	void TextRender(float _DeltaTime);   // Text�� Ư�� ��ġ�� ���

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

