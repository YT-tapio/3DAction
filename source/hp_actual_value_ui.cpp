#include<functional>
#include"DxLib.h"
#include"hp_actual_value_ui.h"

HPActualValueUI::HPActualValueUI(std::function<int()> get_current_hp, const VECTOR& pos)
	: get_current_hp_(get_current_hp)
{

}

HPActualValueUI::~HPActualValueUI()
{

}

void HPActualValueUI::Init()
{

}

void HPActualValueUI::Draw()
{

}