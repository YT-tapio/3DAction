#pragma once

class IEnemyUIGroup
{
public:

	virtual void MakeStatusUI(std::function<int()> get_base_hp, std::function<int()> get_current_hp, std::string name){}

};