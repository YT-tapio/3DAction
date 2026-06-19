#include<memory>
#include<vector>
#include<string>
#include<functional>
#include"DxLib.h"
#include"attack_range_group.h"
#include"object_base.h"
#include"object_3D.h"
#include"attack_range.h"


void AttackRangeGroup::Awake()
{
	attack_ranges_ui_.push_back(std::make_pair(FALSE,std::make_shared<AttackRange>()));
	attack_ranges_ui_.push_back(std::make_pair(FALSE, std::make_shared<AttackRange>()));
	attack_ranges_ui_.push_back(std::make_pair(FALSE, std::make_shared<AttackRange>()));
	attack_ranges_ui_.push_back(std::make_pair(FALSE, std::make_shared<AttackRange>()));
	attack_ranges_ui_.push_back(std::make_pair(FALSE, std::make_shared<AttackRange>()));
}

void AttackRangeGroup::Init()
{
	for (auto& attack_ranges_ : attack_ranges_ui_)
	{
		attack_ranges_.second->Init();
	}
}

void AttackRangeGroup::Update()
{
	int i = 0;
	// activeはupdate
	for (auto& attack_range : attack_ranges_ui_)
	{
		if (attack_range.first)
		{
			// 終了条件の確認
			if (end_functions_[i]())
			{
				// 描画をさせない
				attack_range.first = FALSE;
				continue;
			}
			attack_range.second->Update();
		}
		i++;
	}

}

void AttackRangeGroup::Draw()
{
	// activeのものは描画許可
	for (const auto& attack_range : attack_ranges_ui_)
	{
		if (attack_range.first)
		{
			attack_range.second->Draw();
		}
	}
}

void AttackRangeGroup::End()
{
	attack_ranges_ui_.clear();
}

int AttackRangeGroup::DrawRequest(const VECTOR& pos,const VECTOR& scale,std::function<bool()> end_function)
{
	int i = 0;
	for (auto& attack_range : attack_ranges_ui_)
	{
		// FALSEならTRUEにしてその番号を返す
		if (!attack_range.first)
		{
			attack_range.first = TRUE;
			attack_range.second->Init(pos, scale);
			// 終了条件をあてはめる
			end_functions_[i] = end_function;
			return i;
		}
		i++;
	}


	return -1;
}

AttackRangeGroup::AttackRangeGroup()
{

}