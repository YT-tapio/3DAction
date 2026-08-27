#include<unordered_map>
#include"config_datas.h"
#include"DxLib.h"
#include"pad_config.h"
#include"key_config.h"

void ConfigDatas::Awake()
{
	empty_data_.pad.config = -1;
	empty_data_.pad.name = "";
	empty_data_.pc.config = -1;
	empty_data_.pc.name = "";
	// データの生成
	datas_[ConfigName::dash] = MakeConfig(KeyConfig::dash, "r_shift_key", PadConfig::dash, "a_button");
	datas_[ConfigName::avoid] = MakeConfig(KeyConfig::avoid, "r_shift_key", PadConfig::avoid, "a_button");
	datas_[ConfigName::normal_skill] = MakeConfig(KeyConfig::normal_skill, "left_mouse", PadConfig::normal_skill, "x_button");
	datas_[ConfigName::strong_skill] = MakeConfig(KeyConfig::strong_skill, "right_mouse", PadConfig::strong_skill, "y_button");
	datas_[ConfigName::lock_on] = MakeConfig(KeyConfig::lock_on_enemy, "space_key", PadConfig::lock_on_enemy, "left_button");
	datas_[ConfigName::play] = MakeConfig(KeyConfig::go_next, "space_key", PadConfig::go_next, "a_button");
	datas_[ConfigName::retry] = MakeConfig(KeyConfig::retry, "space_key", PadConfig::retry, "a_button");
	datas_[ConfigName::go_title] = MakeConfig(KeyConfig::game_to_title , "enter_key", PadConfig::game_to_title, "b_button");
	datas_[ConfigName::jump] = MakeConfig(KeyConfig::jump, "f_key", PadConfig::jump, "b_button");
}

const Config ConfigDatas::GetConfigData(ConfigName name) const
{
	auto data = datas_.find(name);
	if (data == datas_.end()) 
	{
		printfDx("データなし\n");
		return empty_data_;
	}
	return data->second;
}

ConfigDatas::ConfigDatas()
{

}

const Config ConfigDatas::MakeConfig(const int& pc_config, const std::string& pc_name, const int& pad_config, const std::string& pad_name) const
{
	Config config;
	
	config.pc.config = pc_config;
	config.pc.name = pc_name;
	config.pad.config = pad_config;
	config.pad.name = pad_name;

	return config;
}
