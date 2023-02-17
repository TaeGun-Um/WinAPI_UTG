#include "GameEngineRender.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineCore/GameEngineResources.h>
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

GameEngineRender::GameEngineRender()
{
}

GameEngineRender::~GameEngineRender()
{
}

// Render�� ����(Frame) ����
void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʴ� �������� �������� �����Ϸ��� �߽��ϴ�.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("��ȿ���� ���� �̹����ε��� �Դϴ�.");
	}

	Frame = _Frame;
}

// GEResource.map �� ����� �̹����� ã�� �ڽ��� �̹����� ����
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}

// �̹��� ������ �� ũ�⸦ �ڽ��� ũ��� ����
void GameEngineRender::SetImageToScaleToImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
	SetScaleToImage();
}

// �̹����� ũ��(������ ũ��)�� �ڽ��� ũ��� ����
void GameEngineRender::SetScaleToImage()
{
	if (nullptr == Image)
	{
		MsgAssert("�̹����� �������� �ʾҴµ� �̹����� ũ��� �����Ϸ��� �߽��ϴ�.")
	}

	SetScale(Image->GetImageScale());
}

// Order ���� �� GELevel.map�� �ڽ��� ���� ����
void GameEngineRender::SetOrder(int _Order)
{
	GameEngineObject::SetOrder(_Order);
	// Render ���� Ǫ����
	GetActor()->GetLevel()->PushRender(this);
}

// vectorsize�� ���Ͽ� ���ٸ� end
bool GameEngineRender::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
	return CurrentIndex == Value;
}

void GameEngineRender::FrameAnimation::Render(float _DeltaTime)
{
	CurrentTime -= _DeltaTime;

	if (CurrentTime <= 0.0f)
	{
		++CurrentIndex;

		if (FrameIndex.size() <= CurrentIndex)
		{
			if (true == Loop)
			{
				CurrentIndex = 0;
			}
			else 
			{
				CurrentIndex = static_cast<int>(FrameIndex.size()) - 1;
			}
		}

		CurrentTime += FrameTime[CurrentIndex];
	}
}

// ���ڷ� ���޹��� string_view&�� RenderText�� ����
void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor)
{
	RenderText = _Text;
	TextHeight = _TextHeight;
	TextType = _TextType;
	Align = _TextAlign;
	TextColor = _TextColor;
}

// ������ Render���� ������ �߰��� ���̱� ������, �� �κп��� � Render�� ������ ������ ó��
void GameEngineRender::Render(float _DeltaTime)
{
	if (RenderText != "")
	{
		TextRender(_DeltaTime);
	}
	else
	{
		ImageRender(_DeltaTime);
	}
}

// RenderText�� ����� Text�� Ư�� ��ġ�� ���
void GameEngineRender::TextRender(float _DeltaTime)
{
	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	float4 RenderPos = GetActorPlusPos() - CameraPos;

	HDC hdc = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
	HFONT hFont, OldFont;
	LOGFONTA lf;
	lf.lfHeight = TextHeight;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 0;
	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = HANGEUL_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	lstrcpy(lf.lfFaceName, TEXT(TextType.c_str()));
	hFont = CreateFontIndirect(&lf);
	OldFont = static_cast<HFONT>(SelectObject(hdc, hFont));

	SetTextAlign(hdc, static_cast<UINT>(Align));
	SetTextColor(hdc, TextColor);
	SetBkMode(hdc, TRANSPARENT);

	TextOutA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderPos.ix(), RenderPos.iy(), RenderText.c_str(), static_cast<int>(RenderText.size()));

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);

	return;
}

// Render�� Image�� Pos, Scale�� ����ۿ� transcopy
void GameEngineRender::ImageRender(float _DeltaTime)
{
	if (nullptr != CurrentAnimation)
	{
		CurrentAnimation->Render(_DeltaTime);
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		Image = CurrentAnimation->Image;
	}

	if (nullptr == Image)
	{
		MsgAssert("�̹����� ���������� �ʾҽ��ϴ�.");
	}
	
	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	// Render�� ��ġ�� OwnerActor�� ��ġ + ������ ��ġ
	float4 RenderPos = GetActorPlusPos() - CameraPos;

	if (true == Image->IsImageCutting())
	{
		if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, Frame, RenderPos, GetScale(), TransColor);
		}
		else if (255 > Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, Frame, RenderPos, GetScale(), Alpha);
		}
	}
	else
	{
		if (255 == Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), TransColor);
		}
		else if (255 > Alpha)
		{
			GameEngineWindow::GetDoubleBufferImage()->AlphaCopy(Image, RenderPos, GetScale(), { 0, 0 }, Image->GetImageScale(), Alpha);
		}
	}
}

// �ִϸ��̼� ����
void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
	// �̹��� ����
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Paramter.ImageName);

	if (nullptr == Image)
	{
		MsgAssert("�������� �ʴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
	}
	if (false == Image->IsImageCutting())
	{
		MsgAssert("�߷��ִ� �̹����� �������� �������� �� �ֽ��ϴ�.");
	}

	std::string UpperName = GameEngineString::ToUpper(_Paramter.AnimationName);

	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("�̹� �����ϴ� �̸��� �ִϸ��̼� �Դϴ�." + UpperName);
	}

	// �ִϸ��̼� �����Ҵ�(map)
	FrameAnimation& NewAnimation = Animation[UpperName];

	// �ִϸ��̼� �̹��� ����
	NewAnimation.Image = Image;

	// �ε��� ���� ��ȣ�� 0�� �ƴ�(���� ���� ����)
	if (0 != _Paramter.FrameIndex.size())
	{
		NewAnimation.FrameIndex = _Paramter.FrameIndex;
	}
	// �ε��� ���� ��ȣ�� Start-End (�⺻)
	else
	{
		for (int i = _Paramter.Start; i <= _Paramter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	// �� �����Ӻ� �ð��� ���
	// �ε��� ���� ��ȣ�� 0�� �ƴ�(���� ���� ����)
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Paramter.FrameTime;
	}
	// �ε��� ���� ��ȣ�� Start-End (�⺻)
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Paramter.InterTime);
		}
	}

	// �ִϸ��̼� Loop on(true)
	NewAnimation.Loop = _Paramter.Loop;

	// �ִϸ��̼� Parent == ȣ���� Render
	NewAnimation.Parent = this;
}

bool GameEngineRender::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}

// �ִϸ��̼� ��ü
void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ��� �߽��ϴ�." + UpperName);
	}

	// ������ �ٲ��� �ʴ� ��Ȳ���� �̹� �������� �ִϸ��̼��̶�� ����(��Ż������ ��)
	if (false == _ForceChange && CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	// �ִϸ��̼� ����
	CurrentAnimation = &Animation[UpperName];

	// �ִϸ��̼� �ε��� ����
	CurrentAnimation->CurrentIndex = 0;

	// �ִϸ��̼� �ð� ����
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}