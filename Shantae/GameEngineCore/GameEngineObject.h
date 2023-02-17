#pragma once

#include <string>
#include <string_view>

// 설명 : Object(Actor, Render)의 상태 표현
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject(); // 상속을 위한 virtual 소멸자

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// Object Render O
	virtual void On()
	{
		ObjectUpdate = true;
	}

	// Object Render X
	virtual void Off()
	{
		ObjectUpdate = false;
	}
	
	// Object Death
	void Death()
	{
		ObjectDeath = true;
	}

	// Object Render O <-> Object Render O
	virtual void OnOffSwtich()
	{
		ObjectUpdate = !ObjectUpdate;
	}

	// 자신의 Order가 무엇?
	int GetOrder()
	{
		return Order;
	}

	// Order 결정
	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	// 자신을 소유하는 Parent 정보 획득 (캐스팅)
	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	// 자신을 소유하는 Parent 정보 획득
	GameEngineObject* GetOwner()
	{
		return Parent;
	}

	// Parent 결정
	virtual void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	// std::string Name 값 획득
	const std::string& GetName()
	{
		return LevelName;
	}
	
	// std::string Name 값 설정
	void SetName(const std::string_view& _View)
	{
		LevelName = _View;
	}

	// std::string Name 값 복사
	std::string GetNameCopy()
	{
		return LevelName;
	}

    // <TRUE>
	// true == ObjectUpdate       : 나의 Render on
	// false == IsDeath()         : 부모 Death false
	// true == Parent->IsUpdate() : 부모 Render on
	// <FALSE>
	// ObjectUpdate               : 나의 Render off
	// false == IsDeath()         : 나의 Death true
	bool IsUpdate()
	{
		return nullptr != Parent ? ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());
	}

	// <TRUE>
	// true == ObjectDeath  : 나의 Death true
	// Parent->IsDeath()    : 부모 Death true
	// <FALSE> 
	// true == ObjectDeath  : 나의 Death false
	bool IsDeath()
	{
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

protected:

private:
	GameEngineObject* Parent = nullptr; // 자기를 관리하거나 자기를 소유한 오브젝트들이 부모라는 느낌
	int Order;

	bool ObjectDeath  = false; // Object Death?
	bool ObjectUpdate = true;  // Object Render?

	std::string LevelName;

};

