#include<string>
#include<vector>
#include<memory>
#include"status.h"
#include"DxLib.h"
#include"stat_modifire_group.h"
#include"active_stat_modifire.h"
#include<unordered_map>
#include"stat_modifire.h"
#include"stat_modifires.h"

ActiveStatModifireGroup::ActiveStatModifireGroup()
{
	// 先にインスタンスを生成
	active_stat_modifires_.reserve(kMaxStatModifire);
	stat_modifires_ = std::make_shared<StatModifires>();
	for (int i = 0; i < kMaxStatModifire; i++)
	{
		active_stat_modifires_.push_back(std::make_shared<ActiveStatModifire>());
	}
}

ActiveStatModifireGroup::~ActiveStatModifireGroup()
{

}

void ActiveStatModifireGroup::Init()
{
	for (auto active_stat_modifire : active_stat_modifires_)
	{
		active_stat_modifire->Init();
	}
}

void ActiveStatModifireGroup::Update(const Status& base_status, Status& current_status)
{
	for (auto active_stat_modifire : active_stat_modifires_)
	{
		if (active_stat_modifire->GetIsActive())
		{
			active_stat_modifire->Update(base_status, current_status);
		}
	}
}

void ActiveStatModifireGroup::Activation(const Status& base_status, Status& current_status,const std::string& name, std::shared_ptr<IPlayerUIGroup> player_ui_group)
{
	for (auto active_stat_modifire : active_stat_modifires_)
	{
		if (!active_stat_modifire->GetIsActive())
		{
			active_stat_modifire->Activation(base_status, current_status, stat_modifires_->GetData(name), player_ui_group);
			break;
		}
	}
}
