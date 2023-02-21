#include "GameEngineMath.h"
#include "GameEngineString.h"

const float GameEngineMath::PIE = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PIE2 = PIE * 2.0f;
const float GameEngineMath::DegToRad = GameEngineMath::PIE / 180;
const float GameEngineMath::RadToDeg = 180 / GameEngineMath::PIE;

//                             x      y     z     w
const float4 float4::Left  = { -1.0f, 0.0f, 0.0f, 1.0f };  // 윈도우 좌표계 기준 왼쪽   : x 증가
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 1.0f };   // 윈도우 좌표계 기준 오른쪽 : x 감소
const float4 float4::Up    = { 0.0f, -1.0f, 0.0f, 1.0f };  // 윈도우 좌표계 기준 위     : y 감소
const float4 float4::Down  = { 0.0f, 1.0f, 0.0f, 1.0f };   // 윈도우 좌표계 기준 아래   : y 증가
const float4 float4::Zero  = { 0.0f, 0.0f, 0.0f, 1.0f };   // x, y, z    == 0
const float4 float4::Null  = { 0.0f, 0.0f, 0.0f, 0.0f };   // x, y, z, w == 0

// 3D
const float4 float4::Forward = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back = { 0.0f, 0.0f, -1.0f, 1.0f };

// 뭘하는 함수냐? int를 문자열로 변환
// 123121 [1][2][3][1][2][1]
std::vector<unsigned int> GameEngineMath::GetDigits(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>(); // int 자료형 벡터 생성

	std::string StringValue = GameEngineString::ToString(_Value);        // ToString을 통해 숫자를 문자로 변환

	int StartIndex = 0;

	if (0 != StringValue.size() && StringValue[0] == '-')                // 인덱스 0이 -이고 벡터 사이즈가 0이 아니라면 인덱스는 1부터 시작하도록 설정
	{
		StartIndex = 1;
	}

	ResultValue.reserve(StringValue.size());                             // reserve는 언제나 실시한 뒤 벡터 사용 필수

	for (size_t i = StartIndex; i < StringValue.size(); i++)             // 인덱스 설정 완료, reserve 실시 후 푸쉬백
	{
		ResultValue.push_back(StringValue[i] - '0');
	}

	return ResultValue;
}

// 문자열 길이 체크
unsigned int GameEngineMath::GetLenth(int _Value)
{
	std::vector<unsigned int> ResultValue = std::vector<unsigned int>(); // 벡터 생성
	
	std::string StringValue = GameEngineString::ToString(_Value);        // ToString

	int StartIndex = 0;                                                  // 인덱스 설정

	if (0 != StringValue.size() && StringValue[0] == '-')                // 인덱스 설정
	{
		StartIndex = 1;
	}

	return static_cast<unsigned int>(StringValue.size()) - StartIndex;   // 벡터 사이즈 리턴(문자열 길이)
}