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

// Render의 순서(Frame) 수정
void GameEngineRender::SetFrame(int _Frame)
{
	if (nullptr == Image)
	{
		MsgAssert("이미지가 존재하지 않는 랜더러에 프레임을 지정하려고 했습니다.");
	}

	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	if (false == Image->IsCutIndexValid(_Frame))
	{
		MsgAssert("유효하지 않은 이미지인덱스 입니다.");
	}

	Frame = _Frame;
}

// 필터 이미지 세팅
void GameEngineRender::SetRotFilter(const std::string_view& _ImageName)
{
	RotationFilter = GameEngineResources::GetInst().ImageFind(_ImageName);
}

// GEResource.map 에 저장된 이미지를 찾아 자신의 이미지로 설정
void GameEngineRender::SetImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
}

// 이미지 세팅한 뒤 크기를 자신의 크기로 설정
void GameEngineRender::SetImageToScaleToImage(const std::string_view& _ImageName)
{
	Image = GameEngineResources::GetInst().ImageFind(_ImageName);
	SetScaleToImage();
}

// 이미지의 크기(저장한 크기)를 자신의 크기로 설정
void GameEngineRender::SetScaleToImage()
{
	if (nullptr == Image)
	{
		MsgAssert("이미지를 세팅하지 않았는데 이미지의 크기로 변경하려고 했습니다.")
	}

	SetScale(Image->GetImageScale());
}

// Order 설정 후 GELevel.map에 자신의 정보 저장
void GameEngineRender::SetOrder(int _Order)
{
	GameEngineObject::SetOrder(_Order);
	// Render 정보 푸쉬백
	GetActor()->GetLevel()->PushRender(this);
}

// vectorsize와 비교하여 같다면 end
bool GameEngineRender::FrameAnimation::IsEnd()
{
	int Value = (static_cast<int>(FrameIndex.size()) - 1);
	return CurrentIndex == Value;
}

// 기존의 Render에서 나눠서 추가한 것이기 때문에, 이 부분에서 어떤 Render를 진행할 것인지 처리
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

// Render할 Image의 Pos, Scale를 빈버퍼에 transcopy
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
		MsgAssert("이미지를 세팅해주지 않았습니다.");
	}
	
	float4 CameraPos = float4::Zero;

	if (true == IsEffectCamera)
	{
		CameraPos = GetActor()->GetLevel()->GetCameraPos();
	}

	// Render의 위치는 OwnerActor의 위치 + 수정된 위치
	float4 RenderPos = GetActorPlusPos() - CameraPos;

	if (true == Image->IsImageCutting())
	{
		if (Angle != 0.0f)
		{
			if (nullptr == RotationFilter)
			{
				MsgAssert("회전시킬수 없는 이미지 입니다. 필터가 존재하지 않습니다.");
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
				MsgAssert("회전시킬수 없는 이미지 입니다. 필터가 존재하지 않습니다.");
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

// 애니메이션 생성
void GameEngineRender::CreateAnimation(const FrameAnimationParameter& _Paramter)
{
	// 이미지 검증
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_Paramter.ImageName);

	if (nullptr == Image)
	{
		MsgAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다.");
	}
	if (false == Image->IsImageCutting())
	{
		MsgAssert("잘려있는 이미지만 프레임을 지정해줄 수 있습니다.");
	}

	std::string UpperName = GameEngineString::ToUpper(_Paramter.AnimationName);

	if (Animation.end() != Animation.find(UpperName))
	{
		MsgAssert("이미 존재하는 이름의 애니메이션 입니다." + UpperName);
	}

	// 애니메이션 동적할당(map)
	FrameAnimation& NewAnimation = Animation[UpperName];

	// 애니메이션 이미지 지정
	NewAnimation.Image = Image;

	if (_Paramter.FilterName != "")
	{
		NewAnimation.FilterImage = GameEngineResources::GetInst().ImageFind(_Paramter.FilterName);

		if (nullptr == NewAnimation.FilterImage)
		{
			MsgAssert("존재하지 않는 이미지로 로테이션 필터를 사용할수 없습니다.");
		}
	}

	// 인덱스 시작 번호가 0이 아님(순서 임의 지정)
	if (0 != _Paramter.FrameIndex.size())
	{
		NewAnimation.FrameIndex = _Paramter.FrameIndex;
	}
	// 인덱스 시작 번호가 Start-End (기본)
	else
	{
		for (int i = _Paramter.Start; i <= _Paramter.End; ++i)
		{
			NewAnimation.FrameIndex.push_back(i);
		}
	}

	// 각 프레임별 시간을 계산
	// 인덱스 시작 번호가 0이 아님(순서 임의 지정)
	if (0 != _Paramter.FrameTime.size())
	{
		NewAnimation.FrameTime = _Paramter.FrameTime;
	}
	// 인덱스 시작 번호가 Start-End (기본)
	else
	{
		for (int i = 0; i < NewAnimation.FrameIndex.size(); ++i)
		{
			NewAnimation.FrameTime.push_back(_Paramter.InterTime);
		}
	}

	// 애니메이션 Loop on(true)
	NewAnimation.Loop = _Paramter.Loop;

	// 애니메이션 Parent == 호출한 Render
	NewAnimation.Parent = this;
}

bool GameEngineRender::IsAnimationEnd()
{
	return CurrentAnimation->IsEnd();
}

// 애니메이션 교체
void GameEngineRender::ChangeAnimation(const std::string_view& _AnimationName, bool _ForceChange)
{
	std::string UpperName = GameEngineString::ToUpper(_AnimationName);

	if (Animation.end() == Animation.find(UpperName))
	{
		MsgAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다." + UpperName);
	}

	// 강제로 바꾸지 않는 상황에서 이미 진행중인 애니메이션이라면 리턴(메탈슬러그 총)
	if (false == _ForceChange && CurrentAnimation == &Animation[UpperName])
	{
		return;
	}

	// 애니메이션 변경
	CurrentAnimation = &Animation[UpperName];

	// 애니메이션 인덱스 변경
	CurrentAnimation->CurrentIndex = 0;

	// 애니메이션 시간 변경
	CurrentAnimation->CurrentTime = CurrentAnimation->FrameTime[CurrentAnimation->CurrentIndex];
}

/////////////////////////////////// Text ///////////////////////////////////

// 인자로 전달받은 string_view&를 RenderText로 설정
void GameEngineRender::SetText(const std::string_view& _Text, const int _TextHeight, const std::string_view& _TextType, const TextAlign _TextAlign, const COLORREF _TextColor, float4 _TextBoxScale)
{
	RenderText = _Text;
	TextHeight = _TextHeight;
	TextType = _TextType;
	Align = _TextAlign;
	TextColor = _TextColor;
	TextBoxScale = _TextBoxScale;
}

// RenderText에 저장된 Text를 특정 위치에 출력
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