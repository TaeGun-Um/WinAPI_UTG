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

	TextRender = CreateRender(RenderOrder::Box);
	BoxScale = { 850, 100 };
	TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
	TextRender->SetPosition(GameEngineWindow::GetScreenSize().half() + float4::Down * 252 + float4::Left * 420);
	TextRender->EffectCameraOff();
	TextRender->Off();

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
		InventoryItemText();

		Icon* Use = SelectItem();
		if (nullptr != Use)
		{
			Player::MainPlayer->SetItemUse(Use->GetIconName().data());
		}
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

	if (GameEngineInput::IsDown("CreateItem"))
	{
		CreateItem("Octopus");
		Player::MainPlayer->PlusPlayerOctopus(1);
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
			if ("Octopus" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName()
				|| "IDCard" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
			{
				return nullptr;
			}
			else
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
	return nullptr;
}

void Inventory::OctopusDelete(int _Minus)
{
	Icon* ReturnValue = Boxes.find(BoxNumber)->second->GetItemIcon();
	Icon* IconList = Boxes.find(BoxNumber)->second->GetItemIcon();

	if (nullptr != IconList)
	{
		for (int i = 0; i < _Minus; i++)
		{
			if ("Octopus" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
			{
				if (1 < Boxes.find(BoxNumber)->second->GetItemIcon()->GetItemCount())
				{
					Boxes.find(BoxNumber)->second->GetItemIcon()->MinusItemCount();
					Player::MainPlayer->MinusPlayerOctopus(1);
				}
				else
				{
					IconList->Death();
					IconList = nullptr;
					Boxes.find(BoxNumber)->second->SetItemIcon(IconList);
					Player::MainPlayer->MinusPlayerOctopus(1);
					break;
				}
			}
		}
	}
}

void Inventory::InventoryItemText()
{
	if (nullptr != Boxes.find(BoxNumber)->second->GetItemIcon())
	{
		TextRender->On();

		if ("Octopus" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
		{
			ItemText = "문어입니다. 네 마리를 모으면 좋은 일이 생길수도?";
			TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else if ("IDCard" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
		{
			ItemText = "스커틀 마을을 통과할 수 있는 출입증입니다.";
			TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else if ("MonsterMilk" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
		{
			ItemText = "공격력을 증가시키세요! 알 수 없는 효소로 가득하답니다!";
			TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else if ("PikeBall" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
		{
			ItemText = "빙글빙글 돌아가는 고통의 강철 구로 자신을 보호하세요.";
			TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else if ("Bubble" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
		{
			ItemText = "공격에 대응하는 최상의 방어 수단입니다.";
			TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else if ("Meat" == Boxes.find(BoxNumber)->second->GetItemIcon()->GetIconName())
		{
			ItemText = "영양만점 고기입니다. 체력을 최대로 회복할 수 있습니다.";
			TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
		else
		{
			ItemText = "error";
			TextRender->SetText(ItemText, 30, "굴림", TextAlign::Left, RGB(255, 255, 255), BoxScale);
		}
	}
	else
	{
		TextRender->Off();
	}
}

void Inventory::SelectMove(float _DeltaTime)
{
	if (GameEngineInput::IsDown("UpMove"))
	{
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
		BGMPlayer.Volume(0.05f);
		BGMPlayer.LoopCount(1);

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
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
		BGMPlayer.Volume(0.05f);
		BGMPlayer.LoopCount(1);

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
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
		BGMPlayer.Volume(0.05f);
		BGMPlayer.LoopCount(1);

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
		BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Botton_move.wav");
		BGMPlayer.Volume(0.05f);
		BGMPlayer.LoopCount(1);

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

void Inventory::Elimination()
{
	for (std::pair<int, ItemSpace*> UpdateGroup : Boxes)
	{
		ItemSpace* SpaceList = UpdateGroup.second;
		Icon* IconList = UpdateGroup.second->GetItemIcon();

		if (nullptr != IconList)
		{
			IconList->SetItemCount(0);
		}
	}
}