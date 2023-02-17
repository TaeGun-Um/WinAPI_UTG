#pragma once

#include <string>
#include <string_view>

// ���� : Object(Actor, Render)�� ���� ǥ��
class GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject(); // ����� ���� virtual �Ҹ���

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

	// �ڽ��� Order�� ����?
	int GetOrder()
	{
		return Order;
	}

	// Order ����
	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	// �ڽ��� �����ϴ� Parent ���� ȹ�� (ĳ����)
	template<typename ConvertType>
	ConvertType* GetOwner()
	{
		return dynamic_cast<ConvertType*>(Parent);
	}

	// �ڽ��� �����ϴ� Parent ���� ȹ��
	GameEngineObject* GetOwner()
	{
		return Parent;
	}

	// Parent ����
	virtual void SetOwner(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}

	// std::string Name �� ȹ��
	const std::string& GetName()
	{
		return LevelName;
	}
	
	// std::string Name �� ����
	void SetName(const std::string_view& _View)
	{
		LevelName = _View;
	}

	// std::string Name �� ����
	std::string GetNameCopy()
	{
		return LevelName;
	}

    // <TRUE>
	// true == ObjectUpdate       : ���� Render on
	// false == IsDeath()         : �θ� Death false
	// true == Parent->IsUpdate() : �θ� Render on
	// <FALSE>
	// ObjectUpdate               : ���� Render off
	// false == IsDeath()         : ���� Death true
	bool IsUpdate()
	{
		return nullptr != Parent ? ((true == ObjectUpdate && false == IsDeath()) && true == Parent->IsUpdate()) : (ObjectUpdate && false == IsDeath());
	}

	// <TRUE>
	// true == ObjectDeath  : ���� Death true
	// Parent->IsDeath()    : �θ� Death true
	// <FALSE> 
	// true == ObjectDeath  : ���� Death false
	bool IsDeath()
	{
		return nullptr != Parent ? (true == ObjectDeath || Parent->IsDeath()) : (true == ObjectDeath);
	}

protected:

private:
	GameEngineObject* Parent = nullptr; // �ڱ⸦ �����ϰų� �ڱ⸦ ������ ������Ʈ���� �θ��� ����
	int Order;

	bool ObjectDeath  = false; // Object Death?
	bool ObjectUpdate = true;  // Object Render?

	std::string LevelName;

};

