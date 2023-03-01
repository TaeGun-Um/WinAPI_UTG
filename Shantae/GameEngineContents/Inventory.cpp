#include "Inventory.h"

#include <map>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentsEnum.h"
#include "ItemSelect.h"

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

	// 0~3 : 230
	// 4~7 : 255
	// 8~11 : 480

	int x = 0;
	int y = 0;
	int i = 0;

	for (;x <= 2; x++)
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
		Select->Off();
	}
	else
	{
		Select->On();
		SelectMove(_DeltaTime);
	}
}

void Inventory::Render(float _DeltaTime)
{

}

// 1 : { 465, 230 }
// 2 : { 580, 230 }
// 3 : { 695, 230 }
// 4 : { 810, 230 }
// 
// 5 : { 465, 355 }
// 6 : { 580, 355 }
// 7 : { 695, 355 }
// 8 : { 810, 355 }
// 
// 9 : { 465, 480 }
// 10 : { 580, 480 }
// 11 : { 695, 480 }
// 12 : { 810, 480 }

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