#include<memory>
#include<vector>
#include<string>
#include<functional>
#include"DxLib.h"
#include"attack_range_group.h"
#include"object_base.h"
#include"object_3D.h"
#include"attack_range.h"
#include"attack_range_circle.h"
#include"attack_range_rectangle.h"

void AttackRangeGroup::Awake()
{
	for (int i = 0; i < kMaxAttackRangeNum; i++)
	{
		attack_ranges_ui_.push_back(std::make_pair(FALSE, std::make_shared<AttackRangeCircle>()));
	}
	for (int i = 0; i < kMaxAttackRangeNum; i++)
	{
		attack_range_rectangles_ui_.push_back(std::make_pair(FALSE, std::make_shared<AttackRangeRectangle>()));
	}
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
	i = 0;
	for (auto& attack_range : attack_range_rectangles_ui_)
	{
		if (attack_range.first)
		{
			// 終了条件の確認
			if (rectangle_end_functions_[i]())
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

	for (const auto& attack_range : attack_range_rectangles_ui_)
	{
		if (attack_range.first)
		{
			attack_range.second->Draw();
		}
	}
}

void AttackRangeGroup::End()
{
	end_functions_.clear();
	attack_ranges_ui_.clear();
}

int AttackRangeGroup::CircleDrawRequest(const VECTOR& pos,const VECTOR& scale, const float& time,std::function<bool()> end_function)
{
	int i = 0;
	for (auto& attack_range : attack_ranges_ui_)
	{
		// FALSEならTRUEにしてその番号を返す
		if (!attack_range.first)
		{
			attack_range.first = TRUE;
			attack_range.second->Active(pos, scale,time);
			// 終了条件をあてはめる
			end_functions_[i] = end_function;
			return i;
		}
		i++;
	}

	return -1;
}

int AttackRangeGroup::RectangleDrawRequest(const VECTOR& pos, const VECTOR& scale, const VECTOR& dir, const float& time,std::function<bool()> end_function)
{
	int i = 0;
	for (auto& attack_range : attack_range_rectangles_ui_)
	{
		// FALSEならTRUEにしてその番号を返す
		if (!attack_range.first)
		{
			attack_range.first = TRUE;
			attack_range.second->Active(pos, scale, dir,time);
			// 終了条件をあてはめる
			rectangle_end_functions_[i] = end_function;
			return i;
		}
		i++;
	}

	return -1;
}

void AttackRangeGroup::CircleSetPos(const int& id,const VECTOR& pos)
{
	if (attack_ranges_ui_.size() < id && attack_ranges_ui_.size() >= id)
	{
		auto attack_range_ui = attack_ranges_ui_[id];
		if (attack_range_ui.first)
		{
			attack_range_ui.second->SetPos(pos);
		}
	}
}

void AttackRangeGroup::RectangleSetPos(const int& id, const VECTOR& pos)
{
	if (attack_range_rectangles_ui_.size() < id && attack_range_rectangles_ui_.size() >= id)
	{
		auto attack_range_ui = attack_range_rectangles_ui_[id];
		if (attack_range_ui.first)
		{
			attack_range_ui.second->SetPos(pos);
		}
	}
}

void AttackRangeGroup::RectangleSetDir(const int& id, const VECTOR& dir)
{
	if (0 <= id && attack_range_rectangles_ui_.size() > id)
	{
		auto attack_range_ui = attack_range_rectangles_ui_[id];
		if (attack_range_ui.first)
		{
			attack_range_ui.second->SetDir(dir);
		}
	}
}

AttackRangeGroup::AttackRangeGroup()
{
	
}