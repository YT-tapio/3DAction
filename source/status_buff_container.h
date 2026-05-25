#pragma once
/*
struct BuffData;

/// <summary>
/// バフ,デバフの管理を行う
/// </summary>
class StatusBuffContainer
{
public:

	StatusBuffContainer();

	~StatusBuffContainer();

	void Init();


private:

	// バフ群
	std::unordered_map<BuffType,BuffData> buffs_;

	// デバフ群
	std::unordered_map<BuffType, BuffData> debuffs_;
};

/*
バフを重複できるように実装してほしい
*/

