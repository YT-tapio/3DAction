#pragma once



class StatModifires
{
public:

	StatModifires();

	~StatModifires();

	void Awake();

	void End();

	const StatModifire GetData(const std::string& name) const;

private:
	
	void LoadFile();

private:

	const std::string kFilePath = "data/csv/stat_modifires/stat_modifires.csv";

	// データ
	std::unordered_map<std::string, StatModifire> effecacy_datas_;

	// 仮の何もないデータ
	StatModifire empty_data_;
};