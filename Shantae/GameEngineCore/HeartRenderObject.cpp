#include "HeartRenderObject.h"
#include "GameEngineResources.h"
#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineString.h>

HeartRenderObject::HeartRenderObject()
{
}

HeartRenderObject::~HeartRenderObject()
{
}

// 이미지를 find한 뒤, NumberScale, ImageName, Order에 정보 저장
void HeartRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName)
{
	// 숫자 이미지 Find
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	// 하나의 이미지에 0~9까지 숫자가 있어야 하며, 그것을 cut해서 사용하도록 함
	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("숫자 이미지는 무조건 10개로 짤려있어야 합니다.");
	}

	// 0 이하 숫자(음수)는 예외처리 실시
	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("크기가 0으로 숫자를 출력할 수 없습니다.");
	}

	// NumberScale, ImageName, Order에 정보 저장
	NumberScale = _Scale;
	ImageName = _ImageName;
	Order = _Order;
	TransColor = _TransColor;
	NegativeName = _NegativeName;
}

// 넘버즈 배치, SetValue에 인자 전달
void HeartRenderObject::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		NumberRenders[i]->SetMove(_RenderPos);
	}
}

// 넘버즈 배치, SetValue에 인자 전달
void HeartRenderObject::SetAlign(Align _Align)
{
	AlignState = _Align;
}

void HeartRenderObject::SetValue(int _Value)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();				  // 자신을 호출한 액터를 부모로 봄 + 헤더에서 Object를 상속했기 때문에 여기서 정해주는 것

	Value = _Value;

	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value); // int를 문자열로 변환한 뒤, int 자료형 벡터에 저장    

	if (nullptr == Actor)
	{
		MsgAssert("액터만이 NumberRenderObject의 부모가 될수 있습니다.");
	}

	// 자리수가 바꼈다면 여기서 푸쉬백으로 늘려줌
	//            자리수가 바뀌었고               만약 3자리 랜더하고 있었는데 5자리가 됐다면
	if (NumberRenders.size() != Numbers.size() && NumberRenders.size() < Numbers.size())
	{
		size_t CurRenderSize = NumberRenders.size();

		//                       5                   3
		for (size_t i = 0; i < (Numbers.size() - CurRenderSize); i++)
		{
			NumberRenders.push_back(Actor->CreateRender(Order));
		}
	}

	float4 RenderPos = float4::Zero;

	// 0208 추가
	Negative = _Value > 0 ? false : true;

	if (true == Negative && nullptr == NegativeRender)
	{
		NegativeRender = Actor->CreateRender(Order);
		NegativeRender->SetTransColor(TransColor);
		NegativeRender->SetPosition(Pos + RenderPos);
		NegativeRender->SetImage(NegativeName);
		NegativeRender->SetScale(NumberScale);
		RenderPos.x += NumberScale.x;
	}

	if (nullptr != NegativeRender)
	{
		NegativeRender->SetPosition(Pos + RenderPos);
		RenderPos.x += NumberScale.x;
	}

	// 랜더러에 NumberRenders size만큼 반복하면서 NumberRenders[index]를 넣어준다.
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		GameEngineRender* Render = NumberRenders[i];

		if (nullptr == Render)
		{
			MsgAssert("숫자랜더러가 nullptr 입니다");
		}

		Render->SetTransColor(TransColor);     // 제외할 색상
		Render->SetPosition(Pos + RenderPos);  // 일단 위치는 임시로 Player 상단에 해보려고 합니다(0206)
		Render->SetImage(ImageName);           // 숫자 이름 (1234~)
		Render->SetScale(NumberScale);         // 숫자 이미지 크기
		Render->SetFrame(Numbers[i]);          // 0번 0, 1번 1, 2번 2 ...

		RenderPos.x += NumberScale.x;          // 좌측정렬
	}

	// AligState에 따라 Numbers 배치 수정
	switch (AlignState)
	{
	case Align::Left:
		break;
	case Align::Right:
		SetMove(float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x);
		break;
	case Align::Center:
		SetMove((float4::Left * static_cast<const float>(GameEngineMath::GetLenth(Value) - 1) * NumberScale.x).half());
		break;
	default:
		break;
	}
}