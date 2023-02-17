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

// �̹����� find�� ��, NumberScale, ImageName, Order�� ���� ����
void HeartRenderObject::SetImage(const std::string_view& _ImageName, float4 _Scale, int _Order, int _TransColor, const std::string_view& _NegativeName)
{
	// ���� �̹��� Find
	GameEngineImage* FindNumberImage = GameEngineResources::GetInst().ImageFind(_ImageName);

	// �ϳ��� �̹����� 0~9���� ���ڰ� �־�� �ϸ�, �װ��� cut�ؼ� ����ϵ��� ��
	if (FindNumberImage->GetImageCuttingCount() != 10)
	{
		MsgAssert("���� �̹����� ������ 10���� ©���־�� �մϴ�.");
	}

	// 0 ���� ����(����)�� ����ó�� �ǽ�
	if (0 >= _Scale.x || 0 >= _Scale.y)
	{
		MsgAssert("ũ�Ⱑ 0���� ���ڸ� ����� �� �����ϴ�.");
	}

	// NumberScale, ImageName, Order�� ���� ����
	NumberScale = _Scale;
	ImageName = _ImageName;
	Order = _Order;
	TransColor = _TransColor;
	NegativeName = _NegativeName;
}

// �ѹ��� ��ġ, SetValue�� ���� ����
void HeartRenderObject::SetMove(float4 _RenderPos)
{
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		NumberRenders[i]->SetMove(_RenderPos);
	}
}

// �ѹ��� ��ġ, SetValue�� ���� ����
void HeartRenderObject::SetAlign(Align _Align)
{
	AlignState = _Align;
}

void HeartRenderObject::SetValue(int _Value)
{
	GameEngineActor* Actor = GetOwner<GameEngineActor>();				  // �ڽ��� ȣ���� ���͸� �θ�� �� + ������� Object�� ����߱� ������ ���⼭ �����ִ� ��

	Value = _Value;

	std::vector<unsigned int> Numbers = GameEngineMath::GetDigits(Value); // int�� ���ڿ��� ��ȯ�� ��, int �ڷ��� ���Ϳ� ����    

	if (nullptr == Actor)
	{
		MsgAssert("���͸��� NumberRenderObject�� �θ� �ɼ� �ֽ��ϴ�.");
	}

	// �ڸ����� �ٲ��ٸ� ���⼭ Ǫ�������� �÷���
	//            �ڸ����� �ٲ����               ���� 3�ڸ� �����ϰ� �־��µ� 5�ڸ��� �ƴٸ�
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

	// 0208 �߰�
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

	// �������� NumberRenders size��ŭ �ݺ��ϸ鼭 NumberRenders[index]�� �־��ش�.
	for (size_t i = 0; i < NumberRenders.size(); i++)
	{
		GameEngineRender* Render = NumberRenders[i];

		if (nullptr == Render)
		{
			MsgAssert("���ڷ������� nullptr �Դϴ�");
		}

		Render->SetTransColor(TransColor);     // ������ ����
		Render->SetPosition(Pos + RenderPos);  // �ϴ� ��ġ�� �ӽ÷� Player ��ܿ� �غ����� �մϴ�(0206)
		Render->SetImage(ImageName);           // ���� �̸� (1234~)
		Render->SetScale(NumberScale);         // ���� �̹��� ũ��
		Render->SetFrame(Numbers[i]);          // 0�� 0, 1�� 1, 2�� 2 ...

		RenderPos.x += NumberScale.x;          // ��������
	}

	// AligState�� ���� Numbers ��ġ ����
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