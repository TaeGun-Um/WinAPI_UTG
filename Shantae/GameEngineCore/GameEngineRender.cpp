#include "GameEngineRender.h"
#include "GameEngineCore.h"
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

// ���� �̹��� ����
void GameEngineRender::SetRotFilter(const std::string_view& _ImageName)
{
	RotationFilter = GameEngineResources::GetInst().ImageFind(_ImageName);
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

// Render�� Image�� Pos, Scale�� ����ۿ� transcopy
void GameEngineRender::ImageRender(float _DeltaTime)
{
	if (nullptr != CurrentAnimation)
	{
		CurrentAnimation->Render(_DeltaTime);
		Frame = CurrentAnimation->FrameIndex[CurrentAnimation->CurrentIndex];
		Image = CurrentAnimation->Image;
		RotationFilter = CurrentAnimation->FilterImage;
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
		if (Angle != 0.0f)
		{
			if (nullptr == RotationFilter)
			{
				MsgAssert("ȸ����ų�� ���� �̹��� �Դϴ�. ���Ͱ� �������� �ʽ��ϴ�.");
			}

			GameEngineWindow::GetDoubleBufferImage()->PlgCopy(Image, Frame, RenderPos, GetScale(), Angle, RotationFilter);
		}
		else if (255 == Alpha)
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
		if (Angle != 0.0f)
		{
			if (nullptr == RotationFilter)
			{
				MsgAssert("ȸ����ų�� ���� �̹��� �Դϴ�. ���Ͱ� �������� �ʽ��ϴ�.");
			}

			GameEngineWindow::GetDoubleBufferImage()->PlgCopy(Image, Frame, RenderPos, GetScale(), Angle, RotationFilter);
		}
		else if (255 == Alpha)
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

	if (_Paramter.FilterName != "")
	{
		NewAnimation.FilterImage = GameEngineResources::GetInst().ImageFind(_Paramter.FilterName);

		if (nullptr == NewAnimation.FilterImage)
		{
			MsgAssert("�������� �ʴ� �̹����� �����̼� ���͸� ����Ҽ� �����ϴ�.");
		}
	}

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

/////////////////////////////////// Text ///////////////////////////////////

// ���ڷ� ���޹��� string_view&�� RenderText�� ����
void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor, float4 _TextBoxScale)
{
	RenderText = _Text;
	TextHeight = _TextHeight;
	TextType = _TextType;
	Align = _TextAlign;
	TextColor = _TextColor;
	TextBoxScale = _TextBoxScale;
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

	//SetTextAlign(hdc, static_cast<UINT>(Align));
	SetTextColor(hdc, TextColor);
	SetBkMode(hdc, TRANSPARENT);

	RECT Rect;
	Rect.left = RenderPos.ix();
	Rect.top = RenderPos.iy();
	Rect.right = RenderPos.ix() + TextBoxScale.ix();
	Rect.bottom = RenderPos.iy() + TextBoxScale.iy();

	if (GameEngineCore::GetInst()->IsDebug())
	{
		HDC DoubleDC = GameEngineWindow::GetDoubleBufferImage()->GetImageDC();
		HBRUSH myBrush = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(DoubleDC, myBrush));
		HPEN myPen = CreatePen(PS_DASH, 0, RGB(0, 0, 0));
		HPEN oldPen = static_cast<HPEN>(SelectObject(DoubleDC, myPen));
		Rectangle(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), Rect.left, Rect.top, Rect.right, Rect.bottom);

		SelectObject(DoubleDC, oldBrush);
		DeleteObject(myBrush);
		SelectObject(DoubleDC, oldPen);
		DeleteObject(myPen);
	}

	DrawTextA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderText.c_str(), static_cast<int>(RenderText.size()), &Rect, static_cast<UINT>(Align));

	// TextOutA(GameEngineWindow::GetDoubleBufferImage()->GetImageDC(), RenderPos.ix(), RenderPos.iy(), RenderText.c_str(), static_cast<int>(RenderText.size()));

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);

	return;
}