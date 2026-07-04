#include<memory>
#include<vector>
#include<unordered_map>
#include<utility>
#include"DxLib.h"
#include"status_buff_container.h"
#include"buff_data.h"
#include"buff_type.h"

StatusBuffContainer::StatusBuffContainer()
{
	// タイプ分用意する
}

StatusBuffContainer::~StatusBuffContainer()
{

}

void StatusBuffContainer::Init()
{
	// TODO: json
	// バフの全種類
	BuffType buff_types[] = { BuffType::kPhysicalATK, BuffType::kPhysicalDEF, BuffType::kMagicATK, BuffType::kMagicDEF };

	for (const auto& type : buff_types)
	{
		std::vector<std::pair<bool, BuffData>> init_buffs;
		for (int i = 0; i < kMaxBuff; i++)
		{
			// 初期バフ
			BuffData init_buff_data;
			init_buff_data.value = 0.f;
			init_buff_data.active_timer = std::make_shared<VariableTimer>();

			// pairを作る
			std::pair<bool,BuffData> active_buff_pair;
			active_buff_pair.first = FALSE;
			active_buff_pair.second = init_buff_data;

			init_buffs.push_back(active_buff_pair);
		}
		buffs_[type] = init_buffs;
	}

}


void StatusBuffContainer::Update()
{
	
}
