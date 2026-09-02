#pragma once
#include"modifire_operation.h"
#include"stat_type.h"

class StatModifireUIData
{
public:

	StatModifireUIData();

	~StatModifireUIData();
	
	// データの読み込み
	void Load();

	// データの開放
	void End();

	// データの取得
	const int GetHandle(StatType stat_type, ModifireOperation operation) const;

private:

	

private:

	// 画像データ
	std::unordered_map<std::string,int> handles_;

};
