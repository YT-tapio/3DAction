#pragma once
#include"config_name.h"
#include"config.h"

class ConfigDatas
{
public:

	~ConfigDatas() = default;

	static ConfigDatas& GetInstance()
	{
		static ConfigDatas instance;
		return instance;
	}

	void Awake();

	const Config GetConfigData(ConfigName name) const;

private:

	ConfigDatas();

	const Config MakeConfig(const int& pc_config, const std::string& pc_name, const int& pad_config, const std::string& pad_name) const;

private:

	std::unordered_map<ConfigName, Config> datas_;

	Config empty_data_;

};