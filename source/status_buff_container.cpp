/*
#include<memory>
#include<unordered_map>
#include<utility>
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
	BuffType buff_types[] = { BuffType::kPhysicalATK,BuffType::kPhysicalDEF, BuffType::kMagicATK, BuffType::kMagicDEF };

	// 初期のバフ状態
	BuffData init_buff_data;

	init_buff_data.buff = 0.f;
	init_buff_data.timer = std::make_shared<VariableTimer>(1.f);

	for (auto type : buff_types)
	{
		// バフ
		buffs_[type] = init_buff_data;

		// デバフ
		debuffs_[type] = init_buff_data;
	}


}
*/
