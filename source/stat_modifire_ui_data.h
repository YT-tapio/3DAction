#pragma once
#include"modifire_operation.h"
#include"stat_type.h"

class StatModifireUIData
{
public:

	static StatModifireUIData& GetInstance()
	{
		static StatModifireUIData instance;
		return instance;
	}

	// データの読み込み
	void Load();

	// データの開放
	void End();

	// データの取得
	const int GetHandle(StatType stat_type, ModifireOperation operation) const;

private:

	StatModifireUIData();

private:

	// 画像データ
	std::unordered_map<std::string,int> handles_;

};
