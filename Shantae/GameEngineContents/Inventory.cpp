#include "Inventory.h"

#include <map>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "Player.h"
#include "ItemSelect.h"
#include "Icon.h"

Inventory* Inventory::PlayerInven = nullptr;

ItemSpace::ItemSpace()
{
}

ItemSpace::~ItemSpace()
{
}

Inventory::Inventory() 
{
}

Inventory::~Inventory() 
{
	for (std::pair<int, ItemSpace*> UpdateGroup : Boxes)
	{
		ItemSpace* SpaceList = UpdateGroup.second;

		if (nullptr != SpaceList)
		{
			delete SpaceList;
			SpaceList = nullptr;
		}
	}
	Boxes.clear();
}

void Inventory::Start()
{
	PlayerInven = this;

	AnimationRender = CreateRender("Inventory.Bmp", RenderOrder::UI);
	AnimationRender->SetScale(AnimationRender->GetImage()->GetImageScale());
	AnimationRender->SetPosition(GameEngineWindow::GetScreenSize().half());
	AnimationRender->EffectCameraOff();
	AnimationRender->Off();

	ItemSpaceSetting();
}

void Inventory::Update(float _DeltaTime)
{
	if (1 == SelectCreate)
	{
		SelectCreate = 0;

		Select = GetLevel()->CreateActor<ItemSelect>();
		float4 Pos = Boxes.find(1)->second->GetBoxPos();
		BoxNumber = Boxes.find(1)->first;
		Select->SetPos(Pos);
	}

	if (false == AnimationRender->IsUpdate())
	{
		FamilyOff();
	}
	else
	{
		FamilyOn();
		SelectMove(_DeltaTime);
		SelectItem();
	}

	PlayerItemCheck();
}

void Inventory::Render(float _DeltaTime)
{

}

void Inventory::FamilyOn()
{
	Select->On();

	std::map<int, ItemSpace*>::iterator GroupStartIter = Boxes.begin();
	std::map<int, ItemSpace*>::iterator GroupEndIter = Boxes.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		Icon* IconList = GroupStartIter->second->GetItemIcon();

		if (nullptr == IconList)
		{
			continue;
		}

		IconList->On();
	}
}

void Inventory::FamilyOff()
{
	Select->Off();

	std::map<int, ItemSpace*>::iterator GroupStartIter = Boxes.begin();
	std::map<int, ItemSpace*>::iterator GroupEndIter = Boxes.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		Icon* IconList = GroupStartIter->second->GetItemIcon();

		if (nullptr == IconList)
		{
			continue;
		}

		IconList->Off();
	}
}

void Inventory::SetItemBox(int _Order, float4 _BoxPos)
{
	if (Boxes.end() != Boxes.find(_Order))
	{
		MsgAssert("이미 존재하는 칸입니다.");
		return;
	}

	ItemSpace* Box = new ItemSpace();
	Box->SetBoxPos(_BoxPos);
	Box->SetBoxNumber(_Order);
	Boxes.insert(std::make_pair(_Order, Box));
}

void Inventory::PlayerItemCheck()
{
	if (true == Player::MainPlayer->GetItemEquip())
	{
		CreateItem(EquipItem);
		Player::MainPlayer->SetItemEquip(false);
	}
}

void Inventory::CreateItem(std::string_view _Name)
{
	std::map<int, ItemSpace*>::iterator GroupStartIter = Boxes.begin();
	std::map<int, ItemSpace*>::iterator GroupEndIter = Boxes.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		ItemSpace* SpaceList = GroupStartIter->second;
		Icon* IconList = GroupStartIter->second->GetItemIcon();
		int Order = GroupStartIter->first;
		
		if (nullptr != IconList)
		{
			if (_Name == IconList->GetIconName())
			{
				if (9 > IconList->GetItemCount())
				{
					IconList->PlusItemCount();
				}
				else
				{
					IconList->SetItemCount(9);
				}
				
				break;
			}
			else 
			{
				continue;
			}
		}
		else
		{
			float4 IconPos = SpaceList->GetBoxPos();
			IconList = GetLevel()->CreateActor<Icon>();
			IconList->SetPos(IconPos);
			IconList->SetIconName(_Name);

			SpaceList->SetItemIcon(IconList);

			break;
		}
	}
}

Icon* Inventory::SelectItem()
{
	if (GameEngineInput::IsDown("Select"))
	{
		Icon* ReturnValue = Boxes.find(BoxNumber)->second->GetItemIcon();
		Icon* IconList = Boxes.find(BoxNumber)->second->GetItemIcon();

		if (nullptr != IconList)
		{
			if (1 < Boxes.find(BoxNumber)->second->GetItemIcon()->GetItemCount())
			{
				Boxes.find(BoxNumber)->second->GetItemIcon()->MinusItemCount();
			}
			else
			{
				IconList->Death();
				IconList = nullptr;
				Boxes.find(BoxNumber)->second->SetItemIcon(IconList);
			}
			return ReturnValue;
		}
	}
}

void Inventory::SelectMove(float _DeltaTime)
{
	if (GameEngineInput::IsDown("UpMove"))
	{
		BoxNumber -= 4;

		if (-3 == BoxNumber)
		{
			BoxNumber = 9;
		}

		if (-2 == BoxNumber)
		{
			BoxNumber = 10;
		}

		if (-1 == BoxNumber)
		{
			BoxNumber = 11;
		}

		if (0 == BoxNumber)
		{
			BoxNumber = 12;
		}

		float4 Pos = Boxes.find(BoxNumber)->second->GetBoxPos();
		Select->SetPos(Pos);
	}

	if (GameEngineInput::IsDown("DownMove"))
	{
		BoxNumber += 4;

		if (13 == BoxNumber)
		{
			BoxNumber = 1;
		}

		if (14 == BoxNumber)
		{
			BoxNumber = 2;
		}

		if (15 == BoxNumber)
		{
			BoxNumber = 3;
		}

		if (16 == BoxNumber)
		{
			BoxNumber = 4;
		}

		float4 Pos = Boxes.find(BoxNumber)->second->GetBoxPos();
		Select->SetPos(Pos);
	}

	if (GameEngineInput::IsDown("LeftMove"))
	{
		--BoxNumber;
		LeftMove = true;

		if (0 == BoxNumber && true == LeftMove)
		{
			LeftMove = false;
			BoxNumber = 4;
		}

		if (4 == BoxNumber && true == LeftMove)
		{
			LeftMove = false;
			BoxNumber = 8;
		}

		if (8 == BoxNumber && true == LeftMove)
		{
			LeftMove = false;
			BoxNumber = 12;
		}

		float4 Pos = Boxes.find(BoxNumber)->second->GetBoxPos();
		Select->SetPos(Pos);
	}

	if (GameEngineInput::IsDown("RightMove"))
	{
		++BoxNumber;

		if (5 == BoxNumber)
		{
			BoxNumber = 1;
		}

		if (9 == BoxNumber)
		{
			BoxNumber = 5;
		}

		if (13 == BoxNumber)
		{
			BoxNumber = 9;
		}
		
		float4 Pos = Boxes.find(BoxNumber)->second->GetBoxPos();
		Select->SetPos(Pos);
	}
}

void Inventory::ItemSpaceSetting()
{
	int x = 0;
	int y = 0;
	int i = 0;

	for (; x <= 2; x++)
	{
		if (0 == x)
		{
			YPos = 230.0f;
		}
		else if (1 == x)
		{
			YPos = 355.0f;
		}
		else if (2 == x)
		{
			YPos = 480.0f;
		}

		for (; y <= 3; y++)
		{
			if (0 == y)
			{
				XPos = 465.0f;
				i++;
			}
			else if (1 == y)
			{
				XPos = 580.0f;
				i++;
			}
			else if (2 == y)
			{
				XPos = 695.0f;
				i++;
			}
			else if (3 == y)
			{
				XPos = 810.0f;
				i++;
			}

			BoxPos = { XPos, YPos };
			SetItemBox(i, BoxPos);
		}
		y = 0;
	}
}

void Inventory::DataCopy(Inventory* _Other)
{
	std::map<int, ItemSpace*>::iterator GroupStartIter = Boxes.begin();
	std::map<int, ItemSpace*>::iterator GroupEndIter = Boxes.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		int Order = GroupStartIter->first;
		ItemSpace* SpaceList = GroupStartIter->second;
		Icon* IconList = GroupStartIter->second->GetItemIcon();
		
		if (nullptr == IconList)
		{
			continue;
		}
		else
		{
			int ItemCount = GroupStartIter->second->GetItemIcon()->GetItemCount();

			for (; ItemCount > 0; ItemCount--)
			{
				_Other->CreateItem(IconList->GetIconName());
			}
		}
	}


}