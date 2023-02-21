#include "GameEngineMath.h"
#include "GameEngineString.h"

const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;
const float GameEngineMath::DegToRad = GameEngineMath::PIE / 180;
const float GameEngineMath::RadToDeg = 180 / GameEngineMath::PIE;

//                             x      y     z     w
const float4 float4::Left  = { -1.0f, 0.0f, 0.0f, 1.0f };  // ������ ��ǥ�� ���� ����   : x ����
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 1.0f };   // ������ ��ǥ�� ���� ������ : x ����
const float4 float4::Up    = { 0.0f, -1.0f, 0.0f, 1.0f };  // ������ ��ǥ�� ���� ��     : y ����
const float4 float4::Down  = { 0.0f, 1.0f, 0.0f, 1.0f };   // ������ ��ǥ�� ���� �Ʒ�   : y ����
const float4 float4::Zero  = { 0.0f, 0.0f, 0.0f, 1.0f };   // x, y, z    == 0
const float4 float4::Null  = { 0.0f, 0.0f, 0.0f, 0.0f };   // x, y, z, w == 0

// 3D
const float4 float4::Forward = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back = { 0.0f, 0.0f, -1.0f, 1.0f };

// ���ϴ� �Լ���? int�� ���ڿ��� ��ȯ
// 123121 [1][2][3][1][2][1]
std::vector<unsigned int> GameEngineMath::GetDigits(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>(); // int �ڷ��� ���� ����

	std::string StringValue = GameEngineString::ToString(_Value);        // ToString�� ���� ���ڸ� ���ڷ� ��ȯ

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')                // �ε��� 0�� -�̰� ���� ����� 0�� �ƴ϶�� �ε����� 1���� �����ϵ��� ����
	{
		StartIndex = 1;
	}

	ResultValue.reserve(StringValue.size());                             // reserve�� ������ �ǽ��� �� ���� ��� �ʼ�

	for (size_t i = StartIndex; i < StringValue.size(); i++)             // �ε��� ���� �Ϸ�, reserve �ǽ� �� Ǫ����
	{
		ResultValue.push_back(StringValue[i] - '0');
	}

	return ResultValue;
}

// ���ڿ� ���� üũ
unsigned int GameEngineMath::GetLenth(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>(); // ���� ����
	
	std::string StringValue = GameEngineString::ToString(_Value);        // ToString

	int StartIndex = 0;                                                  // �ε��� ����

	if (0 != StringValue.size() && StringValue[0] == '-')                // �ε��� ����
	{
		StartIndex = 1;
	}

	return static_cast<unsigned int>(StringValue.size()) - StartIndex;   // ���� ������ ����(���ڿ� ����)
}