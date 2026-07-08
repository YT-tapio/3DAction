#pragma once



class StatModifires
{
public:

	static StatModifires& GetInstance()
	{
		static StatModifires instance;
		return instance;
	}

	StatModifires(const StatModifires&) = delete;
	StatModifires& operator = (const StatModifires&) = delete;

	void Awake();

	const StatModifire GetData(const std::string& name) const;

private:

	StatModifires();
	
	void LoadFile();

private:

	const std::string kFilePath = "data/csv/stat_modifires/stat_modifires.csv";

	// データ
	std::unordered_map<std::string, StatModifire> effecacy_datas_;

	// 仮の何もないデータ
	StatModifire empty_data_;
};